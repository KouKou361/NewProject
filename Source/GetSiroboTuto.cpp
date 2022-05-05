#include "Tuto.h"
#include "Collision.h"
#include "Charactor.h"
#include "Scene.h"
#include "SiroboPlayer.h"

GetSiroboTuto::GetSiroboTuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();
	this->sceneGame = sceneGame;
}

//初期化処理
void GetSiroboTuto::Init()
{
	//ui = make_unique<UITuto>();
	TutoWindowUI->Init();
	TutoWindowUI->Update();

	textIndex = 0;

	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos({ 100,0,100 });
	}

	//シロボの生成
	SummonSirobo();

}

//更新処理
void GetSiroboTuto::Update()
{
	TutoWindowUI->Update();

	//目標位置の更新処理
	ui2DDirection->Update();

}

//判別処理(全てのシロボを回収した場合：return true)
bool GetSiroboTuto::Judge()
{
	int SiroboNum = 0;
	for (int i = 0; i < sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboIndex(i);
		if (Sirobo::StateType::TYPE_IDLE != sirobo->GetState())
		{
			SiroboNum++;
		}
	}
	//シロボの数
	const int MaxSiroboNum = sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboSize();

	if (SiroboNum >= MaxSiroboNum)
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
		return true;
	}
	return false;
}

//描画
void GetSiroboTuto::Render()
{
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();
	ui2DDirection->Render();
}

//シロボの生成
void GetSiroboTuto::SummonSirobo()
{
	const float PosX = 100.0f;
	const float PosY = 100.0f;

	const int SiroboNum = 3;
	for (int i = 0; i < SiroboNum; i++)
	{
		shared_ptr<Sirobo>sirobo;
		sirobo = make_shared<Sirobo>();
		sirobo->Init(sceneGame->GetPlayer());
		sirobo->SetPos({ PosX,0,static_cast<float>(i * 8) + PosY });
		sceneGame->GetPlayer()->GetSiroboManager()->Register(sirobo);
	}

}