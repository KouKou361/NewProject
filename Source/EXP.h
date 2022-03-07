#pragma once

#include <string>
#include "Lib.h"
//�G�t�F�N�g�̊��N���X
class EXPManager;
class SceneGame;

class EXP
{
public:
	EXP() {};
	~EXP() {};

	void SetManager(SceneGame* sceneGame) { scene = sceneGame; };
	//����������
	void Init(VECTOR3 Pos);
	//�X�V����
	void Update();
	//�X�V����
	void Render();

	void Delete();

	VECTOR2 WorldToScreen(VECTOR3 Pos);
protected:
	//�G�t�F�N�g�ԍ�
	int SpriteIndex;

	VECTOR2 Pos;
	VECTOR2 Velocity = { 0,0 };
	VECTOR2 Size = { 50,50 };

	VECTOR2 TargetPos = { 20,20 };

	VECTOR4 Cut;
	float Angle;
	float speed = 0.0f;

	SceneGame* scene;

	float timer;



};