#pragma once
#include "Player.h"
#include "Lib.h"
#include "Mathf.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "SiroboPlayer.h"
#include "CameraController.h"
#include "Animetion.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "UIDerived.h"

#include "UIManager.h"
#include "ExportScript.h"
void Player::Init()
{
	//ステータス設定
	SetStatus("Player");

	//モデル生成
	SetModel(TK_Lib::Load::GetModel("Player"));

	//アニメーションの登録
	RegisterAnimetion();
	
	//タグづけ
	SetTag(ObjectTag::TAG_PLAYER);

	//アニメーション
	RegisterAnimetion();

	//全ての行動を登録
	RegisterState();
	

	//ミニオンたちの初期化処理
	siroboManager = make_unique<SiroboManager>();
	siroboManager->Init();

	//テクスチャの読み込み、設定
	int TargetCursurSprite = TK_Lib::Load::LoadTexture("./Data/Sprite/TargetCursor.png");
	int HealthPointSprite = TK_Lib::Load::LoadTexture("./Data/Sprite/Game/HealthPoint.png");

	//敵マネージャーの設定
	EnemyManager* enemyManager = sceneGame->GetEnemyManager();
	siroboManager->SetEnemyManager(enemyManager);

	//マネージャーの設定
	ObjectManager* objectManager = sceneGame->GetObjectManager();
	siroboManager->SetObjectManager(objectManager);

	//攻撃目標の表示UIの生成
	{
		uiTargetCursur = make_shared<UITargetCursur>();
		uiTargetCursur->SetTexture(TargetCursurSprite);
		uiTargetCursur->SetCharactor(this);
		uiTargetCursur->Init();
	}

	//敵のHPの表示UIの生成
	{
		uiTargetHP = make_shared<UITargetHP>();
		uiTargetHP->SetCharactor(this);
		uiTargetHP->Init();
	}

	//敵に攻撃しているミニオンの数
	{
		uiSiroboAttack = make_shared<UISiroboAttack>();
		uiSiroboAttack->Init();
		uiSiroboAttack->SetCharactor(this);
	}

	//シロボ達の攻撃を受けるリストをクリア（念のため）
	attackSirobo.clear();

	SetOldPos(GetPos());

	//manager->Register(uiPlayerHP);

}
void Player::Update()
{
	
	ImGui::Begin("test");
	ImGui::Text("test=%f", GetMaskVolume());
	if (ImGui::Button("test"))
	{
		MaskStart(0.1f);
	}
	ImGui::End();
	//ダメージ確認
	if (GetDamageFlg() == true)
	{
		ChangeState(stateDamage.get());
	}
	//死亡確認
	if (GetDeadFlg() == true)
	{
		ChangeState(stateDead.get());
	}


	stateMachine->Run(this);

	//敵との当たり判定
	VsEnemy();

	//Navメッシュに現在地を更新する
	Collision::Instance().SetTarget(GetPos());

	//過去の地点の保存
	SetOldPos(GetPos());

	//ターゲットの見失う
	ResetFarTarget(LossTargetFar);

	//ミニオンたちの更新処理
	siroboManager->Update();

	//無敵時間の更新
	InvincibleTimeUpdate();

	//行列などの更新処理
	Charactor::Update();

}

//入力処理
void Player::Input()
{
	//プレイヤーの移動入力処理
	InputMove();

	//敵目標の設定
	SetTargetActor();

	//プレイヤーのカメラ入力処理
	InputCamera();

	//攻撃入力処理
	InputAttack();

	//ミニオンの帰還入力処理
	InputSiroboBack();

	//ミニオンの蘇生処理
	InputSiroboResuscitation();
	
}
//シーンゲームの設定
void Player::SetSceneGame(SceneGame* scene) {
	this->sceneGame = scene;
}

//RBで全てのシロボの帰還
void Player::InputSiroboBack()
{
	if (TK_Lib::Gamepad::GetButtonDown(BTN::RB) == 1)
	{
		siroboManager->AllBack();
	}
}

//入力攻撃
void Player::InputAttack()
{
	CameraManager* cameraManager = sceneGame->GetCameraManager();

	//もしAimカメラ時ではない状態ならreturn 
	if (cameraManager->GetNowType() != CameraManager::CameraType::TYPE_AIM)return;
	//もし攻撃モードならreturn;
	if (state == State::ATTACK)return;

	if (GetSiroboManager()->GetTypeSiroboSize(Sirobo::StateType::TYPE_STAND_BY) == 0)return;

	if (TK_Lib::Gamepad::GetButtonDown(BTN::RT) == 1)
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::Y) == 1)
	{
		ChangeState(stateAttack.get());
	}


}

