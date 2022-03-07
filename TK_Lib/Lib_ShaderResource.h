#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <assert.h>
using namespace Microsoft::WRL;
using namespace DirectX;


//����Shader�̓s�N�Z���V�F�[�_�[,���_�V�F�[�_�[,���̓��C�A�E�g
//�Ȃǂ̕`�悷��Ƃ��ɂ̑f�ނ������Ǘ����Ă���


class ShaderResource
{
public:
	enum class TYPELayout
	{
		TYPE_Layout2DSprite,
		TYPE_LayoutDebugSprite,
		TYPE_layoutPointSprite,
		TYPE_LayoutModel,
		TYPE_LayoutEnd,
	};
public:
	ShaderResource() {};
	~ShaderResource() {};

protected:
	//MEMO:�W�I���g���V�F�[�_�[�Ȃǂ��ǉ����Ă�������
	
	//�s�N�Z���V�F�[�_�[
	ComPtr<ID3D11PixelShader> m_PixelShader = nullptr;
	//���_�V�F�[�_�[
	ComPtr<ID3D11VertexShader> m_VertexShader = nullptr;
	//�W�I���g���V�F�[�_�[
	ComPtr<ID3D11GeometryShader> m_GeometryShader = nullptr;
	//���̓��C�A�E�g
	ComPtr<ID3D11InputLayout> m_inputLayout = nullptr;
public:
	//�쐬
	virtual void Create(ID3D11Device* device, const char* VSname, const char* PSname, TYPELayout type= TYPELayout::TYPE_Layout2DSprite);
	virtual void Create(ID3D11Device* device, const char* VSname, const char* GSname, const char* PSname, TYPELayout type = TYPELayout::TYPE_Layout2DSprite);

	void Activate(ID3D11DeviceContext* device);
	void Inactivate(ID3D11DeviceContext* device);
};
