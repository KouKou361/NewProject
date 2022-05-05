#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
//������
void UITimer::Init()
{
	TextureIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/HP_gage.png");
	fontUI = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");

	//�Q�[���I�[�o�[����
	const int GameOverTimer = 100;
	SetGameOverTimer(GameOverTimer);
	fontScaleTimer = 0;
}
//�X�V����
void UITimer::Update()
{
	//�Q�[���I�[�o�[�^�C�}�[�̍X�V����
	gameTimer -= TK_Lib::Window::GetElapsedTime();
	if (gameTimer <= 0)gameTimer = 0;

	//�t�H���g�̑傫���̍X�V����
	UpdateFontScaleTimer();

	
	
}
//�`�揈��
void UITimer::Render()
{
	//�Q�[�W�̕\��
	GaugeRender();
	//�Q�[���I�[�o�[�^�C�}�[�̕\��
	TextRender();
	
}

//�Q�[���I�[�o�[�̎��Ԑݒ�
void UITimer::SetGameOverTimer(float timer)
{
	maxGameTimer = timer;
	gameTimer = maxGameTimer;

}

void UITimer::AddGameOverTimer(float addTimer)
{
	
	gameTimer += addTimer;
	//�t�H���g���傫���Ȃ鎞��
	const float ScaleTime = 2.0f;
	fontScaleTimer = ScaleTime;

	if (gameTimer >= maxGameTimer) { gameTimer = maxGameTimer; }
}

//�t�H���g�̑傫���̍X�V����
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

//�Q�[�W�̕\��
void UITimer::GaugeRender()
{
	//const  float X = 100;
	//const  float offsetX = 50;
	//const  float offsetY = 80;
	
	//�Q�[�W�T�C�Y
	const  VECTOR2 GaugeSize = { 700,20 };

	//�Q�[�W��\������ʒu
	VECTOR2 GaugePos = { 600,10 };

	//�Q�[�W�^�C�}�[�̔䗦
	const  float TimerRatio = static_cast<float>(gameTimer) / static_cast<float>(maxGameTimer);

	//�������̃Q�[�W�`�b�v�̃T�C�Y
	const VECTOR2 chipSize = { 314,15 };


	//���Q�[�W
	TK_Lib::Draw::Sprite(TextureIndex, GaugePos, VECTOR2{ GaugeSize.x             ,GaugeSize.y },   VECTOR4{ 0,chipSize.y * 3,chipSize.x,chipSize.y});
	//�΃Q�[�W						   																						  		
	TK_Lib::Draw::Sprite(TextureIndex, GaugePos, VECTOR2{ TimerRatio * GaugeSize.x,GaugeSize.y },   VECTOR4{ 0,             0,chipSize.x,chipSize.y});



}
//�Q�[���I�[�o�[�^�C�}�[�̕\��
void UITimer::TextRender()
{
	//�X�N���[���ɕ\������ʒu
	VECTOR2 screenPos;
	screenPos.x = TK_Lib::Window::GetWindowSize().x / 2;
	screenPos.y = 10;
	
	//�e�L�X�g�̑傫��
	const float Scale = fontScaleTimer * 15;

	//�F
	VECTOR4 Color = { 1,1,1,1 };

	//�Ԃ��e�L�X�g�̕\��
	const float RedColorTextTimer = 20.0f;
	//�e�L�X�g�̈ʒu
	const VECTOR2 FontPos = { screenPos.x - 50 - Scale,screenPos.y - Scale };
	//�e�L�X�g�̃T�C�Y
	const VECTOR2 FontSize = { 50 + (Scale * 2),50 + (Scale * 2) };
	//�����ƕ����Ƃ̊�
	const float FontSpace = 30 + (fontScaleTimer * 2);

	text = std::to_string(static_cast<int>(gameTimer));
	if (gameTimer <= RedColorTextTimer)	Color = { 1,0,0,1 };
	//�������ԃe�L�X�g�̕\��
	TK_Lib::Draw::Font(text, fontUI, FontPos, FontSize, Color, FontSpace);
	


	//�X�N���[�������ς��ɏo�邨�����ȃQ�[���I�[�o�[�^�C�}�[�̕\��
	BigGameOverTimeText(10);
	//�Q�[���I�[�o�[�e�L�X�g
	GameOverText();
	
}

//�X�N���[�������ς��ɏo�邨�����ȃQ�[���I�[�o�[�^�C�}�[�̕\��
void UITimer::BigGameOverTimeText(float RenderTime)
{
	if (gameTimer >= RenderTime)return;
	//�X�N���[���ɕ\������ʒu
	const VECTOR2 Screen = TK_Lib::Window::GetWindowSize();
	//�e�L�X�g�̈ʒu
	const VECTOR2 FontPos = { 300,100 };
	//�e�L�X�g�̃T�C�Y
	const VECTOR2 FontSize = { Screen.x - 600,Screen.y - 200 };
	//�e�L�X�g�̐F
	const VECTOR4 FontColor = { 1,1,1,0.3f };
	//�����ƕ����Ƃ̊�
	const float FontSpace = 120;


	//�X�N���[�������ς���GameOverTime��\��
	TK_Lib::Draw::Font(text, fontUI, FontPos, FontSize, FontColor, FontSpace);

}

//�Q�[���I�[�o�[�e�L�X�g
void UITimer::GameOverText()
{
	//�X�N���[���ɕ\������ʒu
	VECTOR2 screenPos;
	screenPos.x = TK_Lib::Window::GetWindowSize().x / 2-50;
	screenPos.y = 60;

	text = "GameOverTimer";
	const VECTOR2 GameOverTextSize = { 15,15 };
	const VECTOR4 GameOverTextColor = { 1,1,1,1};
		
	TK_Lib::Draw::Font(text, fontUI,screenPos, GameOverTextSize, GameOverTextColor);
}