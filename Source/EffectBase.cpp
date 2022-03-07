#include "EffectBase.h"
void EffectBase::Create(string Texturename, int MaxNum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state blendstate)
{

	//�G�t�F�N�g�Ŏg�p���Ă���e�N�X�`���̖��O
	this->Texturename= Texturename;
	//�G�t�F�N�g���q�̍ő吔
	this->MaxNum=MaxNum;

	this->TextureChipSize= TextureChipSize;
	this->TextureNum= TextureNum;
	this->blendstate= blendstate;

	//�G�t�F�N�g�ԍ�
	EffectIndex=TK_Lib::Lib_Effect::Load(Texturename, MaxNum, TextureChipSize, TextureNum, blendstate);
}

void EffectBase::NotRender()
{
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(EffectIndex);
	for (int j = 0; j < spriteEffects->size(); j++)
	{
		EffectData* spriteEffect = &spriteEffects->at(j);
		if (spriteEffect->type >= 0)
		{
			spriteEffect->type = -1;
		}
	}


	
}
void EffectBase::Delete()
{
	TK_Lib::Lib_Effect::Erase(EffectIndex);
}