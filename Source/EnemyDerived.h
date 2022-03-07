#pragma once
class EnemyBase;
class EnemyManager;
class SceneGame;
//�X���C���G
class EnemySlime :public EnemyBase
{
public:
	EnemySlime(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemySlime() { };

	//����������
	void Init();
};

//�T�G
class EnemyTurtleShell :public EnemyBase
{

public:
	EnemyTurtleShell(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyTurtleShell() {};

	//����������
	void Init();
};

//���V�G
class EnemyBeholder :public EnemyBase
{
public:
	EnemyBeholder(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBeholder() {};

	//����������
	void Init();
};

//�󔠓G
class EnemyChest :public EnemyBase
{
public:
	EnemyChest(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyChest() {};

	//����������
	void Init();
};

//���e�G
class EnemyBoom :public EnemyBase
{
public:
	EnemyBoom(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBoom() {};

	//����������
	void Init();
};

//���e�G
class EnemyDummy :public EnemyBase
{
public:
	EnemyDummy(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyDummy() {};

	//����������
	void Init();
};

//�{�X�G
class EnemyBoss :public EnemyBase
{
private:

public:
	EnemyBoss(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBoss() {};

	//����������
	void Init();

	void Update();

	void TargetComplete();

	//�`�揈��
	void ModelRender();

	//�����q�I�u�W�F�N�g�����S���Ă���Ȃ�
	void CheakChildrenDie();
};

//���e�G
class EnemySite :public EnemyBase
{
public:
	EnemySite(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemySite() {};

	//����������
	void Init();

	//�X�V����
	void Update();



	//�_���[�W�𔻒�
	bool AddDamage(int Damage, int SetinvincibleTime);
};








