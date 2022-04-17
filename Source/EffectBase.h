#pragma once
#include <string>
#include "Lib.h"
//�G�t�F�N�g�̊��N���X
class EffectBase
{
public:
	EffectBase() {};
	~EffectBase() {};

	//����������
	virtual void Init()=0;
	//�쐬����
	virtual void Create(string textureName,int maxNum,VECTOR2 textureChipSize,VECTOR2 textureNum, Bland_state blendstate= Bland_state::BS_ALPHA);
	//���s����
	virtual void Play(VECTOR3 Pos,int Num) = 0;
	//�X�V����
	virtual void Update() = 0;

	void Delete();

	void SetPos(VECTOR3 pos) { pos = pos; };
	void NotRender();
protected:
	//�G�t�F�N�g�ԍ�
	int effectIndex;
	//�G�t�F�N�g�Ŏg�p���Ă���e�N�X�`���̖��O
	string textureName;
	//�G�t�F�N�g���q�̍ő吔
	int maxNum;

	VECTOR2 textureChipSize;
	VECTOR2 textureNum;
	Bland_state blendState;

	VECTOR3 pos;


};