//入力処理(入力された数値はmoveVecに入れられる)
void Player::InputMove()
{
	float ax = TK_Lib::Gamepad::GetAxisLX();
	float az = TK_Lib::Gamepad::GetAxisLY();

	VECTOR3 CameraFront = TK_Lib::Camera::GetFront();
	//XZ平面に変換する
	{
		CameraFront.y = 0.0f;
		XMVECTOR Front = DirectX::XMLoadFloat3(&CameraFront);
		Front = XMVector3Normalize(Front);
		DirectX::XMStoreFloat3(&CameraFront, Front);
	}

	VECTOR3 CameraRight = TK_Lib::Camera::GetRight();
	//XZ平面に変換する
	{
		CameraRight.y = 0.0f;
		XMVECTOR right = DirectX::XMLoadFloat3(&CameraRight);
		right = XMVector3Normalize(right);
		DirectX::XMStoreFloat3(&CameraRight, right);
	}

	moveVec.x = (CameraFront.x * az + CameraRight.x * ax);
	moveVec.z = (CameraFront.z * az + CameraRight.z * ax);
	moveVec.y = 0.0f;

	//正規化
	moveVec=Mathf::Vec3Normalize(moveVec);
}

//プレイヤーのカメラ入力処理
void Player::InputCamera()
{
	if (GetSiroboManager()->GetTypeSiroboSize(Sirobo::StateType::TYPE_STAND_BY) == 0)return;

	//if (TK_Lib::Gamepad::GetButtonDown(BTN::X) == 1)
	if (TK_Lib::Gamepad::GetButtonDown(BTN::LT) >= 1)
	{
		CameraManager* cameraManager = sceneGame->GetCameraManager();
		//もしAimカメラ時ではない状態ならreturn 
		if (cameraManager->GetNowType() == CameraManager::CameraType::TYPE_AIM)return;
		//Aimカメラに移行
		ChangeCameraAim();
	}
}

//シロボの蘇生入力処理
void Player::InputSiroboResuscitation()
{
	//シロボ達、蘇生範囲
	const float ResuscitationLength = 10.0f;
	//TK_Lib::Debug3D::Circle(GetPos(), ResuscitationLength, {0,1,0,1});
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::Y) <= 0)return;
	float NearPos = FLT_MAX;
	Sirobo* ResuscitationTarget = nullptr;

	for (int i = 0;i < siroboManager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo=siroboManager->GetSiroboIndex(i);

		//死亡のミニオンのみ
		if (sirobo->GetState() == Sirobo::StateType::TYPE_DEAD ||
			sirobo->GetState() == Sirobo::StateType::TYPE_RESUSCITATION
			)
		{
			const float L = Length(sirobo->GetPos());
			//蘇生範囲に入っていたなら
			if (ResuscitationLength <= L)continue;
			//最短距離のミニオンを蘇生ターゲットにする
			if (NearPos >= L)
			{
				NearPos = L;
				ResuscitationTarget = sirobo;
			}

		}

	}

	//蘇生状態に移行！
	if (ResuscitationTarget != nullptr)
	{
		ResuscitationTarget->SetResuscitation();
	}
}

