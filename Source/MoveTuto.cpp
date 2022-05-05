#include "Tuto.h"
#include "Collision.h"
#include "Charactor.h"
#include "Scene.h"

MoveTuto::MoveTuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();

	this->sceneGame = sceneGame;
}
//‰Šú‰»ˆ—
void MoveTuto::Init()
{
	//ui = make_unique<UITuto>();
	TutoWindowUI->Init();
	TutoWindowUI->Update();

	textIndex = 0;

	circle.pos = { 0,0,0 };
	circle.radius = 10.0f;
	circle.weight = 0;

	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos({ circle.pos });
	}

}
void MoveTuto::Update()
{
	TutoWindowUI->Update();

	ui2DDirection->Update();
}

//‰Šú‰»ˆ—
bool MoveTuto::Judge()
{
	Charactor* player;
	player = sceneGame->GetPlayer();
	VECTOR3 outA, outB;

	if (Collision::Instance().SphereVsSphere(
		player->GetPos(),player->GetWeight(),player->GetCollisionRadius(),
		circle.pos, circle.weight, circle.radius,outA,outB
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
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();
	ui2DDirection->Render();

	TK_Lib::Debug3D::Circle(circle.pos, circle.radius);
}