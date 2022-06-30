#pragma once
#include "Lib.h"
class Actor;
class CameraManager;
class EnemyManager;
class Player;
class BossStage;
enum class EventState;
class EnemyBase;

//カメラの基底クラス
class Camera
{
	friend class CameraManager;
protected:
	//補完用（注視点）
	VECTOR3 startTargetPos;
	VECTOR3 endTargetPos;
	//補完用（視点）
	VECTOR3 startEyePos;
	VECTOR3 endEyePos;
	//カメラ情報
	VECTOR3 targetPos = { 0,0,0 };
	VECTOR3 eye = { 0,0,0 };
	VECTOR3 angle = { 0,0,0 };
	//カメラの持ち主
	Actor* owner = nullptr;
	CameraManager* manager = nullptr;
	//目標のキャラ
	Actor* targetChara = nullptr;

	//振動時間
	float vibrationTime = 0.0f;
	//振動ボリューム
	float vibrationVolume = 0.0f;


public:
	Camera() {}
	~Camera() {};

	//初期化処理
	virtual void Init()=0;
	//更新処理
	virtual void Update() = 0;
	//視点位置を決める更新
	virtual void UpdateEye() = 0;
	//注視点を決める更新
	virtual void UpdateTarget() = 0;
	//終了処理
	virtual void End() = 0;
	//Imgui
	virtual void Imgui()=0;
	//カメラの注視点移動(補完)
	bool LerpTargetCamera(const float time);
	//カメラの視点移動(補完)
	bool LerpEyeCamera(const float time);

	//振動
	void SetVibration(const float volume, const float time);
	//振動更新処理
	void VibrationUpdate();


	inline void SetTarget(const VECTOR3& targetPos) { this->targetPos = targetPos; };
	inline void SetOnwer(Actor* owner) { this->owner = owner; };
	inline Actor* GetActor() { return targetChara; }
	inline void SetActor(Actor* Actor) {targetChara=Actor; }
private:
	//長さを取得
	float GetLength(const VECTOR3 startPos, const VECTOR3 endPos);
	//カメラの線上補完
	bool LerpCamera(VECTOR3& outpos, const VECTOR3 startPos, const VECTOR3 &endPos,const float &minL,const float &time);
};

//通常モード コントローラーでカメラの視点を変える
class CameraNormal:public Camera
{

public:
	CameraNormal() {}
	CameraNormal(Actor* owner);
	//初期化処理
    void Init();
	//更新処理
	void Update();
	//終了処理
	void End();
	//Imgui
	void Imgui();
	//視点位置を決める更新
	void UpdateEye();
	//注視点を決める更新
	void UpdateTarget();
};

//Aimモード 狙いをつけるカメラ
class CameraAim :public Camera
{
private:

	//切り替え時の保存用カメラ
	VECTOR3 saveAngle = { 0,0,0 };
	//敵マネージャー
	EnemyManager* enemyManager = nullptr;

	//入力不可タイマー
	int keyTimer = 0;
public:
	CameraAim() {};
	CameraAim(Actor* owner, Actor* targetChara, EnemyManager* enemyManager);
	//void ChangeTargetChara();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//終了処理
	void End();
	//Imgui
	void Imgui();

	//視点位置を決める更新
	void UpdateEye();
	//注視点を決める更新
	void UpdateTarget();

private:
	//エイムカメラのキャンセル
	void CanselCamera();
};

//BOSS演出用カメラ
class CameraBossEntry :public Camera
{
private:
	float lookAtOwnerTimer = 0.0f;
	BossStage* state=nullptr;
	EnemyBase* enm = nullptr;
public:
	CameraBossEntry() {}
	CameraBossEntry(Actor* owner, EnemyBase* enm, BossStage* stage);
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//終了処理
	void End();
	//Imgui
	void Imgui();
	//視点位置を決める更新
	void UpdateEye();
	//注視点を決める更新
	void UpdateTarget();


	//Ownerの方に向いておく
	bool LookatOwner();
	//敵の方向に向く
	bool LookatOwnerFront();
	//ボスを見る
	bool LookatBoss();
	//ボスからカメラが離れる
	bool BackCamera();
};


//カメラ管理クラス
class CameraManager
{
	friend Camera;

private:

	EnemyManager* enemyManager=nullptr;
	std::unique_ptr<Camera> currentCamera = nullptr;


public:
	enum class CameraType
	{
		TYPE_NORMAL,
		TYPE_AIM,
		TYPE_BOSS,
		TYPE_NONE,
		TYPE_END,
	};
	CameraType cameraType=static_cast<CameraType>(CameraType::TYPE_NONE);
	CameraManager() {};
	~CameraManager() {};
	//初期化
	void Init(Actor* ower);
	//更新処理
	void Update();
	//カメラが切り替わった時の後始末処理
	void End();
	//デバッグ
	void Imgui();
	//カメラの切り替え
	void ChangeCamera(Camera* newScene);
	//カメラの切り替え（Pos指定あり）
	void ChangeCamera(Camera* newScene, const VECTOR3 cameraPos);
	//振動
	void SetVibration(const float volume, const float time);

	inline CameraType GetNowType() { return static_cast<CameraType>(cameraType); }
	//カメラの目標のキャラクターのセット
	inline Actor* GetTargetChractor() {return currentCamera->GetActor(); }
	inline void SetTarget(const VECTOR3 targetPos) { currentCamera->SetTarget(targetPos); };
	inline void SetOwner(Actor* owner) { currentCamera->SetOnwer(owner); };

	inline void SetEnemyManager(EnemyManager* enemyManager) { this->enemyManager = enemyManager; }
};
