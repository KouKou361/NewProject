#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
using namespace Microsoft::WRL;
class Sampler
{
public:

	
	Sampler(ID3D11Device* device);
	~Sampler() {};


	static Sampler* instance;

	enum
	{
		Sampler_CLAMP,
		Sampler_WRAP,
		Sampler_MIRROR,	//サンプラステート(テクスチャ設定)反転
		Sampler_Shadow_BORDER,//影専用
		Sampler_END,
	};

	static Sampler& Instance()
	{
		return *instance;
	}


public:
	ComPtr <ID3D11SamplerState> m_samplerState[Sampler_END];//サンプラー
};
