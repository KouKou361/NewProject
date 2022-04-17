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
	//�⊮�p�i�����_�j
	VECTOR3 startTargetPos;
	VECTOR3 endTargetPos;
	//�⊮�p�i���_�j
	VECTOR3 startEyePos;
	VECTOR3 endEyePos;
	//�J�������
	VECTOR3 targetPos = { 0,0,0 };
	VECTOR3 eye = { 0,0,0 };
	VECTOR3 angle = { 0,0,0 };
	//�J�����̎�����
	Actor* owner = nullptr;
	CameraManager* manager = nullptr;
	//�ڕW�̃L����
	Actor* targetChara = nullptr;


public:
	Camera() {}
	~Camera() {};

	//����������
	virtual void Init()=0;
	//�X�V����
	virtual void Update() = 0;
	//���_�ʒu�����߂�X�V
	virtual void UpdateEye() = 0;
	//�����_�����߂�X�V
	virtual void UpdateTarget() = 0;
	//���_�ړ��X�V����
	virtual bool LerpCameraUpdate();
	//�I������
	virtual void End() = 0;
	//Imgui
	virtual void Imgui()=0;
	//�J�����̒����_�ړ�(�⊮)
	bool LerpTargetCamera(const float time);
	//���C�s�b�N
	void RayPick();
	//�J�����̎��_�ړ�(�⊮)
	bool LerpEyeCamera(const float time);
	inline void SetTarget(const VECTOR3 TargetPos) { this->targetPos = TargetPos; };
	inline void SetOnwer(Actor* owner) { this->owner = owner; };
	inline Actor* GetActor() { return targetChara; }
	inline void SetActor(Actor* Actor) {targetChara=Actor; }
};

//�ʏ탂�[�h �R���g���[���[�ŃJ�����̎��_��ς���
class CameraNormal:public Camera
{

public:
	CameraNormal() {}
	CameraNormal(Actor* owner);
	//����������
    void Init();
	//�X�V����
	void Update();
	//�I������
	void End();
	//Imgui
	void Imgui();
	//���_�ʒu�����߂�X�V
	void UpdateEye();
	//�����_�����߂�X�V
	void UpdateTarget();
};

//Aim���[�h �_��������J����
class CameraAim :public Camera
{
private:

	//�؂�ւ����̕ۑ��p�J����
	VECTOR3 saveAngle = { 0,0,0 };
	//�G�}�l�[�W���[
	EnemyManager* enemyManager = nullptr;

	//���͕s�^�C�}�[
	int keyTimer = 0;
public:
	CameraAim() {};
	CameraAim(Actor* owner, Actor* targetChara, EnemyManager* enemyManager);
	void ChangeTargetChara();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�I������
	void End();
	//Imgui
	void Imgui();

	//���_�ʒu�����߂�X�V
	void UpdateEye();
	//�����_�����߂�X�V
	void UpdateTarget();
};

//BOSS���o�p�J����
class CameraBossEntry :public Camera
{
private:
	float lookAtOwnerTimer = 0.0f;
	BossStage* state=nullptr;
	EnemyBase* enm = nullptr;
public:
	CameraBossEntry() {}
	CameraBossEntry(Actor* owner, EnemyBase* enm, BossStage* stage);
	//����������
	void Init();
	//�X�V����
	void Update();
	//�I������
	void End();
	//Imgui
	void Imgui();
	//���_�ʒu�����߂�X�V
	void UpdateEye();
	//�����_�����߂�X�V
	void UpdateTarget();

	//Owner�̕��Ɍ����Ă���
	bool LookatOwner();
	//�G�̕����Ɍ���
	bool LookatOwnerFront();
	//�{�X������
	bool LookatBoss();
	//�{�X����J�����������
	bool BackCamera();
};


//�J�����Ǘ��N���X
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
	//�J�����̖ڕW�̃L�����N�^�[�̃Z�b�g
	inline Actor* GetTargetChractor() {return currentCamera->GetActor(); }
	inline void SetTarget(const VECTOR3 targetPos) { currentCamera->SetTarget(targetPos); };
	inline void SetOwner(Actor* owner) { currentCamera->SetOnwer(owner); };
	void ChangeCamera(Camera* newScene);
	void ChangeCamera(Camera* newScene,const VECTOR3 cameraPos);
	inline void SetEnemyManager(EnemyManager* enemyManager) { this->enemyManager = enemyManager; }
};
