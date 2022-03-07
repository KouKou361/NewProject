#pragma once
#include "Lib_BaseShader.h"

class Lib_NoLightShader :public BaseShader
{
private:
	static const int MaxBones = 128;
	struct CbScene
	{
		DirectX::XMFLOAT4X4	VP;
		DirectX::XMFLOAT4	lightDirection;
	};
	//TODO Colorのセット
	struct Constant
	{
		DirectX::XMFLOAT4 Color;
	};
	Constant constant;

	struct CbMesh
	{
		DirectX::XMFLOAT4X4	boneTransforms[MaxBones];
	};

	struct CbSubset
	{
		DirectX::XMFLOAT4	materialColor;
	};

	ComPtr<ID3D11Buffer>			m_sceneConstantBuffer;
	ComPtr<ID3D11Buffer>			m_meshConstantBuffer;
	ComPtr<ID3D11Buffer>			m_subsetConstantBuffer;
	//ComPtr<ID3D11Buffer>			m_ConstantBuffer;

	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//デプスステンシル


public:
	Lib_NoLightShader(ID3D11Device* device);
	~Lib_NoLightShader() {};

	void SetConstant(DirectX::XMFLOAT4 color);

	void Begin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection);
	void Render(ID3D11DeviceContext* context, const ModelResource* model);
	void End(ID3D11DeviceContext* context);
};