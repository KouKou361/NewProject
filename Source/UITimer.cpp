#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
//初期化
void UITimer::Init()
{
	TextureIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/HP_gage.png");
	fontUI = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");

	//ゲームオーバー時間
	const int GameOverTimer = 100;
	SetGameOverTimer(GameOverTimer);
	fontScaleTimer = 0;
}
//更新処理
void UITimer::Update()
{
	//ゲームオーバータイマーの更新処理
	gameTimer -= TK_Lib::Window::GetElapsedTime();
	if (gameTimer <= 0)gameTimer = 0;

	//フォントの大きさの更新処理
	UpdateFontScaleTimer();

	
	
}
//描画処理
void UITimer::Render()
{
	//ゲージの表示
	GaugeRender();
	//ゲームオーバータイマーの表示
	TextRender();
	
}

//ゲームオーバーの時間設定
void UITimer::SetGameOverTimer(float timer)
{
	maxGameTimer = timer;
	gameTimer = maxGameTimer;

}

void UITimer::AddGameOverTimer(float addTimer)
{
	
	gameTimer += addTimer;
	//フォントが大きくなる時間
	const float ScaleTime = 2.0f;
	fontScaleTimer = ScaleTime;

	if (gameTimer >= maxGameTimer) { gameTimer = maxGameTimer; }
}

//フォントの大きさの更新処理
void UITimer::UpdateFontScaleTimer()
{
	if (fontScaleTimer > 0)
	{
		fontScaleTimer -= TK_Lib::Window::GetElapsedTime();
	}
	else
	{
		fontScaleTimer = 0;
	}
}

//ゲージの表示
void UITimer::GaugeRender()
{
	//const  float X = 100;
	//const  float offsetX = 50;
	//const  float offsetY = 80;
	
	//ゲージサイズ
	const  VECTOR2 GaugeSize = { 700,20 };

	//ゲージを表示する位置
	VECTOR2 GaugePos = { 600,10 };

	//ゲージタイマーの比率
	const  float TimerRatio = static_cast<float>(gameTimer) / static_cast<float>(maxGameTimer);

	//一つあたりのゲージチップのサイズ
	const VECTOR2 chipSize = { 314,15 };


	//黒ゲージ
	TK_Lib::Draw::Sprite(TextureIndex, GaugePos, VECTOR2{ GaugeSize.x             ,GaugeSize.y },   VECTOR4{ 0,chipSize.y * 3,chipSize.x,chipSize.y});
	//緑ゲージ						   																						  		
	TK_Lib::Draw::Sprite(TextureIndex, GaugePos, VECTOR2{ TimerRatio * GaugeSize.x,GaugeSize.y },   VECTOR4{ 0,             0,chipSize.x,chipSize.y});



}
//ゲームオーバータイマーの表示
void UITimer::TextRender()
{
	//スクリーンに表示する位置
	VECTOR2 screenPos;
	screenPos.x = TK_Lib::Window::GetWindowSize().x / 2;
	screenPos.y = 10;
	
	//テキストの大きさ
	const float Scale = fontScaleTimer * 15;

	//色
	VECTOR4 Color = { 1,1,1,1 };

	//赤いテキストの表示
	const float RedColorTextTimer = 20.0f;
	//テキストの位置
	const VECTOR2 FontPos = { screenPos.x - 50 - Scale,screenPos.y - Scale };
	//テキストのサイズ
	const VECTOR2 FontSize = { 50 + (Scale * 2),50 + (Scale * 2) };
	//文字と文字との間
	const float FontSpace = 30 + (fontScaleTimer * 2);

	text = std::to_string(static_cast<int>(gameTimer));
	if (gameTimer <= RedColorTextTimer)	Color = { 1,0,0,1 };
	//制限時間テキストの表示
	TK_Lib::Draw::Font(text, fontUI, FontPos, FontSize, Color, FontSpace);
	


	//スクリーンいっぱいに出るおおきなゲームオーバータイマーの表示
	BigGameOverTimeText(10);
	//ゲームオーバーテキスト
	GameOverText();
	
}

//スクリーンいっぱいに出るおおきなゲームオーバータイマーの表示
void UITimer::BigGameOverTimeText(float RenderTime)
{
	if (gameTimer >= RenderTime)return;
	//スクリーンに表示する位置
	const VECTOR2 Screen = TK_Lib::Window::GetWindowSize();
	//テキストの位置
	const VECTOR2 FontPos = { 300,100 };
	//テキストのサイズ
	const VECTOR2 FontSize = { Screen.x - 600,Screen.y - 200 };
	//テキストの色
	const VECTOR4 FontColor = { 1,1,1,0.3f };
	//文字と文字との間
	const float FontSpace = 120;


	//スクリーンいっぱいにGameOverTimeを表示
	TK_Lib::Draw::Font(text, fontUI, FontPos, FontSize, FontColor, FontSpace);

}

//ゲームオーバーテキスト
void UITimer::GameOverText()
{
	//スクリーンに表示する位置
	VECTOR2 screenPos;
	screenPos.x = TK_Lib::Window::GetWindowSize().x / 2-50;
	screenPos.y = 60;

	text = "GameOverTimer";
	const VECTOR2 GameOverTextSize = { 15,15 };
	const VECTOR4 GameOverTextColor = { 1,1,1,1};
		
	TK_Lib::Draw::Font(text, fontUI,screenPos, GameOverTextSize, GameOverTextColor);
}