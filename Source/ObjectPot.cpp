#include "ObjectDerived.h"
#include "Collision.h"
#include "Scene.h"
#include "MinionPlayer.h"

//����������
void ObjectPot::Init()
{
	SetQuaternion({ 0, 0, 0, 1 });
	//SetPos({ 0,0,0 });
	SetScale({ 0.1f,0.1f,0.1f });

	//SetCollisionModel("Pat");
	SetModel(TK_Lib::Load::GetModel("Pat"));

	SetHp(10);
	SetMaxHp(GetHp());


	SetTag(ObjectTag::TAG_OBJECT);
	collisionRadius = 5;
	objectType = ObjectType::Pot;


	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());

}
//�X�V����
void ObjectPot::Update()
{

}

bool ObjectPot::AddDamage(int Damage, int MaxinvincibleTime)
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

		{
			//�~�j�I���̏���
			shared_ptr<MinionPlayer> minion;
			minion = make_shared<MinionPlayer>();
			minion->Init(scene->GetPlayer());
			minion->SetPos(this->GetPos());
			//	minion->pos = { 5,0,static_cast<float>(140) };
			scene->GetPlayer()->GetMinionManager()->Register(minion);
		}

		
		//�_���[�W�t���O�̃I��
		Dead();
	}
	return true;
}
