#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <memory>
#include <assert.h>
#include "vector.h"
#include <string>
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;

//�e�N�X�`���̏�񂾂��̃f�[�^
class TextureResource
{

public:
	TextureResource() {};
	~TextureResource() {};
public:
	//�e�N�X�`���̃��[�h
	void Load(ID3D11Device* device, const string name);
	//�e�N�X�`���̍쐬
	void Create(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format);
	void CreateDepth(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format = DXGI_FORMAT_R24G8_TYPELESS);
private:
	//�ǂݍ��݋@�\�i�V�F�[�_�[���\�[�X�r���[�j
	ComPtr<ID3D11ShaderResourceView> m_shaderResourceView = nullptr;
	//�F���������ނ���(�����_�[�^�[�Q�b�g)
	ComPtr<ID3D11RenderTargetView> m_renderTargetview = nullptr;
	//�[�x���
	ComPtr<ID3D11DepthStencilView> m_depthStencilView = nullptr;

	//�e�N�X�`���̑傫��
	VECTOR2 textureScreen = VECTOR2{ 0,0 };
public:
	//���O�̕ۑ�
	string filename = "";
	//�n���h��
	int handle = -1;

	//�e�N�X�`���̑傫���i���j
	UINT GetWidth() { return static_cast<UINT>(textureScreen.x); }
	//�e�N�X�`���̑傫���i�c�j
	UINT GetHeight() { return static_cast<UINT>(textureScreen.y); }
	void Set(ID3D11DeviceContext* device,UINT slot);
	void Empty(ID3D11DeviceContext* device, UINT slot);
	const string GetFilename() { return filename; }
	
	ID3D11ShaderResourceView** GetShaderResourceView() { return m_shaderResourceView.GetAddressOf(); }
	ID3D11RenderTargetView* GetRenderTargetView() { return m_renderTargetview.Get(); }
	ID3D11DepthStencilView* GetDepthStencilView() { return m_depthStencilView.Get(); }
};
