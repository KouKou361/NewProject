#include "Tuto.h"

Tuto::Tuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();


	uiNextMessage = std::make_unique<UINextMessage>();
	uiNextMessage->Init();

	this->sceneGame = sceneGame;
}

//初期化処理
void Tuto::Init()
{
	TutoWindowUI->Init();
	TutoWindowUI->Update();

	textIndex = 0;
}

//
void Tuto::Update()
{
	TutoWindowUI->Update();
	uiNextMessage->Update();
	uiTimer+=TK_Lib::Window::GetElapsedTime();
}

//初期化処理
bool Tuto::Judge()
{
	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoButton", false);
		//もし次のテキストがあるなら
		if (textes.size()-1 > textIndex)
		{
			uiTimer = 0;
			textIndex++;
			return false;
		}
		//最後のテキストを読み終えたなら
		return true;
	}
	return false;
}

//描画
void Tuto::Render()
{
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();


	//bool DrawFlg = true;

	//[○]で次に進むチカチカ処理
	const float uiRenderTimer = 6;
	const int FrashTime = 2;

	if (uiTimer >= uiRenderTimer)
	{
		if (static_cast<int>(uiTimer) % FrashTime <= 0)
		{
			uiNextMessage->Render();
		}
	}
	//if (DrawFlg)	uiNextMessage->Render();
}