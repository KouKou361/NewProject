#include "SiroboPlayer.h"
#include "Player.h"
#include "SiroboPlayerAI.h"
#include "Animetion.h"
#include "UIDerived.h"
#include "ExportScript.h"
#include "Scene.h"
//����������
void Sirobo::Init(Player* pl)
{
	//���f���̐ݒ�
	SetModel(TK_Lib::Load::GetModel("Sirobo"));

	//�v���C���[�̓o�^
	this->pl = pl;

	//�X�e�[�^�X�̐ݒ�
	SetStatus("Sirobo");

	//�^�O�t��
	SetTeam(Team::TEAM_NEUTRAL);
	SetTag(ObjectTag::TAG_SIROBO);

	//����
	resuscitationTime = 0;
	resuscitationFlg = false;

	//�O�̂��ߍU��������Ă���̃V���{�̃N���A
	attackSirobo.clear();

	//�A�j���[�V�����̓o�^
	RegisterAnimetion();
	
	//�V���{AI
	ai = make_shared<SiroboPlayerAI>(this, pl);

	//�_�E����Ԃ̃w���v�A�C�R���̍쐬
	CreateDownHelpUI();

	TK_Lib::Model::PlayAnimation(GetModel(), anime->GetIndex("Run"), true);

	//�s��̍X�V����
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::AnimetionUpdate(GetModel());
}


//�X�V����
void Sirobo::Update()
{
	if (state != StateType::TYPE_DEAD)
	{
		ai->Update();
	}

	Turn(moveVec);
	Move();
	//�U���̃N�[���^�C���X�V����
	AttackCoolTimeUpdate();
	//�c�����̓����蔻��iY�����j
	//VerticalCollision();
	//	TK_Lib::Debug3D::Circle(pos,collisionRadius);
	
	//�s��Ȃǂ̍X�V����
	Charactor::Update();
}

//���Ԃɉ����
void Sirobo::Join()
{

}
//�폜
void Sirobo::Destroy()
{
	manager->Destroy(this);
}
void Sirobo::ResetNode()
{	
	ai->ResetNode();
}
void Sirobo::HPRender(const int &spriteIndex, const VECTOR2 &pos)
{
	//�L���Ȃ�
}

//Sprite�̕`��
void Sirobo::Render()
{

	if (GetState() == StateType::TYPE_RESUSCITATION ||
		GetState() == StateType::TYPE_DEAD)
	{
		uiSiroboDownHelp->SetValue(static_cast<float>(resuscitationTime));
		uiSiroboDownHelp->Render();
	}
	
}


//�h���X�e�[�g�ϊ�����
void Sirobo::SetResuscitation()
{
	SetState(StateType::TYPE_RESUSCITATION);
	resuscitationFlg = true;
}
//�h���X�e�[�g�ϊ�����
bool Sirobo::IsResuscitation()
{
	return resuscitationFlg;
}

//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
void Sirobo::SetStatus(const string& SearchName)
{
	AlliesStatusData* data = GetPlayer()->GetSceneGame()->GetexportSCV()->GetAlliesStatusDataSearchName(SearchName);
	SetQuaternion({ 0,0,0,1 });
	SetMaxHp(data->GetHp());
	SetHp(data->GetHp());
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	speed = data->GetSpeed();
	collisionRadius = data->GetCollisionRadius();
	weight = data->GetWeight();
	SetMaxInvincibleTime(data->GetMaxInvincibleTime());
}

//�A�j���[�V�����̓o�^
void Sirobo::RegisterAnimetion()
{
	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		anime->Attack1,
		"Attack02",
		anime->Die,//"Die",
		"Dodge",
		anime->Idle,//"Idle",
		"Jump",
		anime->Damage,//"Land",
		"Reload",
		"Reload.001",
		anime->Run,//"Run",
		"Swap",
		"Throw",
		"ThrowReady",
		anime->Walk,
		anime->End//"End",
	};
	//�A�j���[�V�����̓o�^
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//�_�E����Ԃ̃w���v�A�C�R���̍쐬
void Sirobo::CreateDownHelpUI()
{
	//�e�N�X�`���̃��[�h
	int DoenHelpIconTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Game/HelpIcon.png");


	//�v���C���[��HP�̕\��UI�̐���
	
	uiSiroboDownHelp = make_shared<UISiroboDownHelp>();
	uiSiroboDownHelp->SetTexture(DoenHelpIconTexture);
	uiSiroboDownHelp->SetCharactor(this);
	

}