//デバッグ
void Player::CollisionDebug()
{
	//当たり判定
	TK_Lib::Debug3D::Circle(GetPos(), collisionRadius);
	//レイピックの補正

	//レイピック用の当たり判定
	VECTOR3 Start = { GetPos().x,GetPos().y + BesideRayPickUP,     GetPos().z };
	VECTOR3 End = { GetPos().x,GetPos().y - VerticalRayPickUnder, GetPos().z };
	TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });

	//レイピック用の当たり判定
	Start = { GetPos().x - moveVec.x, GetPos().y - moveVec.y + BesideRayPickUP,     GetPos().z - moveVec.z };
	End = { GetPos().x + moveVec.x ,GetPos().y + moveVec.y + BesideRayPickUP, GetPos().z + moveVec.z };

	TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });

	for (int i = 0; i < siroboManager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = siroboManager->GetSiroboIndex(i);
		sirobo->CollisionDebug();

		//当たり判定
		//TK_Lib::Debug3D::Circle(GetPos(), sirobo->StandBySerchL);
	}
}
//目標の敵の設定
bool Player::SetTargetActor()
{
	float nearDot = FLT_MAX;

	VECTOR3  vec1 = TK_Lib::Camera::GetFront();
	vec1.y = 0;
	XMVECTOR Vec1 = XMLoadFloat3(&vec1);
	XMVECTOR NVec1 = XMVector3Normalize(Vec1);

	SetTarget(nullptr);


	//敵のターゲット設定

	{
		EnemyManager* enemyManager = sceneGame->GetEnemyManager();
		constexpr float ViewAngle = 10;
		for (int i = 0; i < enemyManager->GetEnemiesSize(); i++)
		{
			EnemyBase* enm = enemyManager->GetEnemiesIndex(i);

			if (enm->GetTargetFlg() == TargetFlg::FAILED)continue;
			//最短距離までの長さ


			//距離が遠いならcontinue;
			if (Length(enm->GetPos()) >= AttackMaxLength)continue;

			float dot = 0;
			{
				VECTOR3  vec2 = enm->GetPos() - TK_Lib::Camera::GetPos();
				vec2.y = 0;
				XMVECTOR Vec2 = XMLoadFloat3(&vec2);
				XMVECTOR Nvec2 = XMVector3Normalize(Vec2);
				XMVECTOR Dot = XMVector3Dot(NVec1, Nvec2);
				XMStoreFloat(&dot, Dot);
				dot = acosf(dot);
			}
			//ターゲット視野角に入ってないならcontinue
			if (XMConvertToDegrees(dot) >= ViewAngle)
			{
				continue;
			}
			if (dot >= nearDot)
			{
				continue;
			}

			////もしプレイヤーからみて敵が後ろ側ならcontinue;
			//if(sceneGame->GetCameraManager()->GetNowType()!=CameraManager::CameraType::TypeAim)
			//{
			//	float Dot=0;

			//	//プレイヤーと敵のベクトル
			//	XMVECTOR Nvec2;
			//	{
			//		VECTOR3  vec2 = enm->GetPos() - GetPos();
			//		vec2.y = 0;
			//		XMVECTOR Vec2 = XMLoadFloat3(&vec2);
			//		Nvec2 = XMVector3Normalize(Vec2);
			//	}
			//	//カメラと敵のベクトル
			//	XMVECTOR Nvec3;
			//	{
			//		VECTOR3 PlayerFront = enm->GetPos() - TK_Lib::Camera::GetPos();
			//		PlayerFront.y = 0;
			//		XMVECTOR Vec3 = XMLoadFloat3(&PlayerFront);
			//		Nvec3 = XMVector3Normalize(Vec3);
			//	}

			//
			//	XMVECTOR mDot = XMVector3Dot(Nvec3, Nvec2);
			//	XMStoreFloat(&Dot, mDot);
			//	Dot = acosf(Dot);
			//	if (XMConvertToDegrees(Dot) >=  180 - ViewAngle)continue;
			//}

			SetTargetEnemy(enm);
			nearDot = dot;
		}
	}


	//オブジェクトの設定
	{
		ObjectManager* objectManager = sceneGame->GetObjectManager();
		constexpr float ViewAngle = 10;
		for (int i = 0; i < objectManager->GetObjesSize(); i++)
		{
			ObjectBase* obj = objectManager->GetObjesIndex(i);
			//最短距離までの長さ


			//距離が遠いならcontinue;
			if (Length(obj->GetPos()) >= AttackMaxLength)continue;

			float dot = 0;
			{
				VECTOR3  vec2 = obj->GetPos() - TK_Lib::Camera::GetPos();
				vec2.y = 0;
				XMVECTOR Vec2 = XMLoadFloat3(&vec2);
				XMVECTOR Nvec2 = XMVector3Normalize(Vec2);
				XMVECTOR Dot = XMVector3Dot(NVec1, Nvec2);
				XMStoreFloat(&dot, Dot);
				dot = acosf(dot);
			}
			//ターゲット視野角に入ってないならcontinue
			if (XMConvertToDegrees(dot) >= ViewAngle)
			{
				continue;
			}
			if (dot >= nearDot)
			{
				continue;
			}
			SetTargetEnemy(obj);
			nearDot = dot;
		}
	}



	//ターゲットにとらえることが出来ないなら
	if (GetTarget() == nullptr)
	{
		return false;
	}
	return true;
}
//Aimカメラの視点変更
bool Player::ChangeCameraAim()
{
	CameraManager* cameraManager = sceneGame->GetCameraManager();
	EnemyManager* enemyManager = sceneGame->GetEnemyManager();

	if (GetTarget() != nullptr)
	{
		cameraManager->ChangeCamera(new CameraAim(this, GetTarget(), enemyManager));
		return true;
	}
	return false;
}

