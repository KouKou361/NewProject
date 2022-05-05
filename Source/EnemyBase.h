#pragma once
#include "Charactor.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
class SceneGame;
class UISiroboAttack;
enum class TargetFlg
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
	virtual void Init()=0;
	//更新処理
	void Update();
	//経路探索
	void RouteSearch(VECTOR3& target);
	//ImGuiのデバッグ
	void ImguiDebug();
	//削除
	void Destroy();
	//自分が視野角内に入っているかどうか
	//指定された視野角内にいるかどうか(視点位置,視点のベクトル,視野角)
	bool IsDotAngle(const VECTOR3& pos,const VECTOR3& vec,const float& angle);
	//フラグが来ていないか確認
	void FlgCheak();
	//当たり判定
	void AttackCircleNode(const string& nodeName, const float& circleL, const float& startTime, const float& EndTime);
	void AttackCircle(const VECTOR3& pos, const float& circleL);

	inline void SetDamageFlg(const bool flg) { damageFlg = flg; };
	inline void SetDeadFlg(const bool flg) { deadFlg = flg; }; 

	void HPRender(const int &spriteIndex, const VECTOR2& pos);
	
	//索敵範囲にTargetがいればTRUEを返す
	bool SearchTarget(const float &l);

	bool VsTargetAttackCircle(const VECTOR3& pos, const float& radius);



	//死亡時間の更新
	bool UpdateDeathTime();
	//死亡フラグやダメージフラグが来ていないか確認
	void ResetNode();

	bool AddDamage(const int damage, const float setInvincibleTime=0);

	//ビヘイビアツリーの行動処理
	void ActionBehaviorTree();

	virtual void TargetComplete();
	void TargetFaild();

	//行動開始処理(行動をするかどうか)
	inline void SetActionFlg(const bool flg) { actionFlg = flg; }


	inline SceneGame* GetSceneGame() { return sceneGame; };

	inline TargetFlg GetTargetFlg() { return targetFlg; }

	//死亡時間取得
	inline float  GetDeathTime() { return deathTime; }
	inline void SetDeathTime(const float time) { this->deathTime = time; }

	inline string GetAttackNode() { return attackNode; }
	inline bool GetOldDamageFlg() { return oldDamageFlg; }

	inline EnemyTag GetEnemyTag() { return enemyType; };
	inline void SetEnemyTag(const EnemyTag& tag) { enemyType = tag; };

	inline float GetSearchL() { return searchL; }
	inline float GetAttackL() { return attackL; }
	inline float GetAttackRadius() { return attackRadius; }
	inline int GetExpNum() { return ExpNum; }
protected:
	//アニメション設定
	virtual void SetAnimetion() = 0;
	//CSVからデータを取り出して、ステータスの設定する。
	void SetStatus(const string& searchName);
	//behaviorTreeの設定
	virtual void SetBehaviorTree()=0;
public:
	EnemyBase* parent=nullptr;//親設定
protected:
	TargetFlg targetFlg = TargetFlg::COMPLETE;
	EnemyTag enemyType = EnemyTag::NONE;

	//索敵範囲
	float searchL = 60.0f;
	float attackL = 4.0f;
	float attackRadius = 4.0f;
	float deathTime = 0;
	string attackNode="";

	
	NodeBase* actionNode=nullptr;
	unique_ptr<BehaviorTree> behaviorTree=nullptr;
	unique_ptr<BehaviorData> behaviordata=nullptr;
	SceneGame* sceneGame = nullptr;

	//過去にダメージを受けたかどうか
	bool oldDamageFlg = false;
	bool actionFlg = true;

	//経験値の数
	int ExpNum = 5;

	std::vector<EnemyBase*> children;


};
