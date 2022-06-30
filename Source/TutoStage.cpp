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
	StageIndex[static_cast<int>(StageType::RENDER_MODEL)] = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[static_cast<int>(StageType::COLISION_MODEL)] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[static_cast<int>(StageType::NAV_MODEL)] = TK_Lib::Load::GetModel(NavModel);

	//ステージ
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::RENDER_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::RENDER_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::RENDER_MODEL)]);

	//影なしステージ
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)]);

	//Navメッシュ
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::NAV_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::NAV_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NAV_MODEL)]);



	//当たり判定
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::COLISION_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::COLISION_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::COLISION_MODEL)]);

	//ステージのオブジェクト配置
	stageExport = std::make_unique<Export>();
	stageExport->SetManager(scene);
	stageExport->Loading(SetData);

	sceneGame = scene;
}

//初期化処理
void TutoStage::Init()
{
	tutoIndex = 0;
	
	{
		//当たり判定登録
		Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], ModelCollisionType::COLLISION_MODEL, nullptr);
		//ナビメッシュ登録							   
		Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::NAV_MODEL)], ModelCollisionType::NAV_MODEL, nullptr);
		//ナビメッシュの構成
		Collision::Instance().NacStageBuild();
		//ステージのオブジェクト配置
		stageExport->ObjectSet();
	}

	tutoManager.clear();


	ExportText* script;
	script = new ExportText("Data/Tuto/TutoScript.txt");
	vector<string>* readScripts = script->GetScripts();
	
	//チュートリアルへようこそ
	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(0));
		tuto->AddText(readScripts->at(1));
		tutoManager.push_back(tuto);
	}

	//球に移動
	{
		shared_ptr<MoveTuto> tuto = std::make_shared<MoveTuto>(sceneGame);
		tuto->AddText(readScripts->at(2));
		tutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(3));
		tuto->AddText(readScripts->at(4));
		tutoManager.push_back(tuto);
	}
	//シロボを仲間に
	{
		shared_ptr<GetSiroboTuto> tuto = std::make_shared<GetSiroboTuto>(sceneGame);
		tuto->AddText(readScripts->at(5));
		tutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(6));
		tuto->AddText(readScripts->at(7));
		tuto->AddText(readScripts->at(8));
		tuto->AddText(readScripts->at(9));
		tuto->AddText(readScripts->at(10));
		tutoManager.push_back(tuto);
	}
	//チュートリアルの敵に攻撃
	{
		shared_ptr<KillDummyEnemyTuto> tuto = std::make_shared<KillDummyEnemyTuto>(sceneGame);
		tuto->AddText(readScripts->at(11));
		tutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(12));
		tuto->AddText(readScripts->at(13));
		tuto->AddText(readScripts->at(14));
		tutoManager.push_back(tuto);
	}

	//蘇生
	{
		shared_ptr<ResurectionSiroboTuto> tuto = std::make_shared<ResurectionSiroboTuto>(sceneGame);
		tuto->AddText(readScripts->at(15));
		tutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(16));
		tuto->AddText(readScripts->at(17));
		tutoManager.push_back(tuto);
	}

	//操作に慣れよう
	{
		shared_ptr<KillEnemyTuto> tuto = std::make_shared<KillEnemyTuto>(sceneGame);
		tuto->AddText(readScripts->at(18));
		tutoManager.push_back(tuto);
	}

	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(19));
		tuto->AddText(readScripts->at(20));
		tuto->AddText(readScripts->at(21));
		tutoManager.push_back(tuto);
	}


	delete script;
	script = nullptr;
	
	nowTuto = tutoManager.at(tutoIndex);
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
		skyModel = TK_Lib::Load::GetModel("Sky");
		//ステージ
        TK_Lib::Model::Tranceform(skyModel, Pos, Angle, Scale);
        TK_Lib::Model::PlayAnimation(skyModel, 0, false);
        TK_Lib::Model::AnimetionUpdate(skyModel);
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

	//復活
	DeadIsResurection();
	//ゲームオーバータイマーが回復
	ResurectionGameOverTime(50);

	//UIの更新
	uiTimer->Update();
}
void TutoStage::NextTuto()
{

	tutoIndex++;
	if (tutoIndex >= tutoManager.size())
	{
		nowTuto = nullptr;
		return;
	}


	nowTuto = tutoManager.at(tutoIndex);
	nowTuto->Init();
}

//描画
void TutoStage::Render()
{
	//死亡時の救済措置
	DeadIsResurection();

	if (tutoIndex>= renderUiNumTower)
	{
		uiNumTower->Render();
	}

	if (nowTuto == nullptr)return;
	nowTuto->Render();

	uiTimer->Render();
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

//ゲームオーバータイマーが回復
void TutoStage::ResurectionGameOverTime(const float time)
{
	if (uiTimer->GetGameTimer() <= time)
	{
		uiTimer->AddGameOverTimer(10);
	}
}
