#include "Tuto.h"

Tuto::Tuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();


	uiNextMessage = std::make_unique<UINextMessage>();
	uiNextMessage->Init();

	this->sceneGame = sceneGame;
}
//初期化処理
void Tuto::Init()
{

	textIndex = 0;
}
void Tuto::Update()
{
	ui->Update();
	uiNextMessage->Update();
	uiTimer++;
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
	ui->SetText(textes.at(textIndex));
	ui->Render();


	bool DrawFlg = true;
	if (uiTimer >= 300)
	{
		if (uiTimer % 100 <= 25)
		{
			DrawFlg = false;
		}
	}
	if (DrawFlg)	uiNextMessage->Render();
}