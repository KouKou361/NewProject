#include "Tuto.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "ObjectManager.h"
#include "ObjectDerived.h"
KillEnemyTuto::KillEnemyTuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();

	this->sceneGame = sceneGame;
}
//����������
void KillEnemyTuto::Init()
{
	//ui = make_unique<UITuto>();
	TutoWindowUI->Init();
	TutoWindowUI->Update();
	textIndex = 0;

	//�G�̐���
	SummonEnemy();
	//�I�u�W�F�N�g�̐���
	SummonObject();

	
}
void KillEnemyTuto::Update()
{
	TutoWindowUI->Update();
	UiTargetUpdate();
}

//����������
bool KillEnemyTuto::Judge()
{
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() <= 0)
	{
		if (sceneGame->GetObjectManager()->GetTowerNum() <= 0)
		{
			TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
			return true;
	
		}
	}
	return  false;
}
//�`��
void KillEnemyTuto::Render()
{
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();

	ui2DDirection->Render();
}

//UI�̍X�V����
void KillEnemyTuto::UiTargetUpdate()
{
	VECTOR3 pos = { 0,0,0 };
	
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() > 0)
	{
		pos = sceneGame->GetEnemyManager()->GetEnemiesIndex(0)->GetPos();
	}
	if (sceneGame->GetObjectManager()->GetTowerNum() > 0)
	{
		pos = sceneGame->GetObjectManager()->GetObjesIndex(0)->GetPos();
	}
	ui2DDirection->Update();
}
//�G�̐���
void KillEnemyTuto::SummonEnemy()
{

	for (int i = 0; i < 2; i++)
	{
		shared_ptr<EnemySlime> enm;
		enm = make_shared<EnemySlime>(sceneGame);
		enm->SetPos({ 50 - static_cast<float>(i * 50),0,20 });
		sceneGame->GetEnemyManager()->Register(enm);
	}

}
//�I�u�W�F�N�g�̐���
void KillEnemyTuto::SummonObject()
{
	shared_ptr<ObjectTower> obj;
	obj = make_shared<ObjectTower>(sceneGame->GetObjectManager(), sceneGame);
	obj->SetPos({ 50,0,0 });
	sceneGame->GetObjectManager()->Register(obj);

	VECTOR3 pos = { 0,0,0 };
	if (sceneGame->GetObjectManager()->GetObjesSize() > 0)
	{
		pos = sceneGame->GetObjectManager()->GetObjesIndex(0)->GetPos();
	}

	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos(pos);
	}
}