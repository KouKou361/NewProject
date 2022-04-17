#include "EffectDerived.h"

//����������
void EffectAttack::Init()
{
	pos = VECTOR3{ 11,0,-2 };
	//	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
}
//�X�V����
void EffectAttack::Play(VECTOR3 Pos, int Num)
{

	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);
			if (spriteEffect->type >= 0)continue;
			if (!spriteEffect->IsCameraRender())continue;
			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 v = { 0,0,0 };
			DirectX::XMFLOAT3 f = { 0,0,0 };
			DirectX::XMFLOAT2 s = { .006f,.006f };

			p.x = Pos.x + (rand() % 10001 - 5000) * 0.00031f;
			p.y = Pos.y + (rand() % 10001 - 5000) * 0.00031f+2.0f;
			p.z = Pos.z + (rand() % 10001 - 5000) * 0.00031f;

			v.x = (rand() % 10001 - 5000) * 0.0002f;
			v.y = (rand() % 10001 - 5000) * 0.0002f;
			v.z = (rand() % 10001 - 5000) * 0.0002f;

			f.x = (rand() % 10001 - 5000) * 0.0002f;
			f.y = (rand() % 10001 - 5000) * 0.0002f;
			f.z = (rand() % 10001 - 5000) * 0.0002f;

			spriteEffect->Set(2, 0.3f, p, v, f, s);
			
			break;
		}


	}
}
//�X�V����
void EffectAttack::Update()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);
		if (spriteEffect->type < 0) continue;

		spriteEffect->vx += spriteEffect->ax * time;
		spriteEffect->vy += spriteEffect->ay * time;
		spriteEffect->vz += spriteEffect->az * time;
		spriteEffect->x += spriteEffect->vx * time;
		spriteEffect->y += spriteEffect->vy * time;
		spriteEffect->z += spriteEffect->vz * time;
		spriteEffect->timer -= time;
		spriteEffect->alpha = spriteEffect->timer / 0.2f;
		spriteEffect->h += 0.005f;
		spriteEffect->w += 0.005f;

		if (spriteEffect->timer <= 0) {
			spriteEffect->type = -1;
		}
	}
}