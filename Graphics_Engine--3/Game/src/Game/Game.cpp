#include "Game.h"

float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 2.5f;
float speed = 2;
glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
float scale1 = 0;
bool auxCheck = false;

float lastX = 0;
float lastY = 0;
bool firstMouse = true;
using namespace MikkaiEngine;

int Down, Left, Right, Up;

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
		glm::vec3(5.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -8.0f),
		glm::vec3(-6.0f,  0.0f, -0.0f)
};
Game::Game() {
	MainLoop(960, 540, "Mikkai Engine");
	if (_a != nullptr)
		_a = nullptr;
	if (_b != nullptr)
		_b = nullptr;
	if (_t != nullptr)
		_t = nullptr;
	if (_dirLight != nullptr)
		_dirLight = nullptr;
	for (int i = 0; i < 4; i++)
		if (_pointLight[i] != nullptr)
			_pointLight[i] = nullptr;
	for (int i = 0; i < 4; i++)
		if (_lightcubes[i] != nullptr)
			_lightcubes[i] = nullptr;
	if (_Wall1 != nullptr)
		_Wall1 = nullptr;
	_spotLight = nullptr;
	_modeloTanke = nullptr;
	_modeloTanke1 = nullptr;
	_modeloTanke2 = nullptr;
	_modeloTanke3 = nullptr;
}
Game::~Game() {}

void Game::Init() {
	_renderer->SetDepth();
	_cam = _mainCamera2;
	color::RGBA colorFondoRGBA(glm::vec4(0, 0, 0, 0));
	SetBackGroundColor(colorFondoRGBA);
	_entity3dScene = new MikkaiEngine::Entity3D(_renderer, "res/i/scene.fbx");
	MikkaiEngine::Entity2* wantedNode = _entity3dScene->model->GetBaseNode()->GetNode("Tanke");
	MikkaiEngine::Entity2* wantedNode1 = _entity3dScene->model->GetBaseNode()->GetNode("Tanke1");
	MikkaiEngine::Entity2* wantedNode2 = _entity3dScene->model->GetBaseNode()->GetNode("Tanke2");
	MikkaiEngine::Entity2* wantedNode3 = _entity3dScene->model->GetBaseNode()->GetNode("Tanke3");

	sceneObjects.push_back(wantedNode);
	sceneObjects.push_back(wantedNode1);
	sceneObjects.push_back(wantedNode2);
	sceneObjects.push_back(wantedNode3);

	if (wantedNode != nullptr)
	{
		_modeloTanke = new MikkaiEngine::Model(GetRenderer());
		_modeloTanke->SetBaseNode(wantedNode);
		_modeloTanke->GetBaseNode()->Init();
		_modeloTanke->GetBaseNode()->SetPos(0, 0, 0);
		Entity2::personalList.push_back(wantedNode);
	}
	if (wantedNode1 != nullptr)
	{
		_modeloTanke1 = new MikkaiEngine::Model(GetRenderer());
		_modeloTanke1->SetBaseNode(wantedNode1);
		_modeloTanke1->GetBaseNode()->Init();
		_modeloTanke1->GetBaseNode()->SetPos(-15, 0, 0);
	}
	if (wantedNode2 != nullptr)
	{
		_modeloTanke2 = new MikkaiEngine::Model(GetRenderer());
		_modeloTanke2->SetBaseNode(wantedNode2);
		_modeloTanke2->GetBaseNode()->Init();
		_modeloTanke2->GetBaseNode()->SetPos(15, 0, 0);
	}
	if (wantedNode3 != nullptr)
	{
		_modeloTanke3 = new MikkaiEngine::Model(GetRenderer());
		_modeloTanke3->SetBaseNode(wantedNode3);
		_modeloTanke3->GetBaseNode()->Init();
		_modeloTanke3->GetBaseNode()->SetPos(0, 0, -15);
	}

	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);

	_Wall1 = new MikkaiEngine::Entity2(_renderer);
	_Wall1->setName("Wall");
	_Wall1->SetPos(10, 0, 0);
	_Wall1->SetRotations(0, 90, 0);
	_Wall1->SetScale(10, 10);

	_dirLight = new MikkaiEngine::DirectionLight(_renderer);
	_dirLight->Init();
	_dirLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	_dirLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	_dirLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	_dirLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

	MikkaiEngine::frustrumCulling::Init(_cam);
	_renderer->UseShader();

	for (int i = 0; i < 4; i++)
	{
		_pointLight[i] = new MikkaiEngine::PointLight(_renderer);
		_pointLight[i]->Init();
		_pointLight[i]->SetPos(pointLightPositions[i]);
		_pointLight[i]->SetAmbient(vec3(0.05f, 0.05f, 0.05f));
		_pointLight[i]->SetDiffuse(vec3(0.8f, 0.8f, 0.8f));
		_pointLight[i]->SetSpecular(vec3(1.0f, 1.0f, 1.0f));
		_pointLight[i]->SetConstant(1.0f);
		_pointLight[i]->SetLinear(0.09f);
		_pointLight[i]->SetQuadratic(0.032f);

		_lightcubes[i] = new Shape(_renderer);
		_lightcubes[i]->Init(SHAPE_TYPE::QUAD);
		_lightcubes[i]->SetColor(vec3(75.f / 255.f, 139.f / 255.f, 59.f / 255.f));
		string name = "_lightcubes[";
		name += i;
		name += "]";
		_lightcubes[i]->setName(name);
	}

	_spotLight = new MikkaiEngine::SpotLight(_renderer);
	_spotLight->Init();
	_spotLight->SetCamera(_cam);
	_spotLight->SetAmbient(vec3(0.0f, 0.0f, 0.0f));
	_spotLight->SetDiffuse(vec3(1.0f, 1.0f, 1.0f));
	_spotLight->SetSpecular(vec3(1.0f, 1.0f, 1.0f));
	_spotLight->SetConstant(1.0f);
	_spotLight->SetLinear(0.09f);
	_spotLight->SetQuadratic(0.032f);
	_spotLight->SetCutOff(glm::cos(glm::radians(12.5f)));
	_spotLight->SetOuterCutOff(glm::cos(glm::radians(15.0f)));

	_cam->SetCameraType(MikkaiEngine::CAMERA_TYPE::FC);
	_cam->SetPos(vec3(0.0f, 0.0f, 10.0f));

	_cam->ToogleEjes();

	_bsp = new MikkaiEngine::BSP(_renderer, _cam);

	_bsp->AddEntity(wantedNode);
	_bsp->AddEntity(wantedNode1);
	_bsp->AddEntity(wantedNode2);
	_bsp->AddEntity(wantedNode3);

	for (std::list<Entity2*>::iterator it = MikkaiEngine::Importer2::planos.begin(); it != MikkaiEngine::Importer2::planos.end(); it++)
	{
		_bsp->AddPlane(*it);
	}

	_a = _cam;
	_t = _entity3dScene->model->GetBaseNode()->GetNode("Tanke");

	_renderer->SetBackgroundColor(vec4((float)(140.f / 255.f), (float)(224.f / 255.f), (float)(216.f / 255.f), 0.5f));
}

