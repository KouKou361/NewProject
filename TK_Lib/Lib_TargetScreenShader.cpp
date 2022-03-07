#include "Lib_TargetScreenShader.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
#include "Lib_DepthStencil.h"
#include "Lib_DirectXFunctions.h"
#include "Lib.h"

Lib_TargetScreenShader::Lib_TargetScreenShader(ID3D11Device* device)
{

	HRESULT hr = S_OK;

	VERTEX2D vertices[] = {
			{ XMFLOAT3(-0.5, +0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1, 1, 1, 1)},
			{ XMFLOAT3(+0.5, +0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1, 0, 0, 1)},
			{ XMFLOAT3(-0.5, -0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0, 1, 0, 1)},
			{ XMFLOAT3(+0.5, -0.5, 0),XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0, 0, 1, 1)},
	};
	//���_�̐�
	int VerticesNum = ARRAYSIZE(vertices);
	//=========================
	//���_�o�b�t�@�̍쐬
	//=========================
	{
		D3D11_BUFFER_DESC vertex_buffer_desc = {};
		::ZeroMemory(&vertex_buffer_desc, sizeof(D3D11_BUFFER_DESC));
		vertex_buffer_desc.ByteWidth = sizeof(VERTEX2D) * VerticesNum;
		vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;//�ǂݍ��݁A�������ސݒ�
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sub_data = {};
		::ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = vertices;
		sub_data.SysMemPitch = 0;
		sub_data.SysMemSlicePitch = 0;
		//���_�o�b�t�@�̍쐬
		hr = device->CreateBuffer(&vertex_buffer_desc, &sub_data, m_vertexBuffer.GetAddressOf());
	}


	//�V�F�[�_�[
	m_shader = make_unique<ShaderResource>();
	m_shader->Create(device, "./Shader/TargetScreen_vs.cso", "./Shader/TargetScreen_ps.cso", ShaderResource::TYPELayout::TYPE_Layout2DSprite);


	//ScreenTexture�̐���
	VECTOR2 WindowSize = TK_Lib::Window::GetWindowSize();
	ScreenTexture = make_unique<TextureResource>();
	ScreenTexture->Create(device, static_cast<u_int>(WindowSize.x), static_cast<u_int>(WindowSize.y), DXGI_FORMAT_R8G8B8A8_UNORM);

	// �萔�o�b�t�@
	{
		// �V�[���p�o�b�t�@
		D3D11_BUFFER_DESC desc;
		::ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.ByteWidth = sizeof(SceneConstantBuffer);
		desc.StructureByteStride = 0;
		
		hr = device->CreateBuffer(&desc, 0, m_sceneConstantBuffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�R���X�^���g�o�b�t�@�̃G���[");
		
		//// ���b�V���p�o�b�t�@
		//desc.ByteWidth = sizeof(CbMesh);
		//hr = device->CreateBuffer(&desc, 0, m_meshConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"Mesh�p�̃R���X�^���g�o�b�t�@�̃G���[");
		//
		//// �T�u�Z�b�g�p�o�b�t�@
		//desc.ByteWidth = sizeof(CbSubset);
		//hr = device->CreateBuffer(&desc, 0, m_subsetConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"�T�u�Z�b�g�p�̃R���X�^���g�o�b�t�@�̃G���[");
		
	
		////�R���X�^���g�o�b�t�@
		//desc.ByteWidth = sizeof(Constant);
		//hr = device->CreateBuffer(&desc, 0, m_ConstantBuffer.GetAddressOf());
		//_ASSERT_EXPR(SUCCEEDED(hr), L"�R���X�^���g�o�b�t�@�̃G���[");

	}


	// �[�x�X�e���V���X�e�[�g
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		//�[�x�e�X�g
		desc.DepthEnable = FALSE;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;//�������݂��\�ɂ�����
		//�X�e���V���e�X�g�͕s�v
		desc.StencilEnable = FALSE;

		hr = device->CreateDepthStencilState(&desc, m_depthStencilState.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"�[�x�X�e���V���X�e�[�g�̃G���[");
	}

}

