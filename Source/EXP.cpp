#include "EXP.h"
#include "EXPManager.h"
#include "Scene.h"
#include "UIDerived.h"
//初期化処理
void EXP::Init(VECTOR3 Pos)
{
	SpriteIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/EXP.png");


	TargetPos = TK_Lib::Window::GetWindowSize();

	TargetPos.x = TargetPos.x/2;
	TargetPos.y = 20;
	//this->Pos = { 600,700 };
	this->Pos=WorldToScreen(Pos);
	this->Pos.y -= 10;

	Angle = XMConvertToRadians(rand() % 360);

	this->Velocity = { sinf(Angle),cosf(Angle)};

	timer = 0;
	speed = -10;

}
//更新処理
void EXP::Update()
{
	speed += 0.2f;
	//念のため
	timer += TK_Lib::Window::GetElapsedTime();

	if (timer >= TK_Lib::Window::GetElapsedTime() * 240)
	{
		Delete();
	}

	if (speed >= 0)
	{

		Angle = atan2f(TargetPos.y - Pos.y, TargetPos.x - Pos.x);


		const VECTOR2 V = { cosf(Angle), sinf(Angle) };
	

		//if(timer>= TK_Lib::Window::GetElapsedTime()*120)
		{
			VECTOR2 Vec;
			Vec.x = TargetPos.x - Pos.x;
			Vec.y = TargetPos.y - Pos.y;
			XMVECTOR V;
			V = XMLoadFloat2(&Vec);
			V = XMVector3Length(V);
			float L; XMStoreFloat(&L, V);
			//V = XMVector2Normalize(V);
			//XMStoreFloat2(&Vec,V);
			//
			//Vec.x *= Speed_X;
			//Vec.y *= Speed_X;
			//
			////Velocity += Vec;


			if (L <= 40)
			{
				Delete();
			}


		}

	}

	const VECTOR2 V = { cosf(Angle), sinf(Angle) };
	Velocity = speed * V;

	Pos.x += Velocity.x;
	Pos.y += Velocity.y;
}
//更新処理
void EXP::Render()
{
//	TK_Lib::Blender::SetBlender(Bland_state::BS_ADD);

	TK_Lib::Draw::Sprite(SpriteIndex, Pos, Size, VECTOR4{ 0,0,1024,1024 }, Angle);
	//TK_Lib::Draw::Sprite(SpriteIndex, TargetPos, Size, VECTOR4{ 0,0,1024,1024 }, Angle);

//	TK_Lib::Blender::SetBlender(Bland_state::BS_NONE);
}

void EXP::Delete()
{
	TK_Lib::Lib_Sound::SoundPlay("GetCoin",false);
	scene->GetStageManager()->GetNowStage()->GetUiTimer()->AddGameOverTimer(5);
	scene->GetExpManager()->Destroy(this);
}

VECTOR2 EXP::WorldToScreen(VECTOR3 Pos)
{
	XMVECTOR WorldPosition;
	WorldPosition = XMLoadFloat3(&Pos);

	//座標変換
	XMMATRIX View = XMLoadFloat4x4(&TK_Lib::Camera::GetView());
	XMMATRIX Projection = XMLoadFloat4x4(&TK_Lib::Camera::GetProjection());
	XMMATRIX World = XMMatrixIdentity();

	VECTOR2 viewport = TK_Lib::Window::GetWindowSize();

	VECTOR3 screenPos;
	//ワールド座標からスクリーン座標に変換する
	XMVECTOR ScreenPosition;
	ScreenPosition = XMVector3Project(WorldPosition, 0, 0, viewport.x, viewport.y, 0.0f, 1.0, Projection, View, World);
	XMStoreFloat3(&screenPos, ScreenPosition);

	return VECTOR2{ screenPos.x,screenPos.y };
}