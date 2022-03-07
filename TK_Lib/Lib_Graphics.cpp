#include "Lib_Graphics.h"

#include <memory>
#include <wrl.h>
#include "Delete.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics(HWND hwnd, UINT ScreenWight, UINT ScreenHeight)
{

	instance = this;
	screenWight= ScreenWight;
	screenHeight= ScreenHeight;
	HRESULT hr = S_OK;
	//デバイス・デバイスコンテキスト・スワップチェーンの作成
	{
		UINT	CreateDeviceFlags = 0;
#if	defined( DEBUG ) || defined( _DEBUG )
		//	DirectXのデバッグ用の設定フラグ(これ重要!)
		//	これを立てる事で
		//	・DirectXに関するエラーや警告を教えてくれます。
		//	・アプリケーションの終了時に
		//	　DirectXに関するリソースの解放漏れを教えてくれます。
		//	
		//	リソースの解放漏れやメモリの解放漏れなどが大量に発生した場合、
		//	他のアプリケーションでメモリの確保ができなくなり、アプリケーションが強制終了する可能性がある。
		//	最悪OSで必要なメモリが確保できなくなり、Windowsが停止する可能性がある。
		CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif	//	defined( DEBUG ) || defined( _DEBUG )

		//	DirectXの機能レベルの設定用配列
		//	もっとも良い設定を選んでくれるように並べる
		D3D_FEATURE_LEVEL	FeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};



		//	スワップチェインの作成用構造体に情報を設定していく
		DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
		::ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		SwapChainDesc.BufferDesc.Width = ScreenWight;//pos.x
		SwapChainDesc.BufferDesc.Height = ScreenHeight;//pos.y
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;//
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;//
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//	1ピクセルあたりの各色(RGBA)を8bit(0～255)のテクスチャ(バックバッファ)を作成する。//色？
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 1;			//	バックバッファの数
		SwapChainDesc.OutputWindow = hwnd;		//	DirectXで描いた画を表示するウインドウ
		SwapChainDesc.Windowed = TRUE;			//	ウインドウモードか、フルスクリーンにするか。
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDesc.Flags = 0; //DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH


		D3D_DRIVER_TYPE d3d_driver_type[]
		{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
		};

		for (auto type : d3d_driver_type)
		{
			//	選択された機能レベルの受け取り用変数
			//	どの機能
			D3D_FEATURE_LEVEL	SelectedFeatureLevel;
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,                           //	どのビデオアダプタを使用するか？既定ならばnullptrで、IDXGIAdapterのアドレスを渡す。使いたいグラフィックボードを指定したい時に利用します。例えば、NVIDIAのCUDAを利用したい時等
				type,		                       //	ドライバのタイプを渡す。D3D_DRIVER_TYPE_HARDWARE 以外は基本的にソフトウェア実装で、特別なことをする場合に用いる。
				nullptr,						   //	上記をD3D_DRIVER_TYPE_SOFTWAREに設定した際に、その処理を行うDLLのハンドルを渡す。それ以外を指定している際には必ずnullptrを渡す。
				CreateDeviceFlags,				   //	何らかのフラグを指定する。詳しくはD3D11_CREATE_DEVICE列挙型で検索。エラーのメッセージを出すかどうか、ログに残る
				FeatureLevels,					   //	D3D_FEATURE_LEVEL列挙型の配列を与える。nullptrにすることでも上記featureと同等の内容の配列が使用される。
				ARRAYSIZE(FeatureLevels),		   //	feature_levels配列の要素数を渡す。
				D3D11_SDK_VERSION,				   //	SDKのバージョン。必ずこの値。
				&SwapChainDesc,					   //	ここで設定した構造体に設定されているパラメータでSwapChainが作成される。
				m_swapchain.GetAddressOf(),					   //	作成が成功した場合に、SwapChainのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でSwapChainを操作する。
				m_device.GetAddressOf(),						   //	作成が成功した場合に、Deviceのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でDeviceを操作する。
				&SelectedFeatureLevel,			   //	作成に成功したD3D_FEATURE_LEVELを格納するためのD3D_FEATURE_LEVEL列挙型変数のアドレスを設定する。
				m_context.GetAddressOf());                       //	作成が成功した場合に、Contextのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でContextを操作する。
			//もし使えるなら
			if (hr == S_OK)break;
		}

		_ASSERT_EXPR(SUCCEEDED(hr), L"CreateDeviceAndSwapChain()でエラーが起こったなり");
		if (FAILED(hr))
			return;	//	作成できなかったので初期化失敗
	}
	//	RenderTargetViewの生成
	D3D11_TEXTURE2D_DESC	BackBufferDesc;
	::ZeroMemory(&BackBufferDesc, sizeof(ID3D11Texture2D));
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_swapchain->GetBuffer(0
			, __uuidof(ID3D11Texture2D)
			, reinterpret_cast<void**>(&pBackBuffer));
		_ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer()でエラーが起こったなり");
		if (FAILED(hr))
			return;

		hr = m_device->CreateRenderTargetView(pBackBuffer,
			nullptr,
			m_renderTargetview.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"CreateRenderTargetView()でエラーが起こったなり");
		if (FAILED(hr))
		{
			D3D_SAFE_RELEASE(pBackBuffer);
			return;
		}
	

		//	バックバッファの情報だけは後で使用するので取得しておく
		pBackBuffer->GetDesc(&BackBufferDesc);
		D3D_SAFE_RELEASE(pBackBuffer);
	}
	//===================
	//初期設定
	//===================
	//もう覚えるか　コピペしたらいい

	//	DepthStencilViewの生成
	D3D11_TEXTURE2D_DESC DepthStencilBufferDesc;
	{
		//	深度ステンシル情報を書き込むためのテクスチャを作成する。
		ID3D11Texture2D* pDepthStencilBuffer = nullptr;
		DepthStencilBufferDesc.Width = ScreenWight;
		DepthStencilBufferDesc.Height = ScreenHeight;
		DepthStencilBufferDesc.MipLevels = 1;
		DepthStencilBufferDesc.ArraySize = 1;
		DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	//	1ピクセルあたり、深度情報を24Bit / ステンシル情報を8bitのテクスチャを作成する。//奥行２４のせやつを生成
		DepthStencilBufferDesc.SampleDesc.Count = 1;
		DepthStencilBufferDesc.SampleDesc.Quality = 0;
		DepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//	深度ステンシル用のテクスチャを作成する。
		DepthStencilBufferDesc.CPUAccessFlags = 0;
		DepthStencilBufferDesc.MiscFlags = 0;
		hr = m_device->CreateTexture2D(&DepthStencilBufferDesc, NULL, &pDepthStencilBuffer);
		_ASSERT_EXPR(SUCCEEDED(hr), "深度ステンシル情報でエラーが起こったなり");
		if (FAILED(hr))return;

		//	深度ステンシルテクスチャへの書き込みに窓口になる深度ステンシルビューを作成する。
		D3D11_DEPTH_STENCIL_VIEW_DESC	DepthStencilViewDesc;
		ZeroMemory(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc));
		DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
		DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DepthStencilViewDesc.Flags = 0;
		DepthStencilViewDesc.Texture2D.MipSlice = 0;
		hr = m_device->CreateDepthStencilView(pDepthStencilBuffer, &DepthStencilViewDesc, m_depthStencilView.GetAddressOf());
		D3D_SAFE_RELEASE(pDepthStencilBuffer);
		_ASSERT_EXPR(SUCCEEDED(hr), L"深度ステンシルビューでエラーが起こったなり");
		if (FAILED(hr))return;
	}

	//Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D;
	//
	//hr = S_OK;
	////	テクスチャ作成
	//	//テクスチャ
	//D3D11_TEXTURE2D_DESC m_texture_desc;
	//ZeroMemory(&m_texture_desc, sizeof(m_texture_desc));
	//m_texture_desc.Width = screenWight;
	//m_texture_desc.Height = screenHeight;
	//m_texture_desc.MipLevels = 1;
	//m_texture_desc.ArraySize = 1;
	//m_texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//ここでR32G32B32などの設定(R32G32だけなら赤と緑だけ)
	//m_texture_desc.SampleDesc.Count = 1;
	//m_texture_desc.Usage = D3D11_USAGE_DEFAULT;
	//m_texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//m_texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	//
	//hr = m_device->CreateTexture2D(&m_texture_desc, NULL, Texture2D.GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), L"テクスチャエラー");
	//
	////	シェーダーリソースビュー作成
	//D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	//ZeroMemory(&srvd, sizeof(srvd));
	//srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//srvd.Texture2D.MostDetailedMip = 0;
	//srvd.Texture2D.MipLevels = 1;
	//hr = m_device->CreateShaderResourceView(Texture2D.Get(), &srvd, m_shaderResourceView.GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), L"シェーダーリソースビューエラー");
	//
	//ID3D11Texture2D* back_buffer;
	//hr=m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
	//_ASSERT_EXPR(SUCCEEDED(hr), L"back_bufferビュー");
	//
	//// BufferからRenderTargetViewの作成
	//
	//hr = m_device->CreateRenderTargetView(Texture2D, NULL, m_renderTargetview.GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), L"RenderTargetView");

	//if (FAILED(m_Device->CreateRenderTargetView(back_buffer, NULL, &m_RenderTargetView)))
	//{
	//	return false;
	//}

		//	バックバッファの情報だけは後で使用するので取得しておく
	//back_buffer->GetDesc(&BackBufferDesc);
	//D3D_SAFE_RELEASE(back_buffer);
}
Graphics::~Graphics()
{

}