#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"
//#include "Model/Model.h"

	const int quantity= 20;
	//using namespace MikkaiEngine;
class Game : BaseGame {
	//Sprite* _sprites[quantity];
	//Shape* _pj;
	//Sprite* _pjS;
	//Sprite* _Wall1;
	MikkaiEngine::Entity2* _a;
	MikkaiEngine::Entity2* _b;
	MikkaiEngine::Entity2* _t;
	list <MikkaiEngine::Entity2*> tankesitos;
	list <MikkaiEngine::Entity2*> planos;
	//MikkaiEngine::Entity3D* _entity3d;
	MikkaiEngine::Entity3D* _entity3dScene;
	MikkaiEngine::Model* _modeloTanke;
	MikkaiEngine::Model* _modeltest2;
	MikkaiEngine::Camera2* _cam;
	MikkaiEngine::plane* _planeXample;
	//Sprite* _floor;
	MikkaiEngine::DirectionLight* _dirLight;
	MikkaiEngine::PointLight* _pointLight[4];
	MikkaiEngine::SpotLight* _spotLight;
	MikkaiEngine::Shape* _lightcubes[4];

public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;
	void UpdateImgui() override;

	void LightsUpdate();

	void processInput();
};
#endif