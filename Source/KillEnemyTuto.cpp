#include "Tuto.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "ObjectManager.h"
#include "ObjectDerived.h"
KillEnemyTuto::KillEnemyTuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();

	this->sceneGame = sceneGame;
}
//‰Šú‰»ˆ—
void KillEnemyTuto::Init()
{
	ui = make_unique<UITuto>();
	ui->Init();
	TextIndex = 0;

	for (int i = 0; i < 2; i++)
	{
		shared_ptr<EnemySlime> enm;
		enm = make_shared<EnemySlime>(sceneGame);
		enm->SetPos({ 50-static_cast<float>(i*50),0,20 });
		sceneGame->GetEnemyManager()->Register(enm);
	}

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
void KillEnemyTuto::Update()
{
	ui->Update();
	UiTargetUpdate();
}

//‰Šú‰»ˆ—
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
//•`‰æ
void KillEnemyTuto::Render()
{
	ui->SetText(textes.at(TextIndex));
	ui->Render();

	ui2DDirection->Render();
}

//UI‚ÌXVˆ—
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

	ui2DDirection->SetTargetPos(pos);
}