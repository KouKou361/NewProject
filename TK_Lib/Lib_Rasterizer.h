#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
using namespace Microsoft::WRL;
class Rasterizer
{
public:
	Rasterizer(ID3D11Device* device) ;
	Rasterizer() {};
	~Rasterizer() {};
	enum
	{
		RasterizerFill_TRUE,//表向き(面)
		RasterizerLine_TRUE,//裏向き(線)
		RasterizerFill_FALSE,//裏向き(面)
		RasterizerLine_FALSE,//裏向き(線)
		RasterizerShader,//影
		Rasterizer_END,
	};
private:

	static Rasterizer* instance;

public:
	ComPtr <ID3D11RasterizerState> m_rasterizer[Rasterizer_END];//サンプラー

		//インスタンス取得
	static Rasterizer& Instance()
	{
		return *instance;
	}
};
