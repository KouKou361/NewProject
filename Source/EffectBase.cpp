#include "EffectBase.h"
#include "ExportScript.h"
#include "Scene.h"

//�������ݒ�
void EffectBase::Init()
{
	//�S�Ẵp�[�e�B�N�����\����
	NotRender();
}

//�G�t�F�N�g�̐���
void EffectBase::Create(const string& textureName, const int& maxNum, const VECTOR2& textureChipSize, const VECTOR2& textureNum, const Bland_state& blendstate)
{
	//�ݒ��ۑ����Ă����i�ۑ�����K�v�Ȃ��Ǝv�����A�O�̂��߂ɕۑ��I�j
	{
		//�G�t�F�N�g�Ŏg�p���Ă���e�N�X�`���̖��O
		this->textureName = textureName;
		//�G�t�F�N�g���q�̍ő吔
		this->maxNum = maxNum;
		//�������̃`�b�v�T�C�Y
		this->textureChipSize = textureChipSize;
		//�`�b�v���������邩�ǂ����iX�AY�j
		this->textureNum = textureNum;
		//�u�����h�̎��
		this->blendState = blendstate;
	}
	

	//�G�t�F�N�g�̃��[�h
	effectIndex =TK_Lib::Lib_Effect::Load(this->textureName, this->maxNum, this->textureChipSize, this->textureNum, this->blendState);
}

//�S�Ẵp�[�e�B�N�����\����
void EffectBase::NotRender()
{
	//�p�[�e�B�N���z����̎擾
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	//�S�Ĕ�\��
	for (int j = 0; j < spriteEffects->size(); j++)
	{
		EffectData* spriteEffect = &spriteEffects->at(j);
		//��\���ɂ���
		if (spriteEffect->type >= 0)
		{
			spriteEffect->type = -1;
		}
	}


	
}
//�G�t�F�N�g�̍폜�֐�
void EffectBase::Delete()
{
	TK_Lib::Lib_Effect::Erase(effectIndex);
}

//csv�f�[�^����X�e�[�^�X�̐ݒ������
void EffectBase::SetStatus(SceneGame* sceneGame, const string& SearchName)
{
	//�G�t�F�N�g�̃f�[�^�擾
	EffectStatusData* data = sceneGame->GetexportSCV()->GetEffectStatusDataSearchName(SearchName);


	this->initStatus.effectType        = data->GetEffectType();                 //�G�t�F�N�g�̃^�C�v
	this->initStatus.timer             = data->GetTimer();                      //��������
	this->initStatus.updateAlpha       = data->GetUpdateAlpha();                //�X�V�����̓����x�̕ω���
	
	this->initStatus.posMax            = data->GetPosMax();		                //�ʒu�����̍ō��l
	this->initStatus.posMix            = data->GetPosMix();	                    //�ʒu�����̍Œ�l

	this->initStatus.velocityMax       = data->GetVelocityMax();	            //���x�����̍ō��l
	this->initStatus.velocityMix       = data->GetVelocityMix();                //���x�����̍Œ�l

	this->initStatus.accelMax          = data->GetAccelMax();	                //�����x�����̍ō��l
	this->initStatus.accelMix          = data->GetAccelMix();	                //�����x�����̍Œ�l

	this->initStatus.scale             = { data->GetScale(),data->GetScale() };	//�傫��

	this->initStatus.color             = data->GetColor();                      //�F
																																							
	this->initStatus.updateScale       = { data->GetUpdateScale(),data->GetUpdateScale() };//�X�V�����̑傫���̕ω���																	
														
}			
//�G�t�F�N�g�̏o������
void EffectBase::Play(const VECTOR3& pos, const int &num)
{
	//�p�[�e�B�N���z����̎擾
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);


	for (int i = 0; i < num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);
			if (spriteEffect->type >= 0)continue;

			VECTOR3 p = { 0,0,0 };      //�ʒu
			VECTOR3 v = { 0,0,0 };	    //���x
			VECTOR3 f = { 0,0,0 };	    //�����x		  
			VECTOR2 s = { 0,0 };
			VECTOR4 color = { 0,0,0,0 };

			//�傫��
			{
				s = initStatus.GetScale();
			}
			//�ʒu�̎Z�o
			{
				p.x = pos.x + Mathf::RandomRange(initStatus.GetPosMix().x, initStatus.GetPosMax().x);
				p.y = pos.y + Mathf::RandomRange(initStatus.GetPosMix().y, initStatus.GetPosMax().y);
				p.z = pos.z + Mathf::RandomRange(initStatus.GetPosMix().z, initStatus.GetPosMax().z);
			}

			//���x�̎Z�o
			{
				v.x = Mathf::RandomRange(initStatus.GetVelocityMix().x, initStatus.GetVelocityMax().x);
				v.y = Mathf::RandomRange(initStatus.GetVelocityMix().y, initStatus.GetVelocityMax().y);
				v.z = Mathf::RandomRange(initStatus.GetVelocityMix().z, initStatus.GetVelocityMax().z);
			}

			//�����x�̎Z�o
			{
				f.x = Mathf::RandomRange(initStatus.GetAccelMix().x, initStatus.GetAccelMax().x);
				f.y = Mathf::RandomRange(initStatus.GetAccelMix().y, initStatus.GetAccelMax().y);
				f.z = Mathf::RandomRange(initStatus.GetAccelMix().z, initStatus.GetAccelMax().z);
			}

			//�F
			{
				color.x = initStatus.GetColor().x;
				color.y = initStatus.GetColor().y;
				color.z = initStatus.GetColor().z;
				color.w = initStatus.GetColor().w;
			}




			//�ݒ�֐�	
			spriteEffect->Set(
				initStatus.GetEffectType(),
				initStatus.GetTimer(),
				p, v, f, s,color);
			break;
		}


	}
}

