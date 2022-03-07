#include "Lib_Graphics.h"

#include <memory>
#include <wrl.h>
#include "Delete.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics(HWND hwnd, UINT ScreenWight, UINT ScreenHeight)
{

	instance = this;
	screenWight= ScreenWight;
	screenHeight= ScreenHeight;
	HRESULT hr = S_OK;
	//�f�o�C�X�E�f�o�C�X�R���e�L�X�g�E�X���b�v�`�F�[���̍쐬
	{
		UINT	CreateDeviceFlags = 0;
#if	defined( DEBUG ) || defined( _DEBUG )
		//	DirectX�̃f�o�b�O�p�̐ݒ�t���O(����d�v!)
		//	����𗧂Ă鎖��
		//	�EDirectX�Ɋւ���G���[��x���������Ă���܂��B
		//	�E�A�v���P�[�V�����̏I������
		//	�@DirectX�Ɋւ��郊�\�[�X�̉���R��������Ă���܂��B
		//	
		//	���\�[�X�̉���R��⃁�����̉���R��Ȃǂ���ʂɔ��������ꍇ�A
		//	���̃A�v���P�[�V�����Ń������̊m�ۂ��ł��Ȃ��Ȃ�A�A�v���P�[�V�����������I������\��������B
		//	�ň�OS�ŕK�v�ȃ��������m�ۂł��Ȃ��Ȃ�AWindows����~����\��������B
		CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif	//	defined( DEBUG ) || defined( _DEBUG )

		//	DirectX�̋@�\���x���̐ݒ�p�z��
		//	�����Ƃ��ǂ��ݒ��I��ł����悤�ɕ��ׂ�
		D3D_FEATURE_LEVEL	FeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};



		//	�X���b�v�`�F�C���̍쐬�p�\���̂ɏ���ݒ肵�Ă���
		DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
		::ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		SwapChainDesc.BufferDesc.Width = ScreenWight;//pos.x
		SwapChainDesc.BufferDesc.Height = ScreenHeight;//pos.y
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;//
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;//
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//	1�s�N�Z��������̊e�F(RGBA)��8bit(0�`255)�̃e�N�X�`��(�o�b�N�o�b�t�@)���쐬����B//�F�H
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 1;			//	�o�b�N�o�b�t�@�̐�
		SwapChainDesc.OutputWindow = hwnd;		//	DirectX�ŕ`�������\������E�C���h�E
		SwapChainDesc.Windowed = TRUE;			//	�E�C���h�E���[�h���A�t���X�N���[���ɂ��邩�B
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDesc.Flags = 0; //DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH


		D3D_DRIVER_TYPE d3d_driver_type[]
		{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
		};

		for (auto type : d3d_driver_type)
		{
			//	�I�����ꂽ�@�\���x���̎󂯎��p�ϐ�
			//	�ǂ̋@�\
			D3D_FEATURE_LEVEL	SelectedFeatureLevel;
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,                           //	�ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr�ŁAIDXGIAdapter�̃A�h���X��n���B�g�������O���t�B�b�N�{�[�h���w�肵�������ɗ��p���܂��B�Ⴆ�΁ANVIDIA��CUDA�𗘗p����������
				type,		                       //	�h���C�o�̃^�C�v��n���BD3D_DRIVER_TYPE_HARDWARE �ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA���ʂȂ��Ƃ�����ꍇ�ɗp����B
				nullptr,						   //	��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n���B
				CreateDeviceFlags,				   //	���炩�̃t���O���w�肷��B�ڂ�����D3D11_CREATE_DEVICE�񋓌^�Ō����B�G���[�̃��b�Z�[�W���o�����ǂ����A���O�Ɏc��
				FeatureLevels,					   //	D3D_FEATURE_LEVEL�񋓌^�̔z���^����Bnullptr�ɂ��邱�Ƃł���Lfeature�Ɠ����̓��e�̔z�񂪎g�p�����B
				ARRAYSIZE(FeatureLevels),		   //	feature_levels�z��̗v�f����n���B
				D3D11_SDK_VERSION,				   //	SDK�̃o�[�W�����B�K�����̒l�B
				&SwapChainDesc,					   //	�����Őݒ肵���\���̂ɐݒ肳��Ă���p�����[�^��SwapChain���쐬�����B
				m_swapchain.GetAddressOf(),					   //	�쐬�����������ꍇ�ɁASwapChain�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��SwapChain�𑀍삷��B
				m_device.GetAddressOf(),						   //	�쐬�����������ꍇ�ɁADevice�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��Device�𑀍삷��B
				&SelectedFeatureLevel,			   //	�쐬�ɐ�������D3D_FEATURE_LEVEL���i�[���邽�߂�D3D_FEATURE_LEVEL�񋓌^�ϐ��̃A�h���X��ݒ肷��B
				m_context.GetAddressOf());                       //	�쐬�����������ꍇ�ɁAContext�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��Context�𑀍삷��B
			//�����g����Ȃ�
			if (hr == S_OK)break;
		}

		_ASSERT_EXPR(SUCCEEDED(hr), L"CreateDeviceAndSwapChain()�ŃG���[���N�������Ȃ�");
		if (FAILED(hr))
			return;	//	�쐬�ł��Ȃ������̂ŏ��������s
	}
	//	RenderTargetView�̐���
	D3D11_TEXTURE2D_DESC	BackBufferDesc;
	::ZeroMemory(&BackBufferDesc, sizeof(ID3D11Texture2D));
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_swapchain->GetBuffer(0
			, __uuidof(ID3D11Texture2D)
			, reinterpret_cast<void**>(&pBackBuffer));
		_ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer()�ŃG���[���N�������Ȃ�");
		if (FAILED(hr))
			return;

		hr = m_device->CreateRenderTargetView(pBackBuffer,
			nullptr,
			m_renderTargetview.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), L"CreateRenderTargetView()�ŃG���[���N�������Ȃ�");
		if (FAILED(hr))
		{
			D3D_SAFE_RELEASE(pBackBuffer);
			return;
		}
	

		//	�o�b�N�o�b�t�@�̏�񂾂��͌�Ŏg�p����̂Ŏ擾���Ă���
		pBackBuffer->GetDesc(&BackBufferDesc);
		D3D_SAFE_RELEASE(pBackBuffer);
	}
	//===================
	//�����ݒ�
	//===================
	//�����o���邩�@�R�s�y�����炢��

	//	DepthStencilView�̐���
	D3D11_TEXTURE2D_DESC DepthStencilBufferDesc;
	{
		//	�[�x�X�e���V�������������ނ��߂̃e�N�X�`�����쐬����B
		ID3D11Texture2D* pDepthStencilBuffer = nullptr;
		DepthStencilBufferDesc.Width = ScreenWight;
		DepthStencilBufferDesc.Height = ScreenHeight;
		DepthStencilBufferDesc.MipLevels = 1;
		DepthStencilBufferDesc.ArraySize = 1;
		DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	//	1�s�N�Z��������A�[�x����24Bit / �X�e���V������8bit�̃e�N�X�`�����쐬����B//���s�Q�S�̂���𐶐�
		DepthStencilBufferDesc.SampleDesc.Count = 1;
		DepthStencilBufferDesc.SampleDesc.Quality = 0;
		DepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//	�[�x�X�e���V���p�̃e�N�X�`�����쐬����B
		DepthStencilBufferDesc.CPUAccessFlags = 0;
		DepthStencilBufferDesc.MiscFlags = 0;
		hr = m_device->CreateTexture2D(&DepthStencilBufferDesc, NULL, &pDepthStencilBuffer);
		_ASSERT_EXPR(SUCCEEDED(hr), "�[�x�X�e���V�����ŃG���[���N�������Ȃ�");
		if (FAILED(hr))return;

		//	�[�x�X�e���V���e�N�X�`���ւ̏������݂ɑ����ɂȂ�[�x�X�e���V���r���[���쐬����B
		D3D11_DEPTH_STENCIL_VIEW_DESC	DepthStencilViewDesc;
		ZeroMemory(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc));
		DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
		DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DepthStencilViewDesc.Flags = 0;
		DepthStencilViewDesc.Texture2D.MipSlice = 0;
		hr = m_device->CreateDepthStencilView(pDepthStencilBuffer, &DepthStencilViewDesc, m_depthStencilView.GetAddressOf());
		D3D_SAFE_RELEASE(pDepthStencilBuffer);
		_ASSERT_EXPR(SUCCEEDED(hr), L"�[�x�X�e���V���r���[�ŃG���[���N�������Ȃ�");
		if (FAILED(hr))return;
	}

	//Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D;
	//
	//hr = S_OK;
	////	�e�N�X�`���쐬
	//	//�e�N�X�`��
	//D3D11_TEXTURE2D_DESC m_texture_desc;
	//ZeroMemory(&m_texture_desc, sizeof(m_texture_desc));
	//m_texture_desc.Width = screenWight;
	//m_texture_desc.Height = screenHeight;
	//m_texture_desc.MipLevels = 1;
	//m_texture_desc.ArraySize = 1;
	//m_texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//������R32G32B32�Ȃǂ̐ݒ�(R32G32�����Ȃ�ԂƗ΂���)
	//m_texture_desc.SampleDesc.Count = 1;
	//m_texture_desc.Usage = D3D11_USAGE_DEFAULT;
	//m_texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//m_texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	//
	//hr = m_device->CreateTexture2D(&m_texture_desc, NULL, Texture2D.GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), L"�e�N�X�`���G���[");
	//
	////	�V�F�[�_�[���\�[�X�r���[�쐬
	//D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	//ZeroMemory(&srvd, sizeof(srvd));
	//srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//srvd.Texture2D.MostDetailedMip = 0;
	//srvd.Texture2D.MipLevels = 1;
	//hr = m_device->CreateShaderResourceView(Texture2D.Get(), &srvd, m_shaderResourceView.GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), L"�V�F�[�_�[���\�[�X�r���[�G���[");
	//
	//ID3D11Texture2D* back_buffer;
	//hr=m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
	//_ASSERT_EXPR(SUCCEEDED(hr), L"back_buffer�r���[");
	//
	//// Buffer����RenderTargetView�̍쐬
	//
	//hr = m_device->CreateRenderTargetView(Texture2D, NULL, m_renderTargetview.GetAddressOf());
	//_ASSERT_EXPR(SUCCEEDED(hr), L"RenderTargetView");

	//if (FAILED(m_Device->CreateRenderTargetView(back_buffer, NULL, &m_RenderTargetView)))
	//{
	//	return false;
	//}

		//	�o�b�N�o�b�t�@�̏�񂾂��͌�Ŏg�p����̂Ŏ擾���Ă���
	//back_buffer->GetDesc(&BackBufferDesc);
	//D3D_SAFE_RELEASE(back_buffer);
}
Graphics::~Graphics()
{

}