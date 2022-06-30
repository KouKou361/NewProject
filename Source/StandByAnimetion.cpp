#include "StandByAnimetion.h"
#include "Animetion.h"
#include "SiroboPlayer.h"
#include "Lib.h"

//�؂�ւ�������̏����i�~�܂�j
void IdelStandByAnimetion::Init()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Idle), true);
}

//�؂�ւ�菈���i�~�܂�j
bool IdelStandByAnimetion::Judge(const float speed)
{
	const float MaxSpeed = 0.2f;
	if (speed <= MaxSpeed)	return true;
	return false;
}
//�؂�ւ�������̏����i�����j
void WalkStandByAnimetion::Init()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Walk), true);
}

//�؂�ւ�菈���i�����j
bool WalkStandByAnimetion::Judge(const float speed)
{
	const float MaxSpeed = 0.5f;
	if (speed <= MaxSpeed)
	{
		return true;
	}
	return false;
}

//�؂�ւ�������̏����i����j
void RunStandByAnimetion::Init()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Run), true);
}

//�؂�ւ�菈���i����j
bool RunStandByAnimetion::Judge(const float speed)
{
	const float MaxSpeed = 0.5;
	if (speed >= MaxSpeed)	return true;
	return false;
}

