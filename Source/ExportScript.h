#pragma once
#include <string>
#include <vector>
using namespace std;
class ExportCSV;
//.txtの読み込み
class ExportText
{
private:
	// 構文解析
	vector<string> scripts;
public:
	ExportText(string fileName);
	~ExportText() {};


	vector<string>* GetScripts() { return &scripts; }

};
class EnemyStatusData
{
	friend class ExportCSV;

private:
	int hp;
	float scale;
	float speed;
	float collisionRadius;
	int minionMaxBeAttacked;
    string attackNode;
    string name;
public:
	EnemyStatusData() {};
	~EnemyStatusData() {};
	void SetData(int HP, float Scale, float Speed,
		float collisionRadius, int MinionMaxBeAttacked, string AttackNode);

	int    GetHp() { return hp; };
	float  GetScale() { return scale; };
	float  GetSpeed() { return speed; };
	float  GetCollisionRadius() { return collisionRadius; };
	int    GetMinionMaxBeAttacked() { return minionMaxBeAttacked; };
	string GetAttackNode() { return attackNode; };
	string Getname() { return name; };
};


class AlliesStatusData
{
	friend class ExportCSV;

private:
	int hp;
	float scale;
	float speed;
	float collisionRadius;
	float weight;
	int maxInvincibleTime;
	string name;
public:
	AlliesStatusData() {};
	~AlliesStatusData() {};

	void SetData(int HP, float Scale, float Speed,
		float collisionRadius, float weight, int maxInvincibleTime);

	int    GetHp() { return hp; };
	float  GetScale() { return scale; };
	float  GetSpeed() { return speed; };
	float  GetCollisionRadius() { return collisionRadius; };
	float  GetWeight() { return weight; };
	int    GetMaxInvincibleTime() { return maxInvincibleTime; };
};



class EffectStatusData
{
	friend class ExportCSV;

private:
	int   effectType;
	float timer;
	float scale;
	float posRandStart;
	float posRandEnd;
	float velocityRandStart;
	float velocityRandEnd;
	float accelXRandStart;
	float accelXRandEnd;
	float accelYRandStart;
	float accelYRandEnd;
	float accelZRandStart;
	float accelZRandEnd;
	float colorX;
	float colorY;
	float colorZ;
	float colorW;

	string name;
public:
	EffectStatusData() {};
	~EffectStatusData() {};

	void SetData(int HP, float Scale, float Speed,
		float collisionRadius, float weight, int maxInvincibleTime);

	int   GetEffectType()         {return effectType;};
	float GetYimer()              {return timer;};
	float GetScale()			  {return scale;};
	float GetPosRandStart()	      {return posRandStart;};
	float GetPosRandEnd()		  {return posRandEnd;};
	float GetVelocityRandStart()  {return velocityRandStart;};
	float GetVelocityRandEnd()	  {return velocityRandEnd;};
	float GetAccelXRandStart()	  {return accelXRandStart;};
	float GetAccelXRandEnd()	  {return accelXRandEnd;};
	float GetAccelYRandStart()	  {return accelYRandStart;};
	float GetAccelYRandEnd()	  {return accelYRandEnd;};
	float GetAccelZRandStart()	  {return accelZRandStart;};
	float GetAccelZRandEnd()	  {return accelZRandEnd;};
	float GetColorX()			  {return colorX;};
	float GetColorY()			  {return colorY;};
	float GetColorZ()			  {return colorZ;};
	float GetColorW()             {return colorW;};
};





//.csvの読み込み
class ExportCSV
{

private:
	// 敵ステータス構文解析
	vector<EnemyStatusData> enemyStatusData;
	// 味方ステータス構文解析
	vector<AlliesStatusData> alliesStatusData;
public:
	ExportCSV() {};
	
	~ExportCSV() {};
	//敵のステータス取得
	void LoadEnemyStatusData(string fileName);
	//味方のステータス取得
	void LoadAlliesStatusData(string fileName);
	EnemyStatusData* GetEnemyStatusDataSearchName(string SearchName);
	AlliesStatusData* GetAlliesStatusDataSearchName(string SearchName);

};