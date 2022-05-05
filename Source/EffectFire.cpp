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
//void EffectFire::Init()
//{
//	//pos = VECTOR3{ 11,0,-2 };
//    //	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
//}
//更新処理
//void EffectFire::Update()
//{
//
//	float time = TK_Lib::Window::GetElapsedTime();
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	
//	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//		if (!spriteEffect->IsCameraRender())continue;
//
//		spriteEffect->vx +=    spriteEffect->ax * time;
//		spriteEffect->vy +=    spriteEffect->ay * time;
//		spriteEffect->vz +=    spriteEffect->az * time;
//		spriteEffect->x +=     spriteEffect->vx  * time;
//		spriteEffect->y +=     spriteEffect->vy  * time;
//		spriteEffect->z +=     spriteEffect->vz  * time;
//		spriteEffect->timer -= time;
//		spriteEffect->h +=     InitStatus.GetUpdateScale().x * time;
//		spriteEffect->w +=     InitStatus.GetUpdateScale().y * time;
//		spriteEffect->color.w -= InitStatus.GetUpdateAlpha() * time;
//		//非表示にする
//		if (spriteEffect->timer <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//}