#include "ExportScript.h"
#include <assert.h>

//敵のステータス取得
EnemyStatusData* ExportCSV::GetEnemyStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < enemyStatusData.size(); i++)
    {
        if (enemyStatusData.at(i).name == searchName)return &enemyStatusData.at(i);
    }
    return nullptr;
}
//味方のステータス取得
AlliesStatusData* ExportCSV::GetAlliesStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < alliesStatusData.size(); i++)
    {
        if (alliesStatusData.at(i).name == searchName)return &alliesStatusData.at(i);
    }
    return nullptr;
}

//エフェクトのステータス取得
EffectStatusData* ExportCSV::GetEffectStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < effectStatusData.size(); i++)
    {
        if (effectStatusData.at(i).name == searchName)return &effectStatusData.at(i);
    }
    return nullptr;
}

//オブジェクトのステータス取得
ObjectStatusData* ExportCSV::GetObjectStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < objectStatusData.size(); i++)
    {
        if (objectStatusData.at(i).name == searchName)return &objectStatusData.at(i);
    }
    return nullptr;
}

//charからstring(警告が出るのでこれで改善している)
void ExportCSV::charToString(string& name, const char* name2)
{
    size_t len;
    char ntbs[16];
    /* コピー元 source に値が設定される（サイズ、NULL終端の有無は不明） */
    strncpy_s(ntbs, name2, sizeof(ntbs) - 1);
    /* 結果的に ntbs はNULL終端されていないかも知れない */
    ntbs[sizeof(ntbs) - 1] = '\0'; /* NULL 終端する */
    len = strlen(ntbs);
    name = name2;
}


//CSVから敵のステータス取得
void ExportCSV::LoadEnemyStatusData(const string& fileName)
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
    int index = 0;

    char line[MaxReadText];
    char name[256];
    char attackNode[256];

    while (true) {
        //CSVからデータを取得
        int result = CSVReadText(*line, fp, index, MaxReadText);

        if (result == -1)break;
        if (result == 0)continue;

        EnemyStatusData csvData;
  


        sscanf_s(line, "%[^,],%d,%f,%f,%f,%d,%[^,],",
            name, static_cast<u_int>(sizeof(name)),
            &csvData.hp,
            &csvData.scale,   //sizeof(year),
            &csvData.speed,  //sizeof(month),
            &csvData.collisionRadius,    //sizeof(day),
            &csvData.siroboMaxBeAttacked, //sizeof(height),
            attackNode, static_cast<u_int>(sizeof(attackNode)) //sizeof(weight)
        ); 

        //charからstring
        charToString(csvData.name, name);
        charToString(csvData.attackNode, attackNode);

        enemyStatusData.push_back(csvData);

    }
    fclose(fp); // ファイルを閉じる
}

//CSVから味方のステータス取得
void ExportCSV::LoadAlliesStatusData(const string& fileName)
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
    int index = 0;

    char line[MaxReadText];
    char name[MaxReadText];

    //ここでCSVデータを読み込み
    while (true) {
        //CSVからデータを取得
        int result = CSVReadText(*line, fp, index, MaxReadText);

        if (result == -1)break;
        if (result == 0)continue;

        AlliesStatusData csvData;
        


        sscanf_s(line, "%[^,],%d,%f,%f,%f,%f,%f,",
            name, static_cast<u_int>(sizeof(name)),
            &csvData.hp,
            &csvData.scale,  
            &csvData.speed, 
            &csvData.collisionRadius,    
            &csvData.weight, 
            &csvData.maxInvincibleTime
             
        );
        //charからstring
        charToString(csvData.name, name);

        alliesStatusData.push_back(csvData);
        
    }
    fclose(fp); // ファイルを閉じる
}

//CSVからエフェクトのステータス取得
void ExportCSV::LoadEffectStatusData(const string& fileName)
{
    // FILE型構造体
    FILE* fp; 
    // 1行の最大文字数(バイト数)
    const int MaxReadText = 256;
    int index = 0;
    char line[MaxReadText];
    char name[256];


    //初期化
    effectStatusData.clear();

    fopen_s(&fp, fileName.c_str(), "r"); // ファイルを開く。失敗するとNULLを返す。
    if (fp == NULL) {
        assert(!"No file not open!");

        return;
    }

    //ここでCSVデータを読み込み
    while (true) {
        //一行ずつデータを取得
        int result = CSVReadText(*line, fp, index, MaxReadText);

        if (result == -1)break;
        if (result == 0)continue;

        EffectStatusData csvData;
      
        sscanf_s(line, "%[^,],%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
            name, static_cast<u_int>(sizeof(name)),        &csvData.effectType,      &csvData.timer,              &csvData. scale,
            &csvData.posMax.x,        &csvData.posMix.x,        
            &csvData.posMax.y,        &csvData.posMix.y,
            &csvData.posMax.z,        &csvData.posMix.z,

            &csvData.velocityMax.x,   &csvData.velocityMix.x,
            &csvData.velocityMax.y,   &csvData.velocityMix.y,
            &csvData.velocityMax.z,   &csvData.velocityMix.z,

            &csvData.accelMax.x,      &csvData.accelMix.x,
            &csvData.accelMax.y,      &csvData.accelMix.y,
            &csvData.accelMax.z,      &csvData.accelMix.z,

            &csvData.color.x,&csvData.color.y,&csvData.color.z,&csvData.color.w,

            &csvData.updateScale, & csvData.updateAlpha
        );
        //charからstring
        charToString(csvData.name, name);
        effectStatusData.push_back(csvData);

    }
    fclose(fp); // ファイルを閉じる
}

//CSVからオブジェクトのステータス取得
void ExportCSV::LoadObjectStatusData(const string& fileName)
{
    //初期化
    objectStatusData.clear();

    FILE* fp=nullptr; // FILE型構造体

    // ファイルを開く。失敗するとNULLを返す。
    fopen_s(&fp, fileName.c_str(), "r");

    if (fp == NULL) {
        assert(!L"ファイルが見つかりません！");
        return;
    }

    // 1行の最大文字数(バイト数)
    const int MaxReadText = 256;
    int index = 0;
    char line[MaxReadText];
    char name[MaxReadText];

    //ここでCSVデータを読み込み
    while (true)
    {
        //CSVからデータを取得
        int result = CSVReadText(*line, fp, index, MaxReadText);

        if(result==-1)break;
        if(result == 0)continue;
        //データの設定していく
        ObjectStatusData csvData;
 
        sscanf_s(line, "%[^,],%d,%f,%f,",
            name, static_cast<u_int>(sizeof(name)),
            &csvData.hp,
            &csvData.collisionRadius,
            &csvData.scale

        );
        //charからstring
        charToString(csvData.name, name);
        objectStatusData.push_back(csvData);
    }
    fclose(fp); // ファイルを閉じる
}

//SCVデータから文字列の読み込む処理
int ExportCSV::CSVReadText(char& line, FILE* fp, int& index,int textSize)
{
    index++;
    //一行目は読み込まない
    if (fgets(&line, textSize, fp) == nullptr)return -1;//終了
    if (index == 1)return 0;//読み込まないがもう一度回す
    
    return 1;//もう一度回す
    
}
