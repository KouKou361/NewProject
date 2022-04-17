#include "Scene.h"
#include "Lib.h"
//����������
void SceneTitle::Initialize()
{
	fontTexture=TK_Lib::Load::LoadTexture("./Data/Sprite/fonts/font0.png");
	titleSceneBackTitleTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/unnamed.png");
	smoke_driftTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/smoke_drift.png");
	titleLogoTexture= TK_Lib::Load::LoadTexture("./Data/Sprite/Title/TitleLogo.png");
	playerTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/player.png");

	minionTextue = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/Minion.png");

	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Title/BGM/TitleBGM.wav","TitleBGM");
	TK_Lib::Lib_Sound::SoundPlay("TitleBGM",true);
	TK_Lib::Lib_Sound::SoundSetVolume("TitleBGM", 0.5f);

	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
}
//�X�V����
void SceneTitle::Update()
{
	
	timer += TK_Lib::Window::GetElapsedTime(); 

	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
		//SceneManager::Instance().ChangeScene(new SceneLoad(new SceneGame));
	}
	if(TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		SceneManager::Instance().ChangeScene(new SceneLoad(new SceneGame));
		//SceneManager::Instance().ChangeScene(new SceneClear);
	}

}
//�`�揈��
void SceneTitle::Render()
{
	VECTOR2 WindowSize= TK_Lib::Window::GetWindowSize();

	const float ScreenBackSpeed = 50.0f;
	const float SmokeSpeed = 150.0f;
	const float PlayerSpeed = XMConvertToRadians(50);
	const float SinVolume = 25.0f;
	const float cosVolume = 50.0f;
	
	//�o�b�N�X�N���[��
	TK_Lib::Draw::Sprite(titleSceneBackTitleTexture, { 0,0 }, WindowSize, { ScreenBackSpeed*timer,0,1000,750 });
	//�V���{
	TK_Lib::Draw::Sprite(minionTextue, { 90,400 + cosf(PlayerSpeed * timer) * cosVolume }, { 200,200 }, { 0,0,76,97 });
	//�v���C���[
	TK_Lib::Draw::Sprite(playerTexture, {-100,300 + sinf(PlayerSpeed * timer) * SinVolume }, {900,900 }, { 0,0,624,689 });
	//�V���{
	TK_Lib::Draw::Sprite(minionTextue, { 1500,500 + cosf(PlayerSpeed * timer) * cosVolume }, { 200,200 }, { 0,0,76,97 });
	
	//��
	TK_Lib::Draw::Sprite(smoke_driftTexture, { 0,100 }, WindowSize, { SmokeSpeed * timer,0,960,540 });
	//�^�C�g�����S
	TK_Lib::Draw::Sprite(titleLogoTexture, { WindowSize.x / 2 - 500,100 }, { 900,300 }, { 0,0,1620,480 });

	if(static_cast<int>(timer*60) %60>=30)
	TK_Lib::Draw::JapanFont("PS4�R���g���[���[�u�Z�v�L�[�ŃX�^�[�g�I", {700,500});

	//TK_Lib::Draw::Font("TITLE", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 },20);
	//TK_Lib::Draw::Sprite(MinionTexture, { MinionSpeed,WindowSize.y / 2 }, { 76,97 }, { 0,0,76,97 });
	
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