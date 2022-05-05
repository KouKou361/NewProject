#include "ObjectDerived.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "UIDerived.h"

//����������
void ObjectTower::Init()
{
	//���f���̐ݒ�
	SetModel(TK_Lib::Load::GetModel("Tower"));

	//�X�e�[�^�X�f�[�^�̐ݒ�
	SetStatus("Tower");

	//�^�O�̐ݒ�
	SetTag(ObjectTag::TAG_OBJECT);
	objectType = ObjectType::TOWER;

	//�X�|�b�g���C�g�̍쐬
	spotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,0,1,1 }, 20.0f);

	//���f���̍s��X�V
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());

	//���C�g�̖��邳
	spotLightRadius = 10.0f;

	timer = 0.0f;
}
//�X�V����
void ObjectTower::Update()
{
	//���Ԃ̍X�V����
	timer += TK_Lib::Window::GetElapsedTime();
	
	//�X�|�b�g���C�g�̍X�V����
	TK_Lib::SpotLight::Set(spotLightHandle, GetPos(), { 1,0,1,1 }, sinf(timer)* spotLightRadius+20.0f);
	
}
//�I�u�W�F�N�g�̎��S����
void ObjectTower::Dead()
{
	//�^���[�̐���m�点��_�Ń^�C�}�[
	const float blinkingTimer = 10.0f;
	scene->GetStageManager()->GetNowStage()->GetNumTower()->SetBlinkingTimer(blinkingTimer);

	//�G�t�F�N�g�̐��i�^���[�̔j���G�t�F�N�g�������j
	const int EffectNum = 30;
	scene->GetEffectManager()->GetEffectFromSerchKey("TowerBreak")->Play(GetPos(), EffectNum);

	//�^���[�̃T�E���h
	TK_Lib::Lib_Sound::SoundPlay("TowerBreak",false);
	TK_Lib::Lib_Sound::SoundPlay("TowerBreak2", false);

	//�X�|�b�g���C�g�̔j��
	TK_Lib::SpotLight::Delete(spotLightHandle);

	Destroy();
}
