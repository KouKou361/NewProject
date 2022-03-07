#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "Lib_Texture.h"
#include "Lib_ShaderResource.h"

using namespace Microsoft::WRL;
using namespace DirectX;

class Gauss
{
public:

	Gauss(ID3D11Device* device);
	~Gauss() {};
private:
	//影について
	static	constexpr	u_int	KARNEL_SIZE = 16;
	static	constexpr	float	PI = 3.141592f;
	static	constexpr	u_int	BUFFER_SIZE = KARNEL_SIZE * KARNEL_SIZE;

	unique_ptr<ShaderResource> Gauss_shader;

	struct ConstantBufferForPerFrameGaussianBlur
	{
		XMFLOAT4 Weight[BUFFER_SIZE];
		float KarneSize;
		XMFLOAT2 texcel;
		float dummy;
	};
	ComPtr<ID3D11Buffer> ConstantBufferGaussian;

	static Gauss* instance;

public:
	static Gauss& Instance()
	{
		return *instance;
	}
	//第一引数:ガウスにかける側、第二引数:ガウスにかけられる側、
	void GausianFilter(ID3D11DeviceContext* device, TextureResource* tex1, TextureResource* tex2);

	void CalcGaussianFilter(XMFLOAT4* array, int karnel_size, float sigma);

};
