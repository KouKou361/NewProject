#include "EffectBase.h"
void EffectBase::Create(string Texturename, int MaxNum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state blendstate)
{

	//�G�t�F�N�g�Ŏg�p���Ă���e�N�X�`���̖��O
	this->textureName= Texturename;
	//�G�t�F�N�g���q�̍ő吔
	this->maxNum=MaxNum;

	this->textureChipSize= TextureChipSize;
	this->textureNum= TextureNum;
	this->blendState= blendstate;

	//�G�t�F�N�g�ԍ�
	effectIndex=TK_Lib::Lib_Effect::Load(Texturename, MaxNum, TextureChipSize, TextureNum, blendstate);
}

void EffectBase::NotRender()
{
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
	for (int j = 0; j < spriteEffects->size(); j++)
	{
		EffectData* spriteEffect = &spriteEffects->at(j);
		//��\���ɂ���
		if (spriteEffect->type >= 0)
		{
			spriteEffect->type = -1;
		}
	}


	
}
void EffectBase::Delete()
{
	TK_Lib::Lib_Effect::Erase(effectIndex);
}