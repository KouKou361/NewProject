#include "Lib_CascadeShader.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
#include "Lib.h"
#include "Lib_LightManager.h"
#include "Lib_Gauss.h"
#include "Lib_CameraLib.h"
//====================
//������
//====================
Lib_CascadeShader::Lib_CascadeShader(ID3D11Device* device)
{
	HRESULT hr = S_OK;
	//�J�X�P�[�h�V���h�E�V�F�[�_�[
	m_shader = make_unique<ShaderResource>();
	m_shader->Create(device, "./Shader/Cascade_vs.cso", "./Shader/Cascade_ps.cso", ShaderResource::TYPELayout::TYPE_LayoutModel);
	//�J�X�P�[�h�V���h�E�̃e�N�X�`���𐶐�����V�F�[�_�[
	shadowShader = make_unique<ShaderResource>();
	shadowShader->Create(device, "./Shader/ToShadowMap_vs.cso", "./Shader/ToShadowMap_ps.cso", ShaderResource::TYPELayout::TYPE_LayoutModel);
	//shadowShader->Create(device, "./Shader/NoLight_vs.cso", "./Shader/NoLight_ps.cso", ShaderResource::TYPELayout::TYPE_LayoutModel);

	//�J�X�P�[�h�V���h�E�e�N�X�`���쐬
	for (int i = 0; i < NUM_SHADOW_MAP; i++)
	{
		shadow_Texture[i] = std::make_shared<TextureResource>();
		shadow_Texture[i]->Create(device, shadowSize[i].x, shadowSize[i].y, DXGI_FORMAT_R32G32_FLOAT);
		shadow_Texture[i]->CreateDepth(device, shadowSize[i].x, shadowSize[i].y, DXGI_FORMAT_R32G32_FLOAT);

		Gauss_Texture[i] = std::make_shared<TextureResource>();
		Gauss_Texture[i]->Create(device, shadowSize[i].x, shadowSize[i].y, DXGI_FORMAT_R32G32_FLOAT);
		Gauss_Texture[i]->CreateDepth(device, shadowSize[i].x, shadowSize[i].y, DXGI_FORMAT_R32G32_FLOAT);
	}

//	depth_Texture = std::make_shared<TextureResource>();
//	depth_Texture->CreateDepth(device, 2048, 2048, DXGI_FORMAT_R32G32_FLOAT);

	//GaussTexture = make_unique<TextureResource>();
	//GaussTexture->Create(device, 1500, 1500, DXGI_FORMAT_R32G32_FLOAT);
	//GaussTexture->CreateDepth(device, 1500, 1500, DXGI_FORMAT_R32G32_FLOAT);

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
		desc.ByteWidth = sizeof(CreateShadowConstant);
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
//�N���b�v�s��
XMFLOAT4X4 Lib_CascadeShader::CreateClop(const int Shadow_Index,const CameraLib& ModelView, const CameraLib& LightView, const XMMATRIX	viewMatrix,const XMMATRIX projectionMatrix)
{


	// �J��������p�����[�^�[���擾
	DirectX::XMVECTOR	viewFront, viewRight, viewUp, viewPos;
	{
		DirectX::XMMATRIX   View = DirectX::XMLoadFloat4x4(&ModelView.GetView());
		DirectX::XMMATRIX	matrix = DirectX::XMMatrixInverse(nullptr, View);
		viewRight = DirectX::XMVector3Normalize(matrix.r[0]);
		viewUp = DirectX::XMVector3Normalize(matrix.r[1]);
		viewFront = DirectX::XMVector3Normalize(matrix.r[2]);
		viewPos = matrix.r[3];
	}
	//	�V���h�E�}�b�v�̕����G���A��`
	float	splitAreaTable[] =
	{
		ModelView.GetNear(),	//	�J�����̃j�A�N���b�v
		shadowArea[0],
		shadowArea[1],
		shadowArea[2]
	};

	float	nearDepth = splitAreaTable[Shadow_Index + 0];
	float	farDepth = splitAreaTable[Shadow_Index + 1];
	//	�G���A�����鎋�����8���_���Z�o����
	DirectX::XMVECTOR	vertex[8];
	{
		//	�G���A�̋ߕ��ʂ̒��S����̏�ʂ܂ł̋��������߂�
		float	nearY = tanf(ModelView.GetFor() * 0.5f) * nearDepth;
		//	�G���A�̋ߕ��ʂ̒��S����̉E�ʂ܂ł̋��������߂�
		float	nearX = nearY * ModelView.GetAspext();
		//	�G���A�̉����ʂ̒��S����̏�ʂ܂ł̋��������߂�
		float	farY = tanf(ModelView.GetFor() * 0.5f) * farDepth;
		//	�G���A�̉����ʂ̒��S����̉E�ʂ܂ł̋��������߂�
		float	farX = farY * ModelView.GetAspext();

		//	�G���A�̋ߕ��ʂ̒��S���W�����߂�
		DirectX::XMVECTOR	nearPosition = DirectX::XMVectorAdd(viewPos, DirectX::XMVectorScale(viewFront, nearDepth));
		//	�G���A�̉����ʂ̒��S���W�����߂�
		DirectX::XMVECTOR	farPosition = DirectX::XMVectorAdd(viewPos, DirectX::XMVectorScale(viewFront, farDepth));

		//	8���_�����߂�
		{
			// �ߕ��ʂ̉E��
			vertex[0] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, nearY), DirectX::XMVectorScale(viewRight, nearX)));
			// �ߕ��ʂ̍���
			vertex[1] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, nearY), DirectX::XMVectorScale(viewRight, -nearX)));
			// �ߕ��ʂ̉E��
			vertex[2] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -nearY), DirectX::XMVectorScale(viewRight, nearX)));
			// �ߕ��ʂ̍���
			vertex[3] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -nearY), DirectX::XMVectorScale(viewRight, -nearX)));
			// �����ʂ̉E��
			vertex[4] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, farY), DirectX::XMVectorScale(viewRight, farX)));
			// �����ʂ̍���
			vertex[5] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, farY), DirectX::XMVectorScale(viewRight, -farX)));
			// �����ʂ̉E��
			vertex[6] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -farY), DirectX::XMVectorScale(viewRight, farX)));
			// �����ʂ̍���
			vertex[7] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -farY), DirectX::XMVectorScale(viewRight, -farX)));
		}
	}

	//	8���_�����C�g�r���[�v���W�F�N�V������Ԃɕϊ����āA�ő�l�A�ŏ��l�����߂�
	DirectX::XMFLOAT3	vertexMin(FLT_MAX, FLT_MAX, FLT_MAX), vertexMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for (auto& it : vertex)
	{
		DirectX::XMFLOAT3	p;
		DirectX::XMStoreFloat3(&p, DirectX::XMVector3TransformCoord(it, viewMatrix * projectionMatrix));

		vertexMin.x = min(p.x, vertexMin.x);
		vertexMin.y = min(p.y, vertexMin.y);
		vertexMax.x = max(p.x, vertexMax.x);
		vertexMax.y = max(p.y, vertexMax.y);
	}

	//	�N���b�v�s������߂�
	DirectX::XMFLOAT4X4	ClopMatrix;
	DirectX::XMMATRIX	clopMatrix = DirectX::XMMatrixIdentity();
	{
		float	xScale = 2.0f / (vertexMax.x - vertexMin.x);
		float	yScale = 2.0f / (vertexMax.y - vertexMin.y);
		float	xOffset = -0.5f * (vertexMax.x + vertexMin.x) * xScale;
		float	yOffset = -0.5f * (vertexMax.y + vertexMin.y) * yScale;

		DirectX::XMStoreFloat4x4(&ClopMatrix, clopMatrix);
		ClopMatrix._11 = xScale;
		ClopMatrix._22 = yScale;
		ClopMatrix._41 = xOffset;
		ClopMatrix._42 = yOffset;
	}

	return ClopMatrix;
}

