#include "EffectDerived.h"


//将来の俺へ
//============================================
//エフェクトの派生クラスは全てコメントアウトしました。
//これ全部基底クラスで完結できる事に気がついて派生クラスの関数を全て消滅させました！
//また、csvからデータ取得しているのでこのcppすら要らない。
//でも成し遂げた形跡を残したいのでコメントアウトでとどめている。
//もし必要なら参考にして。
//=============================================


////初期化処理
//void EffectBossSiteBreak::Init()
//{
//	pos = VECTOR3{ 11,0,-2 };
//	//	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
//}
////更新処理
//void EffectBossSiteBreak::Play(VECTOR3 Pos, int Num)
//{
//
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	for (int i = 0; i < Num; i++) {
//		for (int j = 0; j < spriteEffects->size(); j++)
//		{
//			EffectData* spriteEffect = &spriteEffects->at(j);
//			if (spriteEffect->type >= 0)continue;
//	
//			DirectX::XMFLOAT3 p;                               //速度
//			DirectX::XMFLOAT3 v = { 0,0,0 };				   //加速度
//			DirectX::XMFLOAT3 f = { 0,-2.0f,0 };			   //大きさ
//			DirectX::XMFLOAT2 s = { 1.2f,1.2f };
//			
//			p.x = Pos.x + (rand() % 10001 - 5000) * 0.0005f;   //位置の算出
//			p.y = Pos.y + (rand() % 10001 - 5000) * 0.0005f;   //位置の算出
//			p.z = Pos.z + (rand() % 10001 - 5000) * 0.0005f;   //位置の算出
//			
//			v.x = (rand() % 10001 - 5000) * 0.0006f;		   //速度の算出
//			v.y = (rand() % 10001 - 5000) * 0.0006f;		   //速度の算出
//			v.z = (rand() % 10001 - 5000) * 0.0006f;           //速度の算出
//			spriteEffect->Set(14, 4, p, v, f, s);
//			break;
//		}
//
//
//	}
//}
//更新処理
//void EffectBossSiteBreak::Update()
//{
//	float time = TK_Lib::Window::GetElapsedTime();
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//
//	for (int i = 0; i < spriteEffects->size(); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//
//		spriteEffect->alpha -= time;
//		if (!spriteEffect->IsCameraRender())continue;
//
//		spriteEffect->vx += spriteEffect->ax * time;
//		spriteEffect->vy += spriteEffect->ay * time;
//		spriteEffect->vz += spriteEffect->az * time;
//		spriteEffect->x += spriteEffect->vx * time;
//		spriteEffect->y += spriteEffect->vy * time;
//		spriteEffect->z += spriteEffect->vz * time;
//		spriteEffect->timer -= time;
//		//spriteEffect->alpha -= time;
//		spriteEffect->h += 0.005f;
//		spriteEffect->w += 0.005f;
//
//		//非表示にする
//		if (spriteEffect->alpha <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//}