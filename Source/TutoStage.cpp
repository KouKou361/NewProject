#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "Tuto.h"
#include "ExportScript.h"
#include "Scene.h"
#include "UIDerived.h"

TutoStage::TutoStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene)
{
	//データの登録
	StageIndex[StageType::RenderModel] = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[StageType::NoMakeShadowModel] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[StageType::CollisionModel] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[StageType::NavModel] = TK_Lib::Load::GetModel(NavModel);

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
void TutoStage::Init()
{
	TutoIndex = 0;
	
	{
		//当たり判定登録
		Collision::Instance().RegisterModel(StageIndex[StageType::CollisionModel], ModelCollisionType::CollisionModel, nullptr);
		//ナビメッシュ登録
		Collision::Instance().RegisterModel(StageIndex[StageType::NavModel], ModelCollisionType::NavModel, nullptr);
		//ナビメッシュの構成
		Collision::Instance().NacStageBuild();
		//ステージのオブジェクト配置
		stageExport->ObjectSet();
	}

	TutoManager.clear();

	ExportScript* script;
	script = new ExportScript("Data/Tuto/TutoScript.txt");
	vector<string>* test = script->GetScripts();
	
	//チュートリアルへようこそ
	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(test->at(0));
		tuto->AddText(test->at(1));
		TutoManager.push_back(tuto);
	}

	//球に移動
	{
		shared_ptr<MoveTuto> tuto = std::make_shared<MoveTuto>(sceneGame);
		tuto->AddText(test->at(2));
		TutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(test->at(3));
		tuto->AddText(test->at(4));
		TutoManager.push_back(tuto);
	}
	//シロボを仲間に
	{
		shared_ptr<GetMinionTuto> tuto = std::make_shared<GetMinionTuto>(sceneGame);
		tuto->AddText(test->at(5));
		TutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(test->at(6));
		tuto->AddText(test->at(7));
		tuto->AddText(test->at(8));
		tuto->AddText(test->at(9));
		tuto->AddText(test->at(10));
		TutoManager.push_back(tuto);
	}
	//チュートリアルの敵に攻撃
	{
		shared_ptr<KillDummyEnemyTuto> tuto = std::make_shared<KillDummyEnemyTuto>(sceneGame);
		tuto->AddText(test->at(11));
		TutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(test->at(12));
		tuto->AddText(test->at(13));
		tuto->AddText(test->at(14));
		TutoManager.push_back(tuto);
	}

	//蘇生
	{
		shared_ptr<ResurectionMinionTuto> tuto = std::make_shared<ResurectionMinionTuto>(sceneGame);
		tuto->AddText(test->at(15));
		TutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(test->at(16));
		tuto->AddText(test->at(17));
		TutoManager.push_back(tuto);
	}

	//操作に慣れよう
	{
		shared_ptr<KillEnemyTuto> tuto = std::make_shared<KillEnemyTuto>(sceneGame);
		tuto->AddText(test->at(18));
		TutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(test->at(19));
		tuto->AddText(test->at(20));
		tuto->AddText(test->at(21));
		TutoManager.push_back(tuto);
	}


	delete script;
	
	nowTuto = TutoManager.at(TutoIndex);
	TK_Lib::Lib_Sound::SoundPlay("Title", true);

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
void TutoStage::Update()
{
	uiNumTower->Update();
	if (nowTuto == nullptr)return;
	nowTuto->Update();


	if (nowTuto->Judge())
	{
		NextTuto();
	}

	//ゲームオーバータイマーが回復
	if (sceneGame->GetStageManager()->GetNowStage()->GetUiTimer()->GetGameTimer() <= 50)
	{
		sceneGame->GetStageManager()->GetNowStage()->GetUiTimer()->AddGameOverTimer(10);
	}

	//UIの更新
	uiTimer->Update();
}
void TutoStage::NextTuto()
{

	TutoIndex++;
	if (TutoIndex >= TutoManager.size())
	{
		nowTuto = nullptr;
		return;
	}

	nowTuto = TutoManager.at(TutoIndex);
	nowTuto->Init();
}

//描画
void TutoStage::Render()
{
	if (TutoIndex>= RenderUiNumTower)
	{
		uiNumTower->Render();
	}

	if (nowTuto == nullptr)return;
	nowTuto->Render();

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

void TutoStage::ModelRender()
{
	Stage::ModelRender();

	
}
//終了処理
void TutoStage::End()
{

}

//クリア判定
bool TutoStage::ClearJudge()
{
	if (nowTuto == nullptr)return true;
	return false;
}