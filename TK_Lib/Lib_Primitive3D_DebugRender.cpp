#include "Lib_DebugRender.h"
#include "Lib_Rasterizer.h"
#include "Lib_Sampler.h"
#include "Lib_DepthStencil.h"
Primitive3D_DebugRender::Primitive3D_DebugRender(ID3D11Device* device, u_int MaxVertex)
{

	m_shader = make_shared<ShaderResource>();
	m_shader->Create(device, "./Shader/Primitive3D_vs.cso", "./Shader/Primitive3D_ps.cso",ShaderResource::TYPELayout::TYPE_LayoutDebugSprite);

	SetMaxVertex(MaxVertex);

	//�l�p�̃C���f�b�N�X�̍쐬
	CreateIndexBox(device);
	//�~�̃C���f�b�N�X�̍쐬
	CreateIndexCircle(device, 15, 15);

	HRESULT hr = S_OK;
	//���_�o�b�t�@
	{
		D3D11_BUFFER_DESC vertexdesc;
		ZeroMemory(&vertexdesc, sizeof(vertexdesc));
		vertexdesc.ByteWidth = static_cast<UINT>(sizeof(VERTEXDEBUG) * vertices.size());
		vertexdesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//D3D11_CPU_ACCESS_WRITE
		vertexdesc.MiscFlags = false;
		vertexdesc.StructureByteStride = false;

		D3D11_SUBRESOURCE_DATA subresource;
		ZeroMemory(&subresource, sizeof(subresource));
		subresource.pSysMem = vertices.data();
		subresource.SysMemPitch = false;
		subresource.SysMemSlicePitch = false;
		//���_�o�b�t�@�̍쐬
		hr = device->CreateBuffer(&vertexdesc, &subresource, m_vertexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			assert(!"���_�o�b�t�@�̃G���[");
			return;
		}
	}

	
	//�R���X�^���g�o�b�t�@
	{
		D3D11_BUFFER_DESC constant_desc;
		ZeroMemory(&constant_desc, sizeof(constant_desc));
		constant_desc.ByteWidth = sizeof(ConstantBuffer);
		constant_desc.Usage = D3D11_USAGE_DEFAULT;
		constant_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constant_desc.CPUAccessFlags = false;//D3D11_CPU_ACCESS_WRITE
		constant_desc.MiscFlags = false;
		constant_desc.StructureByteStride = false;
		//���_�o�b�t�@�̍쐬
		hr = device->CreateBuffer(&constant_desc, nullptr, m_constantBuffer.GetAddressOf());
		if (FAILED(hr))
		{

			assert(!"�R���X�^���g�o�b�t�@�̃G���[");
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
			assert(!"�[�x�X�e���V���X�e�[�g�̃G���[");
			return;	//	�쐬�ł��Ȃ������̂ŏ��������s
		}
	}
}
//�l�p�̃C���f�b�N�X�̍쐬
void Primitive3D_DebugRender::CreateIndexBox(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	//�C���f�b�N�X�o�b�t�@�̍쐬

	u_int Indicies[] = {

		//�O��
		1,0,2,
		1,2,3,
		//���
		5,4,7,
		4,6,7,
		//���
		10,8,9,
		11,10,9,
		//����
		////����
		12,13,15,
		15,14,12,
		////�E
		19,17,16,
		16,18,19,
		////�E
		20,21,23,
		23,22,20,
		//1,5,3,
		//5,3,7,
		////��
		//0,4,6,
		//0,2,6,

	};
	u_int Index_count = (sizeof(Indicies)) / sizeof(Indicies[0]);

	//�C���f�b�N�X�o�b�t�@
	{
		D3D11_BUFFER_DESC index_desc;
		ZeroMemory(&index_desc, sizeof(index_desc));
		index_desc.ByteWidth = sizeof(Indicies);
		index_desc.Usage = D3D11_USAGE_DEFAULT;
		index_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_desc.CPUAccessFlags = false;
		index_desc.MiscFlags = false;
		index_desc.StructureByteStride = false;

		D3D11_SUBRESOURCE_DATA subresource;
		ZeroMemory(&subresource, sizeof(subresource));
		subresource.pSysMem = Indicies;
		subresource.SysMemPitch = false;
		subresource.SysMemSlicePitch = false;
		//���_�o�b�t�@�̍쐬
		hr = device->CreateBuffer(&index_desc, &subresource, m_indexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			assert(!"�C���f�b�N�o�b�t�@�̃G���[");
			return;
		}

	}
}
//���̃C���f�b�N�̍쐬
void Primitive3D_DebugRender::CreateIndexCircle(ID3D11Device* device,int slice, int stacks)
{
	HRESULT hr = S_OK;
	circle_stacks = stacks;
	circle_slice = slice;

	// �C���f�b�N�X��
	circle_Indices_num = stacks * slice * 2 * 3;
	// �C���f�b�N�X�ݒ�
	std::unique_ptr<u_int[]> indices = std::make_unique<u_int[]>(circle_Indices_num);
	//	u_int* indices = new u_int[Circle_Indices_num];
	for (int y = 0; y < stacks; y++) {
		for (int x = 0; x < slice; x++) {
			int face = (y * slice + x);
			int vertices_index = y * (slice + 1) + x;
			indices[face * 6] = vertices_index + 1;
			indices[face * 6 + 1] = vertices_index;
			indices[face * 6 + 2] = vertices_index + (slice + 1);

			indices[face * 6 + 3] = vertices_index + 1;
			indices[face * 6 + 4] = vertices_index + (slice + 1);
			indices[face * 6 + 5] = vertices_index + (slice + 1) + 1;
		}
	}

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(u_int) * circle_Indices_num;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = indices.get();
		hr = device->CreateBuffer(&bd, &InitData, m_CircleIndexBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			assert(!"�C���f�b�N�o�b�t�@�̃G���[");
			return;
		}
	}
}
void Primitive3D_DebugRender::SetConstantBuffer(ID3D11DeviceContext* device, const ConstantBuffer &data)
{
	//�萔�o�b�t�@�̍X�V
	device->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &data, 0, 0);
	//�萔�o�b�t�@�𒸓_�V�F�[�_�[�ɑ���
	device->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
}

