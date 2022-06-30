#include "SiroboPlayer.h"
#include "Player.h"
#include "SiroboPlayerAI.h"
#include "Animetion.h"
#include "UIDerived.h"
#include "ExportScript.h"
#include "Scene.h"
//初期化処理
void Sirobo::Init(Player* pl)
{
	//モデルの設定
	SetModel(TK_Lib::Load::GetModel("Sirobo"));

	//プレイヤーの登録
	this->pl = pl;

	//ステータスの設定
	SetStatus("Sirobo");

	//タグ付け
	SetTeam(Team::TEAM_NEUTRAL);
	SetTag(ObjectTag::TAG_SIROBO);

	//復活
	resuscitationTime = 0;
	resuscitationFlg = false;

	//念のため攻撃中されているのシロボのクリア
	attackSirobo.clear();

	//アニメーションの登録
	RegisterAnimetion();
	
	//シロボAI
	ai = make_shared<SiroboPlayerAI>(this, pl);

	//ダウン状態のヘルプアイコンの作成
	CreateDownHelpUI();

	TK_Lib::Model::PlayAnimation(GetModel(), anime->GetIndex("Run"), true);

	//行列の更新処理
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::AnimetionUpdate(GetModel());
}


//更新処理
void Sirobo::Update()
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
void Sirobo::Join()
{

}
//削除
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
	//記入なし
}

//Spriteの描画
void Sirobo::Render()
{

	if (GetState() == StateType::TYPE_RESUSCITATION ||
		GetState() == StateType::TYPE_DEAD)
	{
		uiSiroboDownHelp->SetValue(static_cast<float>(resuscitationTime));
		uiSiroboDownHelp->Render();
	}
	
}


//蘇生ステート変換処理
void Sirobo::SetResuscitation()
{
	SetState(StateType::TYPE_RESUSCITATION);
	resuscitationFlg = true;
}
//蘇生ステート変換処理
bool Sirobo::IsResuscitation()
{
	return resuscitationFlg;
}

//CSVからデータを取り出して、ステータスの設定する。
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

//アニメーションの登録
void Sirobo::RegisterAnimetion()
{
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
		anime->Walk,
		anime->End//"End",
	};
	//アニメーションの登録
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//ダウン状態のヘルプアイコンの作成
void Sirobo::CreateDownHelpUI()
{
	//テクスチャのロード
	int DoenHelpIconTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Game/HelpIcon.png");


	//プレイヤーのHPの表示UIの生成
	
	uiSiroboDownHelp = make_shared<UISiroboDownHelp>();
	uiSiroboDownHelp->SetTexture(DoenHelpIconTexture);
	uiSiroboDownHelp->SetCharactor(this);
	

}


