#include "MinionPlayer.h"
#include "Player.h"
#include "MinionPlayerAI.h"
#include "Animetion.h"
#include "UIDerived.h"
//初期化処理
void MinionPlayer::Init(Player* pl)
{
	SetQuaternion({ 0,0,0,1 });
	//pos = { 0,0,0 };
	SetScale({ 0.4f,0.4f,0.4f });
	speed = 0.7f;
	collisionRadius = 2.0f;
	weight = 0.2f;
	SetModel(TK_Lib::Load::GetModel("MinionPlayer"));
	//プレイヤーの登録
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
	//アニメーション番号
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
	//アニメーションの登録
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}



	//テクスチャのロード
	//int BottonIconTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Game/BottonIcon.png");

	int DoenHelpIconTexture= TK_Lib::Load::LoadTexture("./Data/Sprite/Game/HelpIcon.png");


	//プレイヤーのHPの表示UIの生成
	{
		uiMinionDownHelp = make_shared<UIMinionDownHelp>();
		uiMinionDownHelp->SetTexture(DoenHelpIconTexture);
		uiMinionDownHelp->SetCharactor(this);
	}

	TK_Lib::Model::PlayAnimation(GetModel(), anime->GetIndex("Run"), true);

	//行列の更新処理
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::AnimetionUpdate(GetModel());
}


//更新処理
void MinionPlayer::Update()
{
	if (state != StateType::TYPE_DEAD)
	{
		Ai->Update();
	}

	Turn(moveVec);
	Move();
	//攻撃のクールタイム更新処理
	AttackCoolTimeUpdate();
	//縦方向の当たり判定（Y方向）
	//VerticalCollision();
	//	TK_Lib::Debug3D::Circle(pos,collisionRadius);
	
	//行列などの更新処理
	Charactor::Update();
}

//仲間に加わる
void MinionPlayer::Join()
{

}
//削除
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
	//記入なし
}

//Spriteの描画
void MinionPlayer::Render()
{

	if (GetState() == StateType::TYPE_RESUSCITATION ||
		GetState() == StateType::TYPE_DEAD)
	{
		uiMinionDownHelp->SetValue(static_cast<float>(ResuscitationTime));
		uiMinionDownHelp->Render();
	}
	
}


//蘇生ステート変換処理
void MinionPlayer::SetResuscitation()
{
	SetState(StateType::TYPE_RESUSCITATION);
	ResuscitationFlg = true;
}
//蘇生ステート変換処理
bool MinionPlayer::IsResuscitation()
{
	return ResuscitationFlg;
}