//�e�e�N�X�`���̐���
void Lib_CascadeShader::CreateShadowTexture(ID3D11DeviceContext* context, const CameraLib& ModelView, const CameraLib& LightView,const vector<ModelResource*> *list)
{
	//�e�쐬�V�F�[�_�[�̓K��
	shadowShader->Activate(context);

	

	// ���C�g�r���[�v���W�F�N�V�����s����Z�o
	DirectX::XMMATRIX	viewMatrix, projectionMatrix;
	{
		// ���C�g�ʒu����̃r���[�̐ݒ�
		VECTOR3 t(0, 0, 0);
		VECTOR3 p;

		t.x = ModelView.GetTarget().x;
		t.y = ModelView.GetTarget().y;
		t.z = ModelView.GetTarget().z;

		//p.x = LightView.GetPos().x;
		//p.y = LightView.GetPos().y;
		//p.z = LightView.GetPos().z;

		p.x = t.x - LightView.GetFront().x * 500.0f;
		p.y = t.y - LightView.GetFront().y * 500.0f;
		p.z = t.z - LightView.GetFront().z * 500.0f;

		// ���C�g�p�̃J����
		CameraLib v;
		v.SetLookAt(p, t, VECTOR3(0, 1, 0));
		v.SetOrthongraphic(10000, 10000, 0.01f, 2000.0f);// ���s���e
		viewMatrix = XMLoadFloat4x4(&v.GetView());
		projectionMatrix = XMLoadFloat4x4(&v.GetProjection());
	}


	Begin(context);

	//�e�̌���
	XMFLOAT4 LightDirection;
	LightDirection.x = LightView.GetFront().x;
	LightDirection.y = LightView.GetFront().y;
	LightDirection.z = LightView.GetFront().z;
	LightDirection.w = 1.0;

	//WARNING����Ƃ��Ă����ɒu��
	for (int i = 0; i < NUM_SHADOW_MAP; i++)
	{
		shadow_Texture[i]->Empty(context, i + 1);
	}

	//�f�v�X�X�e���V���X�e�[�g�ݒ�
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);

	context->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_Shadow_BORDER].GetAddressOf());
	context->PSSetSamplers(1, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_Shadow_BORDER].GetAddressOf());

	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerShader].Get());
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�@�V���h�E�}�b�v�̍쐻
	for (int Shadow_Index = 0; Shadow_Index < NUM_SHADOW_MAP; Shadow_Index++)
	{
		//�N���b�v�s��̍쐬
		XMMATRIX clopMatrix;
		{
			XMFLOAT4X4 clop;
			clop = CreateClop(Shadow_Index, ModelView, LightView, viewMatrix, projectionMatrix);
			clopMatrix = XMLoadFloat4x4(&clop);
		}


		//���C�g�r���[�v���W�F�N�V�����s����v�Z
		{
			DirectX::XMStoreFloat4x4(&shadowconstant.LightVP[Shadow_Index], viewMatrix * projectionMatrix * clopMatrix);
			shadowconstant.ShadowColor = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
		}

		//�R���X�^���g�o�b�t�@�̐ݒ�
		{
			
			XMFLOAT4X4 VPC;
			XMStoreFloat4x4(&VPC, viewMatrix * (projectionMatrix * clopMatrix));
			SetShadowConstant(context, LightDirection, VPC);
		}

		// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���̐ݒ�
		{
			ID3D11RenderTargetView* rtv[1] = { shadow_Texture[Shadow_Index]->GetRenderTargetView() };
			ID3D11DepthStencilView* dsv = shadow_Texture[Shadow_Index]->GetDepthStencilView();

			float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			context->ClearRenderTargetView(rtv[0], clearColor);
			context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
			context->OMSetRenderTargets(1, rtv, dsv);
			// �r���[�|�[�g�̐ݒ�
			TK_Lib::Screen::SetViewPort(VECTOR2{ shadowSize[Shadow_Index].x, shadowSize[Shadow_Index].y });
		}
	
		CascadeShadowRender(context, list,ShadowType::Drawshadow);
	}



}
void Lib_CascadeShader::CreateShadowEnd(ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	//�ڂ�������
	for (int i = 0; i < NUM_SHADOW_MAP; i++)
	{
		// �r���[�|�[�g�̐ݒ�
		TK_Lib::Screen::SetViewPort(VECTOR2{ shadowSize[i].x, shadowSize[i].y });
		CreateGauss(context, shadow_Texture[i].get(), Gauss_Texture[i].get());
	}

}

