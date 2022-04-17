#pragma once

#include "Charactor.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class Player;
class MinionManager;
class MinionPlayerAI;
class EnemyManager;
class EnemyBase;
class UIMinionDownHelp;
class ObjectManager;


//�~�j�I��
class MinionPlayer :public Charactor
{
public:
	enum Team
	{
		TEAM_PLAYER,//�v���C���[�̒���
		TEAM_ENEMY,//�G�`�[���̒���(�ꉞ�@����Ȃ�����)
		TEAM_NEUTRAL,//����
		TEAM_END
	};
	enum StateType
	{
		TYPE_IDLE,   //�����i�{�[���Ƃ��Ă���j
		TYPE_STAND_BY,//�w���҂��i�U��OK�j
		TYPE_ATTACK, //�U����
		TYPE_BACK,   //�P�ޒ�
		TYPE_THROW,  //������ꒆ
		TYPE_DAMAGE, //�_���[�W��
		TYPE_DEAD,//���S��
		TYPE_RESUSCITATION,//�h������Ă��鎞
		TypeEnd,
	};
private:
	shared_ptr<MinionPlayerAI> Ai=nullptr;
	shared_ptr<UIMinionDownHelp> uiMinionDownHelp = nullptr;

	MinionManager* manager=nullptr;
	Player* pl=nullptr;
	int index = 0;//�����̔ԍ�
	Team team;//�`�[��
	StateType state;//�����̏��
	bool AttackStandBy=false;//�U���\�ȏ��



public:
	//����������
	void Init(Player* pl);
	//�X�V����
	void Update();
	//���Ԃɉ����
	void Join();
	//�폜
	void Destroy();
	//HP�̕\��
	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	//Sprite�̕`��
	void Render();
	//�����̔ԍ�
	void SetIndex(int index) { this->index = index; }
	int GetIndx() { return index; }

	Player* GetPlayer() { return pl; }
	//�}�l�[�W���[�̎擾
	MinionManager* GetManager() { return manager; };
	void SetManager(MinionManager* manager) { this->manager = manager; }
	//�`�[��
	void SetTeam(Team team) { this->team = team; };
	Team GetTeam() { return team; };
	//�����̏��
	void SetState(StateType type) { this->state = type; };
	StateType GetState() { return state; };
	//�U���\�ȏ��
	void SetAttackStandBy(bool flg) { AttackStandBy = flg; }
	bool GetAttackStandBy() { return AttackStandBy; }
	//Ai�̒T�������Z�b�g����
	void ResetNode();
	//�h���X�e�[�g�ϊ�����
	void SetResuscitation();
	//�h�������ǂ���
	bool IsResuscitation();
	//

	//���ԂɂȂ�͈�
	const float FollowSerchL = 20.0f;
	//�v���C���[�͈̔�
	const float StandBySerchL = 7.0f;


	const int MaxAttackCoolTime = 0;
public:
	//��������
	int ResuscitationTime = 0;

	bool ResuscitationFlg = false;
};

//�~�j�I���Ǘ��N���X
class MinionManager :public Manager
{
public:
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//���f���`�揈��
	void ModelRender();
	//�S�폜
	void Clear();
	//�o�^
	void Register(shared_ptr<MinionPlayer> enm);
	//�j������
	void Destroy(MinionPlayer* enm);
	//�����蔻��f�o�b�O
	void CollisionDebug();
	//�~�j�I���̐��̎擾
	int GetMinionsSize() { return minions.size(); }
	//�~�j�I���̐��̎擾
	MinionPlayer* GetMinionIndex(const int& index) { return minions.at(index).get(); }
	//�~�j�I���̍U��OK�s���̂ݍU������
	void OneAttack(MinionPlayer* minion);
	//�~�j�I���̋A��
	void AllBack();

	void SetEnemyManager(EnemyManager* manager) { this->enemyManager = manager; }
	EnemyManager* GetEnemyManager() { return enemyManager; }

	void SetObjectManager(ObjectManager* manager) { this->objectManager = manager; }
	ObjectManager* GetObjectManager() { return objectManager; }

private:
	EnemyManager* enemyManager = nullptr;
	ObjectManager* objectManager = nullptr;
	vector<shared_ptr<MinionPlayer>>minions;
	vector<shared_ptr<MinionPlayer>>remove;
	Charactor* Target;
	//�~�j�I�������̔ԍ����ӂ邽�߂̕ϐ�
	int IndexMinion=0;


};
