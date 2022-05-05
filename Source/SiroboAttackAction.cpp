#include "SiroboActionDerived.h"
#include "SiroboPlayer.h"
#include "EnemyBase.h"
#include "Animetion.h"
#include "Player.h"
#include "Scene.h"
#include "EffectManager.h"
#include "EffectDerived.h"

//攻撃開始処理
void SiroboAttackAction::Start()
{
	//目標がいないなら
	if (siroboOwner->GetTarget() == nullptr)return;

	//攻撃アニメーションの取得
	const int AttackAnimetionIndex=siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Attack1);
	//アニメーション開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), AttackAnimetionIndex, true);

	
	siroboOwner->SetState(Sirobo::StateType::TYPE_ATTACK);
	siroboOwner->SetAttackStandBy(false);//攻撃可能状態ではない（既に攻撃しているため）

	//もし敵の場合
	EnemyBase* enm = nullptr;
	enm = dynamic_cast<EnemyBase*>(siroboOwner->GetTarget());
	if (enm == nullptr)return;

	//攻撃されている側にカウントを入れる。
	int siroboIndex=enm->GetNumBeAttacked();
	siroboIndex += 1;
	enm->SetNumBeAttacked(siroboIndex);

	//攻撃されている側に自分自身をシロボ登録
	siroboOwner->GetTarget()->attackSirobo.push_back(siroboOwner);
}

//攻撃実行処理
ActionBase::State SiroboAttackAction::Run()
{
	if (siroboOwner->GetTarget()==nullptr)      return ActionBase::State::FAILED;
	if (siroboOwner->GetHp() <= 0)              return ActionBase::State::FAILED;
	if (siroboOwner->GetTarget()->GetHp() <= 0)	return ActionBase::State::FAILED;


	siroboOwner->SetMoveVec({ 0,0,0 });

	//引っ付き処理
	Stick();

	//攻撃目標に対して攻撃する
	AttackTarget();

	
	return ActionBase::State::RUN;
}

//シロボが敵に引っ付き処理
bool SiroboAttackAction::Stick()
{
	if (siroboOwner->GetTarget() == nullptr)assert(!L"ターゲットが消えました！");

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

//攻撃終了処理
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

//攻撃目標に対して攻撃する
void SiroboAttackAction::AttackTarget()
{
	if (siroboOwner->GetAttackCoolTime() <= 0)
	{
		const float SiroboCoolTime = 3;
		siroboOwner->SetAttackCoolTime(SiroboCoolTime);

		//敵に攻撃して与えるダメージ量
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

//Imguiデバッグ
void SiroboAttackAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Attack");
	ImGui::Text("AttackCoolTime=%f", siroboOwner->GetAttackCoolTime());
	ImGui::Text("HP=%d", siroboOwner->GetHp());
	ImGui::End();
}