//�J�X�P�[�h�V���h�E�}�b�v�̐���
void Lib_CascadeShader::CascadeShadowBegin(ID3D11DeviceContext* context, const CameraLib& ModelView, const CameraLib& LightView)
{
	static bool flg = true;
	//ImGui::Begin(u8"�J�X�P�[�h");
	//ImGui::Checkbox("Gauss", &flg);
	//ImGui::End();
	TK_Lib::Screen::Clear();

	if (flg == false)
	{
		shadow_Texture[0]->Set(context, 1);
		shadow_Texture[1]->Set(context, 2);
		shadow_Texture[2]->Set(context, 3);
	}
	else
	{
		Gauss_Texture[0]->Set(context, 1);
		Gauss_Texture[1]->Set(context, 2);
		Gauss_Texture[2]->Set(context, 3);
	}

	XMMATRIX V;
	XMMATRIX P;

	V = XMLoadFloat4x4(&ModelView.GetView());
	P = XMLoadFloat4x4(&ModelView.GetProjection());

	//�R���X�^���g�o�b�t�@�̐ݒ�
	XMFLOAT4X4 VPC;
	//XMStoreFloat4x4(&VPC, viewMatrix* projectionMatrix);
	XMStoreFloat4x4(&VPC, V * P);
	XMFLOAT4 LightDirection;
	LightDirection.x = LightView.GetFront().x;
	LightDirection.y = LightView.GetFront().y;
	LightDirection.z = LightView.GetFront().z;
	LightDirection.w = 1.0;

	SetShadowConstant(context, LightDirection, VPC);


	SetShadowConstan2(context,
		DirectX::XMFLOAT4{ 0.6f,0.6f, 0.6f, 1.0 },
		LightDirection,
		DirectX::XMFLOAT4{ 0.6,0.6, 0.6, 1.0 });
	Begin(context);

	context->OMSetBlendState(BlendState::Instance().GetBlendState(Bland_state::BS_ALPHA), nullptr, 0xffffffff);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_FALSE].Get());
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

}

