#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "UIDerived.h"

Stage::Stage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale,string SetData, SceneGame* scene)
{
	//データの登録
	StageIndex[StageType::RenderModel]    = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[StageType::NoMakeShadowModel] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[StageType::CollisionModel] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[StageType::NavModel]       = TK_Lib::Load::GetModel(NavModel);

	//ステージ
	TK_Lib::Model::Tranceform(StageIndex[StageType::RenderModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::RenderModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::RenderModel]);



	//影なしステージ
	TK_Lib::Model::Tranceform(StageIndex[StageType::NoMakeShadowModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::NoMakeShadowModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::NoMakeShadowModel]);
	
	//Navメッシュ
	TK_Lib::Model::Tranceform(StageIndex[StageType::NavModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::NavModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::NavModel]);


	
	//当たり判定
	TK_Lib::Model::Tranceform(StageIndex[StageType::CollisionModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::CollisionModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::CollisionModel]);
	
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
	Collision::Instance().RegisterModel(StageIndex[StageType::CollisionModel], ModelCollisionType::CollisionModel, nullptr);
	//ナビメッシュ登録
	Collision::Instance().RegisterModel(StageIndex[StageType::NavModel], ModelCollisionType::NavModel, nullptr);
	//ナビメッシュの構成
	Collision::Instance().NacStageBuild();
	//ステージのオブジェクト配置
	stageExport->ObjectSet();

	TK_Lib::Lib_Sound::SoundPlay("Title", true);


	for (int i = 0; i < 4; i++)
	{
		shared_ptr<MinionPlayer> minion;
		minion = make_shared<MinionPlayer>();
		minion->Init(sceneGame->GetPlayer());
		minion->SetPos({ 5,0,static_cast<float>(i * 8) });
		//	minion->pos = { 5,0,static_cast<float>(140) };
		sceneGame->GetPlayer()->GetMinionManager()->Register(minion);
	}

	{
		uiNumTower = make_shared<UINumTower>(sceneGame);
		uiNumTower->Init();
	}

	{
		uiTimer = make_shared<UITimer>();
		uiTimer->Init();
	}

	//Sky
	{
		VECTOR3 Pos, Angle, Scale;
		Pos = { 0,0,0 };
		Angle = { 0,0,0 };
		Scale = { 0.5f,0.5f,0.5f };
		SkyModel = TK_Lib::Load::GetModel("Sky");
		//ステージ
		TK_Lib::Model::Tranceform(SkyModel, Pos, Angle, Scale);
		TK_Lib::Model::PlayAnimation(SkyModel, 0, false);
		TK_Lib::Model::AnimetionUpdate(SkyModel);
	}

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

	//デバッグ
	//死亡時の救済措置
	if (sceneGame->GetPlayer()->GetState() == Player::State::Dead)
	{
		VECTOR2 Window = TK_Lib::Window::GetWindowSize();
		if (TK_Lib::Gamepad::GetButtonDown(BTN::A) >= 50)
		{
			sceneGame->GetPlayer()->ChangeState(Player::State::Wait);
			uiTimer->AddGameOverTimer(100);
		}
		TK_Lib::Draw::JapanFont("「〇キー」長押しで救済措置", { Window.x / 2 - 100, Window.y / 2 - 100 });
	}
}

//描画
void Stage::ModelRender()
{
	TK_Lib::Draw::Model(StageIndex[StageType::RenderModel], ShaderType::Shader_MakeShadow);

	TK_Lib::Draw::Model(StageIndex[StageType::NoMakeShadowModel], ShaderType::Shader_DrawShadow);

	TK_Lib::Draw::Model(SkyModel, ShaderType::Shader_NoLight);
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