void Lib_TargetScreenShader::SetConstant(ID3D11DeviceContext* device, VECTOR4 color, float LineDark, float LineWeight)
{
	SceneConstantBuffer cb;
	cb.Color = color;
	cb.dummy = 0;
	cb.dummy2 = 0;
	cb.LineWeight = LineWeight;
	cb.LineDark = LineDark;

	device->VSSetConstantBuffers(0, 1, m_sceneConstantBuffer.GetAddressOf());
	device->PSSetConstantBuffers(0, 1, m_sceneConstantBuffer.GetAddressOf());
	device->UpdateSubresource(m_sceneConstantBuffer.Get(), 0, 0, &cb, 0, 0);
};
//�`��
void Lib_TargetScreenShader::Render(ID3D11DeviceContext* device)
{
	ScreenRender(device);
	
	//�����_�[�^�[�Q�b�g
	ID3D11RenderTargetView* rtv = TK_Lib::Lib_Graphics::Get_targetview();
	ID3D11DepthStencilView* dsv = TK_Lib::Lib_Graphics::Get_DepthStencilView();
	//�����_�[�^�[�Q�b�g�𑗂荞��
	device->OMSetRenderTargets(1, &rtv, dsv);
	
	m_shader->Activate(device);
	

	D3D11_VIEWPORT	Viewport;//Windows�̐ݒ�̎���
	UINT			ViewportCount = 1;//Window�̐�
	
	//tex->Set(device, 0);
	
	
	device->RSGetViewports(&ViewportCount, &Viewport);
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;
	
	HRESULT hr = S_OK;
	
	VECTOR2 pos = { 0,0 };
	VECTOR2 size = { ScreenWidth,ScreenHeight };
	
	VECTOR2 texture_pos = { 0,0 };
	VECTOR2 texture_size = { ScreenWidth,ScreenHeight };
	VECTOR4 color = { 1,1,1,1 };
	float angle = 0;
	//	�ݒ��񂩂�4���_���쐬
	VERTEX2D VertexList[4] =
	{
	{ DirectX::XMFLOAT3(pos.x,         pos.y         ,0),XMFLOAT2(texture_pos.x,                   texture_pos.y)                 , color},
	{ DirectX::XMFLOAT3(pos.x + size.x,pos.y         ,0),XMFLOAT2(texture_pos.x + texture_size.x,  texture_pos.y)                 , color},
	{ DirectX::XMFLOAT3(pos.x,         pos.y + size.y,0),XMFLOAT2(texture_pos.x,                   texture_pos.y + texture_size.y), color},
	{ DirectX::XMFLOAT3(pos.x + size.x, pos.y + size.y, 0), XMFLOAT2(texture_pos.x + texture_size.x, texture_pos.y + texture_size.y), color},
	};
	constexpr	int	VertexLength = sizeof(VertexList) / sizeof(VertexList[0]);
	//
	//	��]
	{
		//	��]���S�܂Œ��_���ړ�������
		float	CenterWidth = pos.x + size.x * 0.5f;
		float	CenterHeight = pos.y + size.y * 0.5f;
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			VertexList[ii].pos.x -= CenterWidth;
			VertexList[ii].pos.y -= CenterHeight;
		}
	
		//	�w��̊p�x����]������
		float	RadianAngle = angle;
		float	Cos = cosf(RadianAngle);
		float	Sin = sinf(RadianAngle);
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			float rx = VertexList[ii].pos.x;
			float ry = VertexList[ii].pos.y;
	
			VertexList[ii].pos.x = Cos * rx - Sin * ry;
			VertexList[ii].pos.y = Sin * rx + Cos * ry;
		}
	
		//	��]���S�܂Œ��_���ړ�������
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			VertexList[ii].pos.x += CenterWidth;
			VertexList[ii].pos.y += CenterHeight;
		}
	}
	
	//	���K���f�o�C�X���W�n�ɕϊ�����
	for (int ii = 0; ii < VertexLength; ++ii)
	{
		VertexList[ii].pos.x = -1.0f + 2.0f * VertexList[ii].pos.x / ScreenWidth;
		VertexList[ii].pos.y = +1.0f - 2.0f * VertexList[ii].pos.y / ScreenHeight;
	}
	//�F�@�ϊ�
	for (int ii = 0; ii < VertexLength; ++ii)
	{
		//VertexList[ii].tex.x /= tex->GetWidth();
		//VertexList[ii].tex.y /= tex->GetHeight();
		VertexList[ii].tex.x /= ScreenWidth;
		VertexList[ii].tex.y /= ScreenHeight;
	}
	ScreenTexture->Set(device,0);
	
	//	���_�����X�V���܂�
	D3D11_MAPPED_SUBRESOURCE	MappedSubResource;
	hr = device->Map(m_vertexBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&MappedSubResource);
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	if (SUCCEEDED(hr))
	{
		VERTEX2D* pVertices = static_cast<VERTEX2D*>(MappedSubResource.pData);
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			pVertices[ii].pos.x = VertexList[ii].pos.x;
			pVertices[ii].pos.y = VertexList[ii].pos.y;
			pVertices[ii].pos.z = 0.0f;
			pVertices[ii].color = color;
			pVertices[ii].tex = VertexList[ii].tex;
		}
	
		device->Unmap(m_vertexBuffer.Get(), 0);
	}
	
	UINT strides = sizeof(VERTEX2D);
	UINT offset = 0;
	
	//device->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());
	device->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_MIRROR].GetAddressOf());
	
	
	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	
	
	
	
	
	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &strides, &offset);
	
	device->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
	
	device->Draw(4, 0);
	
	m_shader->Inactivate(device);
}


