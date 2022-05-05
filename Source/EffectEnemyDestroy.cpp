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
//void EffectEnemyDestroy::Init()
//{
//
//}



//更新処理
//void EffectEnemyDestroy::Update()
//{
//
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	float time = TK_Lib::Window::GetElapsedTime();
//
//	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//		spriteEffect->color.w -= InitStatus.GetUpdateAlpha() * time;
//
//		if (!spriteEffect->IsCameraRender())continue;
//
//		spriteEffect->vx += spriteEffect->ax * time;
//		spriteEffect->vy += spriteEffect->ay * time;
//		spriteEffect->vz += spriteEffect->az * time;
//										
//		spriteEffect->x += spriteEffect->vx  * time;
//		spriteEffect->y += spriteEffect->vy  * time;
//		spriteEffect->z += spriteEffect->vz  * time;
//
//		spriteEffect->h += InitStatus.GetUpdateScale().x * time;
//		spriteEffect->w += InitStatus.GetUpdateScale().y * time;
//
//	//	spriteEffect->alpha = spriteEffect->timer / 0.2f;
//
//		//非表示にする
//		if (spriteEffect->color.w <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//
//	
//}