#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
#include "Scene.h"
//初期化
void UI2DDirection::Init()
{
	indexTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/BossdirectionUI.png");

	pos = { 500,500 };
	cut = { 0,0,57,116 };
	size = { 70,100 };

	targetWorldPos = { 0,0,0 };
	targetScreenPos = TK_Lib::Window::GetWindowSize()/2;
	targetAngle = 0.0f;
}
//更新処理
void UI2DDirection::Update()
{


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
	TK_Lib::Draw::Sprite(indexTexture, targetScreenPos, size, cut, targetAngle);

	//Windowの描画
	//TK_Lib::Draw::Sprite(indexTexture, targetScreenPos, size, cut, targetAngle, {1,0,0,1});


}

//位置の設定
void UI2DDirection::SetTargetPos(const VECTOR3 TargetPos)
{
	targetWorldPos = TargetPos;
	targetWorldPos.y = 0.0f;
	//プレイヤーの位置の取得(XZ方向)
	XMVECTOR PlayerPos;
	{
		VECTOR3 PlPos = scene->GetPlayer()->GetPos();
		VECTOR3 cameraPos = TK_Lib::Camera::GetPos();
		cameraPos.y = 0.0f;
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
		XMVECTOR targetPos=XMLoadFloat3(&targetWorldPos);
		Vec = XMVectorSubtract(targetPos, PlayerPos);
	}



	CameraFront = XMVector3Normalize(CameraFront);
	Vec = XMVector3Normalize(Vec);

	XMVECTOR Dot= XMVector3Dot(Vec,CameraFront);
	float dot;
	XMStoreFloat(&dot, Dot);
	targetAngle = acosf(dot);

	XMVECTOR Cross = XMVector3Cross(CameraFront,Vec);
	VECTOR3 cross;
	XMStoreFloat3(&cross,Cross);
	if (cross.y <= 0)
	{
		targetAngle = -targetAngle;
	}

	targetAngle -= XMConvertToRadians(90);
	targetScreenPos.x = cosf(targetAngle) * UICenterR;
	targetScreenPos.y = sinf(targetAngle) * UICenterR;

	ImGui::Begin("a");
	ImGui::Text("dor=%f", XMConvertToDegrees(dot));
	ImGui::Text("targetAngle=%f", XMConvertToDegrees(targetAngle));
	static VECTOR2 p = TK_Lib::Window::GetWindowSize()/2;
	ImGui::SliderFloat2("pos",&p.x, 0, 1920);
	ImGui::End();
	TK_Lib::Debug2D::Circle(p,0.2f);
	targetScreenPos.x += p.x - 10.0f;
	targetScreenPos.y += p.y-30.0f;


}