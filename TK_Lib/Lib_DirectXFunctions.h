#pragma once
#include <d3d11.h>
#include <DirectXMath.h>



//----------------------------------------------
//
//	頂点データ構造体定義
//
//----------------------------------------------
using namespace DirectX;

struct VERTEX2D
{
	XMFLOAT3 pos;	//位置
	XMFLOAT2 tex;	//UV座標
	XMFLOAT4 color;	//頂点色
};
struct VERTEXParticle
{
	XMFLOAT3 pos;	//位置
	XMFLOAT2 size;	//大きさ
	XMFLOAT4 tex;//タイプ,空,空,空
	XMFLOAT4 color;	//色
};

struct VERTEXDEBUG
{
	XMFLOAT3 pos;	//位置
	XMFLOAT3 normal;//法線
	XMFLOAT2 tex;	//UV座標
	XMFLOAT4 color;	//頂点色
};

//	頂点シェーダーをCSOファイルから作成する
HRESULT	CreateVertexShaderFromCSO( ID3D11Device* _pDevice, const char* _pFileName, ID3D11VertexShader** _ppVertexShader, ID3D11InputLayout** _ppInputLayout, D3D11_INPUT_ELEMENT_DESC* _pInputElementDesc, UINT _NumElements );

//	ピクセルシェーダーをCSOファイルから作成する
HRESULT	CreatePixelShaderFromCSO( ID3D11Device* _pDevice, const char* _pFileName, ID3D11PixelShader** _ppPixelShader );

