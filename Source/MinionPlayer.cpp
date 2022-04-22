#include "MinionPlayer.h"
#include "Player.h"
#include "MinionPlayerAI.h"
#include "Animetion.h"
#include "UIDerived.h"
#include "ExportScript.h"
#include "Scene.h"
//初期化処理
void MinionPlayer::Init(Player* pl)
{


	SetModel(TK_Lib::Load::GetModel("MinionPlayer"));
	//プレイヤーの登録
	this->pl = pl;
	SetStatus("Minion");
	ai = make_shared<MinionPlayerAI>(this,pl);
//	SetTeam(Team::TeamPlayer);
	SetTeam(Team::TEAM_NEUTRAL);
	resuscitationTime = 0;

	SetTag(ObjectTag::TAG_MINION);

	resuscitationFlg = false;
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
		ai->Update();
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
	ai->ResetNode();
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
		uiMinionDownHelp->SetValue(static_cast<float>(resuscitationTime));
		uiMinionDownHelp->Render();
	}
	
}


//蘇生ステート変換処理
void MinionPlayer::SetResuscitation()
{
	SetState(StateType::TYPE_RESUSCITATION);
	resuscitationFlg = true;
}
//蘇生ステート変換処理
bool MinionPlayer::IsResuscitation()
{
	return resuscitationFlg;
}

//CSVからデータを取り出して、ステータスの設定する。
void MinionPlayer::SetStatus(string SearchName)
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


