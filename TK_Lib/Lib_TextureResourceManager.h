#pragma once
#include "Lib_Texture.h"
#include "Lib_ResoureManager.h"
class TextureResourceManager:public ResourceManager
{
public:
	TextureResourceManager() {};
	~TextureResourceManager() {};

	//����������
	void Init(const UINT MaxLoadNum);
	//���[�h(1:device,2:�e�N�X�`���̃p�X,3:�e�N�X�`���̃n���h��)
	bool Load(ID3D11Device* device, const string name, int& handle,const string RegisterKey = "");
	//�폜
	void Erase(ID3D11Device* device, const  int handle);
	//�e�N�X�`���𐶐�����
	void Create(ID3D11Device* device, int& handle, u_int width, u_int height, DXGI_FORMAT format);
	//�e�N�X�`���̎擾
	TextureResource* GetTextureResource(const int index);
	//�S����
	void Clear();
private:
	//�e�N�X�`���̔z��
	vector<std::shared_ptr<TextureResource>> textures;

private:

	//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
	//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
	 bool DuplicateFind(const string name, int& handle);

	//textures�̋�ł���v�f�ɓo�^���Ă���
	 bool Register(ID3D11Device* device, const string name, int& handle);

};
