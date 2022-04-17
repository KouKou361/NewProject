#include "MinionPlayer.h"
#include "Player.h"
#include "MinionPlayerAI.h"
#include "Animetion.h"
#include "UIDerived.h"
//����������
void MinionPlayer::Init(Player* pl)
{
	SetQuaternion({ 0,0,0,1 });
	//pos = { 0,0,0 };
	SetScale({ 0.4f,0.4f,0.4f });
	speed = 0.7f;
	collisionRadius = 2.0f;
	weight = 0.2f;
	SetModel(TK_Lib::Load::GetModel("MinionPlayer"));
	//�v���C���[�̓o�^
	this->pl = pl;
	Ai = make_shared<MinionPlayerAI>(this,pl);
//	SetTeam(Team::TeamPlayer);
	SetTeam(Team::TEAM_NEUTRAL);
	SetHp(4);
	SetMaxHp(GetHp());
	ResuscitationTime = 0;

	SetTag(ObjectTag::TAG_MINION);

	ResuscitationFlg = false;
	AttackMinions.clear();

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
		"Walk",
		anime->End//"End",
	};
	//�A�j���[�V�����̓o�^
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}



	//�e�N�X�`���̃��[�h
	//int BottonIconTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Game/BottonIcon.png");

	int DoenHelpIconTexture= TK_Lib::Load::LoadTexture("./Data/Sprite/Game/HelpIcon.png");


	//�v���C���[��HP�̕\��UI�̐���
	{
		uiMinionDownHelp = make_shared<UIMinionDownHelp>();
		uiMinionDownHelp->SetTexture(DoenHelpIconTexture);
		uiMinionDownHelp->SetCharactor(this);
	}

	TK_Lib::Model::PlayAnimation(GetModel(), anime->GetIndex("Run"), true);

	//�s��̍X�V����
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::AnimetionUpdate(GetModel());
}


//�X�V����
void MinionPlayer::Update()
{
	if (state != StateType::TYPE_DEAD)
	{
		Ai->Update();
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
void MinionPlayer::Join()
{

}
//�폜
void MinionPlayer::Destroy()
{
	manager->Destroy(this);
}
void MinionPlayer::ResetNode()
{	
	Ai->ResetNode();
}
void MinionPlayer::HPRender(const int SpriteIndex, const VECTOR2 Pos)
{
	//�L���Ȃ�
}

//Sprite�̕`��
void MinionPlayer::Render()
{

	if (GetState() == StateType::TYPE_RESUSCITATION ||
		GetState() == StateType::TYPE_DEAD)
	{
		uiMinionDownHelp->SetValue(static_cast<float>(ResuscitationTime));
		uiMinionDownHelp->Render();
	}
	
}


//�h���X�e�[�g�ϊ�����
void MinionPlayer::SetResuscitation()
{
	SetState(StateType::TYPE_RESUSCITATION);
	ResuscitationFlg = true;
}
//�h���X�e�[�g�ϊ�����
bool MinionPlayer::IsResuscitation()
{
	return ResuscitationFlg;
}