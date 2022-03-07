#include "Lib_LightManager.h"
 Lib_PointLightManager* Lib_PointLightManager::instance;

Lib_PointLightManager::Lib_PointLightManager(ID3D11Device* device)
{
	instance = this;
	HRESULT hr = S_OK;

	// �萔�o�b�t�@
	{
		// �V�[���p�o�b�t�@
		D3D11_BUFFER_DESC desc;
		//::ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.ByteWidth = sizeof(Lib_pointLight)*32;
		desc.StructureByteStride = 0;

		hr = device->CreateBuffer(&desc, 0, m_Constantbuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�R���X�^���g�o�b�t�@�̃G���[");
	}
}
//������(�ۑ����鐔)
void Lib_PointLightManager::Init(int MaxNum)
{
	pointLight.resize(MaxNum);
	//�O�̂���
	Clear();
}
void Lib_PointLightManager::Active(ID3D11DeviceContext* context)
{
	Lib_PointLight light_cb[32];
	memcpy(light_cb,pointLight.data(), sizeof(Lib_PointLight) * 32);
	context->UpdateSubresource(m_Constantbuffer.Get(), 0, NULL, &light_cb, 0, 0);
	context->VSSetConstantBuffers(4, 1, m_Constantbuffer.GetAddressOf());
	context->PSSetConstantBuffers(4, 1, m_Constantbuffer.GetAddressOf());
}
//�|�C���g���C�g�̍쐬
int  Lib_PointLightManager::Create(VECTOR3 pos, VECTOR4 color, float range)
{
	
	for (int i = 0; i < pointLight.size(); i++)
	{
		Lib_PointLight* pointlight = GetPointlight(i);
		if (pointlight->GetIndex() >= 0)continue;//���Ƀf�[�^�������Ă�����͔̂�΂�

		_ASSERT_EXPR((pointlight != nullptr), L"���Ƀf�[�^�������Ă���|�C���g���C�g�ɏ㏑�����悤�Ƃ��܂���");

		VECTOR4 Pos = VECTOR4{ pos.x,pos.y,pos.z,0.0f };
		pointlight->SetIndex(i);
		pointlight->Set(Pos, color, range);

		return pointlight->GetIndex();
	}

	_ASSERT_EXPR((true), L"���ꐶ���o���܂���");
	return 0;
}
//�|�C���g���C�g�̐ݒ�
void Lib_PointLightManager::Set(int handle, VECTOR3 pos, VECTOR4 color, float range)
{
	Lib_PointLight* pointlight = GetPointlight(handle);
	VECTOR4 Pos = VECTOR4{ pos.x,pos.y,pos.z,0.0f };
	pointlight->Set(Pos, color, range);
}
//�n���h���̃|�C���g���C�g�̍폜
void Lib_PointLightManager::Delete(int& handle)
{
	Lib_PointLight* pointlight = GetPointlight(handle);
	_ASSERT_EXPR(!(pointlight == nullptr), L"��̃f�[�^���폜���悤�Ƃ��܂���");
	pointlight->Clear();
}
//�S����
void Lib_PointLightManager::Clear()
{
	for (int i = 0; i < pointLight.size(); i++)
	{
		Lib_PointLight* PoinitLight;
		PoinitLight = &pointLight.at(i);
		PoinitLight->Clear();
	}
}


Lib_PointLight* Lib_PointLightManager::GetPointlight(int handle)
{
	Lib_PointLight* PoinitLight;
	PoinitLight = &pointLight.at(handle);
	//�����n���h����-1�ȉ��Ȃ���Ԃ�
	//if (PoinitLight->GetIndex() <= -1)return nullptr;
	return PoinitLight;
}