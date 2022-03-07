#pragma once
#include "Lib_BaseShader.h"
class CameraLib;

class Lib_CascadeShader :public BaseShader
{
public:
	//�e�e�N�X�`���쐬��Shader
	unique_ptr<ShaderResource> shadowShader;
	


	//�J�X�P�[�h�V���h�E�}�b�v�̐�
	static const int NUM_SHADOW_MAP = 3;
	//�V���h�E�}�b�v�̃T�C�Y
	//const XMFLOAT2 shadowSize[NUM_SHADOW_MAP] = { {512,512} ,{256,256},{128,128} };
	const XMFLOAT2 shadowSize[NUM_SHADOW_MAP] = {{1024, 1024}, { 1024,1024 }, { 512,512 }
};
	//�V���h�E�N���b�v�G���A
	const float shadowArea[NUM_SHADOW_MAP] = { 100,300,600 };
	//�N���b�v�s��
	XMFLOAT4X4 IvpcMatrix[NUM_SHADOW_MAP];
	//�V���h�E�}�b�v�p�̃����_�[�^�[�Q�b�g3��
	std::shared_ptr<TextureResource>shadow_Texture[NUM_SHADOW_MAP] = { nullptr };
	//�K�E�X�e�N�X�`��
	std::shared_ptr<TextureResource>Gauss_Texture[NUM_SHADOW_MAP] = { nullptr };
	std::shared_ptr<TextureResource>depth_Texture = nullptr;



private:
	static const int MaxBones = 128;

	//�J�X�P�[�h�V���h�E�}�b�v���쐬���邽��
	struct CreateShadowConstant
	{
		DirectX::XMFLOAT4X4	VP;
		XMFLOAT4 lightDirection;
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
		DirectX::XMFLOAT4X4 LightVP[3];
		DirectX::XMFLOAT4 ShadowColor;
		DirectX::XMFLOAT4 EyePos;
		DirectX::XMFLOAT4 LightColor;
	};


	// �V�[���p�萔�o�b�t�@�X�V
	ShadowConstant shadowconstant;

	ComPtr<ID3D11Buffer>			m_sceneConstantBuffer;
	ComPtr<ID3D11Buffer>			m_meshConstantBuffer;
	ComPtr<ID3D11Buffer>			m_subsetConstantBuffer;
	ComPtr<ID3D11Buffer>			m_shadowConstantBuffer;

	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//�f�v�X�X�e���V��


public:
	Lib_CascadeShader(ID3D11Device* device);
	~Lib_CascadeShader() {};

	//�N���b�v�s��
	XMFLOAT4X4 CreateClop(const int Shadow_Index, const CameraLib& ModelView, const CameraLib& LightView, const XMMATRIX viewMatrix, const XMMATRIX projectionMatrix);

	//�e�e�N�X�`���̐���
	void CreateShadowTexture(ID3D11DeviceContext* context, const CameraLib& ModelView,const CameraLib& LightView, const vector<ModelResource*> *list);
	void CreateShadowEnd(ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv);
	//�J�X�P�[�h�V���h�E�}�b�v�̐���
	void CascadeShadowBegin(ID3D11DeviceContext* context, const CameraLib& ModelView, const CameraLib& LightView);
	void CascadeShadowRender(ID3D11DeviceContext* context, const vector<ModelResource*> *list, ShadowType DrawType);
	void CascadeShadowEnd(ID3D11DeviceContext* context);


	void SetShadowConstant(
		ID3D11DeviceContext* context,
		XMFLOAT4 lightDirection,
		DirectX::XMFLOAT4X4 ViewProjection
	);
	
	void SetShadowConstan2(ID3D11DeviceContext* context,
		DirectX::XMFLOAT4 ShadowColor,
		DirectX::XMFLOAT4 EyePos,
		DirectX::XMFLOAT4 LightColor);
	////�e�̐���
	//void ShadowBegin(ID3D11DeviceContext* context, const CameraLib& ModelView,
	//	const CameraLib& LightView, vector<ModelResource*> list);
	//
	//void ShadowEnd(ID3D11DeviceContext* context);
	//
	//
	//���f���̐���
	void Begin(ID3D11DeviceContext* context);
	void Begin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection) {};
	void Render(ID3D11DeviceContext* context, const ModelResource* model);
	//���b�V���p�萔�o�b�t�@�X�V
	void UpdateMeshConstantBuffer(ID3D11DeviceContext* context, const ModelResource* model);
	void End(ID3D11DeviceContext* context);


	void CreateGauss(ID3D11DeviceContext* context, TextureResource* tex, TextureResource* tex2);
};