#include "EffectBase.h"
void EffectBase::Create(string Texturename, int MaxNum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state blendstate)
{

	//エフェクトで使用しているテクスチャの名前
	this->textureName= Texturename;
	//エフェクト粒子の最大数
	this->maxNum=MaxNum;

	this->textureChipSize= TextureChipSize;
	this->textureNum= TextureNum;
	this->blendState= blendstate;

	//エフェクト番号
	effectIndex=TK_Lib::Lib_Effect::Load(Texturename, MaxNum, TextureChipSize, TextureNum, blendstate);
}

void EffectBase::NotRender()
{
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
	for (int j = 0; j < spriteEffects->size(); j++)
	{
		EffectData* spriteEffect = &spriteEffects->at(j);
		//非表示にする
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