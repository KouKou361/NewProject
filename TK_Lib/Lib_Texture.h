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

//テクスチャの情報だけのデータ
class TextureResource
{

public:
	TextureResource() {};
	~TextureResource() {};
public:
	//テクスチャのロード
	void Load(ID3D11Device* device, const string name);
	//テクスチャの作成
	void Create(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format);
	void CreateDepth(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format = DXGI_FORMAT_R24G8_TYPELESS);
private:
	//読み込み機構（シェーダーリソースビュー）
	ComPtr<ID3D11ShaderResourceView> m_shaderResourceView = nullptr;
	//色を書き込むため(レンダーターゲット)
	ComPtr<ID3D11RenderTargetView> m_renderTargetview = nullptr;
	//深度情報
	ComPtr<ID3D11DepthStencilView> m_depthStencilView = nullptr;

	//テクスチャの大きさ
	VECTOR2 textureScreen = VECTOR2{ 0,0 };
public:
	//名前の保存
	string filename = "";
	//ハンドル
	int handle = -1;

	//テクスチャの大きさ（横）
	UINT GetWidth() { return static_cast<UINT>(textureScreen.x); }
	//テクスチャの大きさ（縦）
	UINT GetHeight() { return static_cast<UINT>(textureScreen.y); }
	void Set(ID3D11DeviceContext* device,UINT slot);
	void Empty(ID3D11DeviceContext* device, UINT slot);
	const string GetFilename() { return filename; }
	
	ID3D11ShaderResourceView** GetShaderResourceView() { return m_shaderResourceView.GetAddressOf(); }
	ID3D11RenderTargetView* GetRenderTargetView() { return m_renderTargetview.Get(); }
	ID3D11DepthStencilView* GetDepthStencilView() { return m_depthStencilView.Get(); }
};
