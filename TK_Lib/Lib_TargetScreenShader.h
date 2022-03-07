#pragma once
#include "Lib_BaseShader.h"

class Lib_TargetScreenShader 
{
private:
	//Screen�̃e�N�X�`��
	unique_ptr<TextureResource> ScreenTexture=nullptr;

	//TODO Color�̃Z�b�g
	unique_ptr<ShaderResource> m_shader=nullptr;
	//���_�o�b�t�@
	ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
	struct SceneConstantBuffer
	{
		VECTOR4 Color;//�F
		float LineWeight;//�^�[�Q�b�g�X�N���[���̂ӂ��̑���
		float LineDark; //�^�[�Q�b�g�X�N���[���̂ӂ��̔Z��
		float dummy;
		float dummy2;
	};

	ComPtr<ID3D11Buffer>			m_sceneConstantBuffer;
	//ComPtr<ID3D11Buffer>			m_ConstantBuffer;

	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//�f�v�X�X�e���V��


public:
	Lib_TargetScreenShader(ID3D11Device* device);
	~Lib_TargetScreenShader() {};

	void SetConstant(ID3D11DeviceContext* device, VECTOR4 color, float LineDark, float LineWeight);
	//�`��
	void Render(ID3D11DeviceContext* device);
	//Screen�`��
	void ScreenRender(ID3D11DeviceContext* device);


};