#pragma once
#include "Charactor.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
class SceneGame;
class UIMinionAttack;
enum TargetFlg
{
	Complete,
	Failed,
};

enum class EnemyTag
{
	None,
	Boom,
	BossSite,
	Boss,
	Cheast,
	Dummy,
	Slime,
	TurtleShell,
	End,
};

class EnemyBase :public Charactor
{
public:
	EnemyBase(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	EnemyBase() {}
	virtual ~EnemyBase() {};
public:
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//経路探索
	void RouteSearch(VECTOR3& Target);
	//ImGuiのデバッグ
	void ImguiDebug();
	//削除
	void Destroy();
	//自分が視野角内に入っているかどうか
	//指定された視野角内にいるかどうか(視点位置,視点のベクトル,視野角)
	bool IsDotAngle(const VECTOR3 Pos,const VECTOR3 vec,const float Angle);
	//フラグが来ていないか確認
	void FlgCheak();
	//当たり判定
	void AttackCircleNode(string nodeName,float circleL,float startTime, float EndTime);
	void AttackCircle(VECTOR3 pos, float circleL);

	void SetDamageFlg(bool flg)override;
	void SetDeadFlg(bool flg)override;

	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	
	//索敵範囲にTargetがいればTRUEを返す
	bool SearchTarget(float L);

	bool VsTargetAttackCircle(VECTOR3 Pos, float Radius);

	float GetSearchL() { return searchL; }
	float GetAttackL() { return attackL; }
	float GetAttackRadius() { return attackRadius; }

	//死亡時間取得
	int  GetDeathTime() { return DeathTime; }
	//死亡時間設定
	void SetDeathTime(const float time) { this->DeathTime = time; }
	//死亡時間の更新
	bool UpdateDeathTime();
	//死亡フラグやダメージフラグが来ていないか確認
	void ResetNode();
	string GetAttackNode() { return AttackNode; }

	bool AddDamage(int Damage, int MaxinvincibleTime = 0);

	bool GetOldDamageFlg() { return oldDamageFlg; }
	void ActionBehaviorTree();

	virtual void TargetComplete();
	void TargetFaild();

	//行動開始処理(行動をするかどうか)
	void SetActionFlg(bool flg) { actionFlg = flg; }


	SceneGame* GetSceneGame() { return sceneGame; };

	TargetFlg GetTargetFlg() { return targetFlg; }
	EnemyBase* parent;//親設定

	EnemyTag GetEnemyTag() { return enemyType; };
	void SetEnemyTag(EnemyTag tag) { enemyType = tag; };

protected:
	TargetFlg targetFlg = TargetFlg::Complete;
	EnemyTag enemyType = EnemyTag::None;

	//索敵範囲
	float searchL = 60.0f;
	float attackL = 4.0f;
	float attackRadius = 4.0f;
	string AttackNode;
	float DeathTime = 0;
	
	NodeBase* ActionNode=nullptr;
	unique_ptr<BehaviorTree> behaviorTree=nullptr;
	unique_ptr<BehaviorData> behaviordata=nullptr;
	SceneGame* sceneGame = nullptr;

	//過去にダメージを受けたかどうか
	bool oldDamageFlg = false;
	bool actionFlg = true;

	std::vector<EnemyBase*> children;


};
