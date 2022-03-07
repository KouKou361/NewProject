#include "Lib_ShaderResource.h"
#include "WICTextureLoader.h"
#include "Lib_DirectXFunctions.h"



#include	<memory>

D3D11_INPUT_ELEMENT_DESC Layout2DSprite[] = {
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT   ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT      ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR"   ,0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

D3D11_INPUT_ELEMENT_DESC LayoutDebugSprite[] = {
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT   ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL"  ,0,DXGI_FORMAT_R32G32B32_FLOAT   ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT      ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR"   ,0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

D3D11_INPUT_ELEMENT_DESC LayoutPointSprite[] = {
		{ "POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT   ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT      ,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TANGENT",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR"   , 0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

// 入力レイアウト
D3D11_INPUT_ELEMENT_DESC ModelElementDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "WEIGHTS",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BONES",    0, DXGI_FORMAT_R32G32B32A32_UINT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

D3D11_INPUT_ELEMENT_DESC *LayoutList[] =
{
	Layout2DSprite,
	LayoutDebugSprite,
	LayoutPointSprite,
	ModelElementDesc
};

void ShaderResource::Create(ID3D11Device* device, const char* VSname, const char* PSname , ShaderResource::TYPELayout type)
{
	HRESULT hr = S_OK;
	UINT numElements =0;
	switch (type)
	{
	case TYPELayout::TYPE_Layout2DSprite:numElements = ARRAYSIZE(Layout2DSprite);
		break;
	case TYPELayout::TYPE_LayoutDebugSprite:numElements = ARRAYSIZE(LayoutDebugSprite);
		break;
	case TYPELayout::TYPE_layoutPointSprite:numElements = ARRAYSIZE(LayoutPointSprite);
		break;
	case TYPELayout::TYPE_LayoutModel:numElements = ARRAYSIZE(ModelElementDesc);
		
	}
	//頂点シェーダー作成
	hr = CreateVertexShaderFromCSO(device, VSname, m_VertexShader.GetAddressOf(), m_inputLayout.GetAddressOf(), LayoutList[static_cast<UINT>(type)], numElements);

	//ピクセルシェイダー作成
	hr = CreatePixelShaderFromCSO(device, PSname, m_PixelShader.GetAddressOf());

	if (FAILED(hr)) {
		//_ASSERT_EXPR(hr, "シェーダー作成のエラー");
		assert("シェーダー作成のエラー");
		return;
	}
}

void ShaderResource::Create(ID3D11Device* device, const char* VSname, const char* GSname, const char* PSname, ShaderResource::TYPELayout type)
{
	//PSシェーダー　VSシェーダーの生成
	Create(device,VSname,PSname,type);

	//GSシェーダーの生成
	FILE* fp = nullptr;
	errno_t error;

	error = fopen_s(&fp, GSname, "rb");
	assert("CSO File not found");

	fseek(fp, 0, SEEK_END);
	long cso_sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	std::unique_ptr<unsigned char[]> cso_data = std::make_unique<unsigned char[]>(cso_sz);
	fread(cso_data.get(), cso_sz, 1, fp);
	fclose(fp);

	HRESULT hr = device->CreateGeometryShader(cso_data.get(), cso_sz, nullptr, m_GeometryShader.GetAddressOf());
	assert(SUCCEEDED(hr));
}


void ShaderResource::Activate(ID3D11DeviceContext* device)
{
	device->IASetInputLayout(m_inputLayout.Get());
	device->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	device->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	if (m_GeometryShader.Get()) {
		device->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	}
}
void ShaderResource::Inactivate(ID3D11DeviceContext* device)
{

	device->VSSetShader(NULL, NULL, 0);
	device->HSSetShader(NULL, NULL, 0);
	device->DSSetShader(NULL, NULL, 0);
	device->GSSetShader(NULL, NULL, 0);
	device->PSSetShader(NULL, NULL, 0);

}
