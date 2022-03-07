#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
//�����蔻��p�̃��f��
void ObjectBase::SetCollisionModel(string CollisionModelKey)
{
	collisionModel=TK_Lib::Load::GetModel(CollisionModelKey);
	TK_Lib::Model::Tranceform(collisionModel, GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::PlayAnimation(collisionModel,0,false);
	Collision::Instance().RegisterModel(collisionModel, ModelCollisionType::CollisionModel, this);
}
//����������
void ObjectBase::Init()
{
	SetTag(ObjectTag::TagObject);
}
//�X�V����
void ObjectBase::Update()
{
	//���f���̍s��X�V
	if (GetModel() >= 0)
	{
		TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
		TK_Lib::Model::AnimetionUpdate(GetModel());
	}
}
//�`�揈��
void ObjectBase::ModelRender()
{
	if (GetModel() >= 0)
	{

		if (TK_Lib::Camera::IsCamera(GetPos(), 35.0f))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}
void ObjectBase::CollisionRender()
{
	if (GetModel() >= 0)
	{
		TK_Lib::Draw::Model(collisionModel, ShaderType::Shader_NoLight);
	}
}
//ImGui�̃f�o�b�O
void ObjectBase::ImguiDebug()
{

}

void ObjectBase::HPRender(const int SpriteIndex, const VECTOR2 Pos)
{

}
void ObjectBase::Destroy()
{
	
	objectManager->Destroy(this);
	Collision::Instance().DeleteCollisionModel(collisionModel);
}
bool ObjectBase::AddDamage(int Damage, int MaxinvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp() <= 0)return false;

	SetHp(GetHp() - Damage);
	//���������c���Ă����Ȃ�
	if (GetHp() >= 1)
	{	//�I�u�W�F�N�g�̃_���[�W����
		this->Damage();
	}
	else//���S���Ă���Ȃ�
	{
		//�_���[�W�t���O�̃I��
		Dead();
	}
	return true;
}

//�I�u�W�F�N�g�̎��S����
void ObjectBase::Dead()
{
	scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(GetPos(), 20);
	Destroy();
}
//�I�u�W�F�N�g�̃_���[�W����
void ObjectBase::Damage()
{

}