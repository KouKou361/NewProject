#include "Tuto.h"
#include "Collision.h"
#include "Charactor.h"
#include "Scene.h"
#include "MinionPlayer.h"

GetMinionTuto::GetMinionTuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();



	this->sceneGame = sceneGame;
}
//‰Šú‰»ˆ—
void GetMinionTuto::Init()
{
	ui = make_unique<UITuto>();
	ui->Init();
	textIndex = 0;

	for (int i = 0; i < 3; i++)
	{
		shared_ptr<MinionPlayer>minion;
		minion = make_shared<MinionPlayer>();
		minion->Init(sceneGame->GetPlayer());
		minion->SetPos({ 100,0,static_cast<float>(i * 8)+100 });
		sceneGame->GetPlayer()->GetMinionManager()->Register(minion);
	}
	
	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos({ 100,0,100 });
	}

}
void GetMinionTuto::Update()
{
	ui->Update();

	ui2DDirection->Update();
	ui2DDirection->SetTargetPos({ 100,0,100 });
}

//‰Šú‰»ˆ—
bool GetMinionTuto::Judge()
{
	int MinionNum = 0;
	for (int i = 0; i < sceneGame->GetPlayer()->GetMinionManager()->GetMinionsSize(); i++)
	{
		MinionPlayer* minion = sceneGame->GetPlayer()->GetMinionManager()->GetMinionIndex(i);
		if (MinionPlayer::StateType::TYPE_IDLE != minion->GetState())
		{
			MinionNum++;
		}
	}

	if (MinionNum >=3)
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
		return true;
	}
	return false;
}
//•`‰æ
void GetMinionTuto::Render()
{
	ui->SetText(textes.at(textIndex));
	ui->Render();
	ui2DDirection->Render();
}