void Lib_CascadeShader::CascadeShadowEnd(ID3D11DeviceContext* context)
{
	for (int i = 0; i < NUM_SHADOW_MAP; i++)
	{
		TK_Lib::Draw::Sprite(shadow_Texture[i].get(), VECTOR2(0, 200 * i + 5 * i), VECTOR2(200, 200), VECTOR4(0, 0, shadow_Texture[i]->GetWidth(), shadow_Texture[i]->GetHeight()), 0.0f, VECTOR4(1, 1, 1, 1));
	}

	for (int i = 0; i < NUM_SHADOW_MAP; i++)
	{
		TK_Lib::Draw::Sprite(Gauss_Texture[i].get(), VECTOR2(1720, 200 * i + 5 * i), VECTOR2(200, 200), VECTOR4(0, 0, shadow_Texture[i]->GetWidth(), shadow_Texture[i]->GetHeight()), 0.0f, VECTOR4(1, 1, 1, 1));
	}

	shadowShader->Inactivate(context);
	shadow_Texture[0]->Empty(context, 1);
	shadow_Texture[1]->Empty(context, 2);
	shadow_Texture[2]->Empty(context, 3);
}
//
////�e�̐���
//void Lib_CascadeShader::ShadowBegin(ID3D11DeviceContext* context, const CameraLib& ModelView,
//	const CameraLib& LightView, vector<ModelResource*> list)
//{
//
//	shadowShader->Activate(context);
//	// �J��������p�����[�^�[���擾
//	DirectX::XMVECTOR	viewFront, viewRight, viewUp, viewPos;
//	{
//		DirectX::XMMATRIX   View = DirectX::XMLoadFloat4x4(&ModelView.GetView());
//		DirectX::XMMATRIX	matrix = DirectX::XMMatrixInverse(nullptr, View);
//		viewRight = DirectX::XMVector3Normalize(matrix.r[0]);
//		viewUp = DirectX::XMVector3Normalize(matrix.r[1]);
//		viewFront = DirectX::XMVector3Normalize(matrix.r[2]);
//		viewPos = matrix.r[3];
//	}
//
//	// ���C�g�r���[�v���W�F�N�V�����s����Z�o
//	DirectX::XMMATRIX	viewMatrix, projectionMatrix;
//	{
//		// ���C�g�ʒu����̃r���[�̐ݒ�
//		VECTOR3 t(0, 0, 0);
//		VECTOR3 p;
//
//		t.x = ModelView.GetTarget().x;
//		t.y = ModelView.GetTarget().y;
//		t.z = ModelView.GetTarget().z;
//		
//		//p.x = LightView.GetPos().x;
//		//p.y = LightView.GetPos().y;
//		//p.z = LightView.GetPos().z;
//
//		p.x = t.x - LightView.GetFront().x * 1000.0f;
//		p.y = t.y - LightView.GetFront().y * 1000.0f;
//		p.z = t.z - LightView.GetFront().z * 1000.0f;
//
//		// ���C�g�p�̃J����
//		CameraLib v;
//		v.SetLookAt(p, t, VECTOR3(0, 1, 0));
//		v.SetOrthongraphic(10000, 10000, 0.01f, 2000.0f);// ���s���e
//		viewMatrix = XMLoadFloat4x4(&v.GetView());
//		projectionMatrix = XMLoadFloat4x4(&v.GetProjection());
//	}
//	//	�V���h�E�}�b�v�̕����G���A��`
//	float	splitAreaTable[] =
//	{
//		ModelView.GetNear(),	//	�J�����̃j�A�N���b�v
//		shadowArea[0],
//		shadowArea[1],
//		shadowArea[2]
//	};
//
//	
//
//
//	//�@�V���h�E�}�b�v�̍쐻
//	for (int Shadow_Index = 0; Shadow_Index < 3; Shadow_Index++)
//	{
//		float	nearDepth = splitAreaTable[Shadow_Index + 0];
//		float	farDepth = splitAreaTable[Shadow_Index + 1];
//
//		// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���̐ݒ�
//		ID3D11RenderTargetView* rtv[1] = { shadow_Texture[Shadow_Index]->GetRenderTargetView() };
//		ID3D11DepthStencilView* dsv = depth_Texture->GetDepthStencilView();
//		// ��ʃN���A
//		context->OMSetRenderTargets(1, rtv, dsv);
//		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
//		context->ClearRenderTargetView(rtv[0], clearColor);
//		context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//		// �r���[�|�[�g�̐ݒ�
//		TK_Lib::Screen::SetViewPort(VECTOR2{ shadowSize[Shadow_Index].x, shadowSize[Shadow_Index].y });
//
//		//	�G���A�����鎋�����8���_���Z�o����
//		DirectX::XMVECTOR	vertex[8];
//		{
//			//	�G���A�̋ߕ��ʂ̒��S����̏�ʂ܂ł̋��������߂�
//			float	nearY = tanf(ModelView.GetFor() * 0.5f) * nearDepth;
//			//	�G���A�̋ߕ��ʂ̒��S����̉E�ʂ܂ł̋��������߂�
//			float	nearX = nearY * ModelView.GetAspext();
//			//	�G���A�̉����ʂ̒��S����̏�ʂ܂ł̋��������߂�
//			float	farY = tanf(ModelView.GetFor() * 0.5f) * farDepth;
//			//	�G���A�̉����ʂ̒��S����̉E�ʂ܂ł̋��������߂�
//			float	farX = farY * ModelView.GetAspext();
//
//			//	�G���A�̋ߕ��ʂ̒��S���W�����߂�
//			DirectX::XMVECTOR	nearPosition = DirectX::XMVectorAdd(viewPos, DirectX::XMVectorScale(viewFront, nearDepth));
//			//	�G���A�̉����ʂ̒��S���W�����߂�
//			DirectX::XMVECTOR	farPosition = DirectX::XMVectorAdd(viewPos, DirectX::XMVectorScale(viewFront, farDepth));
//
//			//	8���_�����߂�
//			{
//				// �ߕ��ʂ̉E��
//				vertex[0] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, nearY), DirectX::XMVectorScale(viewRight, nearX)));
//				// �ߕ��ʂ̍���
//				vertex[1] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, nearY), DirectX::XMVectorScale(viewRight, -nearX)));
//				// �ߕ��ʂ̉E��
//				vertex[2] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -nearY), DirectX::XMVectorScale(viewRight, nearX)));
//				// �ߕ��ʂ̍���
//				vertex[3] = DirectX::XMVectorAdd(nearPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -nearY), DirectX::XMVectorScale(viewRight, -nearX)));
//				// �����ʂ̉E��
//				vertex[4] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, farY), DirectX::XMVectorScale(viewRight, farX)));
//				// �����ʂ̍���
//				vertex[5] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, farY), DirectX::XMVectorScale(viewRight, -farX)));
//				// �����ʂ̉E��
//				vertex[6] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -farY), DirectX::XMVectorScale(viewRight, farX)));
//				// �����ʂ̍���
//				vertex[7] = DirectX::XMVectorAdd(farPosition, DirectX::XMVectorAdd(DirectX::XMVectorScale(viewUp, -farY), DirectX::XMVectorScale(viewRight, -farX)));
//			}
//		}
//
//		//	8���_�����C�g�r���[�v���W�F�N�V������Ԃɕϊ����āA�ő�l�A�ŏ��l�����߂�
//		DirectX::XMFLOAT3	vertexMin(FLT_MAX, FLT_MAX, FLT_MAX), vertexMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
//		for (auto& it : vertex)
//		{
//			DirectX::XMFLOAT3	p;
//			DirectX::XMStoreFloat3(&p, DirectX::XMVector3TransformCoord(it, viewMatrix * projectionMatrix));
//
//			vertexMin.x = min(p.x, vertexMin.x);
//			vertexMin.y = min(p.y, vertexMin.y);
//			vertexMax.x = max(p.x, vertexMax.x);
//			vertexMax.y = max(p.y, vertexMax.y);
//		}
//
//		//	�N���b�v�s������߂�
//		DirectX::XMMATRIX	clopMatrix = DirectX::XMMatrixIdentity();
//		{
//			float	xScale = 2.0f / (vertexMax.x - vertexMin.x);
//			float	yScale = 2.0f / (vertexMax.y - vertexMin.y);
//			float	xOffset = -0.5f * (vertexMax.x + vertexMin.x) * xScale;
//			float	yOffset = -0.5f * (vertexMax.y + vertexMin.y) * yScale;
//			DirectX::XMFLOAT4X4	ClopMatrix;
//			DirectX::XMStoreFloat4x4(&ClopMatrix, clopMatrix);
//			ClopMatrix._11 = xScale;
//			ClopMatrix._22 = yScale;
//			ClopMatrix._41 = xOffset;
//			ClopMatrix._42 = yOffset;
//			clopMatrix = DirectX::XMLoadFloat4x4(&ClopMatrix);
//		}
//
//		
//		//���C�g�r���[�v���W�F�N�V�����s����v�Z
//
//		{
//			
//			DirectX::XMStoreFloat4x4(&shadowconstant.LightVP[Shadow_Index], viewMatrix * projectionMatrix * clopMatrix);
//			shadowconstant.ShadowColor = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
//		}
//
//
//	
//
//		
//
//		//�R���X�^���g�o�b�t�@�̐ݒ�
//		XMFLOAT4X4 VPC;
//		XMStoreFloat4x4(&VPC, viewMatrix* (projectionMatrix* clopMatrix));
//		//XMStoreFloat4x4(&VPC, V * (P*clopMatrix));
//		XMFLOAT4 LightDirection;
//		LightDirection.x = LightView.GetFront().x;
//		LightDirection.y = LightView.GetFront().y;
//		LightDirection.z = LightView.GetFront().z;
//		LightDirection.w = 1.0;
//	
//		SetShadowConstant(context, LightDirection,VPC);
//
//		//�R���X�^���g�o�b�t�@�̐ݒ�
//		XMFLOAT4X4 V;
//		XMStoreFloat4x4(&VPC, viewMatrix);
//		//�R���X�^���g�o�b�t�@�̐ݒ�
//		XMFLOAT4X4 P;
//		XMStoreFloat4x4(&VPC, projectionMatrix);
//
//		Begin(context);
//
//		//���X�^���C�U�\�ݒ�
//		context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerShader].Get());
//		//�f�v�X�X�e���V���X�e�[�g�ݒ�
//		context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
//
//		for (ModelResource* model : list)
//		{
//			Render(context, model);
//		}
//	}
//
//
//	XMMATRIX V;
//	XMMATRIX P;
//
//	V = XMLoadFloat4x4(&ModelView.GetView());
//	P = XMLoadFloat4x4(&ModelView.GetProjection());
//
//	//�R���X�^���g�o�b�t�@�̐ݒ�
//	XMFLOAT4X4 VPC;
//	//XMStoreFloat4x4(&VPC, viewMatrix* projectionMatrix);
//	XMStoreFloat4x4(&VPC, V * P);
//	XMFLOAT4 LightDirection;
//	LightDirection.x = LightView.GetFront().x;
//	LightDirection.y = LightView.GetFront().y;
//	LightDirection.z = LightView.GetFront().z;
//	LightDirection.w = 1.0;
//
//	SetShadowConstant(context, LightDirection, VPC);
//
//	//Begin(context, view, projection, lightDirection);
//	//
//	//// �J��������p�����[�^�[���擾
//	//DirectX::XMVECTOR	viewFront, viewRight, viewUp, viewPos;
//	//{
//	//	DirectX::XMMATRIX  View = XMLoadFloat4x4(&view);
//	//	DirectX::XMMATRIX	matrix = DirectX::XMMatrixInverse(nullptr, View);
//	//	viewRight = DirectX::XMVector3Normalize(matrix.r[0]);
//	//	viewUp = DirectX::XMVector3Normalize(matrix.r[1]);
//	//	viewFront = DirectX::XMVector3Normalize(matrix.r[2]);
//	//	viewPos = matrix.r[3];
//	//}
//	//
//	//
//	//
//	//
//	//XMMATRIX VP;
//	//VP = XMLoadFloat4x4(&view) * XMLoadFloat4x4(&projection);
//	//XMFLOAT4X4 vp;
//	//XMStoreFloat4x4(&vp, VP);
//	//SetShadowConstant(context,
//	//	ShadowColor,
//	//	EyePos,
//	//	LightColor);
//	//shadowShader->Activate(context);
//	//ID3D11RenderTargetView* rtv = shadowTexture->GetRenderTargetView();
//	//ID3D11DepthStencilView* dsv = shadowTexture->GetDepthStencilView();
//	//VECTOR2 TextureSize = VECTOR2{ static_cast<float>(shadowTexture->GetWidth()),static_cast<float>(shadowTexture->GetHeight()) };
//	//
//	//context->PSSetSamplers(1, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_Shadow_BORDER].GetAddressOf());
//	//
//	//context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerShader].Get());
//	////�Z�b�g
//	//context->OMSetRenderTargets(1, &rtv, dsv);
//	////�r���[�|�[�g�̐ݒ�
//	//TK_Lib::Screen::SetViewPort(TextureSize);
//	////��ʂ̌��̐F��ݒ肷��(R32G32�ɂ����ݒ肵�Ă��Ȃ��̂ŐԂƉ������łȂ�)
//	//FLOAT Back_Color[] = { 0.7f,0.7f, 1.0f,1.0f };
//	//context->ClearRenderTargetView(rtv, Back_Color);
//	//context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//	////�f�v�X�X�e���V���X�e�[�g�ݒ�
//	//context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
//}
//
//
//void Lib_CascadeShader::ShadowEnd(ID3D11DeviceContext* context)
//{
//	for (int i = 0; i < NUM_SHADOW_MAP; i++)
//	{
//		CreateGauss(context, shadow_Texture[i].get(), Gauss_Texture[i].get());
//	}
//
//
//	//for (int i = 0; i < NUM_SHADOW_MAP; i++)
//	//{
//	//	TK_Lib::Draw::Sprite(shadow_Texture[i].get(), VECTOR2(500*i, 500*i), VECTOR2(500, 500), VECTOR4(0, 0, shadow_Texture[i]->GetWidth(), shadow_Texture[i]->GetHeight()), 0.0f, VECTOR4(1, 1, 1, 1));
//	//}
//
//	shadowShader->Inactivate(context);
//
//}

