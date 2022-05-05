#include "Actor.h"

Actor::~Actor()
{
	DeleteModel();
}
//���f���̐ݒ�
void Actor::SetModel(const int& modelIndex)
{
	if (modelIndex <= -1)
	{
		this->modelIndex = modelIndex;
		return;
	}
	this->modelIndex = TK_Lib::Load::CopyModel(modelIndex);
}
//���f���̍폜
void Actor::DeleteModel()
{
	if (modelIndex <= 0)return;
	TK_Lib::Delete::DeleteModel(modelIndex);
	modelIndex = -1;
}
//�U�����Ă���V���{���X�g����w�肳�ꂽ�V���{�̍폜����
void Actor::AttackSiroboErase(Sirobo* sirobo)
{
	//�j������
	for (Sirobo* mSirobo : attackSirobo)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
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
	//�N�H�I�^�j�I���̒l���o�N���Ă��Ȃ����m�F
	assert(!XMQuaternionIsNaN(Q));


	XMMATRIX Qu = XMMatrixRotationQuaternion(Q);
	XMFLOAT4X4 m;
	XMStoreFloat4x4(&m, Qu);

	XMVECTOR Right = XMVectorSet(m._11, m._12, m._13, m._14);//�E�x�N�g���̃Z�b�g
	XMVECTOR Up = XMVectorSet(m._21, m._22, m._23, m._24);//��x�N�g���̃Z�b�g
	XMVECTOR Front = XMVectorSet(m._31, m._32, m._33, m._34);//�O�x�N�g���̃Z�b�g

	XMStoreFloat3(&right, Right);
	XMStoreFloat3(&up, Up);
	XMStoreFloat3(&front, Front);
}