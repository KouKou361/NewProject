#pragma once
#include <string>
#include <vector>
#include "Lib.h"
using namespace std;
class ExportCSV;
//.txt�̓ǂݍ���
class ExportText
{
private:
	// �\�����
	vector<string> scripts;
public:
	ExportText(string fileName);
	~ExportText() {};


	vector<string>* GetScripts() { return &scripts; }

};
//�G�̃X�e�[�^�X�f�[�^
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

//�����̃X�e�[�^�X�f�[�^
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


//�G�t�F�N�g�̃X�e�[�^�X�f�[�^
class EffectStatusData
{
	friend class ExportCSV;

private:
	int   effectType=0;	//�G�t�F�N�g�̃^�C�v
	float timer=0;      //��������
	float scale=0;      //�傫��
	float updateScale=0;  //�X�V�����̑傫���̕ω���
	float updateAlpha=0;  //�X�V�����̓����x�̕ω���
	VECTOR3 posMax={0,0,0};     //�ʒu�����̍ō��l
	VECTOR3 posMix={0,0,0};		//�ʒu�����̍Œ�l

	VECTOR3 velocityMax={0,0,0};//���x�����̍ō��l
	VECTOR3 velocityMix={0,0,0};//���x�����̍Œ�l

	VECTOR3 accelMax={0,0,0};	//�����x�����̍ō��l
	VECTOR3 accelMix={0,0,0};	//�����x�����̍Œ�l
	VECTOR4 color={ 0,0,0,0 };		//�F



	string name;		//���O
public:
	EffectStatusData() {};
	~EffectStatusData() {};

	int   GetEffectType()         {return effectType;};   //�G�t�F�N�g�̃^�C�v�̎擾
	float GetTimer()              {return timer;};		  //�������Ԃ̎擾
	float GetScale()			  {return scale;};		  //�傫���̎擾
	float GetUpdateScale()        {return updateScale;};  //�X�V�����̑傫���̕ω��ʂ̎擾
	float GetUpdateAlpha()        {return updateAlpha;};  //�X�V�����̓����x�̕ω��ʂ̎擾

	VECTOR3 GetPosMax()           {return posMax;};     //�ʒu�����̍ō��l�̎擾
	VECTOR3 GetPosMix()           {return posMix;};     //�ʒu�����̍Œ�l�̎擾
							      
	VECTOR3 GetVelocityMax()      {return velocityMax;};//���x�����̍ō��l�̎擾
	VECTOR3 GetVelocityMix()      {return velocityMix;};//���x�����̍Œ�l�̎擾
							      
	VECTOR3 GetAccelMax()         {return accelMax;};   //�����x�����̍ō��l�̎擾
	VECTOR3 GetAccelMix()         {return accelMix;};   //�����x�����̍Œ�l�̎擾
	VECTOR4 GetColor()            {return color;};      //�F�̎擾
	string  GetName()             {return name;};       //���O�̎擾
};

//�G�t�F�N�g�̃X�e�[�^�X�f�[�^
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






//.csv�̓ǂݍ���
class ExportCSV
{

private:
	// �G�X�e�[�^�X�\�����
	vector<EnemyStatusData> enemyStatusData;
	// �����X�e�[�^�X�\�����
	vector<AlliesStatusData> alliesStatusData;
	// �G�t�F�N�g�X�e�[�^�X�\�����
	vector<EffectStatusData> effectStatusData;
	// �I�u�W�F�N�g�X�e�[�^�X�\�����
	vector<ObjectStatusData> objectStatusData;
public:
	ExportCSV() {};
	
	~ExportCSV() {};

	//char����string
	void charToString(string& name, const char* name2);

	//CSV����G�̃X�e�[�^�X�擾
	void LoadEnemyStatusData(const string& fileName);
	//CSV���疡���̃X�e�[�^�X�擾
	void LoadAlliesStatusData(const string& fileName);
	//CSV����G�t�F�N�g�̃X�e�[�^�X�擾
	void LoadEffectStatusData(const string& fileName);
	//CSV����I�u�W�F�N�g�̃X�e�[�^�X�擾
	void LoadObjectStatusData(const string& fileName);

	//�G�̃X�e�[�^�X�f�[�^�̎擾
	EnemyStatusData* GetEnemyStatusDataSearchName(const string& SearchName);
	//�����̃X�e�[�^�X�f�[�^�̎擾
	AlliesStatusData* GetAlliesStatusDataSearchName(const string& SearchName);
	//�G�t�F�N�g�̃X�e�[�^�X�f�[�^�̎擾
	EffectStatusData* GetEffectStatusDataSearchName(const string& SearchName);
	//�I�u�W�F�N�g�̃X�e�[�^�X�f�[�^�̎擾
	ObjectStatusData* GetObjectStatusDataSearchName(const string& SearchName);

	//CSV����f�[�^���擾
	int CSVReadText(char& line, FILE* fp,int &index, int textSize);
};