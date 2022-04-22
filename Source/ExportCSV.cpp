#include "ExportScript.h"
#include <assert.h>

void EnemyStatusData::SetData(int HP, float Scale, float Speed,
	float collisionRadius, int MinionMaxBeAttacked, string AttackNode)
{
	this->hp= HP;
	this->scale= Scale;
	this->speed= Speed;
	this->collisionRadius= collisionRadius;
	this->minionMaxBeAttacked= MinionMaxBeAttacked;
	this->attackNode= AttackNode;
}

void AlliesStatusData::SetData(int HP,float Scale,float Speed,
float CollisionRadius,float Weight,int MaxInvincibleTime)
{
    this->hp = HP;
    this->scale = Scale;
    this->speed = Speed;
    this->collisionRadius= collisionRadius;
    this->weight = Weight;
    this->maxInvincibleTime = MaxInvincibleTime;
}


EnemyStatusData* ExportCSV::GetEnemyStatusDataSearchName(string SearchName)
{
    for (int i = 0; i < enemyStatusData.size(); i++)
    {
        if (enemyStatusData.at(i).name == SearchName)return &enemyStatusData.at(i);
    }
    return nullptr;
}

AlliesStatusData* ExportCSV::GetAlliesStatusDataSearchName(string SearchName)
{
    for (int i = 0; i < alliesStatusData.size(); i++)
    {
        if (alliesStatusData.at(i).name == SearchName)return &alliesStatusData.at(i);
    }
    return nullptr;
}

//敵のステータス取得
void ExportCSV::LoadEnemyStatusData(string fileName)
{

    FILE* fp; // FILE型構造体
    //初期化
    enemyStatusData.clear();

    fopen_s(&fp, fileName.c_str(), "r"); // ファイルを開く。失敗するとNULLを返す。
    if (fp == NULL) {
        assert(!"No file not open!");

        return;
    }
    // 1行の最大文字数(バイト数)
    const int MaxReadText = 256;
    int Index = 0;

    char line[MaxReadText];

    while (fgets(line, MaxReadText, fp) != NULL) {
        Index++;
        //一行目は読み込まない
        if (Index == 1)continue;

        EnemyStatusData csvData;
        char Name[256];
        char attackNode[256];


        sscanf_s(line, "%[^,],%d,%f,%f,%f,%d,%[^,],",
            Name, sizeof(Name),
            &csvData.hp,
            &csvData.scale,   //sizeof(year),
            &csvData.speed,  //sizeof(month),
            &csvData.collisionRadius,    //sizeof(day),
            &csvData.minionMaxBeAttacked, //sizeof(height),
            attackNode, sizeof(attackNode) //sizeof(weight)
        );
        csvData.name = Name;
        csvData.attackNode = attackNode;
        enemyStatusData.push_back(csvData);

    }
    fclose(fp); // ファイルを閉じる
}

//味方のステータス取得
void ExportCSV::LoadAlliesStatusData(string fileName)
{

    FILE* fp; // FILE型構造体
    //初期化
    alliesStatusData.clear();

    fopen_s(&fp, fileName.c_str(), "r"); // ファイルを開く。失敗するとNULLを返す。
    if (fp == NULL) {
        assert(!"No file not open!");

        return;
    }
    // 1行の最大文字数(バイト数)
    const int MaxReadText = 256;
    int Index = 0;

    char line[MaxReadText];

    while (fgets(line, MaxReadText, fp) != NULL) {
        Index++;
        //一行目は読み込まない
        if (Index == 1)continue;

        AlliesStatusData csvData;
        char Name[256];
        char attackNode[256];


        sscanf_s(line, "%[^,],%d,%f,%f,%f,%f,%d,",
            Name, sizeof(Name),
            &csvData.hp,
            &csvData.scale,  
            &csvData.speed, 
            &csvData.collisionRadius,    
            &csvData.weight, 
            &csvData.maxInvincibleTime
             
        );
        csvData.name = Name;
        alliesStatusData.push_back(csvData);
        
    }
    fclose(fp); // ファイルを閉じる
}
