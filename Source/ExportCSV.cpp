#include "ExportScript.h"
#include <assert.h>

//�G�̃X�e�[�^�X�擾
EnemyStatusData* ExportCSV::GetEnemyStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < enemyStatusData.size(); i++)
    {
        if (enemyStatusData.at(i).name == searchName)return &enemyStatusData.at(i);
    }
    return nullptr;
}
//�����̃X�e�[�^�X�擾
AlliesStatusData* ExportCSV::GetAlliesStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < alliesStatusData.size(); i++)
    {
        if (alliesStatusData.at(i).name == searchName)return &alliesStatusData.at(i);
    }
    return nullptr;
}

//�G�t�F�N�g�̃X�e�[�^�X�擾
EffectStatusData* ExportCSV::GetEffectStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < effectStatusData.size(); i++)
    {
        if (effectStatusData.at(i).name == searchName)return &effectStatusData.at(i);
    }
    return nullptr;
}

//�I�u�W�F�N�g�̃X�e�[�^�X�擾
ObjectStatusData* ExportCSV::GetObjectStatusDataSearchName(const string &searchName)
{
    for (int i = 0; i < objectStatusData.size(); i++)
    {
        if (objectStatusData.at(i).name == searchName)return &objectStatusData.at(i);
    }
    return nullptr;
}

//char����string(�x�����o��̂ł���ŉ��P���Ă���)
void ExportCSV::charToString(string& name, const char* name2)
{
    size_t len;
    char ntbs[16];
    /* �R�s�[�� source �ɒl���ݒ肳���i�T�C�Y�ANULL�I�[�̗L���͕s���j */
    strncpy_s(ntbs, name2, sizeof(ntbs) - 1);
    /* ���ʓI�� ntbs ��NULL�I�[����Ă��Ȃ������m��Ȃ� */
    ntbs[sizeof(ntbs) - 1] = '\0'; /* NULL �I�[���� */
    len = strlen(ntbs);
    name = name2;
}


//CSV����G�̃X�e�[�^�X�擾
void ExportCSV::LoadEnemyStatusData(const string& fileName)
{

    FILE* fp; // FILE�^�\����
    //������
    enemyStatusData.clear();

    fopen_s(&fp, fileName.c_str(), "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
    if (fp == NULL) {
        assert(!"No file not open!");

        return;
    }
    // 1�s�̍ő啶����(�o�C�g��)
    const int MaxReadText = 256;
    int index = 0;

    char line[MaxReadText];
    char name[256];
    char attackNode[256];

    while (true) {
        //CSV����f�[�^���擾
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

        //char����string
        charToString(csvData.name, name);
        charToString(csvData.attackNode, attackNode);

        enemyStatusData.push_back(csvData);

    }
    fclose(fp); // �t�@�C�������
}

//CSV���疡���̃X�e�[�^�X�擾
void ExportCSV::LoadAlliesStatusData(const string& fileName)
{

    FILE* fp; // FILE�^�\����
    //������
    alliesStatusData.clear();

    fopen_s(&fp, fileName.c_str(), "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
    if (fp == NULL) {
        assert(!"No file not open!");

        return;
    }
    // 1�s�̍ő啶����(�o�C�g��)
    const int MaxReadText = 256;
    int index = 0;

    char line[MaxReadText];
    char name[MaxReadText];

    //������CSV�f�[�^��ǂݍ���
    while (true) {
        //CSV����f�[�^���擾
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
        //char����string
        charToString(csvData.name, name);

        alliesStatusData.push_back(csvData);
        
    }
    fclose(fp); // �t�@�C�������
}

//CSV����G�t�F�N�g�̃X�e�[�^�X�擾
void ExportCSV::LoadEffectStatusData(const string& fileName)
{
    // FILE�^�\����
    FILE* fp; 
    // 1�s�̍ő啶����(�o�C�g��)
    const int MaxReadText = 256;
    int index = 0;
    char line[MaxReadText];
    char name[256];


    //������
    effectStatusData.clear();

    fopen_s(&fp, fileName.c_str(), "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
    if (fp == NULL) {
        assert(!"No file not open!");

        return;
    }

    //������CSV�f�[�^��ǂݍ���
    while (true) {
        //��s���f�[�^���擾
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
        //char����string
        charToString(csvData.name, name);
        effectStatusData.push_back(csvData);

    }
    fclose(fp); // �t�@�C�������
}

//CSV����I�u�W�F�N�g�̃X�e�[�^�X�擾
void ExportCSV::LoadObjectStatusData(const string& fileName)
{
    //������
    objectStatusData.clear();

    FILE* fp=nullptr; // FILE�^�\����

    // �t�@�C�����J���B���s�����NULL��Ԃ��B
    fopen_s(&fp, fileName.c_str(), "r");

    if (fp == NULL) {
        assert(!L"�t�@�C����������܂���I");
        return;
    }

    // 1�s�̍ő啶����(�o�C�g��)
    const int MaxReadText = 256;
    int index = 0;
    char line[MaxReadText];
    char name[MaxReadText];

    //������CSV�f�[�^��ǂݍ���
    while (true)
    {
        //CSV����f�[�^���擾
        int result = CSVReadText(*line, fp, index, MaxReadText);

        if(result==-1)break;
        if(result == 0)continue;
        //�f�[�^�̐ݒ肵�Ă���
        ObjectStatusData csvData;
 
        sscanf_s(line, "%[^,],%d,%f,%f,",
            name, static_cast<u_int>(sizeof(name)),
            &csvData.hp,
            &csvData.collisionRadius,
            &csvData.scale

        );
        //char����string
        charToString(csvData.name, name);
        objectStatusData.push_back(csvData);
    }
    fclose(fp); // �t�@�C�������
}

//SCV�f�[�^���當����̓ǂݍ��ޏ���
int ExportCSV::CSVReadText(char& line, FILE* fp, int& index,int textSize)
{
    index++;
    //��s�ڂ͓ǂݍ��܂Ȃ�
    if (fgets(&line, textSize, fp) == nullptr)return -1;//�I��
    if (index == 1)return 0;//�ǂݍ��܂Ȃ���������x��
    
    return 1;//������x��
    
}