void Primitive3D_DebugRender::ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data)
{
	UINT	Stride = sizeof(VERTEXDEBUG);
	UINT	Offset = 0;

	//������₷�����邽�߂ɕʂ̕ϐ����ɂ���
	const VECTOR3 pos =  data.pos ;
	const VECTOR3 pos2 = data.pos2;
	const VECTOR4 color = data.color;

	
	VERTEXDEBUG vertices2[] = {
		//�O
		{ DirectX::XMFLOAT3(pos.x, pos2.y,pos.z), DirectX::XMFLOAT3(0,0,-1),DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos2.y,pos.z), DirectX::XMFLOAT3(0,0,-1),DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos.x, pos.y, pos.z), DirectX::XMFLOAT3(0,0,-1),DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos.y, pos.z), DirectX::XMFLOAT3(0,0,-1),DirectX::XMFLOAT2(0, 0),color},
		//��							  								 
		{ DirectX::XMFLOAT3(pos.x, pos2.y,pos2.z),DirectX::XMFLOAT3(0,1,0) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos2.y,pos2.z),DirectX::XMFLOAT3(0,1,0) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos.x, pos2.y,pos.z), DirectX::XMFLOAT3(0,1,0) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos2.y,pos.z), DirectX::XMFLOAT3(0,1,0) ,DirectX::XMFLOAT2(0, 0),color},
		//��							  								  
		{ DirectX::XMFLOAT3(pos.x, pos2.y,pos2.z),DirectX::XMFLOAT3(0,0,1) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos2.y,pos2.z),DirectX::XMFLOAT3(0,0,1) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos.x, pos.y, pos2.z),DirectX::XMFLOAT3(0,0,1) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos.y, pos2.z),DirectX::XMFLOAT3(0,0,1) ,DirectX::XMFLOAT2(0, 0),color},
		//��														
		{ DirectX::XMFLOAT3(pos.x, pos.y, pos2.z),DirectX::XMFLOAT3(0,-1,0),DirectX::XMFLOAT2(0, 0),color },
		{ DirectX::XMFLOAT3(pos2.x,pos.y, pos2.z),DirectX::XMFLOAT3(0,-1,0),DirectX::XMFLOAT2(0, 0),color },
		{ DirectX::XMFLOAT3(pos.x, pos.y, pos.z), DirectX::XMFLOAT3(0,-1,0),DirectX::XMFLOAT2(0, 0),color },
		{ DirectX::XMFLOAT3(pos2.x,pos.y, pos.z), DirectX::XMFLOAT3(0,-1,0),DirectX::XMFLOAT2(0, 0),color },
		//�E														
		{ DirectX::XMFLOAT3(pos2.x,pos2.y,pos2.z),DirectX::XMFLOAT3(1,0,0) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos.y, pos2.z),DirectX::XMFLOAT3(1,0,0) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos2.y,pos.z), DirectX::XMFLOAT3(1,0,0) ,DirectX::XMFLOAT2(0, 0),color},
		{ DirectX::XMFLOAT3(pos2.x,pos.y, pos.z), DirectX::XMFLOAT3(1,0,0) ,DirectX::XMFLOAT2(0, 0),color},
		//��													
		{ DirectX::XMFLOAT3(pos.x,pos2.y,pos2.z),DirectX::XMFLOAT3(-1,0,0),DirectX::XMFLOAT2(0, 0),color },
		{ DirectX::XMFLOAT3(pos.x,pos.y, pos2.z),DirectX::XMFLOAT3(-1,0,0),DirectX::XMFLOAT2(0, 0),color },
		{ DirectX::XMFLOAT3(pos.x,pos2.y,pos.z) ,DirectX::XMFLOAT3(-1,0,0),DirectX::XMFLOAT2(0, 0),color },
		{ DirectX::XMFLOAT3(pos.x,pos.y, pos.z) ,DirectX::XMFLOAT3(-1,0,0),DirectX::XMFLOAT2(0, 0),color },
	};

	D3D11_MAPPED_SUBRESOURCE subresource;
	device->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
	memcpy(subresource.pData, vertices2, sizeof(VERTEXDEBUG) * ARRAYSIZE(vertices2));
	device->Unmap(m_vertexBuffer.Get(), 0);


	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &Stride, &Offset);

	device->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);//index�o�b�t�@�̐ݒ��`����

	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);




	if (data.fill)device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_FALSE].Get());
	else device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerLine_FALSE].Get());


	//_pImmediateContext->Draw(4, 0);
	device->DrawIndexed(36, 0, 0);
}
//�~�̕`��
void Primitive3D_DebugRender::ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data)
{
	//������₷�����邽�߂ɕʂ̕ϐ����ɂ���
	const VECTOR3 pos = data.pos;
	const VECTOR4 color = data.color;
	float radius = data.radius;

	radius *= 2;
	//���_�̐�

	u_int Circle_Vertex_num = (circle_slice + 1) * (circle_stacks + 1);
	if (Circle_Vertex_num >= vertices.size())	assert(!" Primitive3D::circle�� slice,stacks�����������܂�");
	if (!m_CircleIndexBuffer.Get())	assert(!" m_circle_indexbuffer�ɒl�������Ă��܂���");
	// ���_��`
	std::unique_ptr<VERTEXDEBUG[]> indices = std::make_unique<VERTEXDEBUG[]>(Circle_Vertex_num);
	VERTEXDEBUG* vertices = &indices.get()[0];
	for (u_int y = 0; y < circle_stacks + 1; y++) {
		for (u_int x = 0; x < circle_slice + 1; x++) {
			int index = y * (circle_slice + 1) + x;
			float h = 0.5f * cosf(y * XM_PI / circle_stacks);
			float w = 0.5f * sinf(y * XM_PI / circle_stacks);
			float rad_slices = x * XM_PI * 2.0f / circle_slice;

			vertices[index].pos.x = w * sinf(rad_slices) * radius + pos.x;
			vertices[index].pos.y = h * radius + pos.y;
			vertices[index].pos.z = w * cosf(rad_slices) * radius + pos.z;

			vertices[index].normal.x = vertices[index].pos.x * 2.0f;
			vertices[index].normal.y = vertices[index].pos.y * 2.0f;
			vertices[index].normal.z = vertices[index].pos.z * 2.0f;

			vertices[index].color = color;
		}
	}
	D3D11_MAPPED_SUBRESOURCE subresource;
	device->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
	memcpy(subresource.pData, vertices, sizeof(VERTEXDEBUG) * Circle_Vertex_num);
	device->Unmap(m_vertexBuffer.Get(), 0);


	UINT Stride = sizeof(VERTEXDEBUG);
	UINT Offset = 0;

	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &Stride, &Offset);

	device->IASetIndexBuffer(m_CircleIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);//index�o�b�t�@�̐ݒ��`����


	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (data.fill)device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_FALSE].Get());
	else device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerLine_FALSE].Get());



	device->DrawIndexed(circle_Indices_num, 0, 0);



}
//���̕`��
void Primitive3D_DebugRender::ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data)
{
	D3D11_VIEWPORT	Viewport;//Windows�̐ݒ�̎���
	UINT			ViewportCount = 1;//Window�̐�

	
	device->RSGetViewports(&ViewportCount, &Viewport);
	float	ScreenWidth = Viewport.Width;
	float	ScreenHeight = Viewport.Height;

	//������₷�����邽�߂ɕʂ̕ϐ����ɂ���
	const VECTOR3 pos = data.pos;
	const VECTOR3 pos2 = data.pos2;
	const VECTOR4 color = data.color;

	HRESULT hr = S_OK;
	//	�ݒ��񂩂�4���_���쐬
	VERTEXDEBUG VertexList[2] =
	{
	{ DirectX::XMFLOAT3(pos. x,   pos.y,  pos.z),XMFLOAT3(0.0f, 0.0f, 0.0f),XMFLOAT2(0,0), color},
	{ DirectX::XMFLOAT3(pos2.x,   pos2.y, pos2.z),XMFLOAT3(0.0f, 0.0f, 0.0f),XMFLOAT2(1,1), color},
	};
	constexpr	int	VertexLength = sizeof(VertexList) / sizeof(VertexList[0]);
	//���_�����Z�b�g������
	SetVertex(device, &VertexList[0], VertexLength);

	UINT Stride = sizeof(VERTEXDEBUG);
	UINT Offset = 0;

	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &Stride, &Offset);

	device->IASetIndexBuffer(m_CircleIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);//index�o�b�t�@�̐ݒ��`����


	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	if (data.fill)device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_FALSE].Get());
	else device->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerLine_FALSE].Get());


	device->DrawIndexed(2, 0, 0);
}

