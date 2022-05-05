#include "EXP.h"
#include "EXPManager.h"
#include "Scene.h"
#include "UIDerived.h"
//初期化処理
void EXP::Init(const VECTOR3 &pos)
{
	//テクスチャの読み込み
	spriteIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/EXP.png");

	//目標地点の算出
	SetTargetPos();

	//位置の算出
	SetPos(pos);

	//向きの算出（３６０度）
	angle = XMConvertToRadians(static_cast<float>(rand() % 360));

	//進む方向の算出
	this->velocity = { sinf(angle),cosf(angle)};

	//速さの算出
	speed = -10;

	timer = 0;
}
//更新処理
void EXP::Update()
{
	//ある適度時間が過ぎたら消える処理
	DeleteToTimer();

	//ある適度目標に小さい場合消える処理
	const float DeleteLength = 40.0f;
	DeleteMinLength(DeleteLength);

	//目標地点に進む
	ModeToTarget();

}

//更新処理
void EXP::Render()
{
	const VECTOR4 cut = { 0,0,1024,1024 };
	//EXPの描画
	TK_Lib::Draw::Sprite(spriteIndex, pos, size, cut, angle);
}

//破棄処理
void EXP::Delete()
{
	//サウンド（チャリン）
	TK_Lib::Lib_Sound::SoundPlay("GetCoin",false);

	//ゲームオーバータイマーの回復
	const int AddGameOverTimerNum = 5;
	scene->GetStageManager()->GetNowStage()->GetUiTimer()->AddGameOverTimer(AddGameOverTimerNum);

	//自分自身の破棄
	scene->GetExpManager()->Destroy(this);
}

//ワールドからスクリーン座標に変換
VECTOR2 EXP::WorldToScreen(const VECTOR3& pos)
{
	XMVECTOR WorldPosition;
	WorldPosition = XMLoadFloat3(&pos);

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

//目標地点の算出
void EXP::SetTargetPos()
{
	//目標の高さ
	const float targetPosY = 20.0f;
	//目標の横の半分
	const float targetPosX = TK_Lib::Window::GetWindowSize().x/2;

	targetPos.x = targetPosX;
	targetPos.y = targetPosY;
	
}

//位置の算出
void EXP::SetPos(const VECTOR3& pos)
{

	//位置の算出
	const float PosYScreenDown = 10.0f;//スクリーン座標に変換した時ちょっと上に上げる。
	this->pos = WorldToScreen(pos);//ワールド座標からスクリーン座標
	this->pos.y -= PosYScreenDown;
	
}

//目標地点に進む
void EXP::ModeToTarget()
{
	//加速度
	const float AcceleSpeed = 0.2f;
	speed += AcceleSpeed;//早くする

	if (speed >= 0)
	{
		//角度の算出
		angle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);
	}

	//進むベクトルの算出
	const VECTOR2 V = { cosf(angle), sinf(angle) };
	velocity = speed * V;

	pos.x += velocity.x;	//位置の更新処理
	pos.y += velocity.y;	//位置の更新処理
}
//ある適度時間が過ぎたら消える処理
void EXP::DeleteToTimer()
{
	//念のため
	timer += TK_Lib::Window::GetElapsedTime();

	//消滅時間
	const float DeleteTime = 4;
	if (timer >= DeleteTime)
	{
		Delete();
	}

}

//ある適度目標に小さい場合消える処理
void EXP::DeleteMinLength(const float& DeleteLength)
{
	float l=0;
	{
		VECTOR2 Vec;
		Vec.x = targetPos.x - pos.x;
		Vec.y = targetPos.y - pos.y;
		XMVECTOR V;
		V = XMLoadFloat2(&Vec);
		V = XMVector3Length(V);
		XMStoreFloat(&l, V);
	}
	if (l <= DeleteLength)
	{
		Delete();
	}

}