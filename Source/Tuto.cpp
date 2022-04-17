#include "Tuto.h"

Tuto::Tuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();


	uiNextMessage = std::make_unique<UINextMessage>();
	uiNextMessage->Init();

	this->sceneGame = sceneGame;
}
//����������
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

//����������
bool Tuto::Judge()
{
	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoButton", false);
		//�������̃e�L�X�g������Ȃ�
		if (textes.size()-1 > textIndex)
		{
			uiTimer = 0;
			textIndex++;
			return false;
		}
		//�Ō�̃e�L�X�g��ǂݏI�����Ȃ�
		return true;
	}
	return false;
}

//�`��
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