void Lib_CascadeShader::CreateGauss(ID3D11DeviceContext* context, TextureResource* tex, TextureResource* tex2)
{

	Gauss::Instance().GausianFilter(context, tex, tex2);
	TK_Lib::Screen::Clear(VECTOR4{ 0.0f,0.0f,0.0f,1.0f });
}
void Lib_CascadeShader::Begin(ID3D11DeviceContext* context)
{
	ID3D11Buffer* constantBuffers[] =
	{
		m_sceneConstantBuffer.Get(),
		m_meshConstantBuffer.Get(),
		m_subsetConstantBuffer.Get(),
		m_shadowConstantBuffer.Get()
	};

	context->VSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);
	context->PSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);
//
//	context->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());
//	context->PSSetSamplers(1, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());

	Lib_PointLightManager::Instance().Active(context);


}

void Lib_CascadeShader::SetShadowConstant(
	ID3D11DeviceContext* context,
	XMFLOAT4 lightDirection,
	DirectX::XMFLOAT4X4 ViewProjection)
{
	// �V�[���p�萔�o�b�t�@�X�V
	CreateShadowConstant cb;
	cb.VP = ViewProjection;
	cb.lightDirection = lightDirection;

	context->UpdateSubresource(m_sceneConstantBuffer.Get(), 0, 0, &cb, 0, 0);
	//context->VSSetConstantBuffers(0, 1, m_sceneConstantBuffer.GetAddressOf());
	//context->PSSetConstantBuffers(0, 1, m_sceneConstantBuffer.GetAddressOf());

}

