#include "EffectDerived.h"

//初期化処理
void EffectThrow::Init()
{

}
//更新処理
void EffectThrow::Play(VECTOR3 Pos, int Num)
{
	vector<EffectData> * spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
	

	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);
			if (spriteEffect->type >= 0)continue;
			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 v = { 0,0,0 };
			DirectX::XMFLOAT3 f = { 0,-2.0f,0 };
			DirectX::XMFLOAT2 s = { .4f,.4f };

			p.x = Pos.x + (rand() % 10001 - 5000) * 0.0005f;
			p.y = Pos.y + (rand() % 10001) * 0.0001f + 0.4f;
			p.z = Pos.z + (rand() % 10001 - 5000) * 0.0005f;

			v.x = (rand() % 10001 - 5000) * 0.0002f;
			v.y = (rand() % 10001) * 0.0004f + 0.005f;
			v.z = (rand() % 10001 - 5000) * 0.0002f;

			spriteEffect->Set(13, 100.0f, p, v, f, s);
			break;
		}


	}

}
//更新処理
void EffectThrow::Update()
{

	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);
		if (spriteEffect->type < 0) continue;
		spriteEffect->color.w -= 0.01f;
		if (!spriteEffect->IsCameraRender())continue;


		spriteEffect->vx += spriteEffect->ax * 0.003;
		spriteEffect->vy += spriteEffect->ay * 0.01;
		spriteEffect->vz += spriteEffect->az * 0.003;
		spriteEffect->x += spriteEffect->vx * 0.003;
		spriteEffect->y += spriteEffect->vy * 0.01;
		spriteEffect->z += spriteEffect->vz * 0.003;
		spriteEffect->h += 0.02f;
		spriteEffect->w += 0.02f;
	//	spriteEffect->timer -= 1;
		spriteEffect->color.w -= 0.01f;
	//	spriteEffect->alpha = spriteEffect->timer / 0.2f;

		if (spriteEffect->color.w <= 0) {
			spriteEffect->type = -1;
		}
	}

	
}