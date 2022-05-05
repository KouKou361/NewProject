#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "UIDerived.h"

Stage::Stage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale,string SetData, SceneGame* scene)
{
	//�f�[�^�̓o�^
	StageIndex[static_cast<int>(StageType::RENDER_MODEL)]    = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[static_cast<int>(StageType::COLISION_MODEL)] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[static_cast<int>(StageType::NAV_MODEL)]       = TK_Lib::Load::GetModel(NavModel);

	//�X�e�[�W
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::RENDER_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::RENDER_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::RENDER_MODEL)]);

	//�e�Ȃ��X�e�[�W
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)]);
	
	//Nav���b�V��
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::NAV_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::NAV_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::NAV_MODEL)]);
	
	//�����蔻��
	TK_Lib::Model::Tranceform(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[static_cast<int>(StageType::COLISION_MODEL)]);
	
	//�X�e�[�W�̃I�u�W�F�N�g�z�u
	stageExport = std::make_unique<Export>();
	stageExport->SetManager(scene);
	stageExport->Loading(SetData);

	sceneGame = scene;
}

//����������
void Stage::Init()
{
	//�����蔻��o�^
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::COLISION_MODEL)], ModelCollisionType::COLLISION_MODEL, nullptr);
	//�i�r���b�V���o�^
	Collision::Instance().RegisterModel(StageIndex[static_cast<int>(StageType::NAV_MODEL)], ModelCollisionType::NAV_MODEL, nullptr);
	//�i�r���b�V���̍\��
	Collision::Instance().NacStageBuild();
	//�X�e�[�W�̃I�u�W�F�N�g�z�u
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

	//�X�J�C�h�[���̐���
	CreateSky();
	//�V���{�̐���
	SummonSirobo();

}

//�X�V����
void Stage::Update()
{
	uiNumTower->Update();
	//UI�̍X�V
	uiTimer->Update();
}

//�`��
void Stage::Render()
{
	

	uiNumTower->Render();

	uiTimer->Render();
	//���S���̋~�ϑ[�u
	DeadIsResurection();

}

//�`��
void Stage::ModelRender()
{
	TK_Lib::Draw::Model(StageIndex[static_cast<int>(StageType::RENDER_MODEL)], ShaderType::Shader_MakeShadow);

	TK_Lib::Draw::Model(StageIndex[static_cast<int>(StageType::NO_MAKE_SHADOW_MODEL)], ShaderType::Shader_DrawShadow);

	TK_Lib::Draw::Model(skyModel, ShaderType::Shader_NoLight);
}

//�I������
void Stage::End()
{
	TK_Lib::Lib_Sound::SoundStop("Title");
}

//�N���A����
bool Stage::ClearJudge()
{
	if (sceneGame->GetObjectManager()->GetTowerNum() <= 0)return true;
	return false;
}

//�X�J�C�h�[���̐���
void Stage::CreateSky()
{
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
//�V���{�̐���
void Stage::SummonSirobo()
{
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Sirobo> sirobo;
		sirobo = make_shared<Sirobo>();
		sirobo->Init(sceneGame->GetPlayer());
		sirobo->SetPos({ 5,0,static_cast<float>(i * 8) });
		//�Q�[���V�[���̐ݒ�
		//	sirobo->pos = { 5,0,static_cast<float>(140) };
		sceneGame->GetPlayer()->GetSiroboManager()->Register(sirobo);
	}
}

//���S���̋~�ϑ[�u
void Stage::DeadIsResurection()
{
	//�f�o�b�O
//���S���̋~�ϑ[�u
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
		TK_Lib::Draw::JapanFont("�u�Z�L�[�v�������ŋ~�ϑ[�u", FontSize);
	}
}