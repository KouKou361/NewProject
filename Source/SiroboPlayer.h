#pragma once

#include "Charactor.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class Player;
class SiroboManager;
class SiroboPlayerAI;
class EnemyManager;
class EnemyBase;
class UISiroboDownHelp;
class ObjectManager;


//ミニオン
class Sirobo :public Charactor
{
public:
	enum class Team
	{
		TEAM_PLAYER,//プレイヤーの仲間
		TEAM_ENEMY,//敵チームの仲間(一応　いらないかも)
		TEAM_NEUTRAL,//中立
		TEAM_NONE,
		TEAM_END
	};
	enum class StateType
	{
		TYPE_IDLE,   //中立（ボーっとしている）
		TYPE_STAND_BY,//指示待ち（攻撃OK）
		TYPE_ATTACK, //攻撃中
		TYPE_BACK,   //撤退中
		TYPE_THROW,  //投げられ中
		TYPE_DAMAGE, //ダメージ中
		TYPE_DEAD,//死亡中
		TYPE_RESUSCITATION,//蘇生されている時
		TYPE_NONE,
		TypeEnd,
	};
private:
	shared_ptr<SiroboPlayerAI> ai=nullptr;
	shared_ptr<UISiroboDownHelp> uiSiroboDownHelp = nullptr;

	SiroboManager* manager=nullptr;
	Player* pl=nullptr;
	int index = 0;//自分の番号
	Team team= Team::TEAM_NONE;//チーム
	StateType state= StateType::TYPE_NONE;//自分の状態
	bool attackStandBy=false;//攻撃可能な状態



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
	void HPRender(const int &SpriteIndex, const VECTOR2& Pos);
	//Spriteの描画
	void Render();
	//自分の番号
	void SetIndex(const int& index) { this->index = index; }
	int GetIndx() { return index; }

	Player* GetPlayer() { return pl; }
	//マネージャーの取得
	SiroboManager* GetManager() { return manager; };
	void SetManager(SiroboManager* manager) { this->manager = manager; }
	//チーム
	void SetTeam(Team team) { this->team = static_cast<Team>(team); };
	Team GetTeam() { return team; };
	//自分の状態
	void SetState(StateType type) { this->state = static_cast<StateType>(type); };
	StateType GetState() { return state; };
	//攻撃可能な状態
	void SetAttackStandBy(bool flg) { attackStandBy = flg; }
	bool GetAttackStandBy() { return attackStandBy; }
	//Aiの探索をリセットする
	void ResetNode();
	//蘇生ステート変換処理
	void SetResuscitation();
	//蘇生中かどうか
	bool IsResuscitation();

	//CSVからデータを取り出して、ステータスの設定する。
	void SetStatus(const string& SearchName);

	//仲間になる範囲
	const float FollowSerchL = 20.0f;
	//プレイヤーの範囲
	const float StandBySerchL = 7.0f;


	const float MaxAttackCoolTime = 0;

private:
	//アニメーションの登録
	void RegisterAnimetion();

	//ダウン状態のヘルプアイコンの作成
	void CreateDownHelpUI();
public:
	//復活時間
	float resuscitationTime = 0;

	bool resuscitationFlg = false;
};

//ミニオン管理クラス
class SiroboManager :public Manager
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
	void Register(shared_ptr<Sirobo> enm);
	//破棄処理
	void Destroy(Sirobo* enm);
	//当たり判定デバッグ
	void CollisionDebug();
	//ミニオンの数の取得
	int GetSiroboSize() { return static_cast<int>(sirobos.size()); }
	//ミニオンの数の取得
	Sirobo* GetSiroboIndex(const int& index) { return sirobos.at(index).get(); }
	//ミニオンの攻撃OK行動のみ攻撃する
	void OneAttack(Sirobo* sirobo);
	//ミニオンの帰還
	void AllBack();
	//シロボ達の状態タイプの数を返す
	int GetTypeSiroboSize(const Sirobo::StateType type);

	void SetEnemyManager(EnemyManager* manager) { this->enemyManager = manager; }
	EnemyManager* GetEnemyManager() { return enemyManager; }

	void SetObjectManager(ObjectManager* manager) { this->objectManager = manager; }
	ObjectManager* GetObjectManager() { return objectManager; }

private:
	EnemyManager* enemyManager = nullptr;
	ObjectManager* objectManager = nullptr;
	vector<shared_ptr<Sirobo>>sirobos;
	vector<shared_ptr<Sirobo>>remove;
	Charactor* Target;
	//ミニオンたちの番号をふるための変数
	int indexSirobo =0;


};
