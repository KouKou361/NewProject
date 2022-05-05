#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "UIDerived.h"

Stage::Stage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale,string SetData, SceneGame* scene)
{
	//データの登録
	StageIndex[static_cast<int>(StageType::RENDER_MODEL)]    = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[static_cast<int>(StageType::COLISION_MODEL)] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[static_cast<int>(StageType::NAV_MODEL)]       = TK_Lib::Load::GetModel(NavModel);

	//ステージ
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::RENDER_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::RENDER_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::RENDER_MODEL)]);

	//影なしステージ
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)]);
	
	//Navメッシュ
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::NAV_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::NAV_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NAV_MODEL)]);
	
	//当たり判定
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::COLISION_MODEL)]);
	
	//ステージのオブジェクト配置
	stageExport = std::make_unique<Export>();
	stageExport->SetManager(scene);
	stageExport->Loading(SetData);

	sceneGame = scene;
}

//初期化処理
void Stage::Init()
{
	//当たり判定登録
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], ModelCollisionType::COLLISION_MODEL, nullptr);
	//ナビメッシュ登録
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::NAV_MODEL)], ModelCollisionType::NAV_MODEL, nullptr);
	//ナビメッシュの構成
	Collision::Instance().NacStageBuild();
	//ステージのオブジェクト配置
	stageExport->ObjectSet();

	TK_Lib::Lib_Sound::SoundPlay("Title", true);




	{
		uiNumTower = make_shared<UINumTower>(sceneGame);
		uiNumTower->Init();
	}

	{
		uiTimer = make_shared<UITimer>();
		uiTimer->Init();
	}

	//スカイドームの生成
	CreateSky();
	//シロボの生成
	SummonSirobo();

}

//更新処理
void Stage::Update()
{
	uiNumTower->Update();
	//UIの更新
	uiTimer->Update();
}

//描画
void Stage::Render()
{
	

	uiNumTower->Render();

	uiTimer->Render();
	//死亡時の救済措置
	DeadIsResurection();

}

//描画
void Stage::ModelRender()
{
	TK_Lib::Draw::Model(StageIndex[static_cast<int>(StageType::RENDER_MODEL)], ShaderType::Shader_MakeShadow);

	TK_Lib::Draw::Model(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], ShaderType::Shader_DrawShadow);

	TK_Lib::Draw::Model(skyModel, ShaderType::Shader_NoLight);
}

//終了処理
void Stage::End()
{
	TK_Lib::Lib_Sound::SoundStop("Title");
}

//クリア判定
bool Stage::ClearJudge()
{
	if (sceneGame->GetObjectManager()->GetTowerNum() <= 0)return true;
	return false;
}

//スカイドームの生成
void Stage::CreateSky()
{
	//Sky
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

}
//シロボの生成
void Stage::SummonSirobo()
{
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Sirobo> sirobo;
		sirobo = make_shared<Sirobo>();
		sirobo->Init(sceneGame->GetPlayer());
		sirobo->SetPos({ 5,0,static_cast<float>(i * 8) });
		//ゲームシーンの設定
		//	sirobo->pos = { 5,0,static_cast<float>(140) };
		sceneGame->GetPlayer()->GetSiroboManager()->Register(sirobo);
	}
}

//死亡時の救済措置
void Stage::DeadIsResurection()
{
	//デバッグ
//死亡時の救済措置
	if (sceneGame->GetPlayer()->GetState() == Player::State::DEAD)
	{
		VECTOR2 Window = TK_Lib::Window::GetWindowSize();
		const int PlayerResurectionTime = 50;
		if (TK_Lib::Gamepad::GetButtonDown(BTN::A) >= PlayerResurectionTime)
		{
			sceneGame->GetPlayer()->ChangeState(Player::State::WAIT);
			uiTimer->AddGameOverTimer(100);
		}
		const VECTOR2  FontSize = { Window.x / 2 - 100, Window.y / 2 - 100 };
		TK_Lib::Draw::JapanFont("「〇キー」長押しで救済措置", FontSize);
	}
}