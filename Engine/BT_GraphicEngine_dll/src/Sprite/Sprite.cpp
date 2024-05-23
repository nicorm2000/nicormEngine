#include "Sprite.h"

Sprite::Sprite() : Entity2D()
{
	spriteType = SPRITE_TYPE::QUAD;
	baseTexture = nullptr;
	uniformBaseTexture = 0;
	animationIndex = 0;
	animation = vector<Animation*>();
	frame = Frame();
	transparent = false;
}

Sprite::Sprite(Renderer* renderer) : Entity2D(renderer)
{
	spriteType = SPRITE_TYPE::QUAD;
	baseTexture = nullptr;
	uniformBaseTexture = 0;
	animationIndex = 0;
	animation = vector<Animation*>();
	frame = Frame();
	transparent = false;
}

Sprite::~Sprite()
{
}

void Sprite::Init(SPRITE_TYPE spriteType)
{
	this->spriteType = spriteType;

	useTexture = true;
	SetUniforms();

	switch (spriteType)
	{
	case SPRITE_TYPE::QUAD:
		for (int i = 0; i < quadVertexTam; i++)
		{
			Vertex vertex;
			vertex.Position = quadPositions[i];
			vertex.Normal = quadNormals[i];
			vertex.TexCoords = quadTextureCoords[i];
			vertexs.push_back(vertex);
		}
		for (int i = 0; i < quadIndexTam; i++)
		{
			indexes.push_back(quadIndexes[i]);
		}
		break;

	case SPRITE_TYPE::CUBE:
		for (int i = 0; i < cubeVertexTam; i++)
		{
			Vertex vertex;
			vertex.Position = cubePositions[i];
			vertex.Normal = cubeNormals[i];
			vertex.TexCoords = cubeTextureCoords[i];
			vertexs.push_back(vertex);
		}
		for (int i = 0; i < cubeIndexTam; i++)
		{
			indexes.push_back(cubeIndexes[i]);
		}
		break;

	default:
		break;
	}

	renderer->GenBuffers(VAO, VBO, EBO, UVB);
	renderer->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
	renderer->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);

	renderer->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
	renderer->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	//SetTextureCoordinates(currFrame);
	renderer->SetBaseAttribs(locationTexCoord, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	GenerateVolumeAABB();
}

void Sprite::Update()
{
	if (animation.size() == 0) return;

	if (animation[animationIndex]->Update())
	{
		Frame f = animation[animationIndex]->GetFrames()[animation[animationIndex]->GetCurrentFrame()];
		SetTextureCoordinates(f);
	}
}

void Sprite::Draw()
{
	if (IsCanDraw())
	{
		renderer->UseShader();
		renderer->BlendEnable();

		UpdateShader();
		renderer->UseTexture(0, baseTexture->ID);
		Entity2D::Draw();

		renderer->CleanTexture();
		renderer->TextureDisable();
		renderer->BlendDisable();
		renderer->CleanShader();
		Entity::DrawVolume();
	}

	Entity::Draw();
}

void Sprite::DeInit()
{
	renderer->UnBind(VAO, VBO, EBO, UVB);
	renderer->TextureDelete(uniformBaseTexture, baseTexture->ID);

	if (baseTexture != nullptr)
	{
		delete baseTexture;
		baseTexture = nullptr;
	}

	for (int i = 0; i < animation.size(); i++)
	{
		delete animation[i];
	}

	Entity2D::DeInit();
}

void Sprite::SetTexture(Texture* texture, TEXTURE_TYPE textureType)
{
	switch (textureType)
	{
	case TEXTURE_TYPE::BASE:
		texture = texture;
		break;
	
	case TEXTURE_TYPE::DIFFUSE:
		if (material != nullptr) ((TextureMaterial*)material)->SetDiffuse(texture->ID);
		break;
	
	case TEXTURE_TYPE::SPECULAR:
		if (material != nullptr) ((TextureMaterial*)material)->SetSpecular(texture->ID);
		break;
	
	default:
		texture = nullptr;
		break;
	}
}