//位置補正と更新処理
void Player::UpdateCollision()
{
	//横方向の当たり判定（XZ平面）
	BesideCollision();
	//縦方向の当たり判定（Y方向）
	VerticalCollision();
	//ステージの当たり判定　最終
	//StageOverhang();


}
void Player::VsEnemy()
{
	EnemyManager* enemyManager = sceneGame->GetEnemyManager();

	VECTOR3 OutPos;
	EnemyBase* OutEnm;
	if (enemyManager->CollisionEnemy(GetPos(), weight, collisionRadius, OutPos, OutEnm))
	{
		SetPos(OutPos);
	}
}

//状態マシンの変換
void Player::ChangeState(PlayerState* state)
{
	//もし今のステートと現在のステージが同じなら
	if (stateMachine == state)return;
	//現在のステートマシンの終了処理
	if(stateMachine)stateMachine->End(this);
	stateMachine = state;
	stateMachine->Start(this);
}

//状態マシンの変換
void Player::ChangeState(const State &state,BossStage* stage)
{
	PlayerState* playerstate=nullptr;
	switch (state)
	{
	case State::ATTACK://攻撃
		playerstate = stateAttack.get();
			break;
	case State::DAMAGE://ダメージ
		playerstate = stateDamage.get();
			break;
	case State::DEAD://死亡
		playerstate = stateDead.get();
			break;
	case State::WAIT://待機
		playerstate = stateWait.get();
			break;
	case State::WALK://移動
		playerstate = stateWalk.get();
			break;
	case State::BOSS_ENTRY://ボスの登場
		playerstate = stateBossEntry.get();
		stateBossEntry->SetState(stage);
		break;
	default:
		break;
	}
	if (playerstate == nullptr)return;
	ChangeState(playerstate);
}
//ターゲットがある程度遠かった場合見失う
void Player::ResetFarTarget(const float &L)
{

	if (GetTarget() == nullptr)
	{
		if (sceneGame->GetCameraManager()->GetNowType() == CameraManager::CameraType::TYPE_AIM)
		{
			sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(this));
		
		}
		return;
	}
	float l=Length(GetTarget()->GetPos());
	if (L <= l)
	{
		SetTarget(nullptr);
		sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(this));
	}
}
//目標の敵設定
void Player::SetTargetEnemy(Actor* enm) {

	SetTarget(enm);

	//ミニオンにも攻撃対象を変える
	for (int i = 0; i < siroboManager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = siroboManager->GetSiroboIndex(i);
		if (sirobo->GetState() == Sirobo::StateType::TYPE_STAND_BY)
		{
			sirobo->SetTarget(enm);
		}
	}
}

//CameraManagerの設定
void Player::ModelRender()
{
	TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
	//ミニオンたちのモデル描画処理
	siroboManager->ModelRender();
}
//カーソルの描画
void Player::RenderCursur()
{
	//if (GetTarget() == nullptr)return;
	
	//XMVECTOR WorldPosition;
	//VECTOR3 targetPos = GetTarget()->GetPos();
	//WorldPosition = XMLoadFloat3(&targetPos);  
	//
	////座標変換
	//XMMATRIX View = XMLoadFloat4x4(&TK_Lib::Camera::GetView());
	//XMMATRIX Projection = XMLoadFloat4x4(&TK_Lib::Camera::GetProjection());
	//XMMATRIX World = XMMatrixIdentity();
	//
	//VECTOR2 viewport = TK_Lib::Window::GetWindowSize();
	//
	//VECTOR3 screenPos;
	////ワールド座標からスクリーン座標に変換する
	//XMVECTOR ScreenPosition;
	//ScreenPosition = XMVector3Project(WorldPosition, 0, 0, viewport.x, viewport.y, 0.0f, 1.0, Projection, View, World);
	//XMStoreFloat3(&screenPos, ScreenPosition);
	//const float offsetX = -50;
	//const float offsetY = -75;
	//TK_Lib::Draw::Sprite(TargetCursurSprite, VECTOR2{screenPos.x+ offsetX,screenPos.y + offsetY }, { 100,100 }, { 0,0,256,256 });

	//RenderTargetHP({ screenPos.x - 50,screenPos.y - 80 });
}
//目標のHPの表示
void Player::RenderTargetHP(const VECTOR2& Pos)
{
	//if (GetTarget()->GetHp() <= 0)return;
	//GetTarget()->HPRender(TargetHPGageSprite, Pos);
}
//2Dなどの描画
void Player::Render()
{
	//プレイヤーのHP
	//uiPlayerHP->Render();
	//目標の標準
	uiTargetCursur->Render();
	//目標のHP
	uiTargetHP->Render();

	uiSiroboAttack->Render();
	
	//HPRender(HealthPointSprite, {0,0});
	//目標の標準
	//RenderCursur();
	//ミニオンたちの2Dなどの描画処理
	siroboManager->Render();



}