void Lib_TargetScreenShader::ScreenRender(ID3D11DeviceContext* device)
{
 //�����_�[�^�[�Q�b�g
  //ID3D11RenderTargetView* rtv = TK_Lib::Lib_Graphics::Get_targetview();
  ID3D11RenderTargetView* rtv = ScreenTexture->GetRenderTargetView();
  ID3D11DepthStencilView* dsv = TK_Lib::Lib_Graphics::Get_DepthStencilView();
  //�����_�[�^�[�Q�b�g�𑗂荞��
  device->OMSetRenderTargets(1, &rtv, nullptr);
 // ��ʃN���A
 float ClearColor[4] = { 0, 0, 0, 0 };
  //�S�Ẵ����_�[�^�[�Q�b�g����ʃN���A����
  device->ClearRenderTargetView(rtv, ClearColor);
  //�S�Ẵ����_�[�^�[�Q�b�g�̐[�x�����N���A����
 // device->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

//�X�N���[�����e�N�X�`���𑗂�
ID3D11ShaderResourceView* srv = TK_Lib::Lib_Graphics::Get_ShaderResourceView();
device->PSSetShaderResources(0, 1, &srv);

D3D11_VIEWPORT	Viewport;//Windows�̐ݒ�̎���
UINT			ViewportCount = 1;//Window�̐�

//tex->Set(device, 0);


device->RSGetViewports(&ViewportCount, &Viewport);
float	ScreenWidth = Viewport.Width;
float	ScreenHeight = Viewport.Height;

TK_Lib::Draw::Sprite(nullptr, VECTOR2{ 0, 0 }, VECTOR2{ ScreenWidth, ScreenHeight }, VECTOR4{ 0,0,ScreenWidth,ScreenHeight }, 0, { 1,1,1,1 } );
   
rtv = TK_Lib::Lib_Graphics::Get_targetview();
dsv = TK_Lib::Lib_Graphics::Get_DepthStencilView();
//�����_�[�^�[�Q�b�g�𑗂荞��
device->OMSetRenderTargets(1, &rtv, nullptr);
//�S�Ẵ����_�[�^�[�Q�b�g����ʃN���A����
device->ClearRenderTargetView(rtv, ClearColor);

//�X�N���[�����e�N�X�`���𑗂�
//ID3D11ShaderResourceView* srv = TK_Lib::Lib_Graphics::Get_ShaderResourceView();

TK_Lib::Draw::Sprite(ScreenTexture.get(), VECTOR2{ 0, 0 }, VECTOR2{ ScreenWidth, ScreenHeight }, VECTOR4{ 0,0,ScreenWidth,ScreenHeight }, 0, { 1,1,1,1 });


}