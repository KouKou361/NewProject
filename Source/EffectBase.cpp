#include "EffectBase.h"
void EffectBase::Create(string Texturename, int MaxNum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state blendstate)
{

	//エフェクトで使用しているテクスチャの名前
	this->Texturename= Texturename;
	//エフェクト粒子の最大数
	this->MaxNum=MaxNum;

	this->TextureChipSize= TextureChipSize;
	this->TextureNum= TextureNum;
	this->blendstate= blendstate;

	//エフェクト番号
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