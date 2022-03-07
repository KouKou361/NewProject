#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl.h>
//�O���t�B�b�N�X�֌W�������ɂ܂Ƃ߂�����
class Graphics
{
public:
	Graphics(HWND hWnd,UINT ScreenWight, UINT ScreenHeight);
	~Graphics();
private:

	static Graphics* instance;

	UINT screenWight;
	UINT screenHeight;

	//�f�o�C�X�@���\�[�X���쐬���邽��
	Microsoft::WRL::ComPtr<ID3D11Device> m_device = nullptr;
	//�R���e�L�X�g �`�悷�鎞�Ɏg��
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context = nullptr;
	//�E�B���h�E�Y�ɊG������邽��
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain = nullptr;
	//�����_�[�^�[�Q�b�g �F���������ނ���
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetview = nullptr;

	//�e�N�X�`���QD�@�F�����L�^����
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2d = nullptr;
	//�f�v�X�X�e���V���@���s�����������ނ���
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_depthStencilView = nullptr;
	//�V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView = nullptr;
public:
	ID3D11Device* Get_device() { 
		return m_device.Get();
	};
	ID3D11DeviceContext* Get_context() { return m_context.Get(); };
	IDXGISwapChain* Get_swappchain() { return m_swapchain.Get(); };
	ID3D11RenderTargetView* Get_targetview() { return m_renderTargetview.Get(); };
	ID3D11Texture2D* Get_texture2d() { return m_texture2d.Get(); };
	ID3D11DepthStencilView* Get_DepthStencilView() { return m_depthStencilView.Get(); };
	ID3D11ShaderResourceView* Get_ShaderResourceView() { return m_shaderResourceView.Get(); };

	//�X�N���[�����W�̃Q�b�^�[
	UINT GetScreenWight() {
		return screenWight;
	};
	UINT GetScreenHeight() {
		return screenHeight;
	};

	//�C���X�^���X�擾
	static Graphics& Instance()
	{
		return *instance;
	}

};