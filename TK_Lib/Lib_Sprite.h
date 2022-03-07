#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <string>
#include <memory>
#include "vector.h"
#include "Lib_Texture.h"
using namespace Microsoft::WRL;
using namespace std;
using namespace DirectX;

//================
//スプライト
//================

class Sprite
{
private:
	//頂点バッファ
	ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
	//深度
	ComPtr<ID3D11DepthStencilState> m_deptStencilState = nullptr;

	//struct ConstantDeferred
	//{
	//	XMFLOAT4 LightColor;
	//	XMFLOAT4 LightDir;
	//	XMFLOAT4 AmbientColor;
	//	XMFLOAT4 EyePos;
	//};
public:
	Sprite(ID3D11Device* device);
	~Sprite() {};

	//描画
	void Render(ID3D11DeviceContext* device, TextureResource* tex, VECTOR2 Pos, VECTOR2 Size, VECTOR4 Cut, float angle = 0, VECTOR4 Color = VECTOR4{ 1,1,1,1 });
	void Font(ID3D11DeviceContext* _pDeviceContext,std::string text, TextureResource* texture,VECTOR2 Pos,VECTOR2 Size,VECTOR4 color,float Space);
};