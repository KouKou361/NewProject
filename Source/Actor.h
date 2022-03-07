#pragma once
#include "Lib.h"
//�I�u�W�F�N�g�̃^�C�v
enum ObjectTag
{
	TagPlayer,
	TagMinion,
	TagObject,
	TagEnemy,
};
class MinionPlayer;
class Actor
{
	friend class Charactor;
private:
	//Quaternion��Private�Ȃ̂�Set�֐���K���o�R���Ăق�������
	VECTOR4 quaternion;
	VECTOR3 front;
	VECTOR3 right;
	VECTOR3 up;

	VECTOR3 pos;
	VECTOR3 scale;

	int modelIndex;




	//�_���[�W�󂯂����̖��G����
	int MaxInvincibleTime = 0;

	ObjectTag tag;//�I�u�W�F�N�g�̎��
	

protected:
	float weight = 1.0f;//�d��
	float collisionRadius = 1.0f;//���a

	int hp = 1;
	int maxHp = 1;

	
protected:

	int numBeAttacked = 0;//�U������Ă���~�j�I���̐�
	int maxBeAttacked = 5;//�U������Ă���~�j�I���̍ő吔

public:
	Actor() {};
	~Actor();

	//HP�֌W
	inline int  GetHp() { return hp; }
	inline void SetHp(int SetHp) { hp = SetHp; }
	inline int  GetMaxHp() { return maxHp; }
	inline void SetMaxHp(int SetHp) { maxHp = SetHp; }

	//HP�̕\��
	virtual void HPRender(const int SpriteIndex, const VECTOR2 Pos)=0;

	void SetModel(int modelIndex);
	int GetModel() { return modelIndex; }
	void DeleteModel();

	void AttackMinionErase(MinionPlayer* minion);

	void SetQuaternion(const VECTOR4& Quaternion);
	inline VECTOR4 GetQuaternion() { return quaternion; }
	inline VECTOR3 GetFront() { return front; }
	inline VECTOR3 GetRight() { return right; }
	inline VECTOR3 GetUp() { return up; }
	
	inline VECTOR3 GetPos() { return pos; };
	inline void SetPos(VECTOR3 Pos) { this->pos = Pos; };
	inline VECTOR3 GetScale() { return scale; };
	inline void SetScale(VECTOR3 Scale) { this->scale = Scale; };
	virtual bool AddDamage(int Damage, int MaxinvincibleTime = 0)=0;

	inline void  SetMaxInvincibleTime(int MaxInvincibleTime) { this->MaxInvincibleTime = MaxInvincibleTime; }
	inline float GetMaxinvincibleTime() { return MaxInvincibleTime; }
	 
	inline float GetWeight() { return weight; }
	inline float GetCollisionRadius() { return collisionRadius; }
	 
	inline void SetTag(const ObjectTag tag) { this->tag = tag; };
	inline ObjectTag GetTag() { return tag; };
	 
	inline int GetNumBeAttacked() { return numBeAttacked; }
	inline int GetMaxBeAttacked() { return maxBeAttacked; }

	inline void SetNumBeAttacked(int num) { numBeAttacked = num; }
	inline void SetMaxBeAttacked(int num) { maxBeAttacked = num; }

	//�U������Ă���~�j�I��
	vector<MinionPlayer*> AttackMinions;
	
};