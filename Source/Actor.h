#pragma once
#include "Lib.h"
//オブジェクトのタイプ
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
	//QuaternionがPrivateなのはSet関数を必ず経由してほしいから
	VECTOR4 quaternion = {0,0,0,1};

	VECTOR3 front = { 0,0,0};
	VECTOR3 right = { 0,0,0 };
	VECTOR3 up = { 0,0,0 };

	VECTOR3 pos = { 0,0,0 };
	VECTOR3 scale = { 0,0,0 };

	//モデルの番号
	int modelIndex=-1;
	//ダメージ受けた時の無敵時間
	float maxInvincibleTime = 0;
	//オブジェクトの種類
	ObjectTag tag=static_cast<ObjectTag>(ObjectTag::TAG_NONE);
	

protected:
	float weight = 1.0f;//重さ
	float collisionRadius = 1.0f;//半径

	int hp = 1;
	int maxHp = 1;
protected:
	int numBeAttacked = 0;//攻撃されているミニオンの数
	int maxBeAttacked = 5;//攻撃されているミニオンの最大数

public:
	//攻撃されているミニオン
	vector<Sirobo*> attackSirobo;

public:
	Actor() {};
	~Actor();

	//HP関係
	inline int  GetHp() { return hp; }
	inline void SetHp(const int setHp) { hp = setHp; }
	inline int  GetMaxHp() { return maxHp; }
	inline void SetMaxHp(const int setHp) { maxHp = setHp; }

	//HPの表示
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