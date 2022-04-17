#pragma once

#include "Charactor.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class Player;
class MinionManager;
class MinionPlayerAI;
class EnemyManager;
class EnemyBase;
class UIMinionDownHelp;
class ObjectManager;


//ミニオン
class MinionPlayer :public Charactor
{
public:
	enum Team
	{
		TEAM_PLAYER,//プレイヤーの仲間
		TEAM_ENEMY,//敵チームの仲間(一応　いらないかも)
		TEAM_NEUTRAL,//中立
		TEAM_END
	};
	enum StateType
	{
		TYPE_IDLE,   //中立（ボーっとしている）
		TYPE_STAND_BY,//指示待ち（攻撃OK）
		TYPE_ATTACK, //攻撃中
		TYPE_BACK,   //撤退中
		TYPE_THROW,  //投げられ中
		TYPE_DAMAGE, //ダメージ中
		TYPE_DEAD,//死亡中
		TYPE_RESUSCITATION,//蘇生されている時
		TypeEnd,
	};
private:
	shared_ptr<MinionPlayerAI> Ai=nullptr;
	shared_ptr<UIMinionDownHelp> uiMinionDownHelp = nullptr;

	MinionManager* manager=nullptr;
	Player* pl=nullptr;
	int index = 0;//自分の番号
	Team team;//チーム
	StateType state;//自分の状態
	bool AttackStandBy=false;//攻撃可能な状態



public:
	//初期化処理
	void Init(Player* pl);
	//更新処理
	void Update();
	//仲間に加わる
	void Join();
	//削除
	void Destroy();
	//HPの表示
	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	//Spriteの描画
	void Render();
	//自分の番号
	void SetIndex(int index) { this->index = index; }
	int GetIndx() { return index; }

	Player* GetPlayer() { return pl; }
	//マネージャーの取得
	MinionManager* GetManager() { return manager; };
	void SetManager(MinionManager* manager) { this->manager = manager; }
	//チーム
	void SetTeam(Team team) { this->team = team; };
	Team GetTeam() { return team; };
	//自分の状態
	void SetState(StateType type) { this->state = type; };
	StateType GetState() { return state; };
	//攻撃可能な状態
	void SetAttackStandBy(bool flg) { AttackStandBy = flg; }
	bool GetAttackStandBy() { return AttackStandBy; }
	//Aiの探索をリセットする
	void ResetNode();
	//蘇生ステート変換処理
	void SetResuscitation();
	//蘇生中かどうか
	bool IsResuscitation();
	//

	//仲間になる範囲
	const float FollowSerchL = 20.0f;
	//プレイヤーの範囲
	const float StandBySerchL = 7.0f;


	const int MaxAttackCoolTime = 0;
public:
	//復活時間
	int ResuscitationTime = 0;

	bool ResuscitationFlg = false;
};

//ミニオン管理クラス
class MinionManager :public Manager
{
public:
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//モデル描画処理
	void ModelRender();
	//全削除
	void Clear();
	//登録
	void Register(shared_ptr<MinionPlayer> enm);
	//破棄処理
	void Destroy(MinionPlayer* enm);
	//当たり判定デバッグ
	void CollisionDebug();
	//ミニオンの数の取得
	int GetMinionsSize() { return minions.size(); }
	//ミニオンの数の取得
	MinionPlayer* GetMinionIndex(const int& index) { return minions.at(index).get(); }
	//ミニオンの攻撃OK行動のみ攻撃する
	void OneAttack(MinionPlayer* minion);
	//ミニオンの帰還
	void AllBack();

	void SetEnemyManager(EnemyManager* manager) { this->enemyManager = manager; }
	EnemyManager* GetEnemyManager() { return enemyManager; }

	void SetObjectManager(ObjectManager* manager) { this->objectManager = manager; }
	ObjectManager* GetObjectManager() { return objectManager; }

private:
	EnemyManager* enemyManager = nullptr;
	ObjectManager* objectManager = nullptr;
	vector<shared_ptr<MinionPlayer>>minions;
	vector<shared_ptr<MinionPlayer>>remove;
	Charactor* Target;
	//ミニオンたちの番号をふるための変数
	int IndexMinion=0;


};
