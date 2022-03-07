#pragma once
#include "Charactor.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
class SceneGame;
class UIMinionAttack;
enum TargetFlg
{
	Complete,
	Failed,
};

enum class EnemyTag
{
	None,
	Boom,
	BossSite,
	Boss,
	Cheast,
	Dummy,
	Slime,
	TurtleShell,
	End,
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

	float GetSearchL() { return searchL; }
	float GetAttackL() { return attackL; }
	float GetAttackRadius() { return attackRadius; }

	//���S���Ԏ擾
	int  GetDeathTime() { return DeathTime; }
	//���S���Ԑݒ�
	void SetDeathTime(const float time) { this->DeathTime = time; }
	//���S���Ԃ̍X�V
	bool UpdateDeathTime();
	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	void ResetNode();
	string GetAttackNode() { return AttackNode; }

	bool AddDamage(int Damage, int MaxinvincibleTime = 0);

	bool GetOldDamageFlg() { return oldDamageFlg; }
	void ActionBehaviorTree();

	virtual void TargetComplete();
	void TargetFaild();

	//�s���J�n����(�s�������邩�ǂ���)
	void SetActionFlg(bool flg) { actionFlg = flg; }


	SceneGame* GetSceneGame() { return sceneGame; };

	TargetFlg GetTargetFlg() { return targetFlg; }
	EnemyBase* parent;//�e�ݒ�

	EnemyTag GetEnemyTag() { return enemyType; };
	void SetEnemyTag(EnemyTag tag) { enemyType = tag; };

protected:
	TargetFlg targetFlg = TargetFlg::Complete;
	EnemyTag enemyType = EnemyTag::None;

	//���G�͈�
	float searchL = 60.0f;
	float attackL = 4.0f;
	float attackRadius = 4.0f;
	string AttackNode;
	float DeathTime = 0;
	
	NodeBase* ActionNode=nullptr;
	unique_ptr<BehaviorTree> behaviorTree=nullptr;
	unique_ptr<BehaviorData> behaviordata=nullptr;
	SceneGame* sceneGame = nullptr;

	//�ߋ��Ƀ_���[�W���󂯂����ǂ���
	bool oldDamageFlg = false;
	bool actionFlg = true;

	std::vector<EnemyBase*> children;


};
