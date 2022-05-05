#include "CameraController.h"
#include "Charactor.h"
#include "Collision.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"

CameraBossEntry::CameraBossEntry(Actor* owner, EnemyBase* enm, BossStage* stage) {
	this->owner = owner;
	this->state = stage;
	this->enm = enm;
}
//初期化処理
void CameraBossEntry::Init()
{
	if (this->owner == nullptr)assert(!"ownerがnull");
	if (this->state == nullptr)assert(!"stateがnull");
	if (this->enm == nullptr)assert(!"enmがnull");

	manager->cameraType = CameraManager::CameraType::TYPE_BOSS;

	const float AngleY = 15;
	const float AngleX = 45;
	angle.y = DirectX::XMConvertToRadians(AngleY);
	angle.x = DirectX::XMConvertToRadians(AngleX);

	endTargetPos = owner->GetPos();
	startEyePos = { 0,100,100 };
	eye = startEyePos;
	targetPos = { 0,0,0 };

	lookAtOwnerTimer = 0.0f;
}

//視点位置を決める更新
void CameraBossEntry::UpdateEye()
{
	//BossEntryActionが状況に応じて操作してくれるので
	//記入なし
}
//注視点を決める更新
void CameraBossEntry::UpdateTarget()
{
	//BossEntryActionが状況に応じて操作してくれるので
    //記入なし
}
//更新処理
void CameraBossEntry::Update()
{
	//BossEntryActionが状況に応じて操作してくれるので
    //記入なし
}
//終了処理
void CameraBossEntry::End()
{

}
//Imgui
void CameraBossEntry::Imgui()
{
	ImGui::Begin(u8"ゲーム");
	ImGui::Text("CameraBossEntry");
	ImGui::Text("Angle.x.y.z=%f,%f,%f", angle.x, angle.y, angle.z);
	ImGui::Text("eye.x.y.z=%f,%f,%f", eye.x, eye.y, eye.z);
	ImGui::Text("Target.x.y.z=%f,%f,%f", targetPos.x, targetPos.y, targetPos.z);
	ImGui::End();
}


//Ownerの方に向いておく
bool CameraBossEntry::LookatOwner()
{
	//次の状態に移行するまでの時間
	{
		const float NextTimer = 3.0f;

		lookAtOwnerTimer += TK_Lib::Window::GetElapsedTime();
		if (lookAtOwnerTimer >= NextTimer)
		{
			lookAtOwnerTimer = 0.0f;
			return true;
		}
	}
	
	//カメラの注視点
	{
		targetPos = owner->GetPos();
	}

	//カメラの位置の算出
	{
		//カメラとonwerとの距離
		static float L = 60.0f;

		//回転行列に変換する
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//前方ベクトルの算出
		DirectX::XMVECTOR Front = Transform.r[2];
		//
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);

		eye.x = owner->GetPos().x - front.x * L;
		eye.y = owner->GetPos().y - front.y * L;
		eye.z = owner->GetPos().z - front.z * L;

		startTargetPos = owner->GetPos();
		endTargetPos = enm->GetPos();
	}

	
	
	VECTOR3 Vup = { 0,1,0 };
	//カメラの設定
	TK_Lib::Camera::SetLookAt(eye, targetPos, Vup);

	return false;
}
//敵の方向に向く
bool CameraBossEntry::LookatOwnerFront()
{
	//敵の方向に向くカメラの移動スピード
	constexpr float CameraXSpeed = XMConvertToRadians(0.4f);
	//次のカメラ状態に遷移する角度
	constexpr float NextCameraMax = XMConvertToRadians(170);
	//線上補完の時間
	const float LerpSpeed = 0.004f;

	//カメラの位置算出
	{
		angle.x += CameraXSpeed;
		if (angle.x >= NextCameraMax)
		{
			angle.x = NextCameraMax;
			return true;
		}

		//回転行列に変換する
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//前方ベクトルの算出
		DirectX::XMVECTOR Front = Transform.r[2];
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);

		//カメラとonwerとの距離
		static float L = 60.0f;
		eye.x = owner->GetPos().x - front.x * L;
		eye.y = owner->GetPos().y - front.y * L;
		eye.z = owner->GetPos().z - front.z * L;
	}

	//カメラの注視点の算出
	LerpTargetCamera(LerpSpeed);

	//カメラの設定
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
	return false;
}
//ボスを見る
bool CameraBossEntry::LookatBoss()
{
	//カメラとonwerとの距離
	static float L = 60.0f;
	//敵の方向に向くカメラの移動スピード
	constexpr float CameraX = XMConvertToRadians(180);
	//次のカメラ状態に遷移する角度
	constexpr float CameraY = XMConvertToRadians(15);
	//注視点のY
	const float TargetPosY = 13.0f;


	
	
	angle.x = CameraX;
	angle.y = CameraY;
	
	//カメラの位置算出
	{
		//回転行列に変換する
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//前方ベクトルの算出
		DirectX::XMVECTOR Front = Transform.r[2];
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


		eye.x = enm->GetPos().x - front.x * L;
		eye.y = enm->GetPos().y - front.y * L;
		eye.z = enm->GetPos().z - front.z * L;
		startEyePos = eye;
	}

	//カメラの注視点の算出
	{
		targetPos = enm->GetPos();
		targetPos.y = TargetPosY;
	}

	//カメラの設定
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });

	return true;
}
//ボスからカメラが離れる
bool CameraBossEntry::BackCamera()
{
	//敵が動きだす時間
	const float enmActionTimer = 1.0f;
	//カメラの固定角度
	const float AngleY = 10.0f;
	const float AngleZ = 10.0f;
	//線上補完の時間
	const float LerpTimer = 0.026f;
	//カメラとonwerとの距離
	const float L = 100.0f;



	lookAtOwnerTimer += TK_Lib::Window::GetElapsedTime();
	//時間が来たなら
	if (lookAtOwnerTimer >= enmActionTimer)
	{
		enm->SetActionFlg(true);//敵行動可能の通知
		angle.y = DirectX::XMConvertToRadians(AngleY);
		angle.z = DirectX::XMConvertToRadians(AngleZ);
	
	}

	//endEyePosの算出
	{
		//回転行列に変換する
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//前方ベクトルの算出
		DirectX::XMVECTOR Front = Transform.r[2];
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


		endEyePos.x = owner->GetPos().x - front.x * L;
		endEyePos.y = owner->GetPos().y - front.y * L;
		endEyePos.z = owner->GetPos().z - front.z * L;
	}
	//カメラの注視点の算出
	{
		targetPos = enm->GetPos();
	}

	//線上補完
	if (LerpEyeCamera(LerpTimer))
	{
		//線上補完終了
		return true;
	}
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
	return false;
}

