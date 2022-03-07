#include "Lib_Rasterizer.h"

Rasterizer* Rasterizer::instance = nullptr;
Rasterizer::Rasterizer(ID3D11Device* device)
{
	instance = this;
	HRESULT hr = S_OK;
	D3D11_RASTERIZER_DESC rasterizer_desc;
	::ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));

	//表向き

	rasterizer_desc.CullMode = D3D11_CULL_FRONT;
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.FrontCounterClockwise = true;
	rasterizer_desc.ScissorEnable = false;
	rasterizer_desc.MultisampleEnable = false;
	 hr = device->CreateRasterizerState(&rasterizer_desc, m_rasterizer[RasterizerFill_TRUE].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"ラスタライザのエラー");

	rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
	hr = device->CreateRasterizerState(&rasterizer_desc, m_rasterizer[RasterizerLine_TRUE].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"ラスタライザのエラー");

	//裏向き(面)
	::memset(&rasterizer_desc, 0, sizeof(rasterizer_desc));
	rasterizer_desc.FrontCounterClockwise = false;
	rasterizer_desc.DepthBias = 0;
	rasterizer_desc.DepthBiasClamp = 0;
	rasterizer_desc.SlopeScaledDepthBias = 0;
	rasterizer_desc.DepthClipEnable = true;
	rasterizer_desc.ScissorEnable = false;
	rasterizer_desc.MultisampleEnable = true;
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_BACK;
	rasterizer_desc.AntialiasedLineEnable = false;

	hr = device->CreateRasterizerState(&rasterizer_desc, m_rasterizer[RasterizerFill_FALSE].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"ラスタライザーステートのエラー");

	//影
	rasterizer_desc.FrontCounterClockwise = true;
	rasterizer_desc.CullMode = D3D11_CULL_FRONT;
	hr = device->CreateRasterizerState(&rasterizer_desc, m_rasterizer[RasterizerShader].GetAddressOf());

	//裏向き(線)
	rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizer_desc.CullMode = D3D11_CULL_NONE;
	hr = device->CreateRasterizerState(&rasterizer_desc, m_rasterizer[RasterizerLine_FALSE].GetAddressOf());
	if (FAILED(hr)) {
		assert(!"ラスタライザのエラー");
		return;	//	作成できなかったので初期化失敗
	}




	
}