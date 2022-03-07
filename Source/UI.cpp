#include "UIBase.h"
//#include "UIManager.h"
//破棄処理
void UIBase::Destroy()
{
	//manager->Destroy(this);
}

//子供設定
void UIBase::SetChildren(UIBase* ui)
{
	children.push_back(ui);
}

VECTOR2 UIBase::WorldToScreen(VECTOR3 Pos)
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