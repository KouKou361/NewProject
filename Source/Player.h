#pragma once
#include "Charactor.h"
#include <string>
#include "PlayerState.h"

class MinionManager;
class EnemyBase;
class SceneGame;
class UIPlayerHP;
class UITargetCursur;
class UITargetHP;
class UIMinionAttack;


class Player:public Charactor
{
	friend class AttackState;
	friend class DamageState;
	friend class DeadState;
	friend class WaitState;
	friend class WalkState;
	friend class BossEntryPlayerState;
private:


	//std::shared_ptr<UIPlayerHP> uiPlayerHP;
	std::shared_ptr<UITargetCursur> uiTargetCursur;
	std::shared_ptr<UITargetHP> uiTargetHP;
	shared_ptr<UIMinionAttack>   uiMinionAttack = nullptr;


	//AttackMaxLengthより遠い距離敵はターゲットのできない。
	const float AttackMaxLength = 50.0f;
	//LossTargetFarより遠い距離敵はターゲットは見失う
	const float LossTargetFar = 70.0f;
	//攻撃中はスピードが落ちる
	const float AttackSpeedDown = 0.5f;

	shared_ptr<MinionManager> minionManager;
	//プレイヤーの動きステートマシン
	PlayerState* stateMachine;
	//SceneGameの更新
	SceneGame* sceneGame;

	//全ての行動
	unique_ptr<PlayerState>   stateAttack;
	unique_ptr<PlayerState>   stateDamage;
	unique_ptr<PlayerState>   stateDead;
	unique_ptr<PlayerState>   stateWait;
	unique_ptr<PlayerState>   stateWalk;
	unique_ptr<BossEntryPlayerState>   stateBossEntry;
public:


	
	enum class State
	{
		ATTACK,//攻撃
		DAMAGE,//ダメージ
		DEAD,//死亡
		WAIT,//待機
		WALK,//移動
		BOSS_ENTRY,//ボスの登場
	};


	State state;

public:
	Player() {};
	~Player() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void ModelRender();
	//モデル用の描画処理
	void Render();
	//当たり判定デバッグ
	void CollisionDebug();
	//ゲームシーンの設定
	void SetSceneGame(SceneGame* scene);
	//状態マシンの変換
	void ChangeState(PlayerState* state);
	void ChangeState(State state, BossStage* stage =nullptr);
	//ターゲットがある程度遠かった場合見失う
	void ResetFarTarget(float L);

	inline MinionManager* GetMinionManager() { return minionManager.get(); };
	inline State GetState() { return state; };
	//ゲームシーンの設定
	inline SceneGame* GetSceneGame() { return sceneGame; };

	//プレイヤーのステージリセット処理
	void ResetPlayer();
	//CSVからデータを取り出して、ステータスの設定する。
	void SetStatus(string SearchName);

private:

	//============入力=================
	//入力処理
	void Input();
	//プレイヤーのカメラ入力処理
	void InputCamera();
	//入力動き処理
	void InputMove();
	//入力攻撃
	void InputAttack();
	//ミニオンの帰還入力処理
	void InputMinionBack();
	//Aimカメラの視点変更
	bool ChangeCameraAim();
	//ミニオンの蘇生入力処理
	void InputMinionResuscitation();


	//============当たり判定==============
	//当たり判定
	void UpdateCollision();
	//敵との当たり判定
	void VsEnemy();


	//============描画==============
	//カーソルの描画
	void RenderCursur();
	//目標のHPの表示
	void RenderTargetHP(const VECTOR2 pos);
	//目標の敵設定
	void SetTargetEnemy(Actor* enm);
	//プレイヤーの体力表示
	void HPRender(const int spriteIndex, const VECTOR2 pos);
	
	
	//目標の敵の設定
	bool SetTargetActor();
	//速さ取得
	inline float GetSpeed() { return speed; };
	//速さ設定
	inline void SetSpeed(const float speed) { this->speed = speed; };
	//ダメージ
	bool AddDamage(int damage, int setinvincibleTime);
};