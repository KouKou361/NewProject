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

	
private:

	shared_ptr<MinionManager> minionManager;
	//プレイヤーの動きステートマシン
	PlayerState* stateMachine;
	//SceneGameの更新
	SceneGame* sceneGame;
public:
	//全ての行動
	unique_ptr<PlayerState>   stateAttack;
	unique_ptr<PlayerState>   stateDamage;
	unique_ptr<PlayerState>   stateDead;
	unique_ptr<PlayerState>   stateWait;
	unique_ptr<PlayerState>   stateWalk;
	unique_ptr<BossEntryPlayerState>   stateBossEntry;

	
	enum class State
	{
		Attack,//攻撃
		Damage,//ダメージ
		Dead,//死亡
		Wait,//待機
		Walk,//移動
		BossEntry,//ボスの登場
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

	State GetState() { return state; };
	
	//ターゲットがある程度遠かった場合見失う
	void ResetFarTarget(float L);

	MinionManager* GetMinionManager() { return minionManager.get(); };

	//ゲームシーンの設定
	SceneGame* GetSceneGame() { return sceneGame; };

	//プレイヤーのステージリセット処理
	void ResetPlayer();
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
	void RenderTargetHP(const VECTOR2 Pos);
	//目標の敵設定
	void SetTargetEnemy(Actor* enm);
	//プレイヤーの体力表示
	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	
	
	//目標の敵の設定
	bool SetTargetActor();
	//速さ取得
	float GetSpeed() { return speed; };
	//速さ設定
	void SetSpeed(const float speed) { this->speed = speed; };
	//ダメージ
	bool AddDamage(int Damage, int SetinvincibleTime);
};