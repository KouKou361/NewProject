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
	virtual void Create(string Texturename,int MaxNum,VECTOR2 TextureChipSize,VECTOR2 TextureNum, Bland_state blendstate= Bland_state::BS_ALPHA);
	//���s����
	virtual void Play(VECTOR3 Pos,int Num) = 0;
	//�X�V����
	virtual void Update() = 0;

	void Delete();

	void SetPos(VECTOR3 pos) { Pos = pos; };
	void NotRender();
protected:
	//�G�t�F�N�g�ԍ�
	int EffectIndex;
	//�G�t�F�N�g�Ŏg�p���Ă���e�N�X�`���̖��O
	string Texturename;
	//�G�t�F�N�g���q�̍ő吔
	int MaxNum;

	VECTOR2 TextureChipSize;
	VECTOR2 TextureNum;
	Bland_state blendstate;

	VECTOR3 Pos;


};