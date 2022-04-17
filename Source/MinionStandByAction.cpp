#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"
//�ҋ@�s��


//�J�n����
void MinionStandByAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Idle), true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_STAND_BY);
	TK_Lib::Lib_Sound::SoundPlay("MinionAttack", false);
	
	//�S��
	minionOwner->SetHp(minionOwner->GetMaxHp());
}

//�Q�O����
void MinionStandByAction::Flock()
{
	//�W���ʒu
	VECTOR3 TargetPos = (-minionOwner->GetPlayer()->GetFront()) * 5 + minionOwner->GetPlayer()->GetPos();


	MinionManager* manager = minionOwner->GetManager();

	const float RangeL = 10.0f;
	VECTOR3 AddPosition = { 0,0,0 };//RangeL�͈͓̔��ɂ���~�j�I�������̍��v�̈ʒu
	VECTOR3 AddVelocity = { 0,0,0 };//RangeL�͈͓̔��ɂ���~�j�I�������̍��v�̑��x
	int MinionNum = 0;
	float MaxL = FLT_MAX;
	MinionPlayer* nearMinion=nullptr;

	
	for (int i = 0; i < manager->GetMinionsSize(); i++)
	{
		//�~�j�I���̎擾
		MinionPlayer* minion = manager->GetMinionIndex(i);
		if (minionOwner == minion)continue;
		//if (minionOwner->GetState() != MinionPlayer::StateType::TypeStandBy)continue;

		//�����̎Z�o
		float L=minion->Length(minionOwner->GetPos());
		//RangeL�͈͓̔��ɂ���~�j�I���̎Z�o
		if(RangeL>=L)
		{
			AddPosition += minion->GetPos();
			AddVelocity += minion->GetVelocity();
			MinionNum++;
		}


		//��ԋ߂��̃~�j�I���̎擾
		if (MaxL >= L)
		{
			MaxL = L;
			nearMinion = minion;
		}
	}


	

	//�W���ʒu�ɐi��
	VECTOR3 v2;
	{
		const float power = 0.05f;
		XMVECTOR V;
		v2 = TargetPos-minionOwner->GetPos();
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
		if (nearMinion == nullptr)
		{
			minionOwner->SetMoveVec(v2);
			return;
		}

		const float power = 0.001f;
		XMVECTOR V;
		v = minionOwner->GetPos() - nearMinion->GetPos();
		V = XMLoadFloat3(&v);
		V = XMVector3Normalize(V);
		V = XMVectorScale(V, power);
		XMStoreFloat3(&v, V);
	}

	minionOwner->SetMoveVec(v2+v);
}

//���s����
ActionBase::State MinionStandByAction::Run()
{
	Flock();
	MinionVsMinion();
	VsPlayer();
	//�c�����̓����蔻��iY�����j
	minionOwner->VerticalCollision();

	return ActionBase::State::Run;
}

ActionBase::State MinionStandByAction::DeleteTarget()
{
	return Run();
}

void  MinionStandByAction::MinionVsMinion()
{
	MinionManager* manager = minionOwner->GetManager();
	for (int i = 0; i < manager->GetMinionsSize(); i++)
	{
		MinionPlayer* minion = manager->GetMinionIndex(i);
		if (minion == minionOwner)continue;
		VECTOR3 OutPosA, OutPosB;
		if (Collision::Instance().SphereVsSphere(
			minionOwner->GetPos(), minionOwner->GetWeight(), minionOwner->GetCollisionRadius(),
			minion->GetPos(), minion->GetWeight(), minion->GetCollisionRadius(), OutPosA, OutPosB))
		{
			minion->SetPos(OutPosB);
			minionOwner->SetPos(OutPosA);
		}

	}
}
void MinionStandByAction::VsPlayer()
{
	VECTOR3 OutPosA, OutPosB;
	if (Collision::Instance().SphereVsSphere(
		minionOwner->GetPos(), minionOwner->GetWeight(), minionOwner->GetCollisionRadius(),
		minionOwner->GetPlayer()->GetPos(), minionOwner->GetPlayer()->GetWeight(), minionOwner->GetPlayer()->GetCollisionRadius(), OutPosA, OutPosB))
	{


	//	minionOwner->GetPlayer()->SetPos(OutPosB);
		minionOwner->SetPos(OutPosA);
	}
}

//�I������
void MinionStandByAction::End()
{

}

//Imgui�f�o�b�O
void MinionStandByAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("StandBy");
	ImGui::End();
}
