#pragma once
#include "Charactor.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
class SceneGame;
class UIMinionAttack;
enum TargetFlg
{
	COMPLETE,
	FAILED,
};

enum class EnemyTag
{
	NONE,
	BOMB,
	BOSS_SITE,
	BOSS,
	CHEAST,
	DUMMY_ENEMY,
	SLIME,
	TURTLESHELL,
	END,
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
	//CSVからデータを取り出して、ステータスの設定する。
	void SetStatus(string SearchName);


	//死亡時間の更新
	bool UpdateDeathTime();
	//死亡フラグやダメージフラグが来ていないか確認
	void ResetNode();

	bool AddDamage(int Damage, int MaxinvincibleTime = 0);


	void ActionBehaviorTree();

	virtual void TargetComplete();
	void TargetFaild();

	//行動開始処理(行動をするかどうか)
	inline void SetActionFlg(const bool flg) { actionFlg = flg; }


	inline SceneGame* GetSceneGame() { return sceneGame; };

	inline TargetFlg GetTargetFlg() { return targetFlg; }

	//死亡時間取得
	inline int  GetDeathTime() { return deathTime; }
	inline void SetDeathTime(const float time) { this->deathTime = time; }

	inline string GetAttackNode() { return attackNode; }
	inline bool GetOldDamageFlg() { return oldDamageFlg; }

	inline EnemyTag GetEnemyTag() { return enemyType; };
	inline void SetEnemyTag(const EnemyTag tag) { enemyType = tag; };

	inline float GetSearchL() { return searchL; }
	inline float GetAttackL() { return attackL; }
	inline float GetAttackRadius() { return attackRadius; }
public:
	EnemyBase* parent;//親設定
protected:
	TargetFlg targetFlg = TargetFlg::COMPLETE;
	EnemyTag enemyType = EnemyTag::NONE;

	//索敵範囲
	float searchL = 60.0f;
	float attackL = 4.0f;
	float attackRadius = 4.0f;
	string attackNode;
	float deathTime = 0;
	
	NodeBase* actionNode=nullptr;
	unique_ptr<BehaviorTree> behaviorTree=nullptr;
	unique_ptr<BehaviorData> behaviordata=nullptr;
	SceneGame* sceneGame = nullptr;

	//過去にダメージを受けたかどうか
	bool oldDamageFlg = false;
	bool actionFlg = true;

	std::vector<EnemyBase*> children;


};
