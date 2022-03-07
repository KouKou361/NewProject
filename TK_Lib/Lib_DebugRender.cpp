#include "Lib_DebugRender.h"
#include "Lib_DirectXFunctions.h"
#include "Delete.h"
#include "Lib_DepthStencil.h"


void Primitive_DebugRender::SetMaxVertex(u_int MaxVertex)
{
	vertices.resize(MaxVertex);
}
Primitive_DebugRender::Primitive_DebugRender(ID3D11Device* device, u_int MaxVertex)
{
	//===================
	//shader�̐ݒ�
	//====================
	m_shader = make_shared<ShaderResource>();
	m_shader->Create(device, "./Shader/Primitive2D_vs.cso", "./Shader/Primitive2D_ps.cso");

	HRESULT hr = S_OK;

	SetMaxVertex(MaxVertex);

	//���_�o�b�t�@
	{
		D3D11_BUFFER_DESC bufferdesc;
		ZeroMemory(&bufferdesc, sizeof(bufferdesc));
		bufferdesc.ByteWidth =static_cast<u_int>(sizeof(VERTEXDEBUG)* vertices.size());
		bufferdesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferdesc.MiscFlags = false;
		bufferdesc.StructureByteStride = false;

		D3D11_SUBRESOURCE_DATA subresource;
		ZeroMemory(&subresource, sizeof(subresource));
		subresource.pSysMem = vertices.data();
		subresource.SysMemPitch = false;
		subresource.SysMemSlicePitch = false;
		//���_�o�b�t�@�̍쐬
		hr = device->CreateBuffer(&bufferdesc, &subresource, m_vertexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			_ASSERT_EXPR(SUCCEEDED(hr), L"���_�o�b�t�@�̃G���[");
			return;
		}
	}

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

		hr = device->CreateDepthStencilState(&DepthStencilDesc, m_depthStencilState.GetAddressOf());
		if (FAILED(hr)) {
			_ASSERT_EXPR(SUCCEEDED(hr), L"�[�x�X�e���V���X�e�[�g�̃G���[");
			return;	//	�쐬�ł��Ȃ������̂ŏ��������s
		}
	}
}
void Primitive_DebugRender::SetVertex(ID3D11DeviceContext* device, VERTEXDEBUG* vertex, u_int vertexSize)
{
	HRESULT hr = S_OK;
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
		VERTEXDEBUG* pVertices = static_cast<VERTEXDEBUG*>(MappedSubResource.pData);
		for (u_int ii = 0; ii < vertexSize; ++ii)
		{
			pVertices[ii].pos.x = vertex[ii].pos.x;
			pVertices[ii].pos.y = vertex[ii].pos.y;
			pVertices[ii].pos.z = vertex[ii].pos.z;
			pVertices[ii].normal = vertex[ii].normal;
			pVertices[ii].tex = vertex[ii].tex;
			pVertices[ii].color = vertex[ii].color;
		}

		device->Unmap(m_vertexBuffer.Get(), 0);
	}
}


//�l�p�̕`���o�^����
void Primitive_DebugRender::DrawBox(VECTOR3 pos, VECTOR3 size, float angle, VECTOR4 color, bool fillFlg)
{
	//�f�[�^�ɓo�^����
	PrimitiveData *data=new PrimitiveData();
	data->pos = pos;
	data->pos2 = size;
	data->angle = angle;
	data->color = color;
	data->type = PrimitiveData::BOX;//�l�p�Ƃ��ēo�^����
	data->fill = fillFlg;
	primitiveDatas.emplace_back(data);
}
//�~�̕`���o�^����
void Primitive_DebugRender::DrawCircle(VECTOR3 pos, float radius, VECTOR4 color, bool fillFlg)
{
	//�f�[�^�ɓo�^����
	PrimitiveData* data = new PrimitiveData();
	data->pos = pos;
	data->radius = radius;
	data->color = color;
	data->type = PrimitiveData::CIRCLE;//�~�Ƃ��ēo�^����
	data->fill = fillFlg;
	primitiveDatas.emplace_back(data);
}
//���̕`���o�^����
void Primitive_DebugRender::DrawLine(VECTOR3 pos, VECTOR3 pos2, VECTOR4 color, bool fillFlg)
{
	//�f�[�^�ɓo�^����
	PrimitiveData* data = new PrimitiveData();
	data->pos = pos;
	data->pos2 = pos2;
	data->color = color;
	data->type = PrimitiveData::LINE;//���Ƃ��ēo�^����
	data->fill = fillFlg;
	primitiveDatas.emplace_back(data);
}

//�o�^���Ă���`��f�[�^���܂Ƃ߂ĕ`�悷��
void Primitive_DebugRender::AllDebugDraw(ID3D11DeviceContext* device)
{
	//�n��
	Begin(device);

	for (PrimitiveData* data : primitiveDatas)
	{
		//�^�C�v�ɕ����ĕ`�悵�Ă���
		switch (data->type)
		{
		case PrimitiveData::BOX:
			ScreenDrawBox(device, *data);
			break;
		case PrimitiveData::CIRCLE:
			ScreenDrawCircle(device,*data);
			break;
		case PrimitiveData::LINE:
			ScreenDrawLine(device, *data);
			break;

		}
	}
	//�I���
	End(device);
	Clear();
}
void Primitive_DebugRender::Clear()
{
	for (PrimitiveData* data : primitiveDatas)
	{
		DELETEPOINTER(data);
	}
	primitiveDatas.clear();
}

//�`��n��
void Primitive_DebugRender::Begin(ID3D11DeviceContext* device)
{
//	device->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
	//�f�v�X�X�e���V��
	device->OMSetDepthStencilState(DepthStencil::Instance().m_depthState[DepthStencil::DS_WRITE_FALSE].Get(), 1);
	m_shader->Activate(device);
}
//�`��I��
void Primitive_DebugRender::End(ID3D11DeviceContext* device)
{
	m_shader->Inactivate(device);
}
