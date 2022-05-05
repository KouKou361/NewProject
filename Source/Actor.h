#pragma once
#include "Lib.h"
//�I�u�W�F�N�g�̃^�C�v
enum class ObjectTag
{
	TAG_PLAYER,
	TAG_SIROBO,
	TAG_OBJECT,
	TAG_ENEMY,
	TAG_NONE,
};
class Sirobo;
class Actor
{
private:
	friend class Charactor;
private:
	//Quaternion��Private�Ȃ̂�Set�֐���K���o�R���Ăق�������
	VECTOR4 quaternion = {0,0,0,1};

	VECTOR3 front = { 0,0,0};
	VECTOR3 right = { 0,0,0 };
	VECTOR3 up = { 0,0,0 };

	VECTOR3 pos = { 0,0,0 };
	VECTOR3 scale = { 0,0,0 };

	//���f���̔ԍ�
	int modelIndex=-1;
	//�_���[�W�󂯂����̖��G����
	float maxInvincibleTime = 0;
	//�I�u�W�F�N�g�̎��
	ObjectTag tag=static_cast<ObjectTag>(ObjectTag::TAG_NONE);
	

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
	vector<Sirobo*> attackSirobo;

public:
	Actor() {};
	~Actor();

	//HP�֌W
	inline int  GetHp() { return hp; }
	inline void SetHp(const int setHp) { hp = setHp; }
	inline int  GetMaxHp() { return maxHp; }
	inline void SetMaxHp(const int setHp) { maxHp = setHp; }

	//HP�̕\��
	virtual void HPRender(const int &spriteIndex, const VECTOR2 &pos)=0;

	void SetModel(const int& modelIndex);
	int GetModel() { return modelIndex; }
	void DeleteModel();

	void AttackSiroboErase(Sirobo* sirobo);

	void SetQuaternion(const VECTOR4& quaternion);
	inline VECTOR4 GetQuaternion() { return quaternion; }
	inline VECTOR3 GetFront() { return front; }
	inline VECTOR3 GetRight() { return right; }
	inline VECTOR3 GetUp() { return up; }
	
	inline VECTOR3 GetPos() { return pos; };
	inline void SetPos(const VECTOR3& pos) { this->pos = pos; };
	inline VECTOR3 GetScale() { return scale; };
	inline void SetScale(const VECTOR3& scale) { this->scale = scale; };
	virtual bool AddDamage(const int& damage, const float& maxinvincibleTime = 0)=0;

	inline void  SetMaxInvincibleTime(const float& maxInvincibleTime) { this->maxInvincibleTime = maxInvincibleTime; }
	inline float GetMaxinvincibleTime() { return maxInvincibleTime; }
	 
	inline float GetWeight() { return weight; }
	inline float GetCollisionRadius() { return collisionRadius; }
	 
	inline void SetTag(const ObjectTag& tag) { this->tag = tag; };
	inline ObjectTag GetTag() { return tag; };
	 
	inline int GetNumBeAttacked() { return numBeAttacked; }
	inline int GetMaxBeAttacked() { return maxBeAttacked; }

	inline void SetNumBeAttacked(const int& num) { numBeAttacked = num; }
	inline void SetMaxBeAttacked(const int& num) { maxBeAttacked = num; }


	
};