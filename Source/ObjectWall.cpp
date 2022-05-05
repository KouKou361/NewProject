#include "ObjectDerived.h"
#include "Collision.h"
//����������
void ObjectWall::Init()
{
	//���f���̐ݒ�
	SetCollisionModel("CollisionWall");

	//�X�e�[�^�X�f�[�^�̐ݒ�
	SetModel(TK_Lib::Load::GetModel("Wall"));

	//�^�O�̐ݒ�
	SetTag(ObjectTag::TAG_OBJECT);
	objectType = ObjectType::WALL;

	//���f���̍s��X�V
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	
}
//�X�V����
void ObjectWall::Update()
{

}