#pragma once
#include "Lib.h"
class Actor;
class CameraManager;
class EnemyManager;
class Player;
class BossStage;
enum class EventState;
class EnemyBase;

//�J�����̊��N���X
class Camera
{
	friend class CameraManager;
protected:
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

	//�U������
	float vibrationTime = 0.0f;
	//�U���{�����[��
	float vibrationVolume = 0.0f;


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
	//�I������
	virtual void End() = 0;
	//Imgui
	virtual void Imgui()=0;
	//�J�����̒����_�ړ�(�⊮)
	bool LerpTargetCamera(const float time);
	//�J�����̎��_�ړ�(�⊮)
	bool LerpEyeCamera(const float time);

	//�U��
	void SetVibration(const float volume, const float time);
	//�U���X�V����
	void VibrationUpdate();


	inline void SetTarget(const VECTOR3& targetPos) { this->targetPos = targetPos; };
	inline void SetOnwer(Actor* owner) { this->owner = owner; };
	inline Actor* GetActor() { return targetChara; }
	inline void SetActor(Actor* Actor) {targetChara=Actor; }
private:
	//�������擾
	float GetLength(const VECTOR3 startPos, const VECTOR3 endPos);
	//�J�����̐���⊮
	bool LerpCamera(VECTOR3& outpos, const VECTOR3 startPos, const VECTOR3 &endPos,const float &minL,const float &time);
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
	//void ChangeTargetChara();
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

private:
	//�G�C���J�����̃L�����Z��
	void CanselCamera();
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
	//������
	void Init(Actor* ower);
	//�X�V����
	void Update();
	//�J�������؂�ւ�������̌�n������
	void End();
	//�f�o�b�O
	void Imgui();
	//�J�����̐؂�ւ�
	void ChangeCamera(Camera* newScene);
	//�J�����̐؂�ւ��iPos�w�肠��j
	void ChangeCamera(Camera* newScene, const VECTOR3 cameraPos);
	//�U��
	void SetVibration(const float volume, const float time);

	inline CameraType GetNowType() { return static_cast<CameraType>(cameraType); }
	//�J�����̖ڕW�̃L�����N�^�[�̃Z�b�g
	inline Actor* GetTargetChractor() {return currentCamera->GetActor(); }
	inline void SetTarget(const VECTOR3 targetPos) { currentCamera->SetTarget(targetPos); };
	inline void SetOwner(Actor* owner) { currentCamera->SetOnwer(owner); };

	inline void SetEnemyManager(EnemyManager* enemyManager) { this->enemyManager = enemyManager; }
};
