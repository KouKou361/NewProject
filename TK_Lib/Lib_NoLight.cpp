#include "Lib_NoLight.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
Lib_NoLightShader::Lib_NoLightShader(ID3D11Device* device)
{
	HRESULT hr = S_OK;
	//�V�F�[�_�[
	m_shader = make_unique<ShaderResource>();
	m_shader->Create(device, "./Shader/NoLight_vs.cso", "./Shader/NoLight_ps.cso", ShaderResource::TYPELayout::TYPE_LayoutModel);

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

		////�R���X�^���g�o�b�t�@
		//desc.ByteWidth = sizeof(Constant);
		//hr = device->CreateBuffer(&desc, 0, m_ConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"�R���X�^���g�o�b�t�@�̃G���[");

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

void Lib_NoLightShader::SetConstant(DirectX::XMFLOAT4 color)
{
	constant.Color = color;
}

void Lib_NoLightShader::Begin(
	ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view,
	const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection)
{
	m_shader->Activate(context);

	ID3D11Buffer* constantBuffers[] =
	{
		m_sceneConstantBuffer.Get(),
		m_meshConstantBuffer.Get(),
		m_subsetConstantBuffer.Get(),
		//m_ConstantBuffer.Get()
	};
	context->VSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);
	context->PSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);

	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_FALSE].Get());
	context->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());

	// �V�[���p�萔�o�b�t�@�X�V
	CbScene cbScene;

	DirectX::XMMATRIX V = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX P = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMStoreFloat4x4(&cbScene.VP, V * P);

	cbScene.lightDirection = lightDirection;
	context->UpdateSubresource(m_sceneConstantBuffer.Get(), 0, 0, &cbScene, 0, 0);


}
void Lib_NoLightShader::Render(ID3D11DeviceContext* context, const ModelResource* model)
{
	const std::vector<ModelResource::Node>& nodes = model->GetNodes();
	const std::vector<ModelResource::NodeTest>& testnodes = model->GetNodetest();



	//TODO:�F�̐؂�ւ�(������)
	//�R���X�^���g�o�b�t�@
	//context->UpdateSubresource(m_subsetConstantBuffer.Get(), 0, 0, &constant, 0, 0);

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
void Lib_NoLightShader::End(ID3D11DeviceContext* context)
{
	m_shader->Inactivate(context);
	ModelClear();
}