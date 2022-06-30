#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "Tuto.h"
#include "ExportScript.h"
#include "Scene.h"
#include "UIDerived.h"

TutoStage::TutoStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene)
{
	//�f�[�^�̓o�^
	StageIndex[static_cast<int>(StageType::RENDER_MODEL)] = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[static_cast<int>(StageType::COLISION_MODEL)] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[static_cast<int>(StageType::NAV_MODEL)] = TK_Lib::Load::GetModel(NavModel);

	//�X�e�[�W
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::RENDER_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::RENDER_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::RENDER_MODEL)]);

	//�e�Ȃ��X�e�[�W
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)]);

	//Nav���b�V��
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::NAV_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::NAV_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NAV_MODEL)]);



	//�����蔻��
	TK_Lib::Model::Tranceform(     StageIndex[static_cast<int>(StageType::COLISION_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(  StageIndex[static_cast<int>(StageType::COLISION_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::COLISION_MODEL)]);

	//�X�e�[�W�̃I�u�W�F�N�g�z�u
	stageExport = std::make_unique<Export>();
	stageExport->SetManager(scene);
	stageExport->Loading(SetData);

	sceneGame = scene;
}

//����������
void TutoStage::Init()
{
	tutoIndex = 0;
	
	{
		//�����蔻��o�^
		Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], ModelCollisionType::COLLISION_MODEL, nullptr);
		//�i�r���b�V���o�^							   
		Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::NAV_MODEL)], ModelCollisionType::NAV_MODEL, nullptr);
		//�i�r���b�V���̍\��
		Collision::Instance().NacStageBuild();
		//�X�e�[�W�̃I�u�W�F�N�g�z�u
		stageExport->ObjectSet();
	}

	tutoManager.clear();


	ExportText* script;
	script = new ExportText("Data/Tuto/TutoScript.txt");
	vector<string>* readScripts = script->GetScripts();
	
	//�`���[�g���A���ւ悤����
	{
		shared_ptr<Tuto> tuto = std::make_shared<Tuto>(sceneGame);
		tuto->AddText(readScripts->at(0));
		tuto->AddText(readScripts->at(1));
		tutoManager.push_back(tuto);
	}

	//���Ɉړ�
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
	//�V���{�𒇊Ԃ�
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
	//�`���[�g���A���̓G�ɍU��
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

	//�h��
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

	//����Ɋ���悤
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
		//�X�e�[�W
        TK_Lib::Model::Tranceform(skyModel, Pos, Angle, Scale);
        TK_Lib::Model::PlayAnimation(skyModel, 0, false);
        TK_Lib::Model::AnimetionUpdate(skyModel);
	}

}

//�X�V����
void TutoStage::Update()
{
	uiNumTower->Update();
	if (nowTuto == nullptr)return;
	nowTuto->Update();


	if (nowTuto->Judge())
	{
		NextTuto();
	}

	//����
	DeadIsResurection();
	//�Q�[���I�[�o�[�^�C�}�[����
	ResurectionGameOverTime(50);

	//UI�̍X�V
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

//�`��
void TutoStage::Render()
{
	//���S���̋~�ϑ[�u
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
//�I������
void TutoStage::End()
{

}

//�N���A����
bool TutoStage::ClearJudge()
{
	if (nowTuto == nullptr)return true;
	return false;
}

//�Q�[���I�[�o�[�^�C�}�[����
void TutoStage::ResurectionGameOverTime(const float time)
{
	if (uiTimer->GetGameTimer() <= time)
	{
		uiTimer->AddGameOverTimer(10);
	}
}