//�X�V����
void EffectBase::Update()
{
	//�G�t�F�N�g�ɂ�2�̃^�C�v������B
	//�܂��P�ڂ̓J�����O�͏����Ȃ��X�V�����^�C�v
	//�Q�ڂ̓J�����O�͏�����X�V�����^�C�v�i�y�ʉ��ׁ̈j
	//���ׂ̈̕��򏈗���

	if (isCameraUpdateFlg)
	{
		//���g���J�����O�̏ꍇ�ł�������X�V�������s��
		IsCameraUpdate();
	}
	else
	{
		//���g���J�����O�̏ꍇ�A�����Ȃ��X�V�������s��Ȃ�
		NotIsCameraUpdate();
	}
}

//���g���J�����O�̏ꍇ�A������X�V�������s��Ȃ�
void EffectBase::NotIsCameraUpdate()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);

		if (spriteEffect->type < 0) continue;
		if (!spriteEffect->IsCameraRender())continue;//�J�����O�Ȃ̂ŏ������s��Ȃ�

		//�p�[�e�B�N���̃X�e�[�^�X�X�V����
		ParticleUpdate(spriteEffect);

		spriteEffect->color.w -= initStatus.GetUpdateAlpha() * time;

		//�����鏈��
		if (spriteEffect->color.w <= 0)	spriteEffect->type = -1;
		if (spriteEffect->timer <= 0)spriteEffect->type = -1;
	}
}
//���g���J�����O�̏ꍇ�ł�������X�V�������s��
void EffectBase::IsCameraUpdate()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);

		if (spriteEffect->type < 0) continue;

		spriteEffect->color.w -= initStatus.GetUpdateAlpha() * time;

		//�����鏈��
		if (spriteEffect->color.w <= 0)	spriteEffect->type = -1;
		if (spriteEffect->timer <= 0)spriteEffect->type = -1;

		if (!spriteEffect->IsCameraRender())continue;//�J�����O�Ȃ̂ŏ������s��Ȃ�

		//�p�[�e�B�N���̃X�e�[�^�X�X�V����
		ParticleUpdate(spriteEffect);

	}

}
//�p�[�e�B�N���̃X�e�[�^�X�X�V����
void EffectBase::ParticleUpdate(EffectData* spriteEffect)
{
	float time = TK_Lib::Window::GetElapsedTime();

	spriteEffect->vx += spriteEffect->ax * time;//���x�̍X�V����
	spriteEffect->vy += spriteEffect->ay * time;//���x�̍X�V����
	spriteEffect->vz += spriteEffect->az * time;//���x�̍X�V����

	spriteEffect->x += spriteEffect->vx * time;//�ʒu�̍X�V����
	spriteEffect->y += spriteEffect->vy * time;//�ʒu�̍X�V����
	spriteEffect->z += spriteEffect->vz * time;//�ʒu�̍X�V����

	spriteEffect->timer -= time;
	spriteEffect->h += initStatus.GetUpdateScale().x * time;
	spriteEffect->w += initStatus.GetUpdateScale().y * time;
}
