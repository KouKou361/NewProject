#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "ExportScript.h"

//�����蔻��p�̃��f��
void ObjectBase::SetCollisionModel(const string &CollisionModelKey)
{
	collisionModel=TK_Lib::Load::GetModel(CollisionModelKey);
	TK_Lib::Model::Tranceform(collisionModel, GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::PlayAnimation(collisionModel,0,false);

	//�����蔻�胂�f�����X�g�ɒǉ�
	Collision::Instance().RegisterModel(collisionModel, ModelCollisionType::COLLISION_MODEL, this);
}

//����������
void ObjectBase::Init()
{
	SetTag(ObjectTag::TAG_OBJECT);
}

//�X�V����
void ObjectBase::Update()
{
//	//���f���̍s��X�V
//	if (GetModel() >= 0)
//	{
//		TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
//		TK_Lib::Model::AnimetionUpdate(GetModel());
//	}

	if (GetMaskVolume()>=1.0f)
	{
		Destroy();
	}
}

//���f���̕`�揈��
void ObjectBase::ModelRender()
{
	//���f���̕`��
	if (GetModel() >= 0)
	{
		if (TK_Lib::Camera::IsCamera(GetPos()))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}

//�����蔻��p�̕`��
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

void ObjectBase::HPRender(const int &SpriteIndex, const VECTOR2 &Pos)
{

}

//�j������
void ObjectBase::Destroy()
{
	
	objectManager->Destroy(this);
	//�����蔻��p�̃��f�����j��
	Collision::Instance().DeleteCollisionModel(collisionModel);
}

bool ObjectBase::AddDamage(const int &damage,const float &maxInvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp() <= 0)return false;

	SetHp(GetHp() - damage);
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

//�}�X�N�X�^�[�g
void ObjectBase::MaskStart(const float speed)
{
	TK_Lib::Model::MaskStart(GetModel(), speed);
}
//�}�X�N�傫���擾
float ObjectBase::GetMaskVolume()
{
	return TK_Lib::Model::GetMaskVolume(GetModel());
}


//�I�u�W�F�N�g�̎��S����
void ObjectBase::Dead()
{
	//�j�����̃G�t�F�N�g
	const int EffectNum = 20;
	scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(GetPos(), EffectNum);

	const float MaskSpeed = 0.5f;
	MaskStart(MaskSpeed);

}

//�I�u�W�F�N�g�̃_���[�W����
void ObjectBase::Damage()
{

}

//�X�e�[�^�X�̐ݒ�
void ObjectBase::SetStatus(const string &SearchName)
{
	ObjectStatusData* data = scene->GetexportSCV()->GetObjectStatusDataSearchName(SearchName);
	SetQuaternion({ 0,0,0,1 });
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	SetHp(data->GetHp());
	SetMaxHp(GetHp());
	collisionRadius = data->GetCollisionRadius();

}