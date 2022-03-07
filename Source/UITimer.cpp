#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
//初期化
void UITimer::Init()
{
	indexTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/HP_gage.png");
	FontUI = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");
	SetGameOverTimer(100);
	FontScaleTimer = 0;
}
//更新処理
void UITimer::Update()
{
	//一秒数える。
	if (FrameTimer >= TK_Lib::Window::GetElapsedTime()*60)
	{
		FrameTimer = 0;
		GameTimer--;
	}
	FrameTimer += TK_Lib::Window::GetElapsedTime();

	if (GameTimer <= 0)GameTimer = 0;


	if (FontScaleTimer > 0)
	{
		FontScaleTimer -= TK_Lib::Window::GetElapsedTime();
	}
	else
	{
		FontScaleTimer = 0;
	}
	
	
}
//描画処理
void UITimer::Render()
{
	const  float X = 100;
	const  float offsetX = 50;
	const  float offsetY = 80;
	const  float Size = 700;
	VECTOR2 screenPos = { 100,10 };
	const  float TargetHpRatio = static_cast<float>(GameTimer) / static_cast<float>(MaxGameTimer) ;

	//黒ゲージ
	TK_Lib::Draw::Sprite(indexTexture, { screenPos.x+500,screenPos.y }, VECTOR2{ Size       ,20 }, VECTOR4{ 0,(60 / 4) * 3,942 / 3,60 / 4 });
	//緑ゲージ
	TK_Lib::Draw::Sprite(indexTexture, { screenPos.x + 500,screenPos.y }, VECTOR2{ TargetHpRatio * Size,20 }, VECTOR4{ 0,0,942 / 3,60 / 4 });

	
	screenPos.x = TK_Lib::Window::GetWindowSize().x/2;
	
	//ゲームオーバータイマーの表示
	{
		float Scale = FontScaleTimer * 15;
		VECTOR4 Color = { 1,1,1,1 };
		if (GameTimer <= 20)
		{
			Color = { 1,0,0,1 };
		}
		text = std::to_string(GameTimer);
		TK_Lib::Draw::Font(text, FontUI, { screenPos.x - 50- Scale,screenPos.y- Scale }, { 50 + (Scale*2),50 + (Scale * 2) }, Color, 30+( FontScaleTimer*2));
	}
	if(GameTimer<=9)
	{
		VECTOR2 Screen = TK_Lib::Window::GetWindowSize();
		TK_Lib::Draw::Font(text, FontUI, { 300,100 }, { Screen.x-600,Screen.y - 200 }, { 1,1,1,0.3f }, 120);
	}


	
	text = "GameOverTimer";
	TK_Lib::Draw::Font(text, FontUI, { screenPos.x - 50,screenPos.y+50 }, { 15,15 }, { 1,1,1,1 }, 10);
	

}

//ゲームオーバーの時間設定
void UITimer::SetGameOverTimer(int timer)
{
	MaxGameTimer = timer;
	GameTimer = MaxGameTimer;
	FrameTimer = 0;

}

void UITimer::AddGameOverTimer(int addTimer)
{
	
	GameTimer += addTimer;

	FontScaleTimer = 2;
	if (GameTimer >= MaxGameTimer) { GameTimer = MaxGameTimer; }
}