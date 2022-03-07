#include "Lib_Texture.h"
#include "WICTextureLoader.h"

void TextureResource::Load(ID3D11Device* device,  const string name)
{
	//名前の保存
	filename = name;
	//string からchar に変換する
	size_t len;
	wchar_t wcs[256];
	mbstowcs_s(&len, wcs, name.length() + 1, name.c_str(), _TRUNCATE);


	HRESULT hr = S_OK;
	//==============================================
	//シェーダーリソースビューの作成
	//==============================================
	ID3D11Resource* resource;


	hr = CreateWICTextureFromFile(device, wcs, &resource, m_shaderResourceView.GetAddressOf());
	if (FAILED(hr)) {
		_ASSERT_EXPR(SUCCEEDED(hr), L"シェーダーリソースビューのエラー");
		return;
	}
	//==============================================
	//Texture2Dテクスチャの情報を書き込む
	//==============================================
	ID3D11Texture2D* pTexture2D = nullptr;
	hr = resource->QueryInterface<ID3D11Texture2D>(&pTexture2D);
	if (FAILED(hr)) {
		resource->Release();//解放宣言
		_ASSERT_EXPR(SUCCEEDED(hr), L"TEXTURE2Dエラー");
	}
	//テクスチャ
	D3D11_TEXTURE2D_DESC m_texture_desc;
	ZeroMemory(&m_texture_desc, sizeof(D3D11_TEXTURE2D_DESC));

	pTexture2D->GetDesc(&m_texture_desc);
	textureScreen.x = static_cast<float>(m_texture_desc.Width );
	textureScreen.y = static_cast<float>(m_texture_desc.Height);
	resource->Release();//解放宣言
	pTexture2D->Release();
}
void TextureResource::Create(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format)
{
	ComPtr<ID3D11Texture2D> Texture2D;
	HRESULT hr = S_OK;
	//	テクスチャ作成
		//テクスチャ
	D3D11_TEXTURE2D_DESC m_texture_desc;
	ZeroMemory(&m_texture_desc, sizeof(m_texture_desc));
	m_texture_desc.Width = width;
	m_texture_desc.Height = height;
	m_texture_desc.MipLevels = 1;
	m_texture_desc.ArraySize = 1;
	m_texture_desc.Format = format;//ここでR32G32B32などの設定(R32G32だけなら赤と緑だけ)
	m_texture_desc.SampleDesc.Count = 1;
	m_texture_desc.Usage = D3D11_USAGE_DEFAULT;
	m_texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	hr = device->CreateTexture2D(&m_texture_desc, NULL, Texture2D.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"テクスチャエラー");

	//	レンダーターゲットビュー作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	ZeroMemory(&rtvd, sizeof(rtvd));
	rtvd.Format = format;
	rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvd.Texture2D.MipSlice = 0;
	hr = device->CreateRenderTargetView(Texture2D.Get(), &rtvd, m_renderTargetview.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"レンダーターゲットビューエラー");

	//	シェーダーリソースビュー作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;
	hr = device->CreateShaderResourceView(Texture2D.Get(), &srvd, m_shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"シェーダーリソースビューエラー");

	textureScreen.x = static_cast<float>(m_texture_desc.Width );
	textureScreen.y = static_cast<float>(m_texture_desc.Height);
}
void TextureResource::CreateDepth(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format)
{
	ComPtr<ID3D11Texture2D> Texture2D;
	HRESULT hr = S_OK;
	//	テクスチャ作成
	D3D11_TEXTURE2D_DESC texture2d_desc;
	ZeroMemory(&texture2d_desc, sizeof(texture2d_desc));
	texture2d_desc.Width = width;
	texture2d_desc.Height = height;
	texture2d_desc.MipLevels = 1;
	texture2d_desc.ArraySize = 1;
	texture2d_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texture2d_desc.SampleDesc.Count = 1;
	texture2d_desc.SampleDesc.Quality = 0;
	texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture2d_desc.CPUAccessFlags = 0;
	texture2d_desc.MiscFlags = 0;
	texture2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	hr = device->CreateTexture2D(&texture2d_desc, NULL, Texture2D.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"テクスチャの作成失敗");

	// 深度ステンシルビュー設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.Format = texture2d_desc.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;
	dsvd.Texture2D.MipSlice = 0;
	
	hr = device->CreateDepthStencilView(Texture2D.Get(), &dsvd, m_depthStencilView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"深度ステンシルビューのエラー");



	

	textureScreen.x = static_cast<float>(texture2d_desc.Width );
	textureScreen.y = static_cast<float>(texture2d_desc.Height);

}
void TextureResource::Set(ID3D11DeviceContext* device, UINT slot)
{
	device->PSSetShaderResources(slot, 1, GetShaderResourceView());
}
void TextureResource::Empty(ID3D11DeviceContext* device, UINT slot)
{
	ID3D11ShaderResourceView* rtv = {NULL};
	device->PSSetShaderResources(slot, 1, &rtv);
}