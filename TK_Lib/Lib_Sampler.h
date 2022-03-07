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
		Sampler_MIRROR,	//�T���v���X�e�[�g(�e�N�X�`���ݒ�)���]
		Sampler_Shadow_BORDER,//�e��p
		Sampler_END,
	};

	static Sampler& Instance()
	{
		return *instance;
	}


public:
	ComPtr <ID3D11SamplerState> m_samplerState[Sampler_END];//�T���v���[
};