void Sprite::LoadTexture(const char* path, bool invertImage, TEXTURE_TYPE textureType)
{
	baseTexture = new Texture(TextureImporter::LoadTexture(path, invertImage));
	SetTexture(baseTexture, textureType);
	animationIndex = 0;
}

void Sprite::AddAnimation(AtlasConfig atlas, float speed)
{
	Animation* a = new Animation();
	a->SetAnimation(baseTexture, speed);
	a->AddFrames(atlas);
	animation.push_back(a);

	Frame f = animation[animationIndex]->GetFrames()[0];
	SetTextureCoordinates(f);
}

void Sprite::AddAnimation(int rows, int cols, float speed)
{
	Animation* a = new Animation();
	a->SetAnimation(baseTexture, speed);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			a->AddFrame(i, j, baseTexture->width / cols, baseTexture->height / rows, rows * cols);
		}
	}
	animation.push_back(a);

	Frame f = animation[animationIndex]->GetFrames()[0];
	SetTextureCoordinates(f);
}

void Sprite::ChangeAnimation(int index)
{
	animationIndex = index;
}

void Sprite::SetTextureCoordinates(Frame f)
{
	float quadCoords[8] =
	{
		f.GetUVCords()[0].U, f.GetUVCords()[0].V,
		f.GetUVCords()[1].U, f.GetUVCords()[1].V,
		f.GetUVCords()[2].U, f.GetUVCords()[2].V,
		f.GetUVCords()[3].U, f.GetUVCords()[3].V
	};

	switch (spriteType)
	{
	case SPRITE_TYPE::QUAD:
		renderer->BindUV(UVB, sizeof(quadCoords), quadCoords);

		break;
	case SPRITE_TYPE::CUBE:
		float cubeCoords[72] =
		{
			quadCoords[0], quadCoords[1],
			quadCoords[2], quadCoords[3],
			quadCoords[4], quadCoords[5],
			quadCoords[4], quadCoords[5],
			quadCoords[6], quadCoords[7],
			quadCoords[0], quadCoords[1],

			quadCoords[0], quadCoords[1],
			quadCoords[2], quadCoords[3],
			quadCoords[4], quadCoords[5],
			quadCoords[4], quadCoords[5],
			quadCoords[6], quadCoords[7],
			quadCoords[0], quadCoords[1],

			quadCoords[0], quadCoords[1],
			quadCoords[2], quadCoords[3],
			quadCoords[4], quadCoords[5],
			quadCoords[4], quadCoords[5],
			quadCoords[6], quadCoords[7],
			quadCoords[0], quadCoords[1],

			quadCoords[0], quadCoords[1],
			quadCoords[2], quadCoords[3],
			quadCoords[4], quadCoords[5],
			quadCoords[4], quadCoords[5],
			quadCoords[6], quadCoords[7],
			quadCoords[0], quadCoords[1],

			quadCoords[0], quadCoords[1],
			quadCoords[2], quadCoords[3],
			quadCoords[4], quadCoords[5],
			quadCoords[4], quadCoords[5],
			quadCoords[6], quadCoords[7],
			quadCoords[0], quadCoords[1],

			quadCoords[0], quadCoords[1],
			quadCoords[2], quadCoords[3],
			quadCoords[4], quadCoords[5],
			quadCoords[4], quadCoords[5],
			quadCoords[6], quadCoords[7],
			quadCoords[0], quadCoords[1]
		};

		renderer->BindUV(UVB, sizeof(cubeCoords), cubeCoords);
		break;
	}
}

void Sprite::SetTransparent(bool tranparent)
{
	this->transparent = tranparent;
}

bool Sprite::GetTransparent()
{
	return transparent;
}

void Sprite::SetUniforms()
{
	Entity2D::SetUniforms();
	renderer->SetUniform(uniformBaseTexture, "baseTexture");
}

void Sprite::UpdateShader()
{
	Entity2D::UpdateShader();
	renderer->UpdateTexture(uniformBaseTexture, baseTexture->ID);
}