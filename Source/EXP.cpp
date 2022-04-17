#include "EXP.h"
#include "EXPManager.h"
#include "Scene.h"
#include "UIDerived.h"
//初期化処理
void EXP::Init(VECTOR3 Pos)
{
	spriteIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/EXP.png");


	targetPos = TK_Lib::Window::GetWindowSize();

	targetPos.x = targetPos.x/2;
	targetPos.y = 20;
	//this->Pos = { 600,700 };
	this->pos=WorldToScreen(Pos);
	this->pos.y -= 10;

	angle = XMConvertToRadians(rand() % 360);

	this->velocity = { sinf(angle),cosf(angle)};

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

		angle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);


		const VECTOR2 V = { cosf(angle), sinf(angle) };
	

		//if(timer>= TK_Lib::Window::GetElapsedTime()*120)
		{
			VECTOR2 Vec;
			Vec.x = targetPos.x - pos.x;
			Vec.y = targetPos.y - pos.y;
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

	const VECTOR2 V = { cosf(angle), sinf(angle) };
	velocity = speed * V;

	pos.x += velocity.x;
	pos.y += velocity.y;
}
//更新処理
void EXP::Render()
{
//	TK_Lib::Blender::SetBlender(Bland_state::BS_ADD);

	TK_Lib::Draw::Sprite(spriteIndex, pos, size, VECTOR4{ 0,0,1024,1024 }, angle);
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