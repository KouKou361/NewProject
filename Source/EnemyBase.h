#pragma once
#include "Charactor.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
class SceneGame;
class UISiroboAttack;
enum class TargetFlg
{
	COMPLETE,
	FAILED,
};

enum class EnemyTag
{
	NONE,
	BOMB,
	BOSS_SITE,
	BOSS,
	CHEAST,
	DUMMY_ENEMY,
	SLIME,
	TURTLESHELL,
	END,
};

class EnemyBase :public Charactor
{
public:
	EnemyBase(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	EnemyBase() {}
	virtual ~EnemyBase() {};
public:
	//����������
	virtual void Init()=0;
	//�X�V����
	void Update();
	//�o�H�T��
	void RouteSearch(VECTOR3& target);
	//ImGui�̃f�o�b�O
	void ImguiDebug();
	//�폜
	void Destroy();
	//����������p���ɓ����Ă��邩�ǂ���
	//�w�肳�ꂽ����p���ɂ��邩�ǂ���(���_�ʒu,���_�̃x�N�g��,����p)
	bool IsDotAngle(const VECTOR3& pos,const VECTOR3& vec,const float& angle);
	//�t���O�����Ă��Ȃ����m�F
	void FlgCheak();
	//�����蔻��
	void AttackCircleNode(const string& nodeName, const float& circleL, const float& startTime, const float& EndTime);
	void AttackCircle(const VECTOR3& pos, const float& circleL);

	inline void SetDamageFlg(const bool flg) { damageFlg = flg; };
	inline void SetDeadFlg(const bool flg) { deadFlg = flg; }; 

	void HPRender(const int &spriteIndex, const VECTOR2& pos);
	
	//���G�͈͂�Target�������TRUE��Ԃ�
	bool SearchTarget(const float &l);

	bool VsTargetAttackCircle(const VECTOR3& pos, const float& radius);



	//���S���Ԃ̍X�V
	bool UpdateDeathTime();
	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	void ResetNode();

	bool AddDamage(const int damage, const float setInvincibleTime=0);

	//�r�w�C�r�A�c���[�̍s������
	void ActionBehaviorTree();

	virtual void TargetComplete();
	void TargetFaild();

	//�s���J�n����(�s�������邩�ǂ���)
	inline void SetActionFlg(const bool flg) { actionFlg = flg; }


	inline SceneGame* GetSceneGame() { return sceneGame; };

	inline TargetFlg GetTargetFlg() { return targetFlg; }

	//���S���Ԏ擾
	inline float  GetDeathTime() { return deathTime; }
	inline void SetDeathTime(const float time) { this->deathTime = time; }

	inline string GetAttackNode() { return attackNode; }
	inline bool GetOldDamageFlg() { return oldDamageFlg; }

	inline EnemyTag GetEnemyTag() { return enemyType; };
	inline void SetEnemyTag(const EnemyTag& tag) { enemyType = tag; };

	inline float GetSearchL() { return searchL; }
	inline float GetAttackL() { return attackL; }
	inline float GetAttackRadius() { return attackRadius; }
	inline int GetExpNum() { return ExpNum; }
protected:
	//�A�j���V�����ݒ�
	virtual void SetAnimetion() = 0;
	//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
	void SetStatus(const string& searchName);
	//behaviorTree�̐ݒ�
	virtual void SetBehaviorTree()=0;
public:
	EnemyBase* parent=nullptr;//�e�ݒ�
protected:
	TargetFlg targetFlg = TargetFlg::COMPLETE;
	EnemyTag enemyType = EnemyTag::NONE;

	//���G�͈�
	float searchL = 60.0f;
	float attackL = 4.0f;
	float attackRadius = 4.0f;
	float deathTime = 0;
	string attackNode="";

	
	NodeBase* actionNode=nullptr;
	unique_ptr<BehaviorTree> behaviorTree=nullptr;
	unique_ptr<BehaviorData> behaviordata=nullptr;
	SceneGame* sceneGame = nullptr;

	//�ߋ��Ƀ_���[�W���󂯂����ǂ���
	bool oldDamageFlg = false;
	bool actionFlg = true;

	//�o���l�̐�
	int ExpNum = 5;

	std::vector<EnemyBase*> children;


};
