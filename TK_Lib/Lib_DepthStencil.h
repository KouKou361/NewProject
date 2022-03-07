#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
using namespace Microsoft::WRL;
class DepthStencil
{
public:
	DepthStencil(ID3D11Device* device);
	~DepthStencil() {};
	
	static DepthStencil* instance;
	enum
	{
		DS_TRUE,
		DS_FALSE,
		DS_WRITE_FALSE,
		DS_END,
	};
	static DepthStencil& Instance()
	{
		return *instance;
	}
public:
	ComPtr<ID3D11DepthStencilState> m_depthState[DS_END];
};
