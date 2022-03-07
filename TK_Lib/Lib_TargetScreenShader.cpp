#include "Lib_TargetScreenShader.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
#include "Lib_DepthStencil.h"
#include "Lib_DirectXFunctions.h"
#include "Lib.h"

Lib_TargetScreenShader::Lib_TargetScreenShader(ID3D11Device* device)
{

	HRESULT hr = S_OK;

	VERTEX2D vertices[] = {
			{ XMFLOAT3(-0.5, +0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1, 1, 1, 1)},
			{ XMFLOAT3(+0.5, +0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1, 0, 0, 1)},
			{ XMFLOAT3(-0.5, -0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0, 1, 0, 1)},
			{ XMFLOAT3(+0.5, -0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0, 0, 1, 1)},
	};
	//頂点の数
	int VerticesNum = ARRAYSIZE(vertices);
	//=========================
	//頂点バッファの作成
	//=========================
	{
		D3D11_BUFFER_DESC vertex_buffer_desc = {};
		::ZeroMemory(&vertex_buffer_desc, sizeof(D3D11_BUFFER_DESC));
		vertex_buffer_desc.ByteWidth = sizeof(VERTEX2D) * VerticesNum;
		vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;//読み込み、書き込む設定
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sub_data = {};
		::ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = vertices;
		sub_data.SysMemPitch = 0;
		sub_data.SysMemSlicePitch = 0;
		//頂点バッファの作成
		hr = device->CreateBuffer(&vertex_buffer_desc, &sub_data, m_vertexBuffer.GetAddressOf());
	}


	//シェーダー
	m_shader = make_unique<ShaderResource>();
	m_shader->Create(device, "./Shader/TargetScreen_vs.cso", "./Shader/TargetScreen_ps.cso", ShaderResource::TYPELayout::TYPE_Layout2DSprite);


	//ScreenTextureの生成
	VECTOR2 WindowSize = TK_Lib::Window::GetWindowSize();
	ScreenTexture = make_unique<TextureResource>();
	ScreenTexture->Create(device, static_cast<u_int>(WindowSize.x), static_cast<u_int>(WindowSize.y), DXGI_FORMAT_R8G8B8A8_UNORM);

	// 定数バッファ
	{
		// シーン用バッファ
		D3D11_BUFFER_DESC desc;
		::ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.ByteWidth = sizeof(SceneConstantBuffer);
		desc.StructureByteStride = 0;
		
		hr = device->CreateBuffer(&desc, 0, m_sceneConstantBuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"コンスタントバッファのエラー");
		
		//// メッシュ用バッファ
		//desc.ByteWidth = sizeof(CbMesh);
		//hr = device->CreateBuffer(&desc, 0, m_meshConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"Mesh用のコンスタントバッファのエラー");
		//
		//// サブセット用バッファ
		//desc.ByteWidth = sizeof(CbSubset);
		//hr = device->CreateBuffer(&desc, 0, m_subsetConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"サブセット用のコンスタントバッファのエラー");
		
	
		////コンスタントバッファ
		//desc.ByteWidth = sizeof(Constant);
		//hr = device->CreateBuffer(&desc, 0, m_ConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"コンスタントバッファのエラー");

	}


	// 深度ステンシルステート
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		//深度テスト
		desc.DepthEnable = FALSE;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;//書き込みを可能にさせる
		//ステンシルテストは不要
		desc.StencilEnable = FALSE;

		hr = device->CreateDepthStencilState(&desc, m_depthStencilState.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"深度ステンシルステートのエラー");
	}

}