void Game::Deinit()
{
	std::cout << "-Game";
}
void Game::Update()
{
	for (int i = 0; i < 4; i++)
	{
		_lightcubes[i]->SetPos(_pointLight[i]->getPos());
	}
	_cam->Update();
	LightsUpdate();
	processInput();
	MikkaiEngine::frustrumCulling::Update();
}

void Game::Draw() {
	_bsp->Draw();
	for (std::list<Entity2*>::iterator it = MikkaiEngine::Importer2::planos.begin(); it != MikkaiEngine::Importer2::planos.end(); it++)
	{
		(*it)->setDraw();
	}
}

void Game::UpdateImgui() {}

void Game::LightsUpdate()
{
	_dirLight->UpdateLight();
	for (int i = 0; i < 4; i++)
	{
		_pointLight[i]->UpdateLight();
	}
	_spotLight->UpdateLight();
	_cam->Update();
}

void Game::processInput()
{
	vec3 z(0);
	if (Input::IsKeyPressed(Input::KEY_W))
		z += _cam->GetFront();
	if (Input::IsKeyPressed(Input::KEY_S))
		z -= _cam->GetFront();
	if (Input::IsKeyPressed(Input::KEY_A))
		z -= _cam->GetRight();
	if (Input::IsKeyPressed(Input::KEY_D))
		z += _cam->GetRight();
	if (Input::IsKeyPressed(Input::KEY_Q))
		z += _cam->GetUp();
	if (Input::IsKeyPressed(Input::KEY_E))
		z -= _cam->GetUp();
	_cam->Move(z * _time->_deltaTime * speed);

	glm::vec3 t(0);
	if (Input::IsKeyPressed(Input::KEY_UP))
	{
		t += glm::vec3(0, 0, -1);
	}
	if (Input::IsKeyPressed(Input::KEY_DOWN))
	{
		t += glm::vec3(0, 0, 1);
	}
	if (Input::IsKeyPressed(Input::KEY_RIGHT))
	{
		t += glm::vec3(1, 0, 0);
	}
	if (Input::IsKeyPressed(Input::KEY_LEFT))
	{
		t += glm::vec3(-1, 0, 0);
	}
	_t->Move(t * _time->_deltaTime * speed);

	if (Input::IsKeyDown(Input::KEY_X))
		_cam->DebugInfo();
	if (Input::IsKeyDown(Input::KEY_C))
		Input::toggle_lock_cursor();
	if (Input::IsKeyDown(Input::KEY_B))
		_cam->UpdateCameraType();
	if ((int)_cam->GetCameraType() == 2)//TPS
	{
		Input::UpdateCameraOrientation(_cam, _t->getPos(), 0, 0);
	}
	if (Input::IsKeyDown(Input::KEY_SPACE))
		_cam->ToogleEjes();

	if (Input::IsKeyDown(Input::KEY_F1))
	{
		for (std::list<MikkaiEngine::Entity2*>::iterator it2 = MikkaiEngine::Entity2::EntitysLists.begin(); it2 != MikkaiEngine::Entity2::EntitysLists.end(); ++it2)
			if (*it2 == _a && it2 != MikkaiEngine::Entity2::EntitysLists.begin())
			{
				it2--;
				_a = *it2;
			}
	}

	if (Input::IsKeyDown(Input::KEY_F2))
	{
		for (std::list<MikkaiEngine::Entity2*>::iterator it2 = MikkaiEngine::Entity2::EntitysLists.begin(); it2 != MikkaiEngine::Entity2::EntitysLists.end(); ++it2)
			if (*it2 == _a && it2 != MikkaiEngine::Entity2::EntitysLists.end())
			{
				it2++;
				_a = *it2;
			}
	}

	glm::vec3 b(0);
	if (_b != nullptr)
	{
		if (Input::IsKeyDown(Input::KEY_0))
			b += _b->GetRight();
		if (Input::IsKeyDown(Input::KEY_1))
			b -= _b->GetRight();
		_b->Move(b * _time->_deltaTime * speed);
		if (Input::IsKeyDown(Input::KEY_2))
			_b->DebugInfo();
	}
}