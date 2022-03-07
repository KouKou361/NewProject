#include "Lib_Sampler.h"
Sampler* Sampler::instance = nullptr;
Sampler::Sampler(ID3D11Device* device)
{
	instance = this;

	HRESULT hr = S_OK;
	// サンプラステート
	{
		D3D11_SAMPLER_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		desc.MipLODBias = 0.0f;
		desc.MaxAnisotropy = 1;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0;
		desc.MaxLOD = FLT_MAX;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		hr = device->CreateSamplerState(&desc, m_samplerState[Sampler_CLAMP].GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"サンプラステートのエラー");

		::memset(&desc, 0, sizeof(desc));
		desc.MipLODBias = 0.0f;
		desc.MaxAnisotropy = 1;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0;
		desc.MaxLOD = FLT_MAX;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		hr = device->CreateSamplerState(&desc, m_samplerState[Sampler_WRAP].GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"サンプラステートのエラー");


		//サンプラステート(テクスチャ設定)反転
		{
			D3D11_SAMPLER_DESC smpDesc;
			::ZeroMemory(&smpDesc, sizeof(smpDesc));
			smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//サンプリングする時に使うフィルタ(サンプリングには線形補間を使用)
			smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;//0~1の範囲外にあるUテクスチャ画像の取得方法
			smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;//0~1の範囲外にあるVテクスチャ画像の取得方法
			smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;//0~1の範囲外にあるWテクスチャ画像の取得方法
			smpDesc.BorderColor[0] = 1;
			smpDesc.BorderColor[1] = 1;
			smpDesc.BorderColor[2] = 1;
			smpDesc.BorderColor[3] = 1;
			hr = device->CreateSamplerState(&smpDesc, m_samplerState[Sampler_MIRROR].GetAddressOf());

			assert(hr == S_OK);
		}


		//サンプラステート(テクスチャ設定)反転
		{
			D3D11_SAMPLER_DESC smpDesc;
			::ZeroMemory(&smpDesc, sizeof(smpDesc));
			smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//サンプリングする時に使うフィルタ(サンプリングには線形補間を使用)
			smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;//0~1の範囲外にあるUテクスチャ画像の取得方法
			smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;//0~1の範囲外にあるVテクスチャ画像の取得方法
			smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;//0~1の範囲外にあるWテクスチャ画像の取得方法
			smpDesc.BorderColor[0] = FLT_MAX;
			smpDesc.BorderColor[1] = FLT_MAX;
			smpDesc.BorderColor[2] = FLT_MAX;
			smpDesc.BorderColor[3] = FLT_MAX;
			hr = device->CreateSamplerState(&smpDesc, m_samplerState[Sampler_Shadow_BORDER].GetAddressOf());

			assert(hr == S_OK);
		}
	}
}