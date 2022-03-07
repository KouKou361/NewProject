#include "Lib_Sprite.h"
#include "Lib_DirectXFunctions.h"
#include "Lib_Rasterizer.h"
#include "Lib_Sampler.h"

Sprite::Sprite(ID3D11Device* device)
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

	_ASSERT_EXPR(SUCCEEDED(hr), L"���_�o�b�t�@�̃G���[");

	//===================================================
	//�[�x�X�e���V���X�e�[�g�̍쐬
	//===================================================
	{

		D3D11_DEPTH_STENCIL_DESC DepthStencilDesc = {};
		//�[�x�e�X�g
		DepthStencilDesc.DepthEnable = FALSE;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;//�������݂��\�ɂ�����
		//�X�e���V���e�X�g�͕s�v
		DepthStencilDesc.StencilEnable = FALSE;

		hr = device->CreateDepthStencilState(&DepthStencilDesc, m_deptStencilState.GetAddressOf());

		_ASSERT_EXPR(SUCCEEDED(hr), L"�[�x�X�e���V���X�e�[�g�̃G���[");
	}

}

void Sprite::Font(ID3D11DeviceContext* _pDeviceContext,
	std::string text,//�\������������
	TextureResource* tex,
	VECTOR2 Pos,
	VECTOR2 Size,
	VECTOR4 color,
	float Space
) {

	
	float sw = static_cast<float> (tex->GetWidth() / 16);
	float sh = static_cast<float> (tex->GetHeight() / 16);
	for (auto c : text) {
		float sx = static_cast<float>( (c % 16) * sw);
		float sy = static_cast<float>( (c / 16) * sh);
		Render(_pDeviceContext, tex, Pos, Size, VECTOR4{ sx, sy, sw, sh }, 0, color);
		Pos.x += Space;
	}


}



void Sprite::Render(ID3D11DeviceContext* device, TextureResource* tex, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color)
{

	D3D11_VIEWPORT	Viewport;//Windows�̐ݒ�̎���
	UINT			ViewportCount = 1;//Window�̐�

	if (tex != nullptr)
	{
		tex->Set(device, 0);
	}



	device->RSGetViewports(&ViewportCount, &Viewport);
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;

	HRESULT hr = S_OK;

	//VECTOR2 texture_pos = { 0,0 };
	//VECTOR2 texture_size = { 1,1 };
	VECTOR2 texture_pos = { cut.x,cut.y };
	VECTOR2 texture_size = { cut.z,cut.w };
	//	�ݒ��񂩂�4���_���쐬
	VERTEX2D VertexList[4] =
	{
	{ DirectX::XMFLOAT3(pos.x,         pos.y         ,0),XMFLOAT2(texture_pos.x,                   texture_pos.y)                 , color},
	{ DirectX::XMFLOAT3(pos.x + size.x,pos.y         ,0),XMFLOAT2(texture_pos.x + texture_size.x,  texture_pos.y)                 , color},
	{ DirectX::XMFLOAT3(pos.x,         pos.y + size.y,0),XMFLOAT2(texture_pos.x,                   texture_pos.y + texture_size.y), color},
	{ DirectX::XMFLOAT3(pos.x + size.x,pos.y + size.y,0),XMFLOAT2(texture_pos.x + texture_size.x,  texture_pos.y + texture_size.y), color},
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
	if (tex == nullptr)
	{
		VertexList[0].tex.x = 0;
		VertexList[0].tex.y = 0;

		VertexList[1].tex.x = 1;
		VertexList[1].tex.y = 0;

		VertexList[2].tex.x = 0;
		VertexList[2].tex.y = 1;

		VertexList[3].tex.x = 1;
		VertexList[3].tex.y = 1;
	}
	else
	{
		//�F�@�ϊ�
		for (int ii = 0; ii < VertexLength; ++ii)
		{
			VertexList[ii].tex.x /= tex->GetWidth();
			VertexList[ii].tex.y /= tex->GetHeight();
		}

	}

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

	device->OMSetDepthStencilState(m_deptStencilState.Get(), 1);

	device->Draw(4, 0);

}