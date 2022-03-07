#pragma once
#include "Lib_BaseShader.h"

class Lib_ShadowShader :public BaseShader
{
public:
	//�e�e�N�X�`���쐬��Shader
	unique_ptr<ShaderResource> shadowShader;
	//�e�p�̃e�N�X�`��
	unique_ptr<TextureResource> shadowTexture;
	//�K�E�X�e�N�X�`��
	unique_ptr<TextureResource> GaussTexture;
private:
	static const int MaxBones = 128;
	struct CbScene
	{
		DirectX::XMFLOAT4X4	VP;
		DirectX::XMFLOAT4	lightDirection;
	};

	struct CbMesh
	{
		DirectX::XMFLOAT4X4	boneTransforms[MaxBones];
	};

	struct CbSubset
	{
		DirectX::XMFLOAT4	materialColor;
	};

	struct ShadowConstant
	{
		DirectX::XMFLOAT4X4 LightVP;
		DirectX::XMFLOAT4 ShadowColor;
		DirectX::XMFLOAT4 EyePos;
		DirectX::XMFLOAT4 LightColor;
	};

	ComPtr<ID3D11Buffer>			m_sceneConstantBuffer;
	ComPtr<ID3D11Buffer>			m_meshConstantBuffer;
	ComPtr<ID3D11Buffer>			m_subsetConstantBuffer;
	ComPtr<ID3D11Buffer>			m_shadowConstantBuffer;

	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//�f�v�X�X�e���V��


public:
	Lib_ShadowShader(ID3D11Device* device);
	~Lib_ShadowShader() {};

	void SetShadowConstant(ID3D11DeviceContext* context,
	DirectX::XMFLOAT4X4 LightVP,
	DirectX::XMFLOAT4 ShadowColor,
	DirectX::XMFLOAT4 EyePos,
	DirectX::XMFLOAT4 LightColor);
	//�e�̐���
	void ShadowBegin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view,
		const DirectX::XMFLOAT4X4& projection, DirectX::XMFLOAT4 EyePos, const DirectX::XMFLOAT4& lightDirection,
		DirectX::XMFLOAT4 ShadowColor,DirectX::XMFLOAT4 LightColor);

	void ShadowEnd(ID3D11DeviceContext* context);

	void CreateGauss(ID3D11DeviceContext* context,TextureResource* tex, TextureResource* tex2);
	//���f���̐���
	void Begin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection);
	void Render(ID3D11DeviceContext* context, const ModelResource* model);
	void End(ID3D11DeviceContext* context);
};