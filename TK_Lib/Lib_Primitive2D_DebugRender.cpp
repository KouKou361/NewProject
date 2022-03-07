#include "Lib_DebugRender.h"
#include "Lib_DirectXFunctions.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
Primitive2D_DebugRender::Primitive2D_DebugRender(ID3D11Device* device, u_int MaxVertex)
{
//===================
//shaderの設定
//====================
	m_shader = make_shared<ShaderResource>();
	m_shader->Create(device, "./Shader/Primitive2D_vs.cso", "./Shader/Primitive2D_ps.cso",ShaderResource::TYPELayout::TYPE_LayoutDebugSprite);

	HRESULT hr = S_OK;

	SetMaxVertex(MaxVertex);

	//頂点バッファ
	{
		D3D11_BUFFER_DESC bufferdesc;
		ZeroMemory(&bufferdesc, sizeof(bufferdesc));
		bufferdesc.ByteWidth =UINT(sizeof(VERTEXDEBUG) * vertices.size());
		bufferdesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferdesc.MiscFlags = false;
		bufferdesc.StructureByteStride = false;

		D3D11_SUBRESOURCE_DATA subresource;
		ZeroMemory(&subresource, sizeof(subresource));
		subresource.pSysMem = vertices.data();
		subresource.SysMemPitch = false;
		subresource.SysMemSlicePitch = false;
		//頂点バッファの作成
		hr = device->CreateBuffer(&bufferdesc, &subresource, m_vertexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			_ASSERT_EXPR(SUCCEEDED(hr), L"頂点バッファのエラー");
			return;
		}
	}
	//===================================================
	//深度ステンシルステートの作成
	//===================================================
	{

		D3D11_DEPTH_STENCIL_DESC DepthStencilDesc = {};
		//深度テスト
		DepthStencilDesc.DepthEnable = FALSE;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;//書き込みを可能にさせる
		//ステンシルテストは不要
		DepthStencilDesc.StencilEnable = FALSE;

		hr = device->CreateDepthStencilState(&DepthStencilDesc, m_depthStencilState.GetAddressOf());
		if (FAILED(hr)) {
			_ASSERT_EXPR(SUCCEEDED(hr), L"深度ステンシルステートのエラー");
			return;	//	作成できなかったので初期化失敗
		}
	}
}



