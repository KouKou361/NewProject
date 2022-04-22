#include "EffectDerived.h"

//初期化処理
void EffectStageClear::Init()
{
	pos = VECTOR3{ 11,0,-2 };
	//	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
	//
	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
}
//更新処理
void EffectStageClear::Play(VECTOR3 Pos, int Num)
{
	if (!TK_Lib::Camera::IsCamera(Pos))
	{
		return;
	}
	Pos.y += 3.0f;
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);

			if (spriteEffect->type >= 0)continue;
		//	if (spriteEffect->IsCameraRender())continue;
			DirectX::XMFLOAT3 p;                            //速度
			DirectX::XMFLOAT3 v = { 0,0,0 };				//加速度
			DirectX::XMFLOAT3 f = { 0,0,0 };				//大きさ
			DirectX::XMFLOAT2 s = { 2.4f,2.4f };
			VECTOR4 color = { 0.2f,0.2f, 0.2f, 0.3f };    	
															
			p.x = Pos.x + (rand() % 10001 - 5000) * 0.0005f;//位置の算出  
			p.y = Pos.y + (rand() % 10001 - 5000) * 0.0005f;//位置の算出
			p.z = Pos.z + (rand() % 10001 - 5000) * 0.0005f;//位置の算出
															
			v.x = (rand() % 10001 - 5000) * 0.003f;			//速度の算出
			v.y = (rand() % 10001) * 0.001f;				//速度の算出
			v.z = (rand() % 10001 - 5000) * 0.003f;			//速度の算出
															
			float scale = (rand() % 300) * 0.01f;			
			s = { scale,scale };

			spriteEffect->Set(13, 4, p, v, f, s, color);
			break;
		}


	}
}
//更新処理
void EffectStageClear::Update()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < spriteEffects->size(); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);
		if (spriteEffect->type < 0) continue;
		spriteEffect->alpha = spriteEffect->timer / 0.2f;
		if (!spriteEffect->IsCameraRender())continue;

		spriteEffect->vx += spriteEffect->ax * time;
		spriteEffect->vy += spriteEffect->ay * time;
		spriteEffect->vz += spriteEffect->az * time;
		spriteEffect->x += spriteEffect->vx * time;
		spriteEffect->y += spriteEffect->vy * time;
		spriteEffect->z += spriteEffect->vz * time;
		spriteEffect->timer -= time;
		spriteEffect->alpha = spriteEffect->timer / 0.1f;
		spriteEffect->color.w=spriteEffect->alpha ;
		spriteEffect->h -= 0.0005f;
		spriteEffect->w -= 0.0005f;

		//非表示にする
		if (spriteEffect->alpha <= 0) {
			spriteEffect->type = -1;
		}
	}
}