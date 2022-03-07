#pragma once
#include "Lib_BaseShader.h"

class Lib_TargetScreenShader 
{
private:
	//Screenのテクスチャ
	unique_ptr<TextureResource> ScreenTexture=nullptr;

	//TODO Colorのセット
	unique_ptr<ShaderResource> m_shader=nullptr;
	//頂点バッファ
	ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
	struct SceneConstantBuffer
	{
		VECTOR4 Color;//色
		float LineWeight;//ターゲットスクリーンのふちの太さ
		float LineDark; //ターゲットスクリーンのふちの濃さ
		float dummy;
		float dummy2;
	};

	ComPtr<ID3D11Buffer>			m_sceneConstantBuffer;
	//ComPtr<ID3D11Buffer>			m_ConstantBuffer;

	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//デプスステンシル


public:
	Lib_TargetScreenShader(ID3D11Device* device);
	~Lib_TargetScreenShader() {};

	void SetConstant(ID3D11DeviceContext* device, VECTOR4 color, float LineDark, float LineWeight);
	//描画
	void Render(ID3D11DeviceContext* device);
	//Screen描画
	void ScreenRender(ID3D11DeviceContext* device);


};