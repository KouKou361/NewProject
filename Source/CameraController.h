#pragma once
#include "Lib.h"
class Actor;
class CameraManager;
class EnemyManager;
class Player;
class BossStage;
enum class EventState;
class EnemyBase;

class Camera
{
	friend class CameraManager;
protected:
	float lerpSpeed = 0.02f;
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
	//視点移動更新処理
	virtual bool LerpCameraUpdate();
	//終了処理
	virtual void End() = 0;
	//Imgui
	virtual void Imgui()=0;
	//カメラの注視点移動(補完)
	bool LerpTargetCamera(const float time);
	//レイピック
	void RayPick();
	//カメラの視点移動(補完)
	bool LerpEyeCamera(const float time);
	inline void SetTarget(const VECTOR3 TargetPos) { this->targetPos = TargetPos; };
	inline void SetOnwer(Actor* owner) { this->owner = owner; };
	inline Actor* GetActor() { return targetChara; }
	inline void SetActor(Actor* Actor) {targetChara=Actor; }
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
	void ChangeTargetChara();
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

	EnemyManager* enemyManager;
	std::unique_ptr<Camera> currentCamera = nullptr;


public:
	enum  CameraType
	{
		TYPE_NORMAL,
		TYPE_AIM,
		TYPE_BOSS,
		TYPE_END
	};
	CameraType cameraType;
	CameraManager() {};
	~CameraManager() {};
	void Init(Actor* ower);
	void Update();
	void End();
	void Imgui();
	inline CameraType GetNowType() { return cameraType; }
	//カメラの目標のキャラクターのセット
	inline Actor* GetTargetChractor() {return currentCamera->GetActor(); }
	inline void SetTarget(const VECTOR3 targetPos) { currentCamera->SetTarget(targetPos); };
	inline void SetOwner(Actor* owner) { currentCamera->SetOnwer(owner); };
	void ChangeCamera(Camera* newScene);
	void ChangeCamera(Camera* newScene,const VECTOR3 cameraPos);
	inline void SetEnemyManager(EnemyManager* enemyManager) { this->enemyManager = enemyManager; }
};
