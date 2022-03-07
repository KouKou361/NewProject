#include "Stage.h"
#include "Collision.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "UIDerived.h"

Stage::Stage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel, VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale,string SetData, SceneGame* scene)
{
	//�f�[�^�̓o�^
	StageIndex[StageType::RenderModel]    = TK_Lib::Load::GetModel(RenderModel);
	StageIndex[StageType::NoMakeShadowModel] = TK_Lib::Load::GetModel(NoShadowRenderModel);
	StageIndex[StageType::CollisionModel] = TK_Lib::Load::GetModel(CollisionModel);
	StageIndex[StageType::NavModel]       = TK_Lib::Load::GetModel(NavModel);

	//�X�e�[�W
	TK_Lib::Model::Tranceform(StageIndex[StageType::RenderModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::RenderModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::RenderModel]);



	//�e�Ȃ��X�e�[�W
	TK_Lib::Model::Tranceform(StageIndex[StageType::NoMakeShadowModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::NoMakeShadowModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::NoMakeShadowModel]);
	
	//Nav���b�V��
	TK_Lib::Model::Tranceform(StageIndex[StageType::NavModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::NavModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::NavModel]);


	
	//�����蔻��
	TK_Lib::Model::Tranceform(StageIndex[StageType::CollisionModel], Pos, Angle, Scale);
	TK_Lib::Model::PlayAnimation(StageIndex[StageType::CollisionModel], 0, false);
	TK_Lib::Model::AnimetionUpdate(StageIndex[StageType::CollisionModel]);
	
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
	Collision::Instance().RegisterModel(StageIndex[StageType::CollisionModel], ModelCollisionType::CollisionModel, nullptr);
	//�i�r���b�V���o�^
	Collision::Instance().RegisterModel(StageIndex[StageType::NavModel], ModelCollisionType::NavModel, nullptr);
	//�i�r���b�V���̍\��
	Collision::Instance().NacStageBuild();
	//�X�e�[�W�̃I�u�W�F�N�g�z�u
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
		//�X�e�[�W
		TK_Lib::Model::Tranceform(SkyModel, Pos, Angle, Scale);
		TK_Lib::Model::PlayAnimation(SkyModel, 0, false);
		TK_Lib::Model::AnimetionUpdate(SkyModel);
	}

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

	//�f�o�b�O
	//���S���̋~�ϑ[�u
	if (sceneGame->GetPlayer()->GetState() == Player::State::Dead)
	{
		VECTOR2 Window = TK_Lib::Window::GetWindowSize();
		if (TK_Lib::Gamepad::GetButtonDown(BTN::A) >= 50)
		{
			sceneGame->GetPlayer()->ChangeState(Player::State::Wait);
			uiTimer->AddGameOverTimer(100);
		}
		TK_Lib::Draw::JapanFont("�u�Z�L�[�v�������ŋ~�ϑ[�u", { Window.x / 2 - 100, Window.y / 2 - 100 });
	}
}

//�`��
void Stage::ModelRender()
{
	TK_Lib::Draw::Model(StageIndex[StageType::RenderModel], ShaderType::Shader_MakeShadow);

	TK_Lib::Draw::Model(StageIndex[StageType::NoMakeShadowModel], ShaderType::Shader_DrawShadow);

	TK_Lib::Draw::Model(SkyModel, ShaderType::Shader_NoLight);
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