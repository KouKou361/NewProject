#include "Tuto.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "MinionPlayer.h"
ResurectionMinionTuto::ResurectionMinionTuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();


	this->sceneGame = sceneGame;
}
//‰Šú‰»ˆ—
void ResurectionMinionTuto::Init()
{
	ui = make_unique<UITuto>();
	ui->Init();
	uiTimer = 0;



}
void ResurectionMinionTuto::Update()
{
	ui->Update();


}

//‰Šú‰»ˆ—
bool ResurectionMinionTuto::Judge()
{
	int MinionNum = 0;
	for (int i = 0; i < sceneGame->GetPlayer()->GetMinionManager()->GetMinionsSize(); i++)
	{
		MinionPlayer* minion = sceneGame->GetPlayer()->GetMinionManager()->GetMinionIndex(i);
		if (MinionPlayer::StateType::TypeStandBy == minion->GetState())
		{
			MinionNum++;
		}
	}

	if (MinionNum >= 3)
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
		return true;

	}
	return false;
}
//•`‰æ
void ResurectionMinionTuto::Render()
{
	ui->SetText(textes.at(TextIndex));
	ui->Render();


}