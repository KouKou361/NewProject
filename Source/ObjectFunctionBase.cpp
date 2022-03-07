#include "ObjectFunctionBase.h"
#include "ObjectFunctionManager.h"
#include "Scene.h"
//�����蔻��p
void ObjectFunctionBase::CollisionRender()
{
	//TK_Lib::Debug3D::Circle(GetPos(),radius);
}
//ImGui�̃f�o�b�O
void ObjectFunctionBase::ImguiDebug()
{
	ImGui::Begin("ObjectFunction");
	ImGui::Text("Pos=%f,%f,%f", pos.x, pos.y, pos.z);
	ImGui::Text("Radius=%f",radius);
	ImGui::End();
}
//�I�u�W�F�N�g�̔j������
void ObjectFunctionBase::Destroy()
{
	sceneGame->GetObjectFunctionManager()->Destroy(this);
}
//�͈͓��ɓ����Ă��邩�ǂ���
bool ObjectFunctionBase::IsCircle(const VECTOR3 Pos)
{
	XMVECTOR Vec,Pos1,Pos2;
	Pos1 = XMLoadFloat3(&pos);
	Pos2 = XMLoadFloat3(&Pos);
	Vec = XMVectorSubtract(Pos1,Pos2);
	//�Ԃ̋����̎Z�o
	Vec = XMVector3Length(Vec);
	float l;
	XMStoreFloat(&l,Vec);
	if (l >= radius)return false;
	return true;

}