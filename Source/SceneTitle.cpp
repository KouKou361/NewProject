#include "Scene.h"
#include "Lib.h"
//����������
void SceneTitle::Initialize()
{	
	//�e�N�X�`���̓ǂݍ���
	LoadTexture();
	//�T�E���h�̓ǂݍ���
	LoadSound();
	//�t�F�[�h�A�E�g
	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
}
//�X�V����
void SceneTitle::Update()
{
	
	timer += TK_Lib::Window::GetElapsedTime(); 

	//�Q�[���X�^�[�g
	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
	}
	if(TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		SceneManager::Instance().ChangeScene(new SceneLoad(new SceneGame));
	}

}
//�`�揈��
void SceneTitle::Render()
{
	//�o�b�N�X�N���[��
	RenderBackScreen();

	//�V���{
	RenderSirobo();

	//�v���C���[
	RenderPlayer();

	//�V���{�Q
	RenderSirobo2();

	//��
	RenderSmoke();

	//�^�C�g���t�H���g
	RenderTitleFont();

	//�X�^�[�g�t�H���g
	RenderStartFont();


	//TK_Lib::Draw::Font("TITLE", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 },20);
	//TK_Lib::Draw::Sprite(SiroboTexture, { SiroboSpeed,WindowSize.y / 2 }, { 76,97 }, { 0,0,76,97 });
	
}
//�f�o�b�N
void SceneTitle::DegugImgui()
{
	ImGui::Begin(u8"�Q�[���^�C�g��");
	ImGui::End();
}
//���f���p�̏���
void SceneTitle::ModelRender()
{

}
//�I������
void SceneTitle::End()
{
	TK_Lib::Lib_Sound::SoundStop("TitleBGM");
	TK_Lib::Lib_Sound::SoundClear();
	TK_Lib::Delete::DeleteTexture(fontTexture);
}

//�e�N�X�`���̓ǂݍ���
void SceneTitle::LoadTexture()
{
	fontTexture                = TK_Lib::Load::LoadTexture("./Data/Sprite/fonts/font0.png");
	titleSceneBackTitleTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/unnamed.png");
	smoke_driftTexture         = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/smoke_drift.png");
	titleLogoTexture           = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/TitleLogo.png");
	playerTexture              = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/player.png");

	siroboTextue               = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/Sirobo.png");

}
//�T�E���h�̓ǂݍ���
void SceneTitle::LoadSound()
{
	const float SoundVolume = 0.5f;
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Title/BGM/TitleBGM.wav", "TitleBGM");
	TK_Lib::Lib_Sound::SoundPlay("TitleBGM", true);
	TK_Lib::Lib_Sound::SoundSetVolume("TitleBGM", SoundVolume);

}

//�o�b�N�X�N���[��
void SceneTitle::RenderBackScreen()
{
	//�ʒu
	const VECTOR2 pos = { 0,0 };
	//�傫��
	const VECTOR2 size = TK_Lib::Window::GetWindowSize();
	//����
	const float ScreenBackSpeed = 50.0f;
	//�؂���ʒu
	const VECTOR4 cut = { ScreenBackSpeed*timer,0,1000,750 };

	//�o�b�N�X�N���[��
	TK_Lib::Draw::Sprite(titleSceneBackTitleTexture, pos, size, cut);
}
//�V���{
void SceneTitle::RenderSirobo()
{
	//����
	constexpr float PlayerSpeed = XMConvertToRadians(50);
	const float cosVolume = 50.0f;
	//�ʒu
	const VECTOR2 pos = { 90,400 + cosf(PlayerSpeed * timer) * cosVolume };
	//�傫��
	const VECTOR2 size = { 200,200 };
	//�؂���ʒu
	const VECTOR4 cut = {0,0,76,97 };

	//�V���{
	TK_Lib::Draw::Sprite(siroboTextue,pos, size, cut);

}
//�v���C���[
void SceneTitle::RenderPlayer()
{
	//����
	constexpr float PlayerSpeed = XMConvertToRadians(50);
	const float SinVolume = 50.0f;
	//�ʒu
	const VECTOR2 pos = { -100,300 + sinf(PlayerSpeed * timer) * SinVolume };
	//�傫��
	const VECTOR2 size = { 900,900 };
	//�؂���ʒu
	const VECTOR4 cut = { 0,0,624,689 };

	//�v���C���[
	TK_Lib::Draw::Sprite(playerTexture, pos, size, cut);

}
//�V���{�Q
void SceneTitle::RenderSirobo2()
{
	//����
	constexpr float PlayerSpeed = XMConvertToRadians(50);
	const float cosVolume = 50.0f;
	//�ʒu
	const VECTOR2 pos = { 1500,500 + cosf(PlayerSpeed * timer) * cosVolume };
	//�傫��
	const VECTOR2 size = { 200,200 };
	//�؂���ʒu
	const VECTOR4 cut = { 0,0,76,97 };

	//�V���{
	TK_Lib::Draw::Sprite(siroboTextue, pos, size, cut);


}
//��
void SceneTitle::RenderSmoke()
{
	//����
	const float SmokeSpeed = 150.0f;
	//�ʒu
	const VECTOR2 pos = { 0,100 };
	//�傫��
	const VECTOR2 size = TK_Lib::Window::GetWindowSize();;
	//�؂���ʒu
	const VECTOR4 cut = { SmokeSpeed * timer,0,960,540 };
	//��
	TK_Lib::Draw::Sprite(smoke_driftTexture, pos, size, cut);

}
//�^�C�g���t�H���g
void SceneTitle::RenderTitleFont()
{
	//����
	const float SmokeSpeed = 150.0f;
	//�ʒu
	const VECTOR2 pos = { TK_Lib::Window::GetWindowSize().x / 2 - 500,100 };
	//�傫��
	const VECTOR2 size = { 900,300 };
	//�؂���ʒu
	const VECTOR4 cut = { 0,0,1620,480 };
	//�^�C�g�����S
	TK_Lib::Draw::Sprite(titleLogoTexture,pos,size,cut);


}
//�X�^�[�g�t�H���g
void SceneTitle::RenderStartFont()
{    //��b
	const float Seconds = 60.0f;
	//�V���{���`�悳��鎞��
	const float Frash = 30.0f;
	//�t�H���g�̈ʒu
	const VECTOR2 FontPos = { 700,500 };

	if (static_cast<int>(timer * Seconds) % static_cast<int>(Seconds) >= Frash)
		TK_Lib::Draw::JapanFont("PS4�R���g���[���[�u�Z�v�L�[�ŃX�^�[�g�I", FontPos);
}