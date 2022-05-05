#include "SiroboActionDerived.h"
#include "SiroboPlayer.h"
#include "EnemyBase.h"
#include "Animetion.h"
#include "Player.h"
#include "Scene.h"
#include "EffectManager.h"
#include "EffectDerived.h"

//�U���J�n����
void SiroboAttackAction::Start()
{
	//�ڕW�����Ȃ��Ȃ�
	if (siroboOwner->GetTarget() == nullptr)return;

	//�U���A�j���[�V�����̎擾
	const int AttackAnimetionIndex=siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Attack1);
	//�A�j���[�V�����J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), AttackAnimetionIndex, true);

	
	siroboOwner->SetState(Sirobo::StateType::TYPE_ATTACK);
	siroboOwner->SetAttackStandBy(false);//�U���\��Ԃł͂Ȃ��i���ɍU�����Ă��邽�߁j

	//�����G�̏ꍇ
	EnemyBase* enm = nullptr;
	enm = dynamic_cast<EnemyBase*>(siroboOwner->GetTarget());
	if (enm == nullptr)return;

	//�U������Ă��鑤�ɃJ�E���g������B
	int siroboIndex=enm->GetNumBeAttacked();
	siroboIndex += 1;
	enm->SetNumBeAttacked(siroboIndex);

	//�U������Ă��鑤�Ɏ������g���V���{�o�^
	siroboOwner->GetTarget()->attackSirobo.push_back(siroboOwner);
}

//�U�����s����
ActionBase::State SiroboAttackAction::Run()
{
	if (siroboOwner->GetTarget()==nullptr)      return ActionBase::State::FAILED;
	if (siroboOwner->GetHp() <= 0)              return ActionBase::State::FAILED;
	if (siroboOwner->GetTarget()->GetHp() <= 0)	return ActionBase::State::FAILED;


	siroboOwner->SetMoveVec({ 0,0,0 });

	//�����t������
	Stick();

	//�U���ڕW�ɑ΂��čU������
	AttackTarget();

	
	return ActionBase::State::RUN;
}

//�V���{���G�Ɉ����t������
bool SiroboAttackAction::Stick()
{
	if (siroboOwner->GetTarget() == nullptr)assert(!L"�^�[�Q�b�g�������܂����I");

	if (siroboOwner->GetTarget()->GetTag() != ObjectTag::TAG_ENEMY)return false;

	VECTOR3 PosA, PosB;
	PosA = siroboOwner->GetPos();
	PosB = siroboOwner->GetTarget()->GetPos();
	XMVECTOR siroboPos, enmPos,vec;

	siroboPos=XMLoadFloat3(&PosA);
	enmPos = XMLoadFloat3(&PosB);
	vec = XMVectorSubtract(siroboPos,enmPos);
	vec = XMVector3Normalize(vec);
	Charactor* chara = nullptr;
	chara=static_cast<Charactor*>(siroboOwner->GetTarget());
	if (chara == nullptr)return false;
	vec = XMVectorScale(vec,chara->GetCollisionRadius()+ siroboOwner->GetCollisionRadius());

	siroboPos = XMVectorAdd(vec,enmPos);
	VECTOR3 siroboOwnerPos;
	XMStoreFloat3(&siroboOwnerPos,siroboPos);
	siroboOwner->SetPos(siroboOwnerPos);



	return false;
}

//�U���I������
void SiroboAttackAction::End()
{
	if (siroboOwner->GetTarget() == nullptr)return;
	EnemyBase* enm = nullptr;
	enm = dynamic_cast<EnemyBase*>(siroboOwner->GetTarget());
	if (enm == nullptr)return;
	siroboOwner->GetTarget()->AttackSiroboErase(siroboOwner);
	int attackSirobo = enm->GetNumBeAttacked();
	attackSirobo -= 1;
	enm->SetNumBeAttacked(attackSirobo);
}

//�U���ڕW�ɑ΂��čU������
void SiroboAttackAction::AttackTarget()
{
	if (siroboOwner->GetAttackCoolTime() <= 0)
	{
		const float SiroboCoolTime = 3;
		siroboOwner->SetAttackCoolTime(SiroboCoolTime);

		//�G�ɍU�����ė^����_���[�W��
		const int Damage = 1;

		if (siroboOwner->GetTarget()->AddDamage(Damage, SiroboCoolTime))
		{
			if (siroboOwner->GetTarget() != nullptr)
			{
				siroboOwner->GetPlayer()->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("Attack")->Play(siroboOwner->GetTarget()->GetPos(), 2);
			}
		}
	}

	siroboOwner->AddDamage(1, 120);
}

//Imgui�f�o�b�O
void SiroboAttackAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Attack");
	ImGui::Text("AttackCoolTime=%f", siroboOwner->GetAttackCoolTime());
	ImGui::Text("HP=%d", siroboOwner->GetHp());
	ImGui::End();
}