#pragma once
#include <string>
#include <vector>
#include "Lib.h"
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
//敵のステータスデータ
class EnemyStatusData
{
	friend class ExportCSV;

private:
	int hp=0;
	float scale=0;
	float speed=0;
	float collisionRadius = 0;
	int siroboMaxBeAttacked = 0;
    string attackNode = "";
    string name = "";
public:
	EnemyStatusData() {};
	~EnemyStatusData() {};

	int    GetHp() { return hp; };
	float  GetScale() { return scale; };
	float  GetSpeed() { return speed; };
	float  GetCollisionRadius() { return collisionRadius; };
	int    GetSiroboMaxBeAttacked() { return siroboMaxBeAttacked; };
	string GetAttackNode() { return attackNode; };
	string Getname() { return name; };
};

//味方のステータスデータ
class AlliesStatusData
{
	friend class ExportCSV;

private:
	int hp=0;
	float scale = 0;
	float speed = 0;
	float collisionRadius = 0;
	float weight = 0;
	float maxInvincibleTime = 0;
	string name = "";
public:
	AlliesStatusData() {};
	~AlliesStatusData() {};

	int    GetHp() { return hp; };
	float  GetScale() { return scale; };
	float  GetSpeed() { return speed; };
	float  GetCollisionRadius() { return collisionRadius; };
	float  GetWeight() { return weight; };
	float    GetMaxInvincibleTime() { return maxInvincibleTime; };
};


//エフェクトのステータスデータ
class EffectStatusData
{
	friend class ExportCSV;

private:
	int   effectType=0;	//エフェクトのタイプ
	float timer=0;      //生存時間
	float scale=0;      //大きさ
	float updateScale=0;  //更新処理の大きさの変化量
	float updateAlpha=0;  //更新処理の透明度の変化量
	VECTOR3 posMax={0,0,0};     //位置乱数の最高値
	VECTOR3 posMix={0,0,0};		//位置乱数の最低値

	VECTOR3 velocityMax={0,0,0};//速度乱数の最高値
	VECTOR3 velocityMix={0,0,0};//速度乱数の最低値

	VECTOR3 accelMax={0,0,0};	//加速度乱数の最高値
	VECTOR3 accelMix={0,0,0};	//加速度乱数の最低値
	VECTOR4 color={ 0,0,0,0 };		//色



	string name;		//名前
public:
	EffectStatusData() {};
	~EffectStatusData() {};

	int   GetEffectType()         {return effectType;};   //エフェクトのタイプの取得
	float GetTimer()              {return timer;};		  //生存時間の取得
	float GetScale()			  {return scale;};		  //大きさの取得
	float GetUpdateScale()        {return updateScale;};  //更新処理の大きさの変化量の取得
	float GetUpdateAlpha()        {return updateAlpha;};  //更新処理の透明度の変化量の取得

	VECTOR3 GetPosMax()           {return posMax;};     //位置乱数の最高値の取得
	VECTOR3 GetPosMix()           {return posMix;};     //位置乱数の最低値の取得
							      
	VECTOR3 GetVelocityMax()      {return velocityMax;};//速度乱数の最高値の取得
	VECTOR3 GetVelocityMix()      {return velocityMix;};//速度乱数の最低値の取得
							      
	VECTOR3 GetAccelMax()         {return accelMax;};   //加速度乱数の最高値の取得
	VECTOR3 GetAccelMix()         {return accelMix;};   //加速度乱数の最低値の取得
	VECTOR4 GetColor()            {return color;};      //色の取得
	string  GetName()             {return name;};       //名前の取得
};

//エフェクトのステータスデータ
class ObjectStatusData
{
	friend class ExportCSV;

private:
	int hp=0;
	float scale = 0;
	float collisionRadius = 0;
	string name = "";
public:
	ObjectStatusData() {};
	~ObjectStatusData() {};

	int    GetHp() { return hp; };
	float  GetScale() { return scale; };
	float  GetCollisionRadius() { return collisionRadius; };
};






//.csvの読み込み
class ExportCSV
{

private:
	// 敵ステータス構文解析
	vector<EnemyStatusData> enemyStatusData;
	// 味方ステータス構文解析
	vector<AlliesStatusData> alliesStatusData;
	// エフェクトステータス構文解析
	vector<EffectStatusData> effectStatusData;
	// オブジェクトステータス構文解析
	vector<ObjectStatusData> objectStatusData;
public:
	ExportCSV() {};
	
	~ExportCSV() {};

	//charからstring
	void charToString(string& name, const char* name2);

	//CSVから敵のステータス取得
	void LoadEnemyStatusData(const string& fileName);
	//CSVから味方のステータス取得
	void LoadAlliesStatusData(const string& fileName);
	//CSVからエフェクトのステータス取得
	void LoadEffectStatusData(const string& fileName);
	//CSVからオブジェクトのステータス取得
	void LoadObjectStatusData(const string& fileName);

	//敵のステータスデータの取得
	EnemyStatusData* GetEnemyStatusDataSearchName(const string& SearchName);
	//味方のステータスデータの取得
	AlliesStatusData* GetAlliesStatusDataSearchName(const string& SearchName);
	//エフェクトのステータスデータの取得
	EffectStatusData* GetEffectStatusDataSearchName(const string& SearchName);
	//オブジェクトのステータスデータの取得
	ObjectStatusData* GetObjectStatusDataSearchName(const string& SearchName);

	//CSVからデータを取得
	int CSVReadText(char& line, FILE* fp,int &index, int textSize);
};