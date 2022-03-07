#include "Lib_Gauss.h"
#include"Lib.h"

Gauss* Gauss::instance = nullptr;

//�t�B���^�[�l���v�Z����֐�
void  Gauss::CalcGaussianFilter(DirectX::XMFLOAT4* array, int karnel_size, float sigma)
{
	float sum = 0.0f;
	int id = 0;
	for (int y = -karnel_size / 2; y <= karnel_size / 2; y++)
	{
		for (int x = -karnel_size / 2; x <= karnel_size / 2; x++)
		{
			array[id].x = (float)x;
			array[id].y = (float)y;
			// �K�E�V�A���t�B���^
			array[id].z = static_cast<float>((1 / (2 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma)));
			//array[id].z =  (float)exp(-((x * x + y * y) / (2 * sigma * sigma))) / (2 * PI * sigma * sigma);
			sum += array[id].z;
			id++;
		}
	}
	for (int i = 0; i < karnel_size * karnel_size; i++)
	{
		array[i].z /= sum;
	}
}
Gauss::Gauss(ID3D11Device* device)
{
	instance = this;

	HRESULT hr = S_OK;
	// �V�[���p�o�b�t�@
	D3D11_BUFFER_DESC desc;
	//::ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	::memset(&desc, 0, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.ByteWidth = sizeof(ConstantBufferForPerFrameGaussianBlur);
	desc.StructureByteStride = 0;

	hr = device->CreateBuffer(&desc, 0, ConstantBufferGaussian.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), L"�R���X�^���g�o�b�t�@�̃G���[");


	Gauss_shader = make_unique<ShaderResource>();
	Gauss_shader->Create(device, "./Shader/Gaussian_vs.cso", "./Shader/Gaussian_ps.cso", ShaderResource::TYPELayout::TYPE_Layout2DSprite);
}
void  Gauss::GausianFilter(ID3D11DeviceContext* device, TextureResource* tex1, TextureResource* tex2)
{
	static	constexpr	u_int	BUFFER_SIZE = KARNEL_SIZE * KARNEL_SIZE;
	//�T���v�����O�̈ʒu�I�t�Z�b�g�ƃE�F�C�g���v�Z����


	const int kar = 3;
	const int sig = 50;

	XMFLOAT4 weight[BUFFER_SIZE];
	ZeroMemory(weight, sizeof(weight));
	//Gauss::CalcGaussianFilter(weight, 5, 50);
	Gauss::CalcGaussianFilter(weight, kar,sig);

	//�R���X�^���g�o�b�t�@�ݒ�
	ConstantBufferForPerFrameGaussianBlur cb;
	{
		memcpy(cb.Weight, weight, sizeof(XMFLOAT4) * BUFFER_SIZE);
		//cb.KarneSize = 5;
		cb.KarneSize = kar;
		cb.texcel.x = 1.0f / static_cast<float>(tex2->GetWidth());
		cb.texcel.y = 1.0f / static_cast<float>(tex2->GetHeight());

		//�R���X�^���g�o�b�t�@�X�V(���C�g�����J�����s��Ɖe�̐F)
		device->UpdateSubresource(ConstantBufferGaussian.Get(), 0, NULL, &cb, 0, 0);
		device->VSSetConstantBuffers(0, 1, ConstantBufferGaussian.GetAddressOf());
		device->PSSetConstantBuffers(0, 1, ConstantBufferGaussian.GetAddressOf());
	}



	//�K�E�X��������
	{
		ID3D11RenderTargetView* rtv = tex2->GetRenderTargetView();
		ID3D11DepthStencilView* dsv = tex2->GetDepthStencilView();
		device->OMSetRenderTargets(1, &rtv, nullptr);
		//��ʃN���A
		float clearColor[4] = { 0,0,0,0 };
		device->ClearRenderTargetView(rtv, clearColor);
	
		
		TK_Lib::Draw::Sprite(tex1, Gauss_shader.get(), VECTOR2{ 0,0 }, VECTOR2{ static_cast<float>(tex1->GetWidth()), static_cast<float>(tex1->GetHeight()) }, VECTOR4{ 0,0,static_cast<float>(tex1->GetWidth()), static_cast<float>(tex1->GetHeight()) }, 0.0f, VECTOR4{ 1,1,1,1 });
	}


}
