#include "Tuto.h"
#include "Collision.h"
#include "Charactor.h"
#include "Scene.h"

MoveTuto::MoveTuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();

	this->sceneGame = sceneGame;
}
//‰Šú‰»ˆ—
void MoveTuto::Init()
{
	ui = make_unique<UITuto>();
	ui->Init();
	TextIndex = 0;

	circle.Pos = { 0,0,0 };
	circle.Radius = 10.0f;
	circle.Weight = 0;

	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos({ circle.Pos });
	}

}
void MoveTuto::Update()
{
	ui->Update();

	ui2DDirection->Update();
	ui2DDirection->SetTargetPos({ circle.Pos });
}

//‰Šú‰»ˆ—
bool MoveTuto::Judge()
{
	Charactor* player;
	player = sceneGame->GetPlayer();
	VECTOR3 outA, outB;

	if (Collision::Instance().SphereVsSphere(
		player->GetPos(),player->GetWeight(),player->GetCollisionRadius(),
		circle.Pos, circle.Weight, circle.Radius,outA,outB
		))
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
		return true;

	}
	return false;
}
//•`‰æ
void MoveTuto::Render()
{
	ui->SetText(textes.at(TextIndex));
	ui->Render();
	ui2DDirection->Render();

	TK_Lib::Debug3D::Circle(circle.Pos, circle.Radius);
}