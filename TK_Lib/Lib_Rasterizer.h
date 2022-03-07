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
		RasterizerFill_TRUE,//�\����(��)
		RasterizerLine_TRUE,//������(��)
		RasterizerFill_FALSE,//������(��)
		RasterizerLine_FALSE,//������(��)
		RasterizerShader,//�e
		Rasterizer_END,
	};
private:

	static Rasterizer* instance;

public:
	ComPtr <ID3D11RasterizerState> m_rasterizer[Rasterizer_END];//�T���v���[

		//�C���X�^���X�擾
	static Rasterizer& Instance()
	{
		return *instance;
	}
};
