#include "ObjectFunctionBase.h"
#include "ObjectFunctionManager.h"
#include "Scene.h"
//当たり判定用
void ObjectFunctionBase::CollisionRender()
{
	//TK_Lib::Debug3D::Circle(GetPos(),radius);
}
//ImGuiのデバッグ
void ObjectFunctionBase::ImguiDebug()
{
	ImGui::Begin("ObjectFunction");
	ImGui::Text("Pos=%f,%f,%f", pos.x, pos.y, pos.z);
	ImGui::Text("Radius=%f",radius);
	ImGui::End();
}
//オブジェクトの破棄処理
void ObjectFunctionBase::Destroy()
{
	sceneGame->GetObjectFunctionManager()->Destroy(this);
}
//範囲内に入っているかどうか
bool ObjectFunctionBase::IsCircle(const VECTOR3 Pos)
{
	XMVECTOR Vec,Pos1,Pos2;
	Pos1 = XMLoadFloat3(&pos);
	Pos2 = XMLoadFloat3(&Pos);
	Vec = XMVectorSubtract(Pos1,Pos2);
	//間の距離の算出
	Vec = XMVector3Length(Vec);
	float l;
	XMStoreFloat(&l,Vec);
	if (l >= radius)return false;
	return true;

}