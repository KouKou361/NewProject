#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <assert.h>
using namespace Microsoft::WRL;
using namespace DirectX;


//このShaderはピクセルシェーダー,頂点シェーダー,入力レイアウト
//などの描画するときにの素材だけを管理している


class ShaderResource
{
public:
	enum class TYPELayout
	{
		TYPE_Layout2DSprite,
		TYPE_LayoutDebugSprite,
		TYPE_layoutPointSprite,
		TYPE_LayoutModel,
		TYPE_LayoutEnd,
	};
public:
	ShaderResource() {};
	~ShaderResource() {};

protected:
	//MEMO:ジオメトリシェーダーなども追加していきたい
	
	//ピクセルシェーダー
	ComPtr<ID3D11PixelShader> m_PixelShader = nullptr;
	//頂点シェーダー
	ComPtr<ID3D11VertexShader> m_VertexShader = nullptr;
	//ジオメトリシェーダー
	ComPtr<ID3D11GeometryShader> m_GeometryShader = nullptr;
	//入力レイアウト
	ComPtr<ID3D11InputLayout> m_inputLayout = nullptr;
public:
	//作成
	virtual void Create(ID3D11Device* device, const char* VSname, const char* PSname, TYPELayout type= TYPELayout::TYPE_Layout2DSprite);
	virtual void Create(ID3D11Device* device, const char* VSname, const char* GSname, const char* PSname, TYPELayout type = TYPELayout::TYPE_Layout2DSprite);

	void Activate(ID3D11DeviceContext* device);
	void Inactivate(ID3D11DeviceContext* device);
};
