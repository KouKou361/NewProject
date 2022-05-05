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
	//データの登録
	StageIndex[static_cast<int>(StageType::RENDER_MODEL)]         = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[static_cast<int>(StageType::COLISION_MODEL)]       = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[static_cast<int>(StageType::NAV_MODEL)]            = TK_Lib::Load::GetModel(NavModel);

	//ステージ
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::RENDER_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::RENDER_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::RENDER_MODEL)]);

	//影なしステージ
	TK_Lib::Model::Tranceform(StageIndex[     static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[  static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)]);

	//Navメッシュ
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::NAV_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::NAV_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NAV_MODEL)]);

	//当たり判定
	TK_Lib::Model::Tranceform(StageIndex[     static_cast<int>(StageType::COLISION_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[  static_cast<int>(StageType::COLISION_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::COLISION_MODEL)]);

	//ステージのオブジェクト配置
	stageExport = std::make_unique<Export>();
	stageExport->SetManager(scene);
	stageExport->Loading(SetData);

	sceneGame = scene;
}

//初期化処理
void BossStage::Init()
{
	smoke_driftTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Title/smoke_drift.png");

	//当たり判定登録
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], ModelCollisionType::COLLISION_MODEL, nullptr);
	//ナビメッシュ登録						
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::NAV_MODEL)], ModelCollisionType::NAV_MODEL, nullptr);
	//ナビメッシュの構成
	Collision::Instance().NacStageBuild();
	//ステージのオブジェクト配置
	stageExport->ObjectSet();

//	TK_Lib::Lib_Sound::SoundPlay("Title", true);
// 
	//UIの作成
	CreateUI();

	//スカイドームの作成
	CreateSky();

	//ボスカメラの初期設定
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() == 0)	assert(!"敵がいません！");
	InitBossCamera();

	timer = 0;
	//サウンド（砂煙）
	TK_Lib::Lib_Sound::SoundPlay("BossWind",true);


}

//更新処理
void BossStage::Update()
{
	timer += TK_Lib::Window::GetElapsedTime();

	////テスト
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

			//シロボの召喚
			SummonSirobo();
		}

		break;
	case EventState::END:
		//eventState = EventState::BackCamera;6
		uiNumTower->Update();
		//UIの更新
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

//描画
void BossStage::Render()
{
	VECTOR2 WindowSize = TK_Lib::Window::GetWindowSize();
	const float SmokeSpeed = 100.0f;
	//煙
	

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



	//死亡時の救済措置
	DeadIsResurection();



	
}

//描画
void BossStage::ModelRender()
{
	Stage::ModelRender();
}

//終了処理
void BossStage::End()
{
	TK_Lib::Lib_Sound::SoundStop("BossBGM");
}

//クリア判定
bool BossStage::ClearJudge()
{
	return true;
	//if (sceneGame->GetEnemyManager()->GetEnemiesSize() <= 0)return true;
	//return false;
}


//UIの作成
void BossStage::CreateUI()
{
	uiNumTower = make_shared<UINumTower>(sceneGame);
	uiNumTower->Init();
	
	uiTimer = make_shared<UITimer>();
	uiTimer->Init();
	
}
//スカイドームの作成
void BossStage::CreateSky()
{
	VECTOR3 Pos, Angle, Scale;
	Pos = { 0,0,0 };
	Angle = { 0,0,0 };
	Scale = { 0.5f,0.5f,0.5f };
	skyModel = TK_Lib::Load::GetModel("Sky");
	//ステージ
	TK_Lib::Model::Tranceform(skyModel, Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(skyModel, 0, false);
	TK_Lib::Model::AnimetionUpdate(skyModel);
}
//ボスカメラの初期設定
void BossStage::InitBossCamera()
{
	enm = sceneGame->GetEnemyManager()->SearchEnemyTag(EnemyTag::BOSS);
	camera = new CameraBossEntry(sceneGame->GetPlayer(), enm, this);

	eventState = EventState::LOOK_PLAYER;
	sceneGame->GetCameraManager()->ChangeCamera(camera);
	sceneGame->GetPlayer()->ChangeState(Player::State::BOSS_ENTRY, this);
}

//シロボの召喚
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