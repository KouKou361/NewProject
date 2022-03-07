#include "Scene.h"
#include "Lib.h"
//初期化処理
void SceneClear::Initialize()
{
	Texture[TextureData::Font]            = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/GameClearFont.png");
	Texture[TextureData::Back]  = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture.png");
	Texture[TextureData::Back1] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture1.png");
	Texture[TextureData::Back2] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture2.png");
	Texture[TextureData::Back3] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture3.png");
	Texture[TextureData::SiroboAnimetion] = TK_Lib::Load::LoadTexture("./Data/Sprite/ScreenLoad/SiroboAnimetion.png");

	const float SoundVolume = 0.5f;
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Clear/SE/GameClear.wav", "GameClear");
	TK_Lib::Lib_Sound::SoundSetVolume("GameClear", SoundVolume);
	TK_Lib::Lib_Sound::SoundPlay("GameClear", false);

	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
	timer = 0;
}
//更新処理
void SceneClear::Update()
{
	timer += TK_Lib::Window::GetElapsedTime();
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	//{
	//	SceneManager::Instance().ChangeScene(new SceneOver);
	//}

	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
		//SceneManager::Instance().ChangeScene(new SceneLoad(new SceneGame));
	}
	if (TK_Lib::Lib_Fade::GetFadeVolume() >= 1.0f)
	{
		//SceneManager::Instance().ChangeScene(new SceneLoad(new SceneGame));
		SceneManager::Instance().ChangeScene(new SceneTitle);
	}
}
//描画処理
void SceneClear::Render()
{
	const  VECTOR2 WindowSize = TK_Lib::Window::GetWindowSize();
	const  float Speed1 = 0.5f;
	const  float Speed2 = 0.7f;
	const  float Speed3 = 0.12f;
	//TK_Lib::Draw::Font("Clear", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 }, 20);
	ImGui::Begin("a");
	static VECTOR2 pos = { 100,100 };
	ImGui::SliderFloat2("pos",&pos.x,0,1000);
	ImGui::End();
	TK_Lib::Draw::Sprite(Texture[TextureData::Back], { 0,0 }, WindowSize, {0,0,1920,1080} );
	TK_Lib::Draw::Sprite(Texture[TextureData::Font], {640,100}, { 758,300 }, { 0,0,758,300 });

	TK_Lib::Draw::Sprite(Texture[TextureData::Back1], { 0,0 }, WindowSize, { 0,Speed1 * static_cast<int>(timer * 60),1920,1080 });
	TK_Lib::Draw::Sprite(Texture[TextureData::Back2], { 0,0 }, WindowSize, { 0,Speed2 * static_cast<int>(timer * 60),1920,1080 });
	TK_Lib::Draw::Sprite(Texture[TextureData::Back3], { 0,0 }, WindowSize, { 0,Speed3 * static_cast<int>(timer * 60),1920,1080 });



	//   const float LoadPos = static_cast<float> (48 * LoadIconIndex);
	
	if (timer >= 2)
	{
		const float LoadSiroboIconIndexX = (static_cast<int>((timer * 60) / 5) / 7) * 256;
		const float LoadSiroboIconIndexY = (static_cast<int>((timer * 60) / 5) % 6) * 256;
		TK_Lib::Draw::Sprite(Texture[TextureData::SiroboAnimetion], { 520,760 }, { 100,100 }, { LoadSiroboIconIndexX,LoadSiroboIconIndexY,256,256 });
		if (static_cast<int>(timer * 60) % 60 >= 30)
		{
			TK_Lib::Draw::JapanFont("PS4コントローラー「〇」キーでスタート画面に！", { 640,800 });
		}
	}


	
}
//デバック
void SceneClear::DegugImgui()
{
	ImGui::Begin(u8"ゲームクリア");
	ImGui::End();
}
//モデル用の処理
void SceneClear::ModelRender()
{
	
}
//終了処理
void SceneClear::End()
{
	TK_Lib::Delete::DeleteTexture(Texture[TextureData::Font]);
	TK_Lib::Delete::DeleteTexture(Texture[TextureData::Back]);
	TK_Lib::Delete::DeleteTexture(Texture[TextureData::SiroboAnimetion]);

	TK_Lib::Lib_Sound::SoundStop("GameClear");

	TK_Lib::Lib_Sound::SoundClear();
}