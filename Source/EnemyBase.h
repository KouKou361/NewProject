#pragma once
#include "Charactor.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
class SceneGame;
class UIMinionAttack;
enum TargetFlg
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
	void Init();
	//�X�V����
	void Update();
	//�o�H�T��
	void RouteSearch(VECTOR3& Target);
	//ImGui�̃f�o�b�O
	void ImguiDebug();
	//�폜
	void Destroy();
	//����������p���ɓ����Ă��邩�ǂ���
	//�w�肳�ꂽ����p���ɂ��邩�ǂ���(���_�ʒu,���_�̃x�N�g��,����p)
	bool IsDotAngle(const VECTOR3 Pos,const VECTOR3 vec,const float Angle);
	//�t���O�����Ă��Ȃ����m�F
	void FlgCheak();
	//�����蔻��
	void AttackCircleNode(string nodeName,float circleL,float startTime, float EndTime);
	void AttackCircle(VECTOR3 pos, float circleL);

	void SetDamageFlg(bool flg)override;
	void SetDeadFlg(bool flg)override;

	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	
	//���G�͈͂�Target�������TRUE��Ԃ�
	bool SearchTarget(float L);

	bool VsTargetAttackCircle(VECTOR3 Pos, float Radius);
	//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
	void SetStatus(string SearchName);


	//���S���Ԃ̍X�V
	bool UpdateDeathTime();
	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	void ResetNode();

	bool AddDamage(int Damage, int MaxinvincibleTime = 0);


	void ActionBehaviorTree();

	virtual void TargetComplete();
	void TargetFaild();

	//�s���J�n����(�s�������邩�ǂ���)
	inline void SetActionFlg(const bool flg) { actionFlg = flg; }


	inline SceneGame* GetSceneGame() { return sceneGame; };

	inline TargetFlg GetTargetFlg() { return targetFlg; }

	//���S���Ԏ擾
	inline int  GetDeathTime() { return deathTime; }
	inline void SetDeathTime(const float time) { this->deathTime = time; }

	inline string GetAttackNode() { return attackNode; }
	inline bool GetOldDamageFlg() { return oldDamageFlg; }

	inline EnemyTag GetEnemyTag() { return enemyType; };
	inline void SetEnemyTag(const EnemyTag tag) { enemyType = tag; };

	inline float GetSearchL() { return searchL; }
	inline float GetAttackL() { return attackL; }
	inline float GetAttackRadius() { return attackRadius; }
public:
	EnemyBase* parent;//�e�ݒ�
protected:
	TargetFlg targetFlg = TargetFlg::COMPLETE;
	EnemyTag enemyType = EnemyTag::NONE;

	//���G�͈�
	float searchL = 60.0f;
	float attackL = 4.0f;
	float attackRadius = 4.0f;
	string attackNode;
	float deathTime = 0;
	
	NodeBase* actionNode=nullptr;
	unique_ptr<BehaviorTree> behaviorTree=nullptr;
	unique_ptr<BehaviorData> behaviordata=nullptr;
	SceneGame* sceneGame = nullptr;

	//�ߋ��Ƀ_���[�W���󂯂����ǂ���
	bool oldDamageFlg = false;
	bool actionFlg = true;

	std::vector<EnemyBase*> children;


};