void Lib_TargetScreenShader::SetConstant(ID3D11DeviceContext* device, VECTOR4 color, float LineDark, float LineWeight)
{
	SceneConstantBuffer cb;
	cb.Color = color;
	cb.dummy = 0;
	cb.dummy2 = 0;
	cb.LineWeight = LineWeight;
	cb.LineDark = LineDark;

	device->VSSetConstantBuffers(0, 1, m_sceneConstantBuffer.GetAddressOf());
	device->PSSetConstantBuffers(0, 1, m_sceneConstantBuffer.GetAddressOf());
	device->UpdateSubresource(m_sceneConstantBuffer.Get(), 0, 0, &cb, 0, 0);
};
//描画
void Lib_TargetScreenShader::Render(ID3D11DeviceContext* device)
{
	ScreenRender(device);
	
	//レンダーターゲット
	ID3D11RenderTargetView* rtv = TK_Lib::Lib_Graphics::Get_targetview();
	ID3D11DepthStencilView* dsv = TK_Lib::Lib_Graphics::Get_DepthStencilView();
	//レンダーターゲットを送り込む
	device->OMSetRenderTargets(1, &rtv, dsv);
	
	m_shader->Activate(device);
	

	D3D11_VIEWPORT	Viewport;//Windowsの設定の実体
	UINT			ViewportCount = 1;//Windowの数
	
	//tex->Set(device, 0);
	
	
	device->RSGetViewports(&ViewportCount, &Viewport);
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;
	
	HRESULT hr = S_OK;
	
	VECTOR2 pos = { 0,0 };
	VECTOR2 size = { ScreenWidth,ScreenHeight };
	
	VECTOR2 texture_pos = { 0,0 };
	VECTOR2 texture_size = { ScreenWidth,ScreenHeight };
	VECTOR4 color = { 1,1,1,1 };
	float angle = 0;
	//	設定情報から4頂点を作成
	VERTEX2D VertexList[4] =
	{
	{ DirectX::XMFLOAT3(pos.x,         pos.y         ,0),XMFLOAT2(texture_pos.x,                   texture_pos.y)                 , color},
	{ DirectX::XMFLOAT3(pos.x + size.x,pos.y         ,0),XMFLOAT2(texture_pos.x + texture_size.x,  texture_pos.y)                 , color},
	{ DirectX::XMFLOAT3(pos.x,         pos.y + size.y,0),XMFLOAT2(texture_pos.x,                   texture_pos.y + texture_size.y), color},
	{ DirectX::XMFLOAT3(pos.x + size.x, pos.y + size.y, 0), XMFLOAT2(texture_pos.x + texture_size.x, texture_pos.y + texture_size.y), color},
	};
	constexpr	int	VertexLength = sizeof(VertexList) / sizeof(VertexList[0]);
	//
	//	回転
	{
		//	回転中心まで頂点を移動させる
		float	CenterWidth = pos.x + size.x * 0.5f;
		float	CenterHeight = pos.y + size.y * 0.5f;
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			VertexList[ii].pos.x -= CenterWidth;
			VertexList[ii].pos.y -= CenterHeight;
		}
	
		//	指定の角度分回転させる
		float	RadianAngle = angle;
		float	Cos = cosf(RadianAngle);
		float	Sin = sinf(RadianAngle);
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			float rx = VertexList[ii].pos.x;
			float ry = VertexList[ii].pos.y;
	
			VertexList[ii].pos.x = Cos * rx - Sin * ry;
			VertexList[ii].pos.y = Sin * rx + Cos * ry;
		}
	
		//	回転中心まで頂点を移動させる
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			VertexList[ii].pos.x += CenterWidth;
			VertexList[ii].pos.y += CenterHeight;
		}
	}
	
	//	正規化デバイス座標系に変換する
	for (int ii = 0; ii < VertexLength; ++ii)
	{
		VertexList[ii].pos.x = -1.0f + 2.0f * VertexList[ii].pos.x / ScreenWidth;
		VertexList[ii].pos.y = +1.0f - 2.0f * VertexList[ii].pos.y / ScreenHeight;
	}
	//色　変換
	for (int ii = 0; ii < VertexLength; ++ii)
	{
		//VertexList[ii].tex.x /= tex->GetWidth();
		//VertexList[ii].tex.y /= tex->GetHeight();
		VertexList[ii].tex.x /= ScreenWidth;
		VertexList[ii].tex.y /= ScreenHeight;
	}
	ScreenTexture->Set(device,0);
	
	//	頂点情報を更新します
	D3D11_MAPPED_SUBRESOURCE	MappedSubResource;
	hr = device->Map(m_vertexBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&MappedSubResource);
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	if (SUCCEEDED(hr))
	{
		VERTEX2D* pVertices = static_cast<VERTEX2D*>(MappedSubResource.pData);
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			pVertices[ii].pos.x = VertexList[ii].pos.x;
			pVertices[ii].pos.y = VertexList[ii].pos.y;
			pVertices[ii].pos.z = 0.0f;
			pVertices[ii].color = color;
			pVertices[ii].tex = VertexList[ii].tex;
		}
	
		device->Unmap(m_vertexBuffer.Get(), 0);
	}
	
	UINT strides = sizeof(VERTEX2D);
	UINT offset = 0;
	
	//device->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());
	device->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_MIRROR].GetAddressOf());
	
	
	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	
	
	
	
	
	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &strides, &offset);
	
	device->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
	
	device->Draw(4, 0);
	
	m_shader->Inactivate(device);
}


void Lib_TargetScreenShader::ScreenRender(ID3D11DeviceContext* device)
{
 //レンダーターゲット
  //ID3D11RenderTargetView* rtv = TK_Lib::Lib_Graphics::Get_targetview();
  ID3D11RenderTargetView* rtv = ScreenTexture->GetRenderTargetView();
  ID3D11DepthStencilView* dsv = TK_Lib::Lib_Graphics::Get_DepthStencilView();
  //レンダーターゲットを送り込む
  device->OMSetRenderTargets(1, &rtv, nullptr);
 // 画面クリア
 float ClearColor[4] = { 0, 0, 0, 0 };
  //全てのレンダーターゲットを画面クリアする
  device->ClearRenderTargetView(rtv, ClearColor);
  //全てのレンダーターゲットの深度情報をクリアする
 // device->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

//スクリーンをテクスチャを送る
ID3D11ShaderResourceView* srv = TK_Lib::Lib_Graphics::Get_ShaderResourceView();
device->PSSetShaderResources(0, 1, &srv);

D3D11_VIEWPORT	Viewport;//Windowsの設定の実体
UINT			ViewportCount = 1;//Windowの数

//tex->Set(device, 0);


device->RSGetViewports(&ViewportCount, &Viewport);
float	ScreenWidth = Viewport.Width;
float	ScreenHeight = Viewport.Height;

TK_Lib::Draw::Sprite(nullptr, VECTOR2{ 0, 0 }, VECTOR2{ ScreenWidth, ScreenHeight }, VECTOR4{ 0,0,ScreenWidth,ScreenHeight }, 0, { 1,1,1,1 } );
   
rtv = TK_Lib::Lib_Graphics::Get_targetview();
dsv = TK_Lib::Lib_Graphics::Get_DepthStencilView();
//レンダーターゲットを送り込む
device->OMSetRenderTargets(1, &rtv, nullptr);
//全てのレンダーターゲットを画面クリアする
device->ClearRenderTargetView(rtv, ClearColor);

//スクリーンをテクスチャを送る
//ID3D11ShaderResourceView* srv = TK_Lib::Lib_Graphics::Get_ShaderResourceView();

TK_Lib::Draw::Sprite(ScreenTexture.get(), VECTOR2{ 0, 0 }, VECTOR2{ ScreenWidth, ScreenHeight }, VECTOR4{ 0,0,ScreenWidth,ScreenHeight }, 0, { 1,1,1,1 });


}