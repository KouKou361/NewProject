#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl.h>
//グラフィックス関係をここにまとめた感じ
class Graphics
{
public:
	Graphics(HWND hWnd,UINT ScreenWight, UINT ScreenHeight);
	~Graphics();
private:

	static Graphics* instance;

	UINT screenWight;
	UINT screenHeight;

	//デバイス　リソースを作成するため
	Microsoft::WRL::ComPtr<ID3D11Device> m_device = nullptr;
	//コンテキスト 描画する時に使う
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context = nullptr;
	//ウィンドウズに絵をいれるため
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain = nullptr;
	//レンダーターゲット 色を書き込むため
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetview = nullptr;

	//テクスチャ２D　色情報を記録する
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2d = nullptr;
	//デプスステンシル　奥行情報をかきこむため
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_depthStencilView = nullptr;
	//シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView = nullptr;
public:
	ID3D11Device* Get_device() { 
		return m_device.Get();
	};
	ID3D11DeviceContext* Get_context() { return m_context.Get(); };
	IDXGISwapChain* Get_swappchain() { return m_swapchain.Get(); };
	ID3D11RenderTargetView* Get_targetview() { return m_renderTargetview.Get(); };
	ID3D11Texture2D* Get_texture2d() { return m_texture2d.Get(); };
	ID3D11DepthStencilView* Get_DepthStencilView() { return m_depthStencilView.Get(); };
	ID3D11ShaderResourceView* Get_ShaderResourceView() { return m_shaderResourceView.Get(); };

	//スクリーン座標のゲッター
	UINT GetScreenWight() {
		return screenWight;
	};
	UINT GetScreenHeight() {
		return screenHeight;
	};

	//インスタンス取得
	static Graphics& Instance()
	{
		return *instance;
	}

};