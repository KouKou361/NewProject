#pragma once
#include "Lib.h"
//オブジェクトのタイプ
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
	//QuaternionがPrivateなのはSet関数を必ず経由してほしいから
	VECTOR4 quaternion;
	VECTOR3 front;
	VECTOR3 right;
	VECTOR3 up;

	VECTOR3 pos;
	VECTOR3 scale;

	int modelIndex;




	//ダメージ受けた時の無敵時間
	int MaxInvincibleTime = 0;

	ObjectTag tag;//オブジェクトの種類
	

protected:
	float weight = 1.0f;//重さ
	float collisionRadius = 1.0f;//半径

	int hp = 1;
	int maxHp = 1;

	
protected:

	int numBeAttacked = 0;//攻撃されているミニオンの数
	int maxBeAttacked = 5;//攻撃されているミニオンの最大数

public:
	Actor() {};
	~Actor();

	//HP関係
	inline int  GetHp() { return hp; }
	inline void SetHp(int SetHp) { hp = SetHp; }
	inline int  GetMaxHp() { return maxHp; }
	inline void SetMaxHp(int SetHp) { maxHp = SetHp; }

	//HPの表示
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

	//攻撃されているミニオン
	vector<MinionPlayer*> AttackMinions;
	
};