//プレイヤーの体力表示
void Player::HPRender(const int &spriteIndex, const VECTOR2& pos)
{
//	VECTOR2 HPPosition= Pos;
//	const VECTOR2 SpriteSize = { 150,150 };
//
//	//プレイヤーの最大HPの表示
//	for (int i = 0; i < GetMaxHp(); i++)
//	{
//		HPPosition.x += 50;
//		TK_Lib::Draw::Sprite(SpriteIndex, HPPosition, SpriteSize, VECTOR4{ 0,0,256,256 });
//	}
//	//プレイヤーのHPの表示
//	HPPosition = Pos;
//	for (int i = 0; i < GetHp(); i++)
//	{
//		HPPosition.x += 50;
//		TK_Lib::Draw::Sprite(SpriteIndex, HPPosition, SpriteSize, VECTOR4{ 256 * 2,256 * 1,256,256 });
//	}
//
}
//プレイヤーのステージリセット処理
void Player::ResetPlayer()
{
	siroboManager->Clear();
	sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(this), GetPos());
	
	//for (int i = 0; i < 4; i++)
	//{
	//	shared_ptr<SiroboPlayer> sirobo;
	//	sirobo = make_shared<SiroboPlayer>();
	//	sirobo->Init(this);
	//	sirobo->SetPos({ 5,0,static_cast<float>(i * 8) });
	//	//	sirobo->pos = { 5,0,static_cast<float>(140) };
	//	siroboManager->Register(sirobo);
	//}
}

//ダメージを判定
bool Player::AddDamage(const int &damage, const float &setInvincibleTime)
{
	//体力が0以下なら
	if (GetHp() <= 0)return false;
	//無敵中なら
	if (invincibleTime > 0)return false;

	invincibleTime = setInvincibleTime;
	const float SubtractTime = -10;
	sceneGame->GetStageManager()->GetNowStage()->GetUiTimer()->AddGameOverTimer(SubtractTime);
	TK_Lib::Lib_Sound::SoundPlay("PlayerDamage", false);
	

	if (sceneGame->GetStageManager()->GetNowStage()->GetUiTimer()->GetGameTimer() <= 0)
	{
		//死亡
		SetDeadFlg(true);
	}
	else
	{
		//ダメージフラグのオン
		SetDamageFlg(true);
	}
	//hp -= Damage;
	//もし生き残っていたなら
	//if (hp >= 1)
	//{//ダメージフラグのオン
	//	SetDamageFlg(true);
	//}
	//else//死亡しているなら
	//{
	//	//ダメージフラグのオン
	//	SetDeadFlg(true);
	//}
	return true;
}

//CSVからデータを取り出して、ステータスの設定する。
void Player::SetStatus(const string &searchName)
{
	AlliesStatusData* data = sceneGame->GetexportSCV()->GetAlliesStatusDataSearchName(searchName);
	SetQuaternion({ 0,0,0,1 });
	SetMaxHp(data->GetHp());
	SetHp(data->GetHp());
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	speed = data->GetSpeed();
	collisionRadius = data->GetCollisionRadius();
	weight = data->GetWeight();
	SetMaxInvincibleTime(data->GetMaxInvincibleTime());
}
//アニメーションの設定
void Player::RegisterAnimetion()
{
	anime = make_shared<Animetion>();

	//アニメーション番号
	string AnimeIndex[] =
	{
		anime->Attack1,//"Attack",
		anime->Damage,//"Damage",
		anime->Die,//Dead
		anime->Idle,//"Wait",
		anime->Run,//"Walk",
		anime->End,//"End",
	};
	//アニメーションの登録
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//全てのモーションを登録
void Player::RegisterState()
{
	//全ての状態を先に登録しておく
	stateAttack = make_unique<AttackState>();
	stateDamage = make_unique<DamageState>();
	stateDead = make_unique<DeadState>();
	stateWait = make_unique<WaitState>();
	stateWalk = make_unique<WalkState>();
	stateBossEntry = make_unique<BossEntryPlayerState>();

	stateMachine = nullptr;
	ChangeState(stateWalk.get());
}




