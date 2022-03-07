#include "Lib_ShadowShader.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
#include "Lib.h"
#include "Lib_LightManager.h"
#include "Lib_Gauss.h"
Lib_ShadowShader::Lib_ShadowShader(ID3D11Device* device)
{
	HRESULT hr = S_OK;
	//�V�F�[�_�[
	m_shader = make_unique<ShaderResource>();
	m_shader->Create(device, "./Shader/RenderShadow_vs.cso", "./Shader/RenderShadow_ps.cso", ShaderResource::TYPELayout::TYPE_LayoutModel);
	
	shadowShader = make_unique<ShaderResource>();
	shadowShader->Create(device, "./Shader/VarianceShadowMap_vs.cso", "./Shader/VarianceShadowMap_ps.cso", ShaderResource::TYPELayout::TYPE_LayoutModel);

	//shadowTexture = make_unique<TextureResource>();
	//shadowTexture->Create(device, 1024, 1024, DXGI_FORMAT_R32G32_FLOAT);
	//shadowTexture->CreateDepth(device, 1024, 1024, DXGI_FORMAT_R32G32_FLOAT);
	//
	//GaussTexture = make_unique<TextureResource>();
	//GaussTexture->Create(device, 1024, 1024, DXGI_FORMAT_R32G32_FLOAT);
	//GaussTexture->CreateDepth(device, 1024, 1024, DXGI_FORMAT_R32G32_FLOAT);

	shadowTexture = make_unique<TextureResource>();
	shadowTexture->Create(device, 1500, 1500, DXGI_FORMAT_R32G32_FLOAT);
	shadowTexture->CreateDepth(device, 1500, 1500, DXGI_FORMAT_R32G32_FLOAT);
	
	GaussTexture = make_unique<TextureResource>();
	GaussTexture->Create(device, 1500, 1500, DXGI_FORMAT_R32G32_FLOAT);
	GaussTexture->CreateDepth(device, 1500, 1500, DXGI_FORMAT_R32G32_FLOAT);

	// �萔�o�b�t�@
	{
		// �V�[���p�o�b�t�@
		D3D11_BUFFER_DESC desc;
		//::ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.ByteWidth = sizeof(CbScene);
		desc.StructureByteStride = 0;

		hr = device->CreateBuffer(&desc, 0, m_sceneConstantBuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�R���X�^���g�o�b�t�@�̃G���[");

		// ���b�V���p�o�b�t�@
		desc.ByteWidth = sizeof(CbMesh);

		hr = device->CreateBuffer(&desc, 0, m_meshConstantBuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"Mesh�p�̃R���X�^���g�o�b�t�@�̃G���[");

		// �T�u�Z�b�g�p�o�b�t�@
		desc.ByteWidth = sizeof(CbSubset);

		hr = device->CreateBuffer(&desc, 0, m_subsetConstantBuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�T�u�Z�b�g�p�̃R���X�^���g�o�b�t�@�̃G���[");

		// �V���h�E�C���O�p�o�b�t�@
		desc.ByteWidth = sizeof(ShadowConstant);

		hr = device->CreateBuffer(&desc, 0, m_shadowConstantBuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�T�u�Z�b�g�p�̃R���X�^���g�o�b�t�@�̃G���[");



	}

	
	// �[�x�X�e���V���X�e�[�g
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		hr = device->CreateDepthStencilState(&desc, m_depthStencilState.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�[�x�X�e���V���X�e�[�g�̃G���[");
	}

}
//�e�̐���
void Lib_ShadowShader::ShadowBegin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view,
	const DirectX::XMFLOAT4X4& projection, DirectX::XMFLOAT4 EyePos, const DirectX::XMFLOAT4& lightDirection,
	DirectX::XMFLOAT4 ShadowColor,  DirectX::XMFLOAT4 LightColor)
{

	Begin(context, view, projection, lightDirection);
	XMMATRIX VP;
	VP = XMLoadFloat4x4(&view) * XMLoadFloat4x4(&projection);
	XMFLOAT4X4 vp;
	XMStoreFloat4x4(&vp, VP);
	SetShadowConstant(context,
		vp,
		ShadowColor,
		EyePos,
		LightColor);
	shadowShader->Activate(context);
	ID3D11RenderTargetView* rtv = shadowTexture->GetRenderTargetView();
	ID3D11DepthStencilView* dsv = shadowTexture->GetDepthStencilView();
	VECTOR2 TextureSize = VECTOR2{ static_cast<float>(shadowTexture->GetWidth()),static_cast<float>(shadowTexture->GetHeight()) };

	context->PSSetSamplers(1, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_Shadow_BORDER].GetAddressOf());

	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerShader].Get());
	//�Z�b�g
	context->OMSetRenderTargets(1, &rtv, dsv);
	//�r���[�|�[�g�̐ݒ�
	TK_Lib::Screen::SetViewPort(TextureSize);
	//��ʂ̌��̐F��ݒ肷��(R32G32�ɂ����ݒ肵�Ă��Ȃ��̂ŐԂƉ������łȂ�)
	FLOAT Back_Color[] = { 0.7f,0.7f, 1.0f,1.0f };
	context->ClearRenderTargetView(rtv, Back_Color);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	//�f�v�X�X�e���V���X�e�[�g�ݒ�
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
}
void Lib_ShadowShader::ShadowEnd(ID3D11DeviceContext* context)
{
	CreateGauss(context, shadowTexture.get(), GaussTexture.get());

	shadowShader->Inactivate(context);

}

void Lib_ShadowShader::CreateGauss(ID3D11DeviceContext* context, TextureResource* tex, TextureResource* tex2)
{
	Gauss::Instance().GausianFilter(context, tex, tex2);
	TK_Lib::Screen::Clear(VECTOR4{0.0f,0.0f,0.0f,1.0f});
}

void Lib_ShadowShader::Begin(
	ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view,
	const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection)
{
	m_shader->Activate(context);

	ID3D11Buffer* constantBuffers[] =
	{
		m_sceneConstantBuffer.Get(),
		m_meshConstantBuffer.Get(),
		m_subsetConstantBuffer.Get(),
		m_shadowConstantBuffer.Get()
	};
	context->VSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);
	context->PSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);

	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	//context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerShader].Get());
	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_FALSE].Get());
	context->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());

	

	


	Lib_PointLightManager::Instance().Active(context);


}
void Lib_ShadowShader::SetShadowConstant(ID3D11DeviceContext* context,
	DirectX::XMFLOAT4X4 LightVP,
	DirectX::XMFLOAT4 ShadowColor,
	DirectX::XMFLOAT4 EyePos,
	DirectX::XMFLOAT4 LightColor)
{
	// �V�[���p�萔�o�b�t�@�X�V
	ShadowConstant shadowconstant;

	shadowconstant.LightVP = LightVP;
	shadowconstant.EyePos = EyePos;
	shadowconstant.LightColor = LightColor;
	shadowconstant.ShadowColor = ShadowColor;

	context->UpdateSubresource(m_shadowConstantBuffer.Get(), 0, 0, &shadowconstant, 0, 0);


}
void Lib_ShadowShader::Render(ID3D11DeviceContext* context, const ModelResource* model)
{
	const std::vector<ModelResource::Node>& nodes = model->GetNodes();
	const std::vector<ModelResource::NodeTest>& testnodes = model->GetNodetest();

	for (const ModelResource::Mesh& mesh : model->GetMeshes())
	{
		// ���b�V���p�萔�o�b�t�@�X�V
		CbMesh cbMesh;
		::memset(&cbMesh, 0, sizeof(cbMesh));
		if (mesh.nodeIndices.size() > 0)
		{
			for (size_t i = 0; i < mesh.nodeIndices.size(); ++i)
			{
				DirectX::XMMATRIX worldTransform = DirectX::XMLoadFloat4x4(&testnodes.at(mesh.nodeIndices.at(i)).worldTransform);
				DirectX::XMMATRIX offsetTransform = DirectX::XMLoadFloat4x4(&mesh.offsetTransforms.at(i));
				DirectX::XMMATRIX boneTransform = offsetTransform * worldTransform;
				DirectX::XMStoreFloat4x4(&cbMesh.boneTransforms[i], boneTransform);
			}
		}
		else
		{
			cbMesh.boneTransforms[0] = testnodes.at(mesh.nodeIndex).worldTransform;
		}
		context->UpdateSubresource(m_meshConstantBuffer.Get(), 0, 0, &cbMesh, 0, 0);

		UINT stride = sizeof(ModelResource::Vertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, mesh.vertexBuffer.GetAddressOf(), &stride, &offset);
		context->IASetIndexBuffer(mesh.indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//context->PSSetShaderResources(1, 1, shadowTexture->GetShaderResourceView());
		//context->PSSetShaderResources(1, 1, GaussTexture->GetShaderResourceView());
		


		//���b�V���ɉ�����}�e���A���̐ݒ�
		for (const ModelResource::Subset& subset : mesh.subsets)
		{
			CbSubset cbSubset;
			cbSubset.materialColor = subset.material->color;
			context->UpdateSubresource(m_subsetConstantBuffer.Get(), 0, 0, &cbSubset, 0, 0);

			context->PSSetShaderResources(0, 1, subset.material->shaderResourceView.GetAddressOf());
			//	device->PSSetSamplers(0, 1, m_samplerState[0].GetAddressOf());
			context->DrawIndexed(subset.indexCount, subset.startIndex, 0);
		}
	}
}
void Lib_ShadowShader::End(ID3D11DeviceContext* context)
{
	//�e�p�̃e�N�X�`���̕`��
	//TK_Lib::Draw::Sprite(shadowTexture.get(), VECTOR2(0, 0), VECTOR2(500, 500), VECTOR4(0, 0, 1500, 1500), 0.0f, VECTOR4(1, 1, 1, 1));
	//�K�E�X����̉e�p�̃e�N�X�`���̕`��
	//TK_Lib::Draw::Sprite(GaussTexture.get(), VECTOR2(0, 0), VECTOR2(500, 500), VECTOR4(0, 0, 1500, 1500), 0.0f, VECTOR4(1, 1, 1, 1));




	////�e�p�̃e�N�X�`���̕`��
	//TK_Lib::Draw::Sprite(shadowTexture.get(), VECTOR2(0, 0), VECTOR2(500, 500), VECTOR4(0, 0, 1024, 1024), 0.0f, VECTOR4(1, 1, 1, 1));
	////�K�E�X����̉e�p�̃e�N�X�`���̕`��
	//TK_Lib::Draw::Sprite(GaussTexture.get(), VECTOR2(0, 0), VECTOR2(500, 500), VECTOR4(0, 0, 1024, 1024), 0.0f, VECTOR4(1, 1, 1, 1));

	m_shader->Inactivate(context);
	context->OMSetBlendState(BlendState::Instance().GetBlendState(Bland_state::BS_ALPHA), nullptr, 0xffffffff);
	
		

	ID3D11ShaderResourceView* rtv[1] = { NULL }; // PP
	context->PSSetShaderResources(1, 1, rtv); // PP
	//shadowTexture->Empty(context, 1);
	
	ModelClear();
}