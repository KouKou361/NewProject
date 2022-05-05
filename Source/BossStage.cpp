#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "UIDerived.h"
#include "EnemyManager.h"

BossStage::BossStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene)
{
	//�f�[�^�̓o�^
	StageIndex[static_cast<int>(StageType::RENDER_MODEL)]         = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[static_cast<int>(StageType::COLISION_MODEL)]       = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[static_cast<int>(StageType::NAV_MODEL)]            = TK_Lib::Load::GetModel(NavModel);

	//�X�e�[�W
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::RENDER_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::RENDER_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::RENDER_MODEL)]);

	//�e�Ȃ��X�e�[�W
	TK_Lib::Model::Tranceform(StageIndex[     static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[  static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)]);

	//Nav���b�V��
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::NAV_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::NAV_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NAV_MODEL)]);

	//�����蔻��
	TK_Lib::Model::Tranceform(StageIndex[     static_cast<int>(StageType::COLISION_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[  static_cast<int>(StageType::COLISION_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::COLISION_MODEL)]);

	//�X�e�[�W�̃I�u�W�F�N�g�z�u
	stageExport = std::make_unique<Export>();
	stageExport->SetManager(scene);
	stageExport->Loading(SetData);

	sceneGame = scene;
}

//����������
void BossStage::Init()
{
	smoke_driftTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/smoke_drift.png");

	//�����蔻��o�^
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], ModelCollisionType::COLLISION_MODEL, nullptr);
	//�i�r���b�V���o�^						
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::NAV_MODEL)], ModelCollisionType::NAV_MODEL, nullptr);
	//�i�r���b�V���̍\��
	Collision::Instance().NacStageBuild();
	//�X�e�[�W�̃I�u�W�F�N�g�z�u
	stageExport->ObjectSet();

//	TK_Lib::Lib_Sound::SoundPlay("Title", true);
// 
	//UI�̍쐬
	CreateUI();

	//�X�J�C�h�[���̍쐬
	CreateSky();

	//�{�X�J�����̏����ݒ�
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() == 0)	assert(!"�G�����܂���I");
	InitBossCamera();

	timer = 0;
	//�T�E���h�i�����j
	TK_Lib::Lib_Sound::SoundPlay("BossWind",true);


}

//�X�V����
void BossStage::Update()
{
	timer += TK_Lib::Window::GetElapsedTime();

	////�e�X�g
	//ImGui::Begin("CameraEvent");
	//if (ImGui::Button("NextState"))
	//{
	//	switch (eventState)
	//	{
	//	case EventState::LOOK_PLAYER:
	//		eventState = EventState::TURN_CAMERA_LOOK_FRONT;
	//		break;
	//	case EventState::TURN_CAMERA_LOOK_FRONT:
	//		eventState = EventState::LOOK_ENEMY;
	//		TK_Lib::Lib_Sound::SoundStop("BossWind");
	//		break;
	//	case EventState::LOOK_ENEMY:
	//		eventState = EventState::BACK_CAMERA;
	//		break;
	//	case EventState::END:
	//		//eventState = EventState::BackCamera;
	//		break;
	//	}
	//}
	////ImGui::End();
	////

	switch (eventState)
	{
	case EventState::LOOK_PLAYER:

		if (camera->LookatOwner())
		{
			eventState = EventState::TURN_CAMERA_LOOK_FRONT;
		}
		break;
	case EventState::TURN_CAMERA_LOOK_FRONT:
		if (camera->LookatOwnerFront())
		{
			eventState = EventState::LOOK_ENEMY;
			TK_Lib::Lib_Sound::SoundStop("BossWind");
		}

		break;
	case EventState::LOOK_ENEMY:
		if (camera->LookatBoss())
		{
			eventState = EventState::BACK_CAMERA;
		
		}
		break;
	case EventState::BACK_CAMERA:
		if (camera->BackCamera())
		{
			TK_Lib::Lib_Sound::SoundPlay("BossBGM", true);
			eventState = EventState::END;
			sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(sceneGame->GetPlayer()));
			sceneGame->GetPlayer()->ChangeState(Player::State::WAIT);

			//�V���{�̏���
			SummonSirobo();
		}

		break;
	case EventState::END:
		//eventState = EventState::BackCamera;6
		uiNumTower->Update();
		//UI�̍X�V
		uiTimer->Update();
		break;
	}



	/*if (ClearJudge())
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
		if (TK_Lib::Lib_Fade::GetFadeVolume() >= 1.0f)
		{
			TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
			sceneGame->GetStageManager()->GoNextStage();
		}
	}*/
}

//�`��
void BossStage::Render()
{
	VECTOR2 WindowSize = TK_Lib::Window::GetWindowSize();
	const float SmokeSpeed = 100.0f;
	//��
	

	//uiNumTower->Render();

	if (eventState == EventState::END)
	{
		uiTimer->Render();
	}
	else
	{
		VECTOR3 vec = enm->GetPos() - sceneGame->GetPlayer()->GetPos();
		sceneGame->GetPlayer()->Turn(vec);
		TK_Lib::Draw::Sprite(smoke_driftTexture, { 0,100 }, WindowSize, { SmokeSpeed * timer,0,960,540 });
	}



	//���S���̋~�ϑ[�u
	DeadIsResurection();



	
}

//�`��
void BossStage::ModelRender()
{
	Stage::ModelRender();
}

//�I������
void BossStage::End()
{
	TK_Lib::Lib_Sound::SoundStop("BossBGM");
}

//�N���A����
bool BossStage::ClearJudge()
{
	return true;
	//if (sceneGame->GetEnemyManager()->GetEnemiesSize() <= 0)return true;
	//return false;
}


//UI�̍쐬
void BossStage::CreateUI()
{
	uiNumTower = make_shared<UINumTower>(sceneGame);
	uiNumTower->Init();
	
	uiTimer = make_shared<UITimer>();
	uiTimer->Init();
	
}
//�X�J�C�h�[���̍쐬
void BossStage::CreateSky()
{
	VECTOR3 Pos, Angle, Scale;
	Pos = { 0,0,0 };
	Angle = { 0,0,0 };
	Scale = { 0.5f,0.5f,0.5f };
	skyModel = TK_Lib::Load::GetModel("Sky");
	//�X�e�[�W
	TK_Lib::Model::Tranceform(skyModel, Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(skyModel, 0, false);
	TK_Lib::Model::AnimetionUpdate(skyModel);
}
//�{�X�J�����̏����ݒ�
void BossStage::InitBossCamera()
{
	enm = sceneGame->GetEnemyManager()->SearchEnemyTag(EnemyTag::BOSS);
	camera = new CameraBossEntry(sceneGame->GetPlayer(), enm, this);

	eventState = EventState::LOOK_PLAYER;
	sceneGame->GetCameraManager()->ChangeCamera(camera);
	sceneGame->GetPlayer()->ChangeState(Player::State::BOSS_ENTRY, this);
}

//�V���{�̏���
void BossStage::SummonSirobo()
{
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Sirobo> sirobo;
		sirobo = make_shared<Sirobo>();
		sirobo->Init(sceneGame->GetPlayer());
		sirobo->SetPos({ static_cast<float>(i * 8) - 12,0,70 });
		//	sirobo->pos = { 5,0,static_cast<float>(140) };
		sceneGame->GetPlayer()->GetSiroboManager()->Register(sirobo);
	}
}