void Lib_CascadeShader::SetShadowConstan2(ID3D11DeviceContext* context,
	DirectX::XMFLOAT4 ShadowColor,
	DirectX::XMFLOAT4 EyePos,
	DirectX::XMFLOAT4 LightColor)
{

	shadowconstant.EyePos = EyePos;
	shadowconstant.LightColor = LightColor;
	shadowconstant.ShadowColor = ShadowColor;

	context->UpdateSubresource(m_shadowConstantBuffer.Get(), 0, 0, &shadowconstant, 0, 0);
	m_shader->Activate(context);
}

void Lib_CascadeShader::CascadeShadowRender(ID3D11DeviceContext* context, const vector<ModelResource*>* list,ShadowType DrawType)
{
	//vector<ModelResource*> ModelList;
	//vector<int> Indexes;
	//string SearchName;

	////���ёւ�
	//while (ModelList.size()< list->size())
	//{
	//	bool flg = false;
	//	for (int i = 0; i <= list->size(); i++)
	//	{
	//		flg = false;
	//		for (int Index : Indexes) {
	//			if (Index == i)flg = true;
	//		}

	//		if (flg == true)continue;

	//		ModelResource* model = list->at(i);
	//		ModelList.emplace_back(model);
	//		Indexes.emplace_back(i);
	//		break;
	//	}

	//	if (ModelList.size() >= list->size())break;

	//	
	//	for (int i = 0; i < list->size(); i++)
	//	{
	//		flg = false;
	//		for (int Index : Indexes) {
	//			if (Index == i)flg = true;
	//		}

	//		if (flg ==true)continue;
	//		ModelResource* model = list->at(i);

	//		if (strcmp(ModelList.back()->filename.c_str(), model->filename.c_str()) == 0)
	//		{
	//			ModelList.emplace_back(model);
	//			Indexes.emplace_back(i);
	//		}
	//	}

	//
	//}
	//
	//string SearchNames="";
	for (int i = 0; i < list->size(); i++)
	{
		ModelResource* model = list->at(i);
		if (model->GetType() == DrawType)continue;
		
	//	//�O��`�悵�����f���̖��O������
	//	if (strcmp(SearchNames.c_str(), model->filename.c_str()) == 0)
	//	{
	//		//�`��
	//		Render(context, model);
	//	}
	//	else
	//	{
	//		SearchNames = model->filename.c_str();
	//		//�O��`�悵�����f���̖��O�������ł͂Ȃ�
	//		UpdateMeshConstantBuffer(context, model);
	//		Render(context, model);
	//	}
	//�`��
		Render(context, model);
	}
}
//���b�V���p�萔�o�b�t�@�X�V
void Lib_CascadeShader::UpdateMeshConstantBuffer(ID3D11DeviceContext* context, const ModelResource* model)
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
		

		//context->PSSetShaderResources(1, 1, shadowTexture->GetShaderResourceView());
		//context->PSSetShaderResources(1, 1, GaussTexture->GetShaderResourceView());
	}
}
void Lib_CascadeShader::Render(ID3D11DeviceContext* context, const ModelResource* model)
{
	const std::vector<ModelResource::Node>& nodes = model->GetNodes();
	const std::vector<ModelResource::NodeTest>& testnodes = model->GetNodetest();

	if (model->GetAddTextures().size() == 0)
	{
		assert(!"NoTexture");
	}
	else
	{
		model->GetAddTextures().at(0).textureResource->Set(context,model->GetAddTextures().at(0).SetNum);
	}

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
		//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

void Lib_CascadeShader::End(ID3D11DeviceContext* context)
{
	//TK_Lib::Screen::Clear({ 0,0,0,1 });
	////TK_Lib::Draw::Sprite(shadow_Texture[0].get(), VECTOR2(0, 500), VECTOR2(500, 500), VECTOR4(0, 0, shadow_Texture[0]->GetWidth(), shadow_Texture[0]->GetHeight()), 0.0f, VECTOR4(1, 1, 1, 1));


	//�e�p�̃e�N�X�`���̕`��
	
//	for (int i = 0; i < NUM_SHADOW_MAP; i++)
//	{
//		TK_Lib::Draw::Sprite(shadow_Texture[i].get(), VECTOR2(0, 200*i+5*i), VECTOR2(200, 200), VECTOR4(0, 0, shadow_Texture[i]->GetWidth(), shadow_Texture[i]->GetHeight()), 0.0f, VECTOR4(1, 1, 1, 1));
//	}
//	
//	for (int i = 0; i < NUM_SHADOW_MAP; i++)
//	{
//		TK_Lib::Draw::Sprite(Gauss_Texture[i].get(), VECTOR2(1720, 200 * i + 5 * i), VECTOR2(200, 200), VECTOR4(0, 0, shadow_Texture[i]->GetWidth(), shadow_Texture[i]->GetHeight()), 0.0f, VECTOR4(1, 1, 1, 1));
//	}

	m_shader->Inactivate(context);
	context->OMSetBlendState(BlendState::Instance().GetBlendState(Bland_state::BS_ALPHA), nullptr, 0xffffffff);
	//
	//
	//
	//ID3D11ShaderResourceView* rtv[1] = { NULL }; // PP
	//context->PSSetShaderResources(1, 1, rtv); // PP
	////shadowTexture->Empty(context, 1);

	ModelClear();
}