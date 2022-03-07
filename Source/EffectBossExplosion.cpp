#include "EffectDerived.h"
//初期化処理
void EffectBossExplosion::Init()
{
	Pos = VECTOR3{ 11,0,-2 };
	//	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
	testSlider.x = 30.9f;
	testSlider.y = 30.3f;

	testSlider2.x = 0.1f;
	testSlider2.y = -10.0f;
}
//更新処理
void EffectBossExplosion::Play(VECTOR3 Pos, int Num)
{
	Pos.y += 5.0f;
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(EffectIndex);
	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);
			if (spriteEffect->type >= 0)continue;

			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 v = { 0,0,0 };
			DirectX::XMFLOAT3 f = { testSlider2.x,testSlider2.y,testSlider2.x };
			DirectX::XMFLOAT2 s = { 12.0f,12.0f };

			p.x = Pos.x + (rand() % 10001 - 5000) * 0.00005f;
			p.y = Pos.y + (rand() % 10001) * 0.0001f;
			p.z = Pos.z + (rand() % 10001 - 5000) * 0.00005f;

			v.x = (rand() % 10001 - 5000) * 0.0001f * testSlider.x;
			v.y = (rand() % 10001) * 0.0001f * testSlider.y;
			v.z = (rand() % 10001 - 5000) * 0.0001f * testSlider.x;
			spriteEffect->renderflg = true;
			spriteEffect->Set(13, 4, p, v, f, s);
			break;
		}


	}
}
//更新処理
void EffectBossExplosion::Update()
{

	ImGui::Begin("test2");
	ImGui::SliderFloat("XZ", &testSlider.x, 1.0f, 100.0f);
	ImGui::SliderFloat("Y", &testSlider.y, 1.0f, 100.0f);

	ImGui::SliderFloat("F_XZ", &testSlider2.x, -10.0f, 10.0f);
	ImGui::SliderFloat("F_Y", &testSlider2.y, -10.0f, 10.0f);
	ImGui::End();
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(EffectIndex);

	for (int i = 0; i < spriteEffects->size(); i++) {
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
		spriteEffect->color.w = spriteEffect->alpha;
		spriteEffect->h -= 0.005f;
		spriteEffect->w -= 0.005f;

		if (spriteEffect->h <= 0) {
			spriteEffect->type = -1;
		}
	}
}