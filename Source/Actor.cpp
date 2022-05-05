#include "Actor.h"

Actor::~Actor()
{
	DeleteModel();
}
//モデルの設定
void Actor::SetModel(const int& modelIndex)
{
	if (modelIndex <= -1)
	{
		this->modelIndex = modelIndex;
		return;
	}
	this->modelIndex = TK_Lib::Load::CopyModel(modelIndex);
}
//モデルの削除
void Actor::DeleteModel()
{
	if (modelIndex <= 0)return;
	TK_Lib::Delete::DeleteModel(modelIndex);
	modelIndex = -1;
}
//攻撃しているシロボリストから指定されたシロボの削除処理
void Actor::AttackSiroboErase(Sirobo* sirobo)
{
	//破棄処理
	for (Sirobo* mSirobo : attackSirobo)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<Sirobo*>::iterator it = std::find(attackSirobo.begin(), attackSirobo.end(), sirobo);
		if (it != attackSirobo.end())
		{
			attackSirobo.erase(it);
		}
	}

}


void Actor::SetQuaternion(const VECTOR4& quaternion)
{
	this->quaternion = quaternion;

	XMVECTOR Q = XMLoadFloat4(&this->quaternion);
	//クォオタニオンの値がバクっていないか確認
	assert(!XMQuaternionIsNaN(Q));


	XMMATRIX Qu = XMMatrixRotationQuaternion(Q);
	XMFLOAT4X4 m;
	XMStoreFloat4x4(&m, Qu);

	XMVECTOR Right = XMVectorSet(m._11, m._12, m._13, m._14);//右ベクトルのセット
	XMVECTOR Up = XMVectorSet(m._21, m._22, m._23, m._24);//上ベクトルのセット
	XMVECTOR Front = XMVectorSet(m._31, m._32, m._33, m._34);//前ベクトルのセット

	XMStoreFloat3(&right, Right);
	XMStoreFloat3(&up, Up);
	XMStoreFloat3(&front, Front);
}