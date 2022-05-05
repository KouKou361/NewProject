#include "Scene.h"
#include "Lib.h"
//初期化処理
void SceneTitle::Initialize()
{	
	//テクスチャの読み込み
	LoadTexture();
	//サウンドの読み込み
	LoadSound();
	//フェードアウト
	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
}
//更新処理
void SceneTitle::Update()
{
	
	timer += TK_Lib::Window::GetElapsedTime(); 

	//ゲームスタート
	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
	}
	if(TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		SceneManager::Instance().ChangeScene(new SceneLoad(new SceneGame));
	}

}
//描画処理
void SceneTitle::Render()
{
	//バックスクリーン
	RenderBackScreen();

	//シロボ
	RenderSirobo();

	//プレイヤー
	RenderPlayer();

	//シロボ２
	RenderSirobo2();

	//煙
	RenderSmoke();

	//タイトルフォント
	RenderTitleFont();

	//スタートフォント
	RenderStartFont();


	//TK_Lib::Draw::Font("TITLE", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 },20);
	//TK_Lib::Draw::Sprite(SiroboTexture, { SiroboSpeed,WindowSize.y / 2 }, { 76,97 }, { 0,0,76,97 });
	
}
//デバック
void SceneTitle::DegugImgui()
{
	ImGui::Begin(u8"ゲームタイトル");
	ImGui::End();
}
//モデル用の処理
void SceneTitle::ModelRender()
{

}
//終了処理
void SceneTitle::End()
{
	TK_Lib::Lib_Sound::SoundStop("TitleBGM");
	TK_Lib::Lib_Sound::SoundClear();
	TK_Lib::Delete::DeleteTexture(fontTexture);
}

//テクスチャの読み込み
void SceneTitle::LoadTexture()
{
	fontTexture                = TK_Lib::Load::LoadTexture("./Data/Sprite/fonts/font0.png");
	titleSceneBackTitleTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/unnamed.png");
	smoke_driftTexture         = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/smoke_drift.png");
	titleLogoTexture           = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/TitleLogo.png");
	playerTexture              = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/player.png");

	siroboTextue               = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/Sirobo.png");

}
//サウンドの読み込み
void SceneTitle::LoadSound()
{
	const float SoundVolume = 0.5f;
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Title/BGM/TitleBGM.wav", "TitleBGM");
	TK_Lib::Lib_Sound::SoundPlay("TitleBGM", true);
	TK_Lib::Lib_Sound::SoundSetVolume("TitleBGM", SoundVolume);

}

//バックスクリーン
void SceneTitle::RenderBackScreen()
{
	//位置
	const VECTOR2 pos = { 0,0 };
	//大きさ
	const VECTOR2 size = TK_Lib::Window::GetWindowSize();
	//速さ
	const float ScreenBackSpeed = 50.0f;
	//切り取り位置
	const VECTOR4 cut = { ScreenBackSpeed*timer,0,1000,750 };

	//バックスクリーン
	TK_Lib::Draw::Sprite(titleSceneBackTitleTexture, pos, size, cut);
}
//シロボ
void SceneTitle::RenderSirobo()
{
	//速さ
	constexpr float PlayerSpeed = XMConvertToRadians(50);
	const float cosVolume = 50.0f;
	//位置
	const VECTOR2 pos = { 90,400 + cosf(PlayerSpeed * timer) * cosVolume };
	//大きさ
	const VECTOR2 size = { 200,200 };
	//切り取り位置
	const VECTOR4 cut = {0,0,76,97 };

	//シロボ
	TK_Lib::Draw::Sprite(siroboTextue,pos, size, cut);

}
//プレイヤー
void SceneTitle::RenderPlayer()
{
	//速さ
	constexpr float PlayerSpeed = XMConvertToRadians(50);
	const float SinVolume = 50.0f;
	//位置
	const VECTOR2 pos = { -100,300 + sinf(PlayerSpeed * timer) * SinVolume };
	//大きさ
	const VECTOR2 size = { 900,900 };
	//切り取り位置
	const VECTOR4 cut = { 0,0,624,689 };

	//プレイヤー
	TK_Lib::Draw::Sprite(playerTexture, pos, size, cut);

}
//シロボ２
void SceneTitle::RenderSirobo2()
{
	//速さ
	constexpr float PlayerSpeed = XMConvertToRadians(50);
	const float cosVolume = 50.0f;
	//位置
	const VECTOR2 pos = { 1500,500 + cosf(PlayerSpeed * timer) * cosVolume };
	//大きさ
	const VECTOR2 size = { 200,200 };
	//切り取り位置
	const VECTOR4 cut = { 0,0,76,97 };

	//シロボ
	TK_Lib::Draw::Sprite(siroboTextue, pos, size, cut);


}
//煙
void SceneTitle::RenderSmoke()
{
	//速さ
	const float SmokeSpeed = 150.0f;
	//位置
	const VECTOR2 pos = { 0,100 };
	//大きさ
	const VECTOR2 size = TK_Lib::Window::GetWindowSize();;
	//切り取り位置
	const VECTOR4 cut = { SmokeSpeed * timer,0,960,540 };
	//煙
	TK_Lib::Draw::Sprite(smoke_driftTexture, pos, size, cut);

}
//タイトルフォント
void SceneTitle::RenderTitleFont()
{
	//速さ
	const float SmokeSpeed = 150.0f;
	//位置
	const VECTOR2 pos = { TK_Lib::Window::GetWindowSize().x / 2 - 500,100 };
	//大きさ
	const VECTOR2 size = { 900,300 };
	//切り取り位置
	const VECTOR4 cut = { 0,0,1620,480 };
	//タイトルロゴ
	TK_Lib::Draw::Sprite(titleLogoTexture,pos,size,cut);


}
//スタートフォント
void SceneTitle::RenderStartFont()
{    //一秒
	const float Seconds = 60.0f;
	//シロボが描画される時間
	const float Frash = 30.0f;
	//フォントの位置
	const VECTOR2 FontPos = { 700,500 };

	if (static_cast<int>(timer * Seconds) % static_cast<int>(Seconds) >= Frash)
		TK_Lib::Draw::JapanFont("PS4コントローラー「〇」キーでスタート！", FontPos);
}