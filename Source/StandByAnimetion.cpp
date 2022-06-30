#include "StandByAnimetion.h"
#include "Animetion.h"
#include "SiroboPlayer.h"
#include "Lib.h"

//切り替わった時の処理（止まる）
void IdelStandByAnimetion::Init()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Idle), true);
}

//切り替わり処理（止まる）
bool IdelStandByAnimetion::Judge(const float speed)
{
	const float MaxSpeed = 0.2f;
	if (speed <= MaxSpeed)	return true;
	return false;
}
//切り替わった時の処理（歩く）
void WalkStandByAnimetion::Init()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Walk), true);
}

//切り替わり処理（歩く）
bool WalkStandByAnimetion::Judge(const float speed)
{
	const float MaxSpeed = 0.5f;
	if (speed <= MaxSpeed)
	{
		return true;
	}
	return false;
}

//切り替わった時の処理（走る）
void RunStandByAnimetion::Init()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Run), true);
}

//切り替わり処理（走る）
bool RunStandByAnimetion::Judge(const float speed)
{
	const float MaxSpeed = 0.5;
	if (speed >= MaxSpeed)	return true;
	return false;
}

