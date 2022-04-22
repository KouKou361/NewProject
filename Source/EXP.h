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
	void Init(const VECTOR3 pos);
	//�X�V����
	void Update();
	//�X�V����
	void Render();

	void Delete();
	//���[���h����X�N���[�����W�ɕϊ�
	VECTOR2 WorldToScreen(const VECTOR3 pos);
protected:
	//�G�t�F�N�g�ԍ�
	int spriteIndex;

	float angle;
	float speed = 0.0f;
	float timer;



	VECTOR2 pos;
	VECTOR2 velocity = { 0,0 };
	VECTOR2 size = { 50,50 };

	VECTOR2 targetPos = { 20,20 };

	VECTOR4 cut;

	SceneGame* scene;



};