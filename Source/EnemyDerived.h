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

private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
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
private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
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
private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
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
private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
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
private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
};

//�g���[�j���O�_�~�[
class EnemyDummy :public EnemyBase
{
public:
	EnemyDummy(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyDummy() {};

	//����������
	void Init();
private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
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



private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//���ʂ̒ǉ�
	void AddSite(string setSiteName);
	//�����q�I�u�W�F�N�g�����S���Ă���Ȃ�
	void CheakChildrenDie();
	//���ʒB�̈ʒu�X�V����
	void UpdateAllSiteSetPosition();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();

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
	bool AddDamage(int damage, float setinvincibleTime);
	
	//���ʂ����閼�O
	string siteName;
private:
	//�A�j���V�����ݒ�
	void SetAnimetion();
	//behaviorTree�̐ݒ�
	void SetBehaviorTree();
};








