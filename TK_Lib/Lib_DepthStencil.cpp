#include"Lib_DepthStencil.h"
DepthStencil* DepthStencil::instance = nullptr;

DepthStencil::DepthStencil(ID3D11Device* device)
{
	instance = this;
	//デプスステンシルステート
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = FALSE;
	HRESULT hr = device->CreateDepthStencilState(&depth_stencil_desc, m_depthState[DS_FALSE].GetAddressOf());
	if (FAILED(hr))
	{
		assert("デプスステンシルステート失敗");
		return;
	}



	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = device->CreateDepthStencilState(&depth_stencil_desc, m_depthState[DS_TRUE].GetAddressOf());


	if (FAILED(hr))
	{
		assert("デプスステンシルステート失敗");
		return;
	}

	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = device->CreateDepthStencilState(&depth_stencil_desc, m_depthState[DS_WRITE_FALSE].GetAddressOf());
	if (FAILED(hr))
	{
		assert("デプスステンシルステート失敗");
		return;
	}
}