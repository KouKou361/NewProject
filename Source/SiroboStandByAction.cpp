#include "SiroboActionDerived.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"

//�ҋ@�s��


//�J�n����
void SiroboStandByAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Idle), true);
	siroboOwner->SetState(Sirobo::StateType::TYPE_STAND_BY);
	TK_Lib::Lib_Sound::SoundPlay("SiroboAttack", false);
	speed = 0.0f;
	AppropriateAnimesion(idei);
	//�S��
	siroboOwner->SetHp(siroboOwner->GetMaxHp());
}

//�Q�O����
void SiroboStandByAction::Flock()
{
	//�W���ʒu
	VECTOR3 TargetPos = (-siroboOwner->GetPlayer()->GetFront()) * 5 + siroboOwner->GetPlayer()->GetPos();


	SiroboManager* manager = siroboOwner->GetManager();

	const float RangeL = 10.0f;
	VECTOR3 AddPosition = { 0,0,0 };//RangeL�͈͓̔��ɂ���~�j�I�������̍��v�̈ʒu
	VECTOR3 AddVelocity = { 0,0,0 };//RangeL�͈͓̔��ɂ���~�j�I�������̍��v�̑��x
	int SiroboNum = 0;
	float MaxL = FLT_MAX;
	Sirobo* nearSirobo=nullptr;

	
	for (int i = 0; i < manager->GetSiroboSize(); i++)
	{
		//�~�j�I���̎擾
		Sirobo* sirobo = manager->GetSiroboIndex(i);
		if (siroboOwner == sirobo)continue;
		//if (siroboOwner->GetState() != SiroboPlayer::StateType::TypeStandBy)continue;

		//�����̎Z�o
		float L=sirobo->Length(siroboOwner->GetPos());
		//RangeL�͈͓̔��ɂ���~�j�I���̎Z�o
		if(RangeL>=L)
		{
			AddPosition += sirobo->GetPos();
			AddVelocity += sirobo->GetVelocity();
			SiroboNum++;
		}


		//��ԋ߂��̃~�j�I���̎擾
		if (MaxL >= L)
		{
			MaxL = L;
			nearSirobo = sirobo;
		}
	}


	

	//�W���ʒu�ɐi��
	VECTOR3 v2;
	{
		const float power = 0.05f;
		XMVECTOR V;
		v2 = TargetPos-siroboOwner->GetPos();
		V = XMLoadFloat3(&v2);

		float l;
		XMVECTOR L;
		L = XMVector3Length(V);
		XMStoreFloat(&l,L);
		l *= power;


		V = XMVector3Normalize(V);
		V = XMVectorScale(V, l);
		XMStoreFloat3(&v2, V);
	}

	

	//�߂��ɂ���~�j�I���ɗ����
	VECTOR3 v;
	{
		//�����߂��Ƀ~�j�I�������Ȃ��Ȃ�
		if (nearSirobo == nullptr)
		{
			siroboOwner->SetMoveVec(v2);
			return;
		}

		const float power = 0.001f;
		XMVECTOR V;
		v = siroboOwner->GetPos() - nearSirobo->GetPos();
		V = XMLoadFloat3(&v);
		V = XMVector3Normalize(V);
		V = XMVectorScale(V, power);
		XMStoreFloat3(&v, V);
	}

	siroboOwner->SetMoveVec(v2+v);


	{
		float l;
		XMVECTOR L, V;
		VECTOR3 V2 = (v2 + v);
		V = XMLoadFloat3(&V2);
		L = XMVector3Length(V);
		XMStoreFloat(&l, L);
		speed = l;
	}

}

//���s����
ActionBase::State SiroboStandByAction::Run()
{
	Flock();
	SiroboVsSirobo();
	VsPlayer();
	//�c�����̓����蔻��iY�����j
	siroboOwner->VerticalCollision();
	//�K�؂ȃA�j���[�V�����Ɉڍs����B
	AllAppropriateAnimesion();

	return ActionBase::State::RUN;
}

ActionBase::State SiroboStandByAction::DeleteTarget()
{
	return Run();
}

void  SiroboStandByAction::SiroboVsSirobo()
{
	SiroboManager* manager = siroboOwner->GetManager();
	for (int i = 0; i < manager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = manager->GetSiroboIndex(i);
		if (sirobo == siroboOwner)continue;
		VECTOR3 OutPosA, OutPosB;
		if (Collision::Instance().SphereVsSphere(
			siroboOwner->GetPos(), siroboOwner->GetWeight(), siroboOwner->GetCollisionRadius(),
			sirobo->GetPos(), sirobo->GetWeight(), sirobo->GetCollisionRadius(), OutPosA, OutPosB))
		{
			sirobo->SetPos(OutPosB);
			siroboOwner->SetPos(OutPosA);
		}

	}
}
void SiroboStandByAction::VsPlayer()
{
	VECTOR3 OutPosA, OutPosB;
	if (Collision::Instance().SphereVsSphere(
		siroboOwner->GetPos(), siroboOwner->GetWeight(), siroboOwner->GetCollisionRadius(),
		siroboOwner->GetPlayer()->GetPos(), siroboOwner->GetPlayer()->GetWeight(), siroboOwner->GetPlayer()->GetCollisionRadius(), OutPosA, OutPosB))
	{
	//	siroboOwner->GetPlayer()->SetPos(OutPosB);
		siroboOwner->SetPos(OutPosA);
	}
}
//�K�؂ȃA�j���[�V�����Ɉڍs����B
bool SiroboStandByAction::AppropriateAnimesion(BaseStandByAnimetion* anime)
{
	
	if (anime->Judge(speed))
	{
		if (current == anime)return true;
		current = anime;
		current->Init();//�A�j���[�V�����؂�ւ�
		if (current == anime)return true;
	}
	return false;
}

void SiroboStandByAction::AllAppropriateAnimesion()
{
	//����
	if (AppropriateAnimesion(run))return;
	//�ҋ@
	if (AppropriateAnimesion(idei))return;
	//����
	if (AppropriateAnimesion(walk))return;

}

//�I������
void SiroboStandByAction::End()
{

}

//Imgui�f�o�b�O
void SiroboStandByAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("StandBy");
	ImGui::End();
}
