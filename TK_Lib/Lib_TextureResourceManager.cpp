#include "Lib_TextureResourceManager.h"
//����������
void TextureResourceManager::Init(const UINT MaxLoadNum)
{
	textures.resize(MaxLoadNum);
	for (int i = 0; i < textures.size(); i++)
	{
		textures.at(i) = make_shared<TextureResource>();
	}
}
//���[�h(1:device,2:�e�N�X�`���̃p�X,3:�e�N�X�`���̃n���h��)
bool TextureResourceManager::Load(ID3D11Device* device, const string name, int& handle, const string RegisterKey )
{
	//���ɓǂݍ���ł���e�N�X�`�������邩�ǂ����𒲂ׂ�
	if (DuplicateFind(name, handle) == true)
	{
		//textures�̋�ł���v�f�ɓo�^���Ă���
		Register(device, name, handle);
	}

	return true;
	
}
//�폜
void TextureResourceManager::Erase(ID3D11Device* device, const  int handle)
{

	//�e�N�X�`���̎擾
	TextureResource* textureData = GetTextureResource(handle);
	//�l���폜
	textureData->handle = -1;
	textures.at(handle).reset();
	textures.at(handle) = make_shared<TextureResource>();

	//�e�N�X�`���̓ǂݍ��񂾐���-1����
	LoadNum--;
}
void TextureResourceManager::Clear()
{
	textures.clear();
}
//�e�N�X�`���𐶐�����
void TextureResourceManager::Create(ID3D11Device* device, int& handle, u_int width, u_int height, DXGI_FORMAT format)
{

}
//�e�N�X�`���̎擾
TextureResource* TextureResourceManager::GetTextureResource(const int handle)
{
	//�ݒ肳��Ă��Ȃ��܂��͍폜���ꂽ�e�N�X�`�����g�����Ƃ��Ă��邩�ǂ���
	assert(textures.at(handle)->handle != -1);
	return textures.at(handle).get();
}

//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
bool TextureResourceManager::DuplicateFind(const string name, int& handle)
{
	for (int i = 0; i < textures.size(); i++)
	{


		//�e�N�X�`���̎擾
		TextureResource* textureData = textures.at(i).get();

		if (-1 >= textureData->handle)continue;

		//�e�N�X�`�����d�����Ă��邩�ǂ���������
		if (name == textureData->filename)
		{
			//�d�����Ă���
			handle = textureData->handle;
			return false;
		}
	}
	return true;
}

//textures�̋�ł���v�f�ɓo�^���Ă���
bool TextureResourceManager::Register(ID3D11Device* device, const string name, int& handle)
{
	//Texture�̓ǂݍ��߂鐔���ő�ɒB���Ă��邩�ǂ���
	assert(LoadNum < textures.size());

	for (int i = 0; i < textures.size(); i++)
	{
		//�e�N�X�`���̎擾
		TextureResource* textureData = textures.at(i).get();
		if (-1 < textureData->handle)continue;

		//��ɓo�^����
		textureData->Load(device, name);
		textureData->handle = i;
		handle = i;
		LoadNum++;
		break;

	}
	return true;
}