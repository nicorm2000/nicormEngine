#include "Game.h"

Game::Game()
{
	player = nullptr;
	floor = nullptr;
	staticModel = nullptr;
	model = nullptr;
	planes = nullptr;
	directionalLight = nullptr;
}

Game::~Game()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	if (floor != nullptr)
	{
		delete floor;
		floor = nullptr;
	}

	if (staticModel != nullptr)
	{
		delete staticModel;
		staticModel = nullptr;
	}

	if (model != nullptr)
	{
		delete model;
		model = nullptr;
	}

	if (planes != nullptr)
	{
		delete planes;
		planes = nullptr;
	}

	if (directionalLight != nullptr)
	{
		directionalLight = nullptr;
		delete directionalLight;
	}
}

void Game::Begin()
{
	renderer->SetDepth();

	//----------------------------PLAYER---------------------------------
	player = new Player(renderer);
	player->Init(camera, 5.f, 75.f);
	player->SetPosition(glm::vec3(-2.5f, 5.f, 25.f));

	camera->SetTarget(player);
	camera->SetOffset(10.f);

	//----------------------------OBJECTS---------------------------------
	floor = new Sprite(renderer);
	floor->Init(SPRITE_TYPE::QUAD);
	floor->LoadTexture("res/grass.jpg", false, TEXTURE_TYPE::BASE);
	floor->material = MaterialManager::GetTextureMaterial();
	floor->color.SetColorRGB(255, 255, 255);
	floor->SetPosition(glm::vec3(0.f, -.5f, 0.f));
	floor->SetRotationX(90.f);
	floor->SetScale(50.f, 50.f, 1.f);

	staticModel = new Entity3D(renderer);
	staticModel = ModelImporter::LoadModel(renderer, "res/Models/guitarBackpack/backpack.obj");
	staticModel->SetPosition(glm::vec3(0.f, 2.f, 15.f));

	model = new Entity3D(renderer);
	model = ModelImporter::LoadModel(renderer, "res/Models/guitarBackpack/backpack.obj");
	model->SetPosition(glm::vec3(0.f, 2.f, 0.f));

	planes = new Entity3D(renderer);
	planes = ModelImporter::LoadModel(renderer, "res/Models/Planes/Planes.obj");
	planes->SetPosition(glm::vec3(0.f, 5.f, 0.f));

	//------------------------------BSP---------------------------------	
	BSP::FindPlanes(planes);
	BSP::AddEntity(staticModel);
	BSP::AddEntity(model);

	//----------------------------LIGHTS---------------------------------
	directionalLight = new DirectionalLight(renderer);
	directionalLight->color.SetColorRGB(255, 255, 255);
	directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	directionalLight->SetAmbient(glm::vec3(1.f, 1.f, 1.f));
	directionalLight->SetDiffuse(glm::vec3(0.6f, 0.6f, 0.6f));
	directionalLight->SetSpecular(glm::vec3(0.25f, 0.25f, 0.25f));
}

void Game::Update()
{
	player->Update();
	camera->Update();

	directionalLight->UseLight();

	staticModel->Update();
	model->Update();
	planes->Update();

	Inputs();
}

void Game::Draw()
{
	floor->Draw();
	staticModel->Draw();
	model->Draw();
	planes->Draw();
	player->Draw();
}

void Game::End()
{
	player->DeInit();
	floor->DeInit();
	staticModel->DeInit();
	model->DeInit();
	planes->DeInit();
}

void Game::Inputs()
{
	//----------------------------LIGHTS---------------------------------
	if (Input::IsKeyDown(KEY_1))
	{
		directionalLight->SetEnabled(!directionalLight->IsEnabled());
	}
	if (Input::IsKeyDown(KEY_2))
	{
		directionalLight->color = Color::GetRandomColor();
	}

	//----------------------------TRANSFORMS---------------------------------
	if (Input::IsKeyPressed(KEY_3))
	{
		glm::vec3 guitarScale = model->GetScale();
		guitarScale -= glm::vec3(1) * Timer::GetDeltaTime();
		model->SetScale(guitarScale);
	}
	if (Input::IsKeyPressed(KEY_4))
	{
		glm::vec3 guitarScale = model->GetScale();
		guitarScale += glm::vec3(1) * Timer::GetDeltaTime();
		model->SetScale(guitarScale);
	}
	if (Input::IsKeyPressed(KEY_5))
	{
		float guitarRotX = model->GetRotationX();
		guitarRotX -= 15.f * Timer::GetDeltaTime();
		model->SetRotationX(guitarRotX);
	}
	if (Input::IsKeyPressed(KEY_6))
	{
		float guitarRotX = model->GetRotationX();
		guitarRotX += 15.f * Timer::GetDeltaTime();
		model->SetRotationX(guitarRotX);
	}
	if (Input::IsKeyPressed(KEY_7))
	{
		float guitarRotX = model->GetPositionX();
		guitarRotX -= 10.f * Timer::GetDeltaTime();
		model->SetPositionX(guitarRotX);
	}
	if (Input::IsKeyPressed(KEY_8))
	{
		float guitarRotX = model->GetPositionX();
		guitarRotX += 10.f * Timer::GetDeltaTime();
		model->SetPositionX(guitarRotX);
	}
	if (Input::IsKeyPressed(KEY_9))
	{
		float guitarRotX = model->GetPositionZ();
		guitarRotX -= 10.f * Timer::GetDeltaTime();
		model->SetPositionZ(guitarRotX);
	}
	if (Input::IsKeyPressed(KEY_0))
	{
		float guitarRotX = model->GetPositionZ();
		guitarRotX += 10.f * Timer::GetDeltaTime();
		model->SetPositionZ(guitarRotX);
	}

	//------------------------------------------------------------------
	if (Input::IsKeyDown(KEY_Z))
	{
		model->Reset();
	}

	if (Input::IsKeyDown(KEY_X))
	{
		BSP::TogglePlaneStatus(); // draw
	}
	if (Input::IsKeyDown(KEY_C))
	{
		BSP::ToggleStatus(); // enable
	}
}