void Primitive2D_DebugRender::ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data)
{
	D3D11_VIEWPORT	Viewport;//Windowsの設定の実体
	UINT			ViewportCount = 1;//Windowの数

	//分かりやすくするために別の変数名にする
	const VECTOR2 pos = VECTOR2{ data.pos.x,data.pos.y };
	const VECTOR2 size = VECTOR2{ data.pos2.x,data.pos2.y };
	const VECTOR4 color = data.color;
	const float angle = data.angle;


	device->RSGetViewports(&ViewportCount, &Viewport);
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;

	HRESULT hr = S_OK;
	//	設定情報から4頂点を作成
	VERTEXDEBUG VertexList[4] =
	{
	{ DirectX::XMFLOAT3(pos.x,         pos.y         ,0),XMFLOAT3(0,0,0),XMFLOAT2(0,0), color},
	{ DirectX::XMFLOAT3(pos.x + size.x,pos.y         ,0),XMFLOAT3(0,0,0),XMFLOAT2(1,0), color},
	{ DirectX::XMFLOAT3(pos.x,         pos.y + size.y,0),XMFLOAT3(0,0,0),XMFLOAT2(0,1), color},
	{ DirectX::XMFLOAT3(pos.x + size.x,pos.y + size.y,0),XMFLOAT3(0,0,0),XMFLOAT2(1,1), color},
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
	//頂点情報をセットし直す
	SetVertex(device, &VertexList[0], VertexLength);


	UINT strides = sizeof(VERTEXDEBUG);
	UINT offset = 0;



	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	if (data.fill)device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	else device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerLine_TRUE].Get());

	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &strides, &offset);


	device->Draw(4, 0);

}
void Primitive2D_DebugRender::ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data)
{

	D3D11_VIEWPORT	Viewport;//Windowsの設定の実体
	UINT			ViewportCount = 1;//Windowの数
	device->RSGetViewports(&ViewportCount, &Viewport);
	//スクリーンサイズ
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;


	//分かりやすくするために別の変数名にする
	const VECTOR2 pos = VECTOR2{ data.pos.x,data.pos.y };
	const VECTOR4 color = data.color;
	const float radius = data.radius;

	//頂点の情報のセット
	//まあ予め多く設定している
	VERTEXDEBUG vertices2[Primitive_vertex_num];


	//一周からみて一つあたりからの角度を求める
	float arc = DirectX::XM_2PI / Circle_Num;

	//================================================-
	//頂点の算出
	VERTEXDEBUG* p = &vertices2[0];

	assert(Primitive_vertex_num >= Circle_Num + 1);

	for (int i = 0; i < Circle_Num + 1; i++)
		// circle_vertex_num +1は最後の頂点分も含む
	{

		//=====================================================
		//中心点
		p->pos.x = pos.x; p->pos.y = pos.y;
		p->color = color;
		//NDC変換
		p->pos.x = -1.0f + 2.0f * p->pos.x / ScreenWidth;
		p->pos.y = +1.0f - 2.0f * p->pos.y / ScreenHeight;

		p++;
		//=====================================================
		//円の外周を求める
		p->pos.x = pos.x + cosf(-DirectX::XM_PI * 0.5f + arc * i) * radius;
		p->pos.y = pos.y + sinf(-DirectX::XM_PI * 0.5f + arc * i) * radius;
		p->color = color;
		//NDC変換
		p->pos.x = -1.0f + 2.0f * p->pos.x / ScreenWidth;
		p->pos.y = +1.0f - 2.0f * p->pos.y / ScreenHeight;

		p++;


	}
	SetVertex(device, &vertices2[0], (Circle_Num + 1) * 2);

	UINT strides = sizeof(VERTEXDEBUG);
	UINT offset = 0;



	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	if (data.fill)device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	else device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerLine_TRUE].Get());
	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &strides, &offset);

	device->Draw((Circle_Num + 1) * 2, 0);

}
void Primitive2D_DebugRender::ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data)
{
	D3D11_VIEWPORT	Viewport;//Windowsの設定の実体
	UINT			ViewportCount = 1;//Windowの数

		//分かりやすくするために別の変数名にする
	const VECTOR2 pos = VECTOR2{ data.pos.x,data.pos.y };
	const VECTOR2 pos2 = VECTOR2{ data.pos2.x,data.pos2.y };
	const VECTOR4 color = data.color;


	device->RSGetViewports(&ViewportCount, &Viewport);
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;

	HRESULT hr = S_OK;
	//	設定情報から4頂点を作成
	VERTEXDEBUG VertexList[2] =
	{
	{ DirectX::XMFLOAT3(pos.x,         pos.y         ,0),XMFLOAT3(0,0,0),XMFLOAT2(0,0), color},
	{ DirectX::XMFLOAT3(pos2.x,        pos2.y        ,0),XMFLOAT3(0,0,0),XMFLOAT2(1,1), color},
	};
	constexpr	int	VertexLength = sizeof(VertexList) / sizeof(VertexList[0]);

	//	正規化デバイス座標系に変換する
	for (int ii = 0; ii < VertexLength; ++ii)
	{
		VertexList[ii].pos.x = -1.0f + 2.0f * VertexList[ii].pos.x / ScreenWidth;
		VertexList[ii].pos.y = +1.0f - 2.0f * VertexList[ii].pos.y / ScreenHeight;
	}
	//頂点情報をセットし直す
	SetVertex(device, &VertexList[0], VertexLength);


	UINT strides = sizeof(VERTEXDEBUG);
	UINT offset = 0;



	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	if (data.fill)device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	else device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerLine_TRUE].Get());
	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &strides, &offset);

	device->Draw(2, 0);
}

