#include "Scene.h"
#include "Lib.h"
//����������
void SceneClear::Initialize()
{
	texture[static_cast<int>(TextureData::CLEAR_TITLE )] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/GameClearFont.png");
	texture[static_cast<int>(TextureData::BACK )] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture.png");
	texture[static_cast<int>(TextureData::BACK1)] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture1.png");
	texture[static_cast<int>(TextureData::BACK2)] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture2.png");
	texture[static_cast<int>(TextureData::BACK3)] = TK_Lib::Load::LoadTexture("./Data/Sprite/Clear/ClearBackTexture3.png");
	texture[static_cast<int>(TextureData::SIROBO_ANIMETION)] = TK_Lib::Load::LoadTexture("./Data/Sprite/ScreenLoad/SiroboAnimetion.png");

	//�T�E���h�̓ǂݍ���
	CreateSound();

	const float FadeVolume = 0.02f;
	TK_Lib::Lib_Fade::FadeOutBegin(FadeVolume);
	timer = 0;
}
//�X�V����
void SceneClear::Update()
{
	timer += TK_Lib::Window::GetElapsedTime();

	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		const float FadeVolume = 0.02f;
		TK_Lib::Lib_Fade::FadeInBegin(FadeVolume);
	}
	if (TK_Lib::Lib_Fade::GetFadeVolume() >= 1.0f)
	{
		SceneManager::Instance().ChangeScene(new SceneTitle);
	}
}
//�`�揈��
void SceneClear::Render()
{
	const  VECTOR2 WindowSize = TK_Lib::Window::GetWindowSize();
	const  float Speed1 = 0.5f   *60.0f;
	const  float Speed2 = 0.7f   *60.0f;
	const  float Speed3 = 0.12f  *60.0f;

	const VECTOR2 clearTitlePos = { 640,100 };
	const VECTOR2 clearTitleSize = { 758,300 };
	const VECTOR4 clearTitleCut = { 0,0,758,300 };

	//TK_Lib::Draw::Font("Clear", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 }, 20);

	TK_Lib::Draw::Sprite(texture[static_cast<int>(TextureData::BACK)],        { 0,0 },       WindowSize,     {0,0,WindowSize.x,WindowSize.y} );
	TK_Lib::Draw::Sprite(texture[static_cast<int>(TextureData::CLEAR_TITLE)], clearTitlePos, clearTitleSize, clearTitleCut);

	TK_Lib::Draw::Sprite(texture[static_cast<int>(TextureData::BACK1)],       { 0,0 },       WindowSize,     { 0,Speed1 * static_cast<float>(timer),WindowSize.x,WindowSize.y });
	TK_Lib::Draw::Sprite(texture[static_cast<int>(TextureData::BACK2)],       { 0,0 },       WindowSize,     { 0,Speed2 * static_cast<float>(timer),WindowSize.x,WindowSize.y });
	TK_Lib::Draw::Sprite(texture[static_cast<int>(TextureData::BACK3)],       { 0,0 },       WindowSize,     { 0,Speed3 * static_cast<float>(timer),WindowSize.x,WindowSize.y });



	//�V���{�̕`��
	RenderSirobo();


	
}
//�f�o�b�N
void SceneClear::DegugImgui()
{
	ImGui::Begin(u8"�Q�[���N���A");
	ImGui::End();
}
//���f���p�̏���
void SceneClear::ModelRender()
{
	
}
//�I������
void SceneClear::End()
{												  
	TK_Lib::Delete::DeleteTexture(texture[static_cast<int>(TextureData::CLEAR_TITLE)]);
	TK_Lib::Delete::DeleteTexture(texture[static_cast<int>(TextureData::BACK)]);
	TK_Lib::Delete::DeleteTexture(texture[static_cast<int>(TextureData::SIROBO_ANIMETION)]);

	TK_Lib::Lib_Sound::SoundStop("GameClear");

	TK_Lib::Lib_Sound::SoundClear();
}

//�T�E���h�̓ǂݍ���
void SceneClear::CreateSound()
{
	const float SoundVolume = 0.5f;
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Clear/SE/GameClear.wav", "GameClear");
	TK_Lib::Lib_Sound::SoundSetVolume("GameClear", SoundVolume);
	TK_Lib::Lib_Sound::SoundPlay("GameClear", false);
}


//�V���{�̕`��
void SceneClear::RenderSirobo()
{
	//   const float LoadPos = static_cast<float> (48 * LoadIconIndex);

	//��b
	const float Seconds = 60.0f;

	//�V���{���`�悳��鎞��
	const float SiroboRenderTime = 2.0f;
	//�V���{�e�N�X�`���̈������̃`�b�v�傫��
	const float SiroboTextureSize = 256.0f;
	//�V���{�e�N�X�`���̃`�b�vX��
	const int SiroboChipX = 7;
	//�V���{�e�N�X�`���̃`�b�vY��
	const int SiroboChipY = 6;
	//�V���{�A�j���V�����X�s�[�h
	const float SiroboAnimetionSpeed = 0.2f;
	//�V���{�e�N�X�`���̈ʒu
	const VECTOR2 SiroboPos = { 520,760 };
	//�V���{�e�N�X�`���̃T�C�Y
	const VECTOR2 SiroboSize = { 100,100 };

	//�t�H���g�̓_�ŃX�s�[�h
	const float FlashFontSpeed = 30.0f;

	const VECTOR2 FontPos = { 640,800 };


	if (timer >= SiroboRenderTime)
	{
		const float LoadSiroboIconIndexX = static_cast<float>(static_cast<int>((timer * Seconds) * SiroboAnimetionSpeed) / SiroboChipX) * SiroboTextureSize;
		const float LoadSiroboIconIndexY = static_cast<float>(static_cast<int>((timer * Seconds) * SiroboAnimetionSpeed) % SiroboChipY) * SiroboTextureSize;
		TK_Lib::Draw::Sprite(texture[static_cast<int>(TextureData::SIROBO_ANIMETION)], SiroboPos, SiroboSize, { LoadSiroboIconIndexX,LoadSiroboIconIndexY,SiroboTextureSize,SiroboTextureSize });
		if (static_cast<int>(timer * Seconds) % static_cast<int>(Seconds) >= FlashFontSpeed)
		{
			TK_Lib::Draw::JapanFont("PS4�R���g���[���[�u�Z�v�L�[�ŃX�^�[�g��ʂɁI", FontPos);
		}
	}
}