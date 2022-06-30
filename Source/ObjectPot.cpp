#include "ObjectDerived.h"
#include "Collision.h"
#include "Scene.h"
#include "SiroboPlayer.h"

//����������
void ObjectPot::Init()
{
	//���f���̐ݒ�
	SetModel(TK_Lib::Load::GetModel("Pat"));
	//�X�e�[�^�X�f�[�^�̐ݒ�
	SetStatus("Pot");
	//�^�O�̐ݒ�
	SetTag(ObjectTag::TAG_OBJECT);
	objectType = ObjectType::POT;

	//���f���̍s��X�V
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());

}
//�X�V����
void ObjectPot::Update()
{
	TK_Lib::Model::UpdateMask(GetModel());

	if (GetMaskVolume() >= 1.0f)
	{
		Destroy();
	}
}

bool ObjectPot::AddDamage(const int& damage, const float& maxInvincibleTime)
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
		//�~�j�I���̏���
		SummonSirobo();
	
		//�_���[�W�t���O�̃I��
		Dead();
	}
	return true;
}

//�V���{�̏���
void ObjectPot::SummonSirobo()
{
	shared_ptr<Sirobo> sirobo;
	sirobo = make_shared<Sirobo>();
	sirobo->Init(scene->GetPlayer());
	sirobo->SetPos(this->GetPos());
	//	sirobo->pos = { 5,0,static_cast<float>(140) };
	scene->GetPlayer()->GetSiroboManager()->Register(sirobo);

}
