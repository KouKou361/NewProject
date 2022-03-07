#pragma once
#include <d3d11.h>
#include <DirectXMath.h>



//----------------------------------------------
//
//	���_�f�[�^�\���̒�`
//
//----------------------------------------------
using namespace DirectX;

struct VERTEX2D
{
	XMFLOAT3 pos;	//�ʒu
	XMFLOAT2 tex;	//UV���W
	XMFLOAT4 color;	//���_�F
};
struct VERTEXParticle
{
	XMFLOAT3 pos;	//�ʒu
	XMFLOAT2 size;	//�傫��
	XMFLOAT4 tex;//�^�C�v,��,��,��
	XMFLOAT4 color;	//�F
};

struct VERTEXDEBUG
{
	XMFLOAT3 pos;	//�ʒu
	XMFLOAT3 normal;//�@��
	XMFLOAT2 tex;	//UV���W
	XMFLOAT4 color;	//���_�F
};

//	���_�V�F�[�_�[��CSO�t�@�C������쐬����
HRESULT	CreateVertexShaderFromCSO( ID3D11Device* _pDevice, const char* _pFileName, ID3D11VertexShader** _ppVertexShader, ID3D11InputLayout** _ppInputLayout, D3D11_INPUT_ELEMENT_DESC* _pInputElementDesc, UINT _NumElements );

//	�s�N�Z���V�F�[�_�[��CSO�t�@�C������쐬����
HRESULT	CreatePixelShaderFromCSO( ID3D11Device* _pDevice, const char* _pFileName, ID3D11PixelShader** _ppPixelShader );

