#pragma once
#include "Lib_BaseShader.h"
class CameraLib;

class Lib_CascadeShader :public BaseShader
{
public:
	//影テクスチャ作成のShader
	unique_ptr<ShaderResource> shadowShader;
	


	//カスケードシャドウマップの数
	static const int NUM_SHADOW_MAP = 3;
	//シャドウマップのサイズ
	//const XMFLOAT2 shadowSize[NUM_SHADOW_MAP] = { {512,512} ,{256,256},{128,128} };
	const XMFLOAT2 shadowSize[NUM_SHADOW_MAP] = {{1024, 1024}, { 1024,1024 }, { 512,512 }
};
	//シャドウクリップエリア
	const float shadowArea[NUM_SHADOW_MAP] = { 100,300,600 };
	//クリップ行列
	XMFLOAT4X4 IvpcMatrix[NUM_SHADOW_MAP];
	//シャドウマップ用のレンダーターゲット3枚
	std::shared_ptr<TextureResource>shadow_Texture[NUM_SHADOW_MAP] = { nullptr };
	//ガウステクスチャ
	std::shared_ptr<TextureResource>Gauss_Texture[NUM_SHADOW_MAP] = { nullptr };
	std::shared_ptr<TextureResource>depth_Texture = nullptr;



private:
	static const int MaxBones = 128;

	//カスケードシャドウマップを作成するため
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


	// シーン用定数バッファ更新
	ShadowConstant shadowconstant;

	ComPtr<ID3D11Buffer>			m_sceneConstantBuffer;
	ComPtr<ID3D11Buffer>			m_meshConstantBuffer;
	ComPtr<ID3D11Buffer>			m_subsetConstantBuffer;
	ComPtr<ID3D11Buffer>			m_shadowConstantBuffer;

	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//デプスステンシル


public:
	Lib_CascadeShader(ID3D11Device* device);
	~Lib_CascadeShader() {};

	//クロップ行列
	XMFLOAT4X4 CreateClop(const int Shadow_Index, const CameraLib& ModelView, const CameraLib& LightView, const XMMATRIX viewMatrix, const XMMATRIX projectionMatrix);

	//影テクスチャの生成
	void CreateShadowTexture(ID3D11DeviceContext* context, const CameraLib& ModelView,const CameraLib& LightView, const vector<ModelResource*> *list);
	void CreateShadowEnd(ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv);
	//カスケードシャドウマップの生成
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
	////影の生成
	//void ShadowBegin(ID3D11DeviceContext* context, const CameraLib& ModelView,
	//	const CameraLib& LightView, vector<ModelResource*> list);
	//
	//void ShadowEnd(ID3D11DeviceContext* context);
	//
	//
	//モデルの生成
	void Begin(ID3D11DeviceContext* context);
	void Begin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection) {};
	void Render(ID3D11DeviceContext* context, const ModelResource* model);
	//メッシュ用定数バッファ更新
	void UpdateMeshConstantBuffer(ID3D11DeviceContext* context, const ModelResource* model);
	void End(ID3D11DeviceContext* context);


	void CreateGauss(ID3D11DeviceContext* context, TextureResource* tex, TextureResource* tex2);
};