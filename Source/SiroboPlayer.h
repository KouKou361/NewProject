#pragma once

#include "Charactor.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class Player;
class SiroboManager;
class SiroboPlayerAI;
class EnemyManager;
class EnemyBase;
class UISiroboDownHelp;
class ObjectManager;


//�~�j�I��
class Sirobo :public Charactor
{
public:
	enum class Team
	{
		TEAM_PLAYER,//�v���C���[�̒���
		TEAM_ENEMY,//�G�`�[���̒���(�ꉞ�@����Ȃ�����)
		TEAM_NEUTRAL,//����
		TEAM_NONE,
		TEAM_END
	};
	enum class StateType
	{
		TYPE_IDLE,   //�����i�{�[���Ƃ��Ă���j
		TYPE_STAND_BY,//�w���҂��i�U��OK�j
		TYPE_ATTACK, //�U����
		TYPE_BACK,   //�P�ޒ�
		TYPE_THROW,  //������ꒆ
		TYPE_DAMAGE, //�_���[�W��
		TYPE_DEAD,//���S��
		TYPE_RESUSCITATION,//�h������Ă��鎞
		TYPE_NONE,
		TypeEnd,
	};
private:
	shared_ptr<SiroboPlayerAI> ai=nullptr;
	shared_ptr<UISiroboDownHelp> uiSiroboDownHelp = nullptr;

	SiroboManager* manager=nullptr;
	Player* pl=nullptr;
	int index = 0;//�����̔ԍ�
	Team team= Team::TEAM_NONE;//�`�[��
	StateType state= StateType::TYPE_NONE;//�����̏��
	bool attackStandBy=false;//�U���\�ȏ��



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
	void HPRender(const int &SpriteIndex, const VECTOR2& Pos);
	//Sprite�̕`��
	void Render();
	//�����̔ԍ�
	void SetIndex(const int& index) { this->index = index; }
	int GetIndx() { return index; }

	Player* GetPlayer() { return pl; }
	//�}�l�[�W���[�̎擾
	SiroboManager* GetManager() { return manager; };
	void SetManager(SiroboManager* manager) { this->manager = manager; }
	//�`�[��
	void SetTeam(Team team) { this->team = static_cast<Team>(team); };
	Team GetTeam() { return team; };
	//�����̏��
	void SetState(StateType type) { this->state = static_cast<StateType>(type); };
	StateType GetState() { return state; };
	//�U���\�ȏ��
	void SetAttackStandBy(bool flg) { attackStandBy = flg; }
	bool GetAttackStandBy() { return attackStandBy; }
	//Ai�̒T�������Z�b�g����
	void ResetNode();
	//�h���X�e�[�g�ϊ�����
	void SetResuscitation();
	//�h�������ǂ���
	bool IsResuscitation();

	//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
	void SetStatus(const string& SearchName);

	//���ԂɂȂ�͈�
	const float FollowSerchL = 20.0f;
	//�v���C���[�͈̔�
	const float StandBySerchL = 7.0f;


	const float MaxAttackCoolTime = 0;

private:
	//�A�j���[�V�����̓o�^
	void RegisterAnimetion();

	//�_�E����Ԃ̃w���v�A�C�R���̍쐬
	void CreateDownHelpUI();
public:
	//��������
	float resuscitationTime = 0;

	bool resuscitationFlg = false;
};

//�~�j�I���Ǘ��N���X
class SiroboManager :public Manager
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
	void Register(shared_ptr<Sirobo> enm);
	//�j������
	void Destroy(Sirobo* enm);
	//�����蔻��f�o�b�O
	void CollisionDebug();
	//�~�j�I���̐��̎擾
	int GetSiroboSize() { return static_cast<int>(sirobos.size()); }
	//�~�j�I���̐��̎擾
	Sirobo* GetSiroboIndex(const int& index) { return sirobos.at(index).get(); }
	//�~�j�I���̍U��OK�s���̂ݍU������
	void OneAttack(Sirobo* sirobo);
	//�~�j�I���̋A��
	void AllBack();
	//�V���{�B�̏�ԃ^�C�v�̐���Ԃ�
	int GetTypeSiroboSize(const Sirobo::StateType type);

	void SetEnemyManager(EnemyManager* manager) { this->enemyManager = manager; }
	EnemyManager* GetEnemyManager() { return enemyManager; }

	void SetObjectManager(ObjectManager* manager) { this->objectManager = manager; }
	ObjectManager* GetObjectManager() { return objectManager; }

private:
	EnemyManager* enemyManager = nullptr;
	ObjectManager* objectManager = nullptr;
	vector<shared_ptr<Sirobo>>sirobos;
	vector<shared_ptr<Sirobo>>remove;
	Charactor* Target;
	//�~�j�I�������̔ԍ����ӂ邽�߂̕ϐ�
	int indexSirobo =0;


};
