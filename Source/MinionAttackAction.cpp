#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "EnemyBase.h"
#include "Animetion.h"
#include "Player.h"
#include "Scene.h"
#include "EffectManager.h"
#include "EffectDerived.h"

//�J�n����
void MinionAttackAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Attack1), true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_ATTACK);
	minionOwner->SetAttackStandBy(false);

	if (minionOwner->GetTarget() == nullptr)return;
	EnemyBase* enm = nullptr;
	enm = dynamic_cast<EnemyBase*>(minionOwner->GetTarget());
	if (enm == nullptr)return;

	int attackMinion=enm->GetNumBeAttacked();
	attackMinion += 1;
	enm->SetNumBeAttacked(attackMinion);

	minionOwner->GetTarget()->AttackMinions.push_back(minionOwner);
}

//���s����
ActionBase::State MinionAttackAction::Run()
{
	if (minionOwner->GetTarget()==nullptr)
	{
		return ActionBase::State::Failed;
	}
	minionOwner->SetMoveVec({ 0,0,0 });
	if (minionOwner->GetHp() <= 0)
	{
		return ActionBase::State::Failed;
	}

	if (minionOwner->GetTarget()->GetHp() <= 0)
	{
		return ActionBase::State::Failed;
	}

	Stick();

	//�~�j�I���̍U��
	if (minionOwner->GetAttackCoolTime() <= 0)
	{
		minionOwner->SetAttackCoolTime(180);
		if (minionOwner->GetTarget()->AddDamage(1))
		{
			if (minionOwner->GetTarget() != nullptr)
			{
				minionOwner->GetPlayer()->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("Attack")->Play(minionOwner->GetTarget()->GetPos(), 2);
			}
		}

	
		
	}

	minionOwner->AddDamage(1,120);

	
	return ActionBase::State::Run;
}

//�����t������
bool MinionAttackAction::Stick()
{
	if (minionOwner->GetTarget() == nullptr)assert(!L"�^�[�Q�b�g�������܂����I");

	if (minionOwner->GetTarget()->GetTag() != ObjectTag::TAG_ENEMY)return false;

	VECTOR3 PosA, PosB;
	PosA = minionOwner->GetPos();
	PosB = minionOwner->GetTarget()->GetPos();
	XMVECTOR minionPos, enmPos,vec;

	minionPos=XMLoadFloat3(&PosA);
	enmPos = XMLoadFloat3(&PosB);
	vec = XMVectorSubtract(minionPos,enmPos);
	vec = XMVector3Normalize(vec);
	Charactor* chara = nullptr;
	chara=static_cast<Charactor*>(minionOwner->GetTarget());
	if (chara == nullptr)return false;
	vec = XMVectorScale(vec,chara->GetCollisionRadius()+ minionOwner->GetCollisionRadius());

	minionPos = XMVectorAdd(vec,enmPos);
	VECTOR3 minionOwnerPos;
	XMStoreFloat3(&minionOwnerPos,minionPos);
	minionOwner->SetPos(minionOwnerPos);



	return false;
}

//�I������
void MinionAttackAction::End()
{
	if (minionOwner->GetTarget() == nullptr)return;
	EnemyBase* enm = nullptr;
	enm = dynamic_cast<EnemyBase*>(minionOwner->GetTarget());
	if (enm == nullptr)return;
	minionOwner->GetTarget()->AttackMinionErase(minionOwner);
	int attackMinion = enm->GetNumBeAttacked();
	attackMinion -= 1;
	enm->SetNumBeAttacked(attackMinion);
}

//Imgui�f�o�b�O
void MinionAttackAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Attack");
	ImGui::Text("AttackCoolTime=%d", minionOwner->GetAttackCoolTime());
	ImGui::Text("HP=%d", minionOwner->GetHp());
	ImGui::End();
}