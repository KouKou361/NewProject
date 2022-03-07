#pragma once
class Player;
class BossStage;

//�v���C���[�̃X�e�[�g�}�V��(���N���X)
class PlayerState
{
public:
	PlayerState() {};
	~PlayerState() {};

	//������
	virtual void Start(Player* pl)=0;
	//�X�V
	virtual void Run(Player*pl) = 0;
	//�I��
	virtual void End(Player* pl) = 0;
};

//�v���C���[�̍U���N���X
class AttackState:public PlayerState
{
private:
	//�U���t���O�i��x�ɑ�R�̏o�Ăق����Ȃ����߁j
	bool AttackFlg=false;
	//�U���A�j���[�V�����̃^�C�~���O
	const float AttackTimeRate = 0.5f;
public:
	AttackState() {};
	~AttackState() {};

	//������
	void Start(Player* pl);
	//�X�V
	void Run(Player* pl);
	//�I��
	void End(Player* pl);
private:
	void DownSpeed(Player* pl);
};

//�v���C���[�̃_���[�W�N���X
class DamageState :public PlayerState
{
public:
	DamageState() {};
	~DamageState() {};
private:
	//������
	void Start(Player* pl);
	//�X�V
	void Run(Player* pl);
	//�I��
	void End(Player* pl);
};

//�v���C���[�̎��S�N���X
class DeadState :public PlayerState
{
public:
	DeadState() {};
	~DeadState() {};

	//������
	void Start(Player* pl);
	//�X�V
	void Run(Player* pl);
	//�I��
	void End(Player* pl);
};


//�v���C���[�̑ҋ@�N���X
class WaitState :public PlayerState
{
public:
	WaitState() {};
	~WaitState() {};

	//������
	void Start(Player* pl);
	//�X�V
	void Run(Player* pl);
	//�I��
	void End(Player* pl);
};

//�v���C���[�̈ړ��N���X
class WalkState :public PlayerState
{
public:
	WalkState() {};
	~WalkState() {};

	//������
	void Start(Player* pl);
	//�X�V
	void Run(Player* pl);
	//�I��
	void End(Player* pl);
};


//�v���C���[�̃{�X��o�ꉉ�o�N���X
class BossEntryPlayerState :public PlayerState
{
	BossStage* stage = nullptr;
public:
	BossEntryPlayerState() {};
	~BossEntryPlayerState() {};

	void SetState(BossStage* stage) { this->stage = stage; }
	
	//������
	void Start(Player* pl);
	//�X�V
	void Run(Player* pl);
	//�I��
	void End(Player* pl);
};




