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


	//AttackMaxLength��艓�������G�̓^�[�Q�b�g�̂ł��Ȃ��B
	const float AttackMaxLength = 50.0f;
	//LossTargetFar��艓�������G�̓^�[�Q�b�g�͌�����
	const float LossTargetFar = 70.0f;
	//�U�����̓X�s�[�h��������
	const float AttackSpeedDown = 0.5f;

	shared_ptr<MinionManager> minionManager;
	//�v���C���[�̓����X�e�[�g�}�V��
	PlayerState* stateMachine;
	//SceneGame�̍X�V
	SceneGame* sceneGame;

	//�S�Ă̍s��
	unique_ptr<PlayerState>   stateAttack;
	unique_ptr<PlayerState>   stateDamage;
	unique_ptr<PlayerState>   stateDead;
	unique_ptr<PlayerState>   stateWait;
	unique_ptr<PlayerState>   stateWalk;
	unique_ptr<BossEntryPlayerState>   stateBossEntry;
public:


	
	enum class State
	{
		ATTACK,//�U��
		DAMAGE,//�_���[�W
		DEAD,//���S
		WAIT,//�ҋ@
		WALK,//�ړ�
		BOSS_ENTRY,//�{�X�̓o��
	};


	State state;

public:
	Player() {};
	~Player() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void ModelRender();
	//���f���p�̕`�揈��
	void Render();
	//�����蔻��f�o�b�O
	void CollisionDebug();
	//�Q�[���V�[���̐ݒ�
	void SetSceneGame(SceneGame* scene);
	//��ԃ}�V���̕ϊ�
	void ChangeState(PlayerState* state);
	void ChangeState(State state, BossStage* stage =nullptr);
	//�^�[�Q�b�g��������x���������ꍇ������
	void ResetFarTarget(float L);

	inline MinionManager* GetMinionManager() { return minionManager.get(); };
	inline State GetState() { return state; };
	//�Q�[���V�[���̐ݒ�
	inline SceneGame* GetSceneGame() { return sceneGame; };

	//�v���C���[�̃X�e�[�W���Z�b�g����
	void ResetPlayer();
	//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
	void SetStatus(string SearchName);

private:

	//============����=================
	//���͏���
	void Input();
	//�v���C���[�̃J�������͏���
	void InputCamera();
	//���͓�������
	void InputMove();
	//���͍U��
	void InputAttack();
	//�~�j�I���̋A�ғ��͏���
	void InputMinionBack();
	//Aim�J�����̎��_�ύX
	bool ChangeCameraAim();
	//�~�j�I���̑h�����͏���
	void InputMinionResuscitation();


	//============�����蔻��==============
	//�����蔻��
	void UpdateCollision();
	//�G�Ƃ̓����蔻��
	void VsEnemy();


	//============�`��==============
	//�J�[�\���̕`��
	void RenderCursur();
	//�ڕW��HP�̕\��
	void RenderTargetHP(const VECTOR2 pos);
	//�ڕW�̓G�ݒ�
	void SetTargetEnemy(Actor* enm);
	//�v���C���[�̗͕̑\��
	void HPRender(const int spriteIndex, const VECTOR2 pos);
	
	
	//�ڕW�̓G�̐ݒ�
	bool SetTargetActor();
	//�����擾
	inline float GetSpeed() { return speed; };
	//�����ݒ�
	inline void SetSpeed(const float speed) { this->speed = speed; };
	//�_���[�W
	bool AddDamage(int damage, int setinvincibleTime);
};