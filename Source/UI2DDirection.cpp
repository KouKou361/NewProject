#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
#include "Scene.h"
//初期化
void UI2DDirection::Init()
{
	TextureIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/BossdirectionUI.png");

	pos = { 500,500 };
	cut = { 0,0,57,116 };
	size = { 70,100 };

	targetWorldPos = { 0,0,0 };
	targetScreenPos = TK_Lib::Window::GetWindowSize()/2;
	targetAngle = 0.0f;
	Update();
}
//更新処理
void UI2DDirection::Update()
{

	//スクリーン座標でターゲットの向きを算出
	SetTargetAngle();

	//半径
	const float UiCenterR = 250.0f;
	const VECTOR2 offset = { -10.0f,-30.0f };
	
	targetScreenPos.x = cosf(targetAngle) * UiCenterR;
	targetScreenPos.y = sinf(targetAngle) * UiCenterR;

	//ImGui::Begin("a");
	//ImGui::Text("dor=%f", XMConvertToDegrees(dot));
	//ImGui::Text("targetAngle=%f", XMConvertToDegrees(targetAngle));
	//static VECTOR2 p = TK_Lib::Window::GetWindowSize() / 2;
	//ImGui::SliderFloat2("pos", &p.x, 0, 1920);
	//ImGui::End();
	const VECTOR2 p = TK_Lib::Window::GetWindowSize() / 2;
	//TK_Lib::Debug2D::Circle(p, 0.2f);
	targetScreenPos.x += p.x - offset.x;
	targetScreenPos.y += p.y - offset.y;



}
//描画処理
void UI2DDirection::Render()
{
	//	static VECTOR2 P = { 200,400 };
	//	static VECTOR2 S = { 256,256 };
	//
	//	static VECTOR2 S1 = { 256 / 3,256 / 3 };
	//	static VECTOR2 S2 = { (256 / 3) * 2,(256 / 3) * 2 };
	//	static VECTOR2 S3 = { 1,1 };
	//
	//	static VECTOR2 centerScale = {1,1};
	//
	//	ImGui::Begin("Slice");
	//	ImGui::SliderFloat2("Pos", &P.x,0,1000);
	//	ImGui::SliderFloat2("Size", &S.x, 0, 1000);
	//
	//	ImGui::SliderFloat2("Slice1", &S1.x, 0, 100);
	//	ImGui::SliderFloat2("Slice2", &S2.x, 0, 100);
	//	ImGui::SliderFloat2("Slice3", &S3.x, 0, 5);
	//	ImGui::SliderFloat2("centerScale", &centerScale.x, 0, 20);
	//	ImGui::End();

	//Windowの描画
	TK_Lib::Draw::Sprite(TextureIndex, targetScreenPos, size, cut, targetAngle);
}

//位置の設定
void UI2DDirection::SetTargetPos(const VECTOR3 TargetPos)
{
	targetWorldPos = TargetPos;
	targetWorldPos.y = 0.0f;
	
}

//スクリーン座標でターゲットの向きを算出
void UI2DDirection::SetTargetAngle()
{
	//プレイヤーの位置の取得(XZ方向)
	XMVECTOR PlayerPos;
	{
		VECTOR3 PlPos = scene->GetPlayer()->GetPos();
		PlayerPos = XMLoadFloat3(&PlPos);
	}

	//カメラの正面方向の取得(XZ方向)
	XMVECTOR CameraFront;
	{
		VECTOR3 cameraFront = TK_Lib::Camera::GetFront();
		cameraFront.y = 0.0f;
		CameraFront = XMLoadFloat3(&cameraFront);
	}

	//プレイヤーと目標地点のベクトル
	XMVECTOR Vec;
	{
		XMVECTOR targetPos = XMLoadFloat3(&targetWorldPos);
		Vec = XMVectorSubtract(targetPos, PlayerPos);
	}



	CameraFront = XMVector3Normalize(CameraFront);
	Vec = XMVector3Normalize(Vec);

	XMVECTOR Dot = XMVector3Dot(Vec, CameraFront);
	float dot;
	XMStoreFloat(&dot, Dot);
	targetAngle = acosf(dot);

	XMVECTOR Cross = XMVector3Cross(CameraFront, Vec);
	VECTOR3 cross;
	XMStoreFloat3(&cross, Cross);
	if (cross.y <= 0)
	{
		targetAngle = -targetAngle;
	}

	//テクスチャが真横なので調整するため
	constexpr float Radians= XMConvertToRadians(90);

	targetAngle -= Radians;
}