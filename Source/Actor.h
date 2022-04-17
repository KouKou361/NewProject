#pragma once
#include "Lib.h"
//�I�u�W�F�N�g�̃^�C�v
enum ObjectTag
{
	TAG_PLAYER,
	TAG_MINION,
	TAG_OBJECT,
	TAG_ENEMY,
};
class MinionPlayer;
class Actor
{
private:
	friend class Charactor;
private:
	//Quaternion��Private�Ȃ̂�Set�֐���K���o�R���Ăق�������
	VECTOR4 quaternion;

	VECTOR3 front;
	VECTOR3 right;
	VECTOR3 up;

	VECTOR3 pos;
	VECTOR3 scale;

	//���f���̔ԍ�
	int modelIndex=-1;
	//�_���[�W�󂯂����̖��G����
	int maxInvincibleTime = 0;
	//�I�u�W�F�N�g�̎��
	ObjectTag tag;
	

protected:
	float weight = 1.0f;//�d��
	float collisionRadius = 1.0f;//���a

	int hp = 1;
	int maxHp = 1;
protected:
	int numBeAttacked = 0;//�U������Ă���~�j�I���̐�
	int maxBeAttacked = 5;//�U������Ă���~�j�I���̍ő吔

public:
	//�U������Ă���~�j�I��
	vector<MinionPlayer*> AttackMinions;

public:
	Actor() {};
	~Actor();

	//HP�֌W
	inline int  GetHp() { return hp; }
	inline void SetHp(const int setHp) { hp = setHp; }
	inline int  GetMaxHp() { return maxHp; }
	inline void SetMaxHp(const int setHp) { maxHp = setHp; }

	//HP�̕\��
	virtual void HPRender(const int spriteIndex, const VECTOR2 pos)=0;

	void SetModel(int modelIndex);
	int GetModel() { return modelIndex; }
	void DeleteModel();

	void AttackMinionErase(MinionPlayer* minion);

	void SetQuaternion(const VECTOR4& quaternion);
	inline VECTOR4 GetQuaternion() { return quaternion; }
	inline VECTOR3 GetFront() { return front; }
	inline VECTOR3 GetRight() { return right; }
	inline VECTOR3 GetUp() { return up; }
	
	inline VECTOR3 GetPos() { return pos; };
	inline void SetPos(const VECTOR3 pos) { this->pos = pos; };
	inline VECTOR3 GetScale() { return scale; };
	inline void SetScale(const VECTOR3 scale) { this->scale = scale; };
	virtual bool AddDamage(const int damage, const int maxinvincibleTime = 0)=0;

	inline void  SetMaxInvincibleTime(const int maxInvincibleTime) { this->maxInvincibleTime = maxInvincibleTime; }
	inline float GetMaxinvincibleTime() { return maxInvincibleTime; }
	 
	inline float GetWeight() { return weight; }
	inline float GetCollisionRadius() { return collisionRadius; }
	 
	inline void SetTag(const ObjectTag tag) { this->tag = tag; };
	inline ObjectTag GetTag() { return tag; };
	 
	inline int GetNumBeAttacked() { return numBeAttacked; }
	inline int GetMaxBeAttacked() { return maxBeAttacked; }

	inline void SetNumBeAttacked(const int num) { numBeAttacked = num; }
	inline void SetMaxBeAttacked(const int num) { maxBeAttacked = num; }


	
};