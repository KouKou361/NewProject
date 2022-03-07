#include "Lib_EffectManager.h"
#include "Lib_Rasterizer.h"
#include "Lib_DepthStencil.h"

//����������
void Lib_EffectManager::Init(const UINT MaxLoadNum, ID3D11Device* device)
{
	SpriteEffects.resize(MaxLoadNum);
	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		SpriteEffects.at(i) = make_shared<SpriteEffect>();
	}

	PointSpriteshader = make_unique<ShaderResource>();
	PointSpriteshader->Create(device, "./Shader/PointSprite_vs.cso", "./Shader/PointSprite_gs.cso", "./Shader/PointSprite_ps.cso", ShaderResource::TYPELayout::TYPE_layoutPointSprite);
}
//���[�h(1:device,2:�e�N�X�`���̃p�X,3:�G�t�F�N�g�̃n���h��)
void Lib_EffectManager::Load(ID3D11Device* device, const string name, int& handle, int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state)
{
	//���ɓǂݍ���ł���e�N�X�`�������邩�ǂ����𒲂ׂ�
	if (DuplicateFind(name, handle) == true)
	{
		//textures�̋�ł���v�f�ɓo�^���Ă���
		Register(device, name, handle,Maxnum,TextureChipSize,TextureNum, state);
	}
}
//�폜
void Lib_EffectManager::Erase(ID3D11Device* device, const  int handle)
{
	//�e�N�X�`���̎擾
	SpriteEffect* textureData = GetSpriteEffectResource(handle);
	//�l���폜
	textureData->handle = -1;
	SpriteEffects.at(handle).reset();

	//�e�N�X�`���̓ǂݍ��񂾐���-1����
	LoadNum--;
}
void Lib_EffectManager::Clear()
{
	SpriteEffects.clear();
}
//�e�N�X�`���̎擾
SpriteEffect* Lib_EffectManager::GetSpriteEffectResource(const int handle)
{
	//�ݒ肳��Ă��Ȃ��܂��͍폜���ꂽ�e�N�X�`�����g�����Ƃ��Ă��邩�ǂ���
	assert(SpriteEffects.at(handle)->handle != -1);
	return SpriteEffects.at(handle).get();
}
//�X�V����
void Lib_EffectManager::Update()
{
	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		SpriteEffects.at(i)->SetUseLastEffectIndex();
	}
}
//�A�j���[�V��������
void Lib_EffectManager::Animation(float elapsedtimer, const  int handle, int Starttype, int Endtype, float Animetionspeed)
{
	SpriteEffect* efc= SpriteEffects.at(handle).get();
	if (efc->handle <= -1)return;
	efc->Animation(elapsedtimer, Starttype, Endtype, Animetionspeed);
}
void Lib_EffectManager::SetType(const int handle, int type)
{
	for (int i = 0; i < GetSpriteEffectResource(handle)->Geteffects()->size(); i++)
	{
		GetSpriteEffectResource(handle)->Geteffects()->at(i).type = type;
	}

}



//�G�t�F�N�g�̕`��J�n����
void Lib_EffectManager::Begin(ID3D11DeviceContext* context)
{

	//�V�F�[�_�[�L����
	PointSpriteshader->Activate(context);
	//���X�^���C�U�[�ݒ�
	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	//�f�v�X�X�e���V��
	context->OMSetDepthStencilState(DepthStencil::Instance().m_depthState[DepthStencil::DS_WRITE_FALSE].Get(), 1);
	//�v���~�e�B�u�g�|���W�[���Z�b�g
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
}
//�`�揈��
void Lib_EffectManager::Render(ID3D11DeviceContext* context, XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	string oldTextureFileName="";
	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		if (SpriteEffects.at(i)->handle <= -1)continue;

		if (strcmp(oldTextureFileName.c_str(), SpriteEffects.at(i)->GetTextureName().c_str()) != 0)
		{
			SpriteEffects.at(i)->UpdateConstantBuffer(context,view,projection);
		}

		oldTextureFileName = SpriteEffects.at(i)->GetTextureName();


		SpriteEffects.at(i)->Render(context);
	}
}
//�G�t�F�N�g�̕`��J�n����
void Lib_EffectManager::End(ID3D11DeviceContext* context)
{
	//�f�v�X�X�e���V���ݒ�
	context->OMSetDepthStencilState(DepthStencil::Instance().m_depthState[DepthStencil::DS_FALSE].Get(), 1);
	//�V�F�[�_�[�̖�����
	PointSpriteshader->Inactivate(context);
}

//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
bool Lib_EffectManager::DuplicateFind(const string name, int& handle)
{
//	for (int i = 0; i < SpriteEffects.size(); i++)
//	{
//
//
//		//�e�N�X�`���̎擾
//		SpriteEffect* textureData = SpriteEffects.at(i).get();
//
//		if (-1 >= textureData->handle)continue;
//
//		//�e�N�X�`�����d�����Ă��邩�ǂ���������
//		if (name == textureData->filename)
//		{
//			//�d�����Ă���
//			handle = textureData->handle;
//			return false;
//		}
//	}
	return true;
}

//textures�̋�ł���v�f�ɓo�^���Ă���
void Lib_EffectManager::Register(ID3D11Device* device, const string name, int& handle,int Maxnum,VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state)
{
	//Texture�̓ǂݍ��߂鐔���ő�ɒB���Ă��邩�ǂ���
	assert(LoadNum < SpriteEffects.size());

	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		//�e�N�X�`���̎擾
		SpriteEffect* efc = SpriteEffects.at(i).get();
		if (-1 < efc->handle)continue;

		//��ɓo�^����
		efc->Create(device,Maxnum, name,TextureChipSize,TextureNum);
		efc->handle = i;
		efc->BlenderType = state;
		handle = i;
		LoadNum++;
		break;

	}
}
vector<EffectData>* Lib_EffectManager::Geteffects(const int handle)
{
	_ASSERT_EXPR(SpriteEffects.at(handle)->handle > -1, "�������Ă��Ȃ��G�t�F�N�g���g�p���܂���");
	return SpriteEffects.at(handle)->Geteffects();
}