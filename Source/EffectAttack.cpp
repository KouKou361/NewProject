#include "EffectDerived.h"

//将来の俺へ
//============================================
//エフェクトの派生クラスは全てコメントアウトしました。
//これ全部基底クラスで完結できる事に気がついて派生クラスの関数を全て消滅させました！
//また、csvからデータ取得しているのでこのcppすら要らない。
//でも成し遂げた形跡を残したいのでコメントアウトでとどめている。
//もし必要なら参考にして。
//=============================================



//初期化処理
//void EffectAttack::Init()
//{
//	//pos = VECTOR3{ 11,0,-2 };
//	//PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
//}
////更新処理
//void EffectAttack::Play(VECTOR3 Pos, int Num)
//{
//
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	for (int i = 0; i < Num; i++) {
//		for (int j = 0; j < spriteEffects->size(); j++)
//		{
//			EffectData* spriteEffect = &spriteEffects->at(j);
//			if (spriteEffect->type >= 0)continue;
//			if (!spriteEffect->IsCameraRender())continue;
//			DirectX::XMFLOAT3 p;
//			DirectX::XMFLOAT3 v = { 0,0,0 };	                  //速度
//			DirectX::XMFLOAT3 f = { 0,0,0 };	                  //加速度
//			DirectX::XMFLOAT2 s = { .006f,.006f };                //大きさ
//		
//			p.x = Pos.x + (rand() % 10001 - 5000) * 0.00031f;     //位置の算出
//			p.y = Pos.y + (rand() % 10001 - 5000) * 0.00031f+2.0f;//位置の算出
//			p.z = Pos.z + (rand() % 10001 - 5000) * 0.00031f;	  //位置の算出
//
//			v.x = (rand() % 10001 - 5000) * 0.0002f;              //速度の算出
//			v.y = (rand() % 10001 - 5000) * 0.0002f;              //速度の算出
//			v.z = (rand() % 10001 - 5000) * 0.0002f;              //速度の算出
//													              
//			f.x = (rand() % 10001 - 5000) * 0.0002f;              //加速度の算出
//			f.y = (rand() % 10001 - 5000) * 0.0002f;              //加速度の算出
//			f.z = (rand() % 10001 - 5000) * 0.0002f;              //加速度の算出
//
//			//設定
//			spriteEffect->Set(2, 0.3f, p, v, f, s);
//			
//			break;
//		}
//
//
//	}
//}
//更新処理
//void EffectAttack::Update()
//{
//	float time = TK_Lib::Window::GetElapsedTime();
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//
//	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//
//		spriteEffect->vx += spriteEffect->ax * time;
//		spriteEffect->vy += spriteEffect->ay * time;
//		spriteEffect->vz += spriteEffect->az * time;
//		spriteEffect->x += spriteEffect->vx * time;
//		spriteEffect->y += spriteEffect->vy * time;
//		spriteEffect->z += spriteEffect->vz * time;
//		spriteEffect->timer -= time;
//		spriteEffect->alpha = spriteEffect->timer / AlphaRate;
//		spriteEffect->h += UpdateScale;
//		spriteEffect->w += UpdateScale;
//
//		//非表示にする
//		if (spriteEffect->timer <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//}