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
	void Init(const VECTOR3 &pos);
	//�X�V����
	void Update();
	//�X�V����
	void Render();

	void Delete();

private:
	//�ڕW�n�_�̎Z�o
	void SetTargetPos();
	//�ʒu�̎Z�o
	void SetPos(const VECTOR3& pos);
	//���[���h����X�N���[�����W�ɕϊ�
	VECTOR2 WorldToScreen(const VECTOR3& pos);
	//�ڕW�n�_�ɐi��
	void ModeToTarget();
	//����K�x���Ԃ��߂���������鏈��
	void DeleteToTimer();
	//����K�x�ڕW�ɏ������ꍇ�����鏈��
	void DeleteMinLength(const float& DeleteLength);

protected:
	//�G�t�F�N�g�ԍ�
	int spriteIndex=-1;

	float angle=0;
	float speed = 0.0f;
	float timer=0;

	VECTOR2 pos = {0,0};
	VECTOR2 velocity = { 0,0 };
	VECTOR2 size = { 50,50 };

	VECTOR2 targetPos = { 20,20 };

	VECTOR4 cut = {0,0,0,0};

	SceneGame* scene=nullptr;



};