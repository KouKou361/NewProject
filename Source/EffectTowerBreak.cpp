#include "EffectDerived.h"

//初期化処理
void EffectTowerBreak::Init()
{
	pos = VECTOR3{ 11,0,-2 };
	//	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
}

//更新処理
void EffectTowerBreak::Play(VECTOR3 Pos, int Num)
{
	if (!TK_Lib::Camera::IsCamera(Pos))
	{
		return;
	}

	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);
			if (spriteEffect->type >= 0)continue;
			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 v = { 0,0,0 };
			DirectX::XMFLOAT3 f = { 0,0,0 };
			DirectX::XMFLOAT2 s = { 1.3f,1.3f };

			p.x = Pos.x + (rand() % 10001 - 5000) * 0.00051f;
			p.y = Pos.y + (rand() % 300) * 0.1f + 2.0f;
			p.z = Pos.z + (rand() % 10001 - 5000) * 0.00051f;

			v.x = (rand() % 10001 - 5000) * 0.0002f;
			v.y = (rand() % 10001 - 5000) * 0.0002f;
			v.z = (rand() % 10001 - 5000) * 0.0002f;

			f.x = (rand() % 10001 - 5000) * 0.0002f;
			f.y = (rand() % 10001 - 5000) * 0.0005f;
			f.z = (rand() % 10001 - 5000) * 0.0002f;

			spriteEffect->Set(2, 2.0f, p, v, f, s);
			break;
		}


	}
}
//更新処理
void EffectTowerBreak::Update()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);
		if (spriteEffect->type < 0) continue;
		spriteEffect->alpha = spriteEffect->timer / 0.1f;
		if (spriteEffect->alpha <= 0) {
			spriteEffect->type = -1;
		}
		if (!spriteEffect->IsCameraRender())continue;

		spriteEffect->vx += spriteEffect->ax * time;
		spriteEffect->vy += spriteEffect->ay * time;
		spriteEffect->vz += spriteEffect->az * time;
		spriteEffect->x += spriteEffect->vx * time;
		spriteEffect->y += spriteEffect->vy * time;
		spriteEffect->z += spriteEffect->vz * time;
		spriteEffect->timer -= time;
		spriteEffect->alpha = spriteEffect->timer / 0.1f;
		spriteEffect->h += 0.02f;
		spriteEffect->w += 0.02f;
		spriteEffect->color = { 0.4f,0.4f,0.4f,spriteEffect->alpha };

		if (spriteEffect->alpha <= 0) {
			spriteEffect->type = -1;
		}
	}
}