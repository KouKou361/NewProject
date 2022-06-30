
#include <windows.h>
#include <memory>
#include <sstream>

#include <wchar.h>

#include "Lib_Graphics.h"
#include "Lib.h"
#include "Lib_highResolutionTimer.h"
#include "Lib_Sampler.h"
#include "Lib_Rasterizer.h"
#include "Lib_Sprite.h"
#include "Lib_Texture.h"
#include "Lib_ShaderResource.h"
#include "Lib_TextureResourceManager.h"
#include "Lib_DebugRender.h"
#include "Lib_CameraLib.h"
#include "Lib_ModelResource.h"
#include "Lib_ModelResourceManager.h"
#include "Lib_LambertShader.h"
#include "Lib_ShadowShader.h"
#include "Lib_Gauss.h"
#include "Lib_Light.h"
#include "Lib_LightManager.h"
#include "Lib_DepthStencil.h"
#include "Lib_OutlineShader.h"
#include "Mathf.h"
#include "Lib_TargetScreenShader.h"
#include "Lib_Japanese.h"
#include "Lib_Sound.h"
#include "Lib_NoLight.h"
#include "Lib_CascadeShader.h"


#define IMGUI (1)

using namespace std;


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int test_Texture;
int test_Texture2;
int test_Efc[5];

namespace TK_Lib
{
    //�t�F�[�h
    class Fade
    {
    public:
        enum class FADE_TYPE
        {
            FadeOut,
            FadeIn,
            NONE,
            End,
        };
        FADE_TYPE type= FADE_TYPE::NONE;
        float fadeVolumu = 0;
        int fadeTexture;
        float fadeSpeed = 0;
    };

    //�����o�[
    struct Member
    {
        // �E�B���h�E�n���h��
        HWND hwnd = 0;
        //�`��
        //unique_ptr<Graphics> graphics = nullptr;
        //
        //unique_ptr<Sampler>    sampler = nullptr;
        //unique_ptr<Rasterizer> rasterizer = nullptr;
        //
        //unique_ptr<Sprite>     sprite = nullptr;
        //unique_ptr<ShaderResource>    shader = nullptr;
        //
        //unique_ptr<BlendState> blenderstate = nullptr;
        //
        //unique_ptr<TextureResourceManager> textureResourceManager = nullptr;
        //unique_ptr<ModelResourceManager> modelResourceManager = nullptr;
        //
        //unique_ptr<Lib_LambertShader> lambertShader = nullptr;
        //unique_ptr<Lib_ShadowShader> shadowShader = nullptr;
        //unique_ptr<Lib_OutlineShader> outlineshader = nullptr;
        //
        //unique_ptr<CameraLib> cameralib = nullptr;
        //
        //unique_ptr<Gauss> gauss = nullptr;
        //
        //unique_ptr<LightController> lightController;
        //
        //unique_ptr<Lib_PointLightManager> pointLightManager;
        //
        //unique_ptr<DepthStencil> depthStencil;
        //
        //unique_ptr<Lib_EffectManager> effectManager;
        //
        //unique_ptr<GamePad> gamepad;

        //�O�܂�unique�ɂ��Ă������A�Q�Ƃ̎d���i�s���̈���������ɏ����Ă��܂��j
        //�������̂ň����new�����Ă���B

        Graphics* graphics ;

        Sampler*    sampler = nullptr;
        Rasterizer* rasterizer = nullptr;

        Sprite*     sprite = nullptr;
        ShaderResource*    shader = nullptr;

        BlendState* blenderstate = nullptr;

        TextureResourceManager* textureResourceManager = nullptr;
        ModelResourceManager* modelResourceManager = nullptr;

        Lib_LambertShader* lambertShader = nullptr;
        Lib_ShadowShader* shadowShader = nullptr;
        Lib_OutlineShader* outlineshader = nullptr;
        Lib_NoLightShader* noLightShader = nullptr;
        Lib_CascadeShader* cascadeShader = nullptr;

        CameraLib* cameralib = nullptr;

        Gauss* gauss = nullptr;

        LightController* lightController = nullptr;

        Lib_PointLightManager* pointLightManager = nullptr;

        DepthStencil* depthStencil = nullptr;

        Lib_EffectManager* effectManager = nullptr;

        GamePad* gamepad = nullptr;

        //�t���[���^�C�}�[
        HighResolutionTimer timer = {};
        // //�E�B���h�E�T�C�Y
        VECTOR2 windowSize{};
        Lib_TargetScreenShader* targetScreenShader = nullptr;

        //���{��Font
        JapanFont* japanFont = nullptr;
        //�T�E���h
        SoundManager* soundManager = nullptr;

        Fade fade = {};
        



        //  //Debug
          unique_ptr<Primitive2D_DebugRender> primitive2DDebugRender = nullptr;
          unique_ptr<Primitive3D_DebugRender> primitive3DDebugRender = nullptr;


        
        //  //GamePad
        //  unique_ptr<GamePad_lib> gamepad = nullptr;


    
      //  Blender* m_blander = nullptr;

        //   ShaderResourceManager* shaderResourceManager = nullptr;
        //   ModelManager* modelmanager = nullptr;
        //
        //   unique_ptr<SamplerManager> samplerStateManager = nullptr;
        //
        //   Sprite* sp = nullptr;
        //   unique_ptr<Gauss> gauss = nullptr;
    };
  
    static Member m = {};

 

    //���C�u����������
    void LibInit(LPCTSTR caption, int screenWidth, int screenHeight)
    {


        //window�̏���������
        m.hwnd = Window::Init(caption, screenWidth, screenHeight);
        //�`��̏���������
        m.graphics = new Graphics (m.hwnd, screenWidth, screenHeight);
        //�T�E���h
        m.soundManager = new SoundManager(m.hwnd);
        // �����n��̐ݒ�
        srand((unsigned int)time(NULL));
        //�X�N���[���̑傫���ۑ�
        m.windowSize = VECTOR2{ static_cast<float>(screenWidth),static_cast<float>(screenHeight) };
        m.rasterizer = new Rasterizer(m.graphics->Get_device());
        m.sampler = new Sampler(m.graphics->Get_device());

        m.sprite = new Sprite (m.graphics->Get_device());

        m.shader = new ShaderResource ();
        m.shader->Create(m.graphics->Get_device(), "./Shader/Sprite_vs.cso", "./Shader/Sprite_ps.cso",ShaderResource::TYPELayout::TYPE_Layout2DSprite);

        m.textureResourceManager = new TextureResourceManager();
        m.textureResourceManager->Init(50);

        m.modelResourceManager = new ModelResourceManager();
        m.modelResourceManager->Init(100);

        m.blenderstate = new BlendState(m.graphics->Get_device());

        m.lambertShader = new Lib_LambertShader(m.graphics->Get_device());

        m.shadowShader = new Lib_ShadowShader(m.graphics->Get_device());

        m.outlineshader= new Lib_OutlineShader(m.graphics->Get_device());

        m.noLightShader = new Lib_NoLightShader(m.graphics->Get_device());

        m.cascadeShader = new Lib_CascadeShader(m.graphics->Get_device());

        m.gauss = new Gauss(m.graphics->Get_device());

        m.pointLightManager = new Lib_PointLightManager(m.graphics->Get_device());
        m.pointLightManager->Init(32);

      //m.spriteEffectManager = make_unique<SpriteEffect>(m.graphics->Get_device(), 50,"./Data/particle256x256.png");
      //  m.spriteEffectManager->SetConstant(VECTOR2{ 140,240 }, VECTOR2{ 14,14 });
      //m.spriteEffectManager->SetConstant(VECTOR2{ 64,64 }, VECTOR2{ 4,4 });

        m.depthStencil = new DepthStencil(m.graphics->Get_device());

        m.gamepad= new GamePad();

        

        m.fade.fadeTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/FadeOut.png");
        m.fade.fadeVolumu = 0;



       // test = new ModelResource();
       // test->Load(m.graphics->Get_device(), "./Data/Jummo/Jummo.mdl");
       // test->PlayAnimation(1, true);

       //     //�J����
       m.cameralib = new CameraLib();
       m.lightController = new LightController();


       m.effectManager = new Lib_EffectManager();
       TK_Lib::Lib_Effect::Init(10);

       m.targetScreenShader = new Lib_TargetScreenShader(m.graphics->Get_device());

       m.japanFont = new JapanFont(m.graphics->Get_device(), "Data/Sprite/fonts/Japan/MS Gothic.fnt", 1024);
      


       //    
       // 
       //     m.m_blander = new Blender(m.graphics->Get_device());
       //     m.textureResourceManager = new TextureResourceManager();
       //     m.textureResourceManager->Init(15);
       //    
       //     m.shaderResourceManager = new ShaderResourceManager();
       //     m.shaderResourceManager->Init(15);
       //    
       //     m.modelmanager = new ModelManager();
       //     m.modelmanager->Init(10);
       //    
       //     m.gauss = make_unique<Gauss>(m.graphics->Get_device());
       //    
       //     m.sp = new Sprite(m.graphics->Get_device());
       //    
       //     //Debug
            m.primitive2DDebugRender = make_unique<Primitive2D_DebugRender>(m.graphics->Get_device(), 300);
            m.primitive3DDebugRender = make_unique<Primitive3D_DebugRender>(m.graphics->Get_device(), 300);
       //    
       //     m.samplerStateManager = make_unique<SamplerManager>(m.graphics->Get_device());
       //    
       //     //�e�X�g(1024�ɂ��Ă���)�������d���Ȃ炱����ύX���Ă���������
       //     TK_Lib::Load::Create(m.graphics->Get_device(), test_shader_texture[0], 1024, 1024, DXGI_FORMAT_R32G32_FLOAT);
       //     TK_Lib::Load::Create(m.graphics->Get_device(), test_shader_texture[1], 1024, 1024, DXGI_FORMAT_R32G32_FLOAT);
       //    
       //     //�}���`�����_�[�^�[�Q�b�g�̍쐬
       //     TK_Lib::Load::Create(m.graphics->Get_device(), test_MultiRender[MULTI_POSITION], m.windowSize.x, m.windowSize.y, DXGI_FORMAT_R8G8B8A8_UNORM);
       //     TK_Lib::Load::Create(m.graphics->Get_device(), test_MultiRender[MULTI_NORMAL], m.windowSize.x, m.windowSize.y, DXGI_FORMAT_R16G16B16A16_FLOAT);
       //     TK_Lib::Load::Create(m.graphics->Get_device(), test_MultiRender[MULTI_COLOR], m.windowSize.x, m.windowSize.y, DXGI_FORMAT_R16G16B16A16_FLOAT);
       //    
       //    
       //     TK_Lib::Load::ShaderLoad(L"./Shaders/Gaussian_vs.cso", L"./Shaders/Gaussian_ps.cso", test_Gauss_shader[0]);
       //    
       //     //�{�[���̓����ĂȂ����f��
       //    
       //    // test = new ModelResource(m.graphics->Get_device(),"./Data/Boss/BossModel_Complete.mdl");
       //    //test = new ModelResource(m.graphics->Get_device(), "./Data/Boss/Enemy1.mdl");
       //    // test = new ModelResource(m.graphics->Get_device(), "./Data/Stage/stage01.mdl");
       //    //�Q�[���p�b�h
       //     m.gamepad = make_unique<GamePad_lib>();
#if IMGUI
        Imgui::Init();
#endif



        m.timer.reset();
    }

    void CalculateFrameStats()
    {
        // Code computes the average frames per second, and also the 
        // average time it takes to render one frame.  These stats 
        // are appended to the window caption bar.
        static int frames = 0;
        static float time_tlapsed = 0.0f;

        frames++;

        // Compute averages over one second period.
        if ((m.timer.time_stamp() - time_tlapsed) >= 1.0f)
        {
            float fps = static_cast<float>(frames); // fps = frameCnt / 1
            float mspf = 1000.0f / fps;
            std::ostringstream outs;
            outs.precision(6);
            outs << "  FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
            SetWindowTextA(m.hwnd, outs.str().c_str());

            // Reset for next average.
            frames = 0;
            time_tlapsed += 1.0f;
        }
    }

    //���C�u�����̃��[�v(FPS���m�F����������true�ɂ����炢��)
    bool LibLoop(bool isShowFrameRate)
    {

        static int testIndexAnime = 0;


        //�Q�[���p�b�h�̍X�V
        m.gamepad->Update();

        //�X�N���[���̃N���A�i���Z�b�g�j
        TK_Lib::Screen::Clear(VECTOR4{ 0,0,0,1 });
        TK_Lib::Blender::SetBlender(Bland_state::BS_ALPHA);

#if IMGUI
        TK_Lib::Imgui::UpdateStart();
        TK_Lib::Imgui::Update();
#endif

        MSG msg = {};


        while (WM_QUIT != msg.message)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                m.timer.tick();
                if (isShowFrameRate)
                {
                    CalculateFrameStats();
                }

                return true;
            }
        }
        return false;
    }

    void LibEnd()
    {
        m.textureResourceManager->Clear();
        m.modelResourceManager->Clear();

        delete m.graphics;
        m.graphics = nullptr;

        delete m.sampler;
        m.sampler = nullptr;

        delete m.rasterizer;
        m.rasterizer = nullptr;

        delete m.sprite;
        m.sprite = nullptr;

        delete m.shader;
        m.shader = nullptr;

        delete m.blenderstate;
        m.blenderstate = nullptr;

        delete m.textureResourceManager;
        m.textureResourceManager = nullptr;

        delete m.modelResourceManager;
        m.modelResourceManager = nullptr;

        delete m.lambertShader;
        m.lambertShader = nullptr;
        delete m.shadowShader;
        m.shadowShader  = nullptr;
        delete m.outlineshader;
        m.outlineshader = nullptr;
        delete m.cascadeShader;
        m.cascadeShader = nullptr;

        delete m.cameralib;
        m.cameralib = nullptr;

        delete m.gauss;
        m.gauss = nullptr;

        delete m.lightController;
        m.lightController = nullptr;

        delete m.pointLightManager;
        m.pointLightManager = nullptr;

        delete m.depthStencil;
        m.depthStencil = nullptr;

        delete m.effectManager;
        m.effectManager = nullptr;

        delete m.gamepad;
        m.gamepad = nullptr;

        delete m.targetScreenShader;
        m.targetScreenShader = nullptr;

        delete m.japanFont;
        m.japanFont = nullptr;

        delete m.soundManager;
        m.soundManager = nullptr;

        delete m.noLightShader;
        m.noLightShader = nullptr;

#if IMGUI
        Imgui::End();
#endif

    }

    HWND* GetHWND()
    {
        return &m.hwnd;
    }
    

    //======================================
    //�E�B���h�E�֌W
    //======================================
    namespace Window
    {
        const LPCWSTR CLASS_NAME = L"3dgp";

        // �E�B���h�E�v���V�[�W��
        LRESULT CALLBACK fnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            //using DirectX::Keyboard;

            // �}�E�X�z�C�[���p
            static int nWheelFraction = 0;	// ��]�ʂ̒[��

            // �}�E�X�ړ��p
            static POINT prevPos = POINT{0,0};
#if IMGUI

            if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
                return true;
#endif




            switch (msg)
            {
            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc;
                hdc = BeginPaint(hwnd, &ps);
                EndPaint(hwnd, &ps);
                break;
            }
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            case WM_ACTIVATEAPP:
                //Keyboard::ProcessMessage(msg, wParam, lParam);
                nWheelFraction = 0;
                break;
            case WM_KEYDOWN:
                if (wParam == VK_ESCAPE)
                {
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                }
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP:
                //Keyboard::ProcessMessage(msg, wParam, lParam);
                break;
            case WM_ENTERSIZEMOVE:
                // WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
                m.timer.stop();
                break;
            case WM_EXITSIZEMOVE:
                // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
                // Here we reset everything based on the new window dimensions.
                m.timer.start();
                break;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
            }

            return 0;
        }

        //�E�B���h�E������
        HWND Init(LPCTSTR caption, int screenWidth, int screenHeight)
        {

#if defined(DEBUG) | defined(_DEBUG)
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
            //�����������[���[�N�������ɂ����ɒl�������Ƃ�����
            //_CrtSetBreakAlloc(1427);
#endif
            WNDCLASSEX wcex;
            wcex.cbSize = sizeof(WNDCLASSEX);
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = fnWndProc;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = 0;
            wcex.hInstance = GetModuleHandle(NULL);
            wcex.hIcon = 0;
            wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName = NULL;
            wcex.lpszClassName = CLASS_NAME;
            wcex.hIconSm = 0;
            RegisterClassEx(&wcex);

            m.windowSize = VECTOR2{ static_cast<float>(screenWidth), static_cast<float>(screenHeight) };

            RECT rc = { 0, 0, screenWidth, screenHeight };
            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
            HWND hwnd = CreateWindow(CLASS_NAME, caption, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, GetModuleHandle(NULL), NULL);
            ShowWindow(hwnd, SW_SHOWDEFAULT);
            return hwnd;
        }


        VECTOR2 GetWindowSize() { return m.windowSize; }

        float GetElapsedTime() { return m.timer.time_interval(); }
    }

    //==========================
    //�J�����֌W
    //==========================
    namespace Camera
    {
        void SetLookAt(
            const VECTOR3& eye,
            const VECTOR3& focus,
            const VECTOR3& up)
        {
            m.cameralib->SetLookAt(eye, focus, up);
        }

        void SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ)
        {
            m.cameralib->SetPerspectiveFov(fovY, aspect, nearZ, farZ);
        }

        const DirectX::XMFLOAT4X4& GetView()
        {
            return m.cameralib->GetView();
        }

        const DirectX::XMFLOAT4X4& GetProjection()
        {
            return m.cameralib->GetProjection();
        }

        const CameraLib* GetCamera()
        {
            return m.cameralib;
        }

        // ���_�擾
        const VECTOR3& GetPos()
        {
            return m.cameralib->GetPos();
        }

        // �����_�擾
        const VECTOR3& GetTarget()
        {
            return m.cameralib->GetTarget();
        }

        // ������擾
        const VECTOR3& GetUp()
        {
            return m.cameralib->GetUp();
        }

        // �O�����擾
        const VECTOR3& GetFront()
        {
            return m.cameralib->GetFront();
        }

        // �E�����擾
        const VECTOR3& GetRight()
        {
            return m.cameralib->GetRight();
        }

        //�J�����ɉf���Ă��邩�ǂ���
        const bool IsCamera(const VECTOR3& Position,const float R)
        {
            
            //L�����߂�
            XMVECTOR Vec2;
            float L = 0;
            {
                
                XMVECTOR P= XMLoadFloat3(&Position);
                XMVECTOR C = XMLoadFloat3(&m.cameralib->GetPos());
                XMVECTOR Vec1 = XMVectorSubtract(P,C);
                Vec1 = XMVector3Normalize(Vec1);
                Vec2 = XMLoadFloat3(&GetFront());
                XMVECTOR Dot  = XMVector3Dot(Vec1,Vec2);
                XMStoreFloat(&L,Dot);
                L=acosf(L);
                L=XMConvertToDegrees(L);
            }

          
            if (L>=R)return false;
            return true;
        }


    }


    //======================
    //����
    //======================
    namespace Light
    {
        void SetLookAt(
            const VECTOR3& eye,
            const VECTOR3& focus,
            const VECTOR3& up)
        {
            m.lightController->SetLookAt(eye, focus, up);
        }

        void SetOrthongraphic(float Width, float Height, float Near, float Far)
        {
            m.lightController->SetOrthongraphic(Width, Height, Near, Far);
        }

        const DirectX::XMFLOAT4X4& GetView()
        {
            return m.lightController->GetView();
        }

        const DirectX::XMFLOAT4X4& GetProjection()
        {
            return m.lightController->GetProjection();
        }

        const CameraLib &GetCamera()
        {
            return *m.lightController->GetCamera();
        }

        // ���_�擾
        const VECTOR3& GetPos()
        {
            return m.lightController->GetPos();
        }

        // �����_�擾
        const VECTOR3& GetForward()
        {
            return m.lightController->GetForward();
        }

        // ������擾
        const VECTOR3& GetUp()
        {
            return m.lightController->GetUp();
        }

        // �O�����擾
        const VECTOR3& GetFront()
        {
            return m.lightController->GetFront();
        }

        // �E�����擾
        const VECTOR3& GetRight()
        {
            return m.lightController->GetRight();
        }

    }

    //=======================
    //���f���֌W 
    //======================
    namespace Model
    {
        //���f��
        void Tranceform(const int handle, XMFLOAT4X4 W)
        {
            //���f���̍s��X�V����
            m.modelResourceManager->Tranceform(m.graphics->Get_device(), W, handle);
        }
        //���f��
        void UpdateMask(const int handle)
        {
            ModelResource* model = m.modelResourceManager->GetModelResource(handle);
            model->UpdateMaskVolume();
        }
        //���f��
        void Tranceform(const int handle, VECTOR3 Positoin, VECTOR3 Angle, VECTOR3 Scale)
        {
            // ���[���h�s��̍X�V
            DirectX::XMMATRIX S = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
            DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(Angle.x, Angle.y, Angle.z);
            DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(Positoin.x, Positoin.y, Positoin.z);

            DirectX::XMMATRIX W = S * R * T;
            DirectX::XMFLOAT4X4 World;
            XMStoreFloat4x4(&World, W);
            //���f���̍s��X�V����
            TK_Lib::Model::Tranceform(handle, World);
        }
        //���f��
        void Tranceform(const int handle, VECTOR3 Positoin, VECTOR4 Quoatanion, VECTOR3 Scale)
        {
            XMVECTOR Qu = XMLoadFloat4(&Quoatanion);

            //�N�H�I�^�j�I���̒l���o�N���Ă��Ȃ����m�F
            
            assert(!XMQuaternionIsNaN(Qu));

            // ���[���h�s��̍X�V
            DirectX::XMMATRIX S = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
            DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(Qu);
            DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(Positoin.x, Positoin.y, Positoin.z);

            DirectX::XMMATRIX W = S * R * T;
            DirectX::XMFLOAT4X4 World;
            XMStoreFloat4x4(&World, W);
            //���f���̍s��X�V����
            TK_Lib::Model::Tranceform(handle, World);
        }
        //���f���̃A�j���[�V����

        void AnimetionUpdate(const int handle)
        {

            //���f���̍s��X�V����
            m.modelResourceManager->UPdateAnimetion(m.graphics->Get_device(), handle, m.timer.time_interval());
        }
        //���f���̃A�j���[�V�����Đ�
        void PlayAnimation(const int handle, int animationIndex, bool loop)
        {
            //���f���̍s��X�V����
            m.modelResourceManager->PlayAnimation(handle, animationIndex, loop);
        }
        bool IsPlayAnimetion(const int handle)
        {
            //���f���̍s��X�V����
           return  m.modelResourceManager->IsPlayAnimetion(handle);
        }
        vector<std::shared_ptr<ModelResource>>& GetModels()
        {
          return   m.modelResourceManager->GetModel();
        }

        ModelResource::NodeTest* FindNode(int modelIndex, const char* name)
        {
            return   m.modelResourceManager->FindNode(modelIndex, name);
        }
        float GetEndAnimetionTime(int modelIndex)
        {
            return   m.modelResourceManager->GetEndAnimetionTime(modelIndex);
        }
        float GetAnimetionTime(int modelIndex)
        {
            return   m.modelResourceManager->GetAnimetionTime(modelIndex);
        }
        //�A�j���[�V�����̎��ԁi�O�`�P�܂ł̊Ԃɕϊ����āj��Ԃ�
        float IsPlayAnimetionRate(int modelIndex)
        {

           float endAnimetionTime = TK_Lib::Model::GetEndAnimetionTime(modelIndex);
           float AnimetionTime = TK_Lib::Model::GetAnimetionTime(modelIndex);
           
           if (endAnimetionTime == 0)assert(L"0�Ŋ���Z���悤�Ƃ��܂���");
           //�A�j���[�V�����^�C����0�`1�܂ł̔䗦�ɒ���
           return AnimetionTime /= endAnimetionTime;
           
        }

        

        void LayPick(const int index, const VECTOR3& start, const VECTOR3& end, RayOut& ray)
        {
            ModelResource* model= m.modelResourceManager->GetModelResource(index);
            model->RayPick(start, end, ray);
        }
        void RadiusLayPick(const int index, const VECTOR3& start, const VECTOR3& end, RayOut& ray,const float R)
        {
            //���a���l���������C�s�b�N
            ModelResource* model = m.modelResourceManager->GetModelResource(index);
            model->RadiusRayPick(start, end, ray, R);
        }
        void SetModelTexture(const string ModelName, const string textureName, const int setNum)
        {
            int ModelIndex = m.modelResourceManager->GetModelFromSerchKey(ModelName);
            int TextureIndex = TK_Lib::Load::LoadTexture(textureName);
            SetModelTexture(ModelIndex, TextureIndex, setNum);
        }
        void SetModelTexture(const int setModel, const int textureIndex, const int setNum)
        {
            ModelResource* model = m.modelResourceManager->GetModelResource(setModel);
            TextureResource* texture = m.textureResourceManager->GetTextureResource(textureIndex);
            model->SetTexture(texture, setNum);
        }

        void  MaskStart(const int TextureIndex, const float maskSpeed)
        {
            ModelResource* model = m.modelResourceManager->GetModelResource(TextureIndex);
            model->MaskStart(maskSpeed);
        }

        float GetMaskVolume(const int TextureIndex)
        {
            ModelResource* model = m.modelResourceManager->GetModelResource(TextureIndex);
            return model->GetMaskVolume();
        }
    }
    //======================================
    //�X�N���[���֌W
    //======================================
    namespace Screen
    {
        void SetViewPort(VECTOR2 Size)
        {
            ID3D11DeviceContext* dc = m.graphics->Get_context();
            //Viewport�ݒ�
            D3D11_VIEWPORT	Viewport;
            Viewport.TopLeftX = 0;
            Viewport.TopLeftY = 0;
            Viewport.Width = static_cast<float>(Size.x);
            Viewport.Height = static_cast<float>(Size.y);
            Viewport.MinDepth = 0.0f;
            Viewport.MaxDepth = 1.0f;
            dc->RSSetViewports(1, &Viewport);
        }
        //�X�N���[���̃N���A�i���Z�b�g�j
        void Clear(VECTOR4 color)
        {
            //�r���[�|�[�g�̐ݒ�
            TK_Lib::Screen::SetViewPort();

            ID3D11DeviceContext* dc = m.graphics->Get_context();
            ID3D11RenderTargetView* rtv = m.graphics->Get_targetview();
            ID3D11DepthStencilView* dsv = m.graphics->Get_DepthStencilView();
            //	�r���[�|�[�g�̐ݒ�
            //�L�����o�X�̂ǂ��ɕ`�悷�邩

            SetViewPort(m.windowSize);

            //MEMO:Viewport��������������Ă���
            //���ꂳ�@�������J�������X�N���[���ɓ����ɏo�������ɂȂ�����
            //���ꂶ�Ⴀ�ł��Ȃ��


            //��ʂ̌��̐F��ݒ肷��
            FLOAT Back_Color[] = { color.x,color.y, color.z, color.w };
            dc->ClearRenderTargetView(rtv, Back_Color);
            dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            dc->OMSetRenderTargets(1, &rtv, dsv);

        }
        //�X�N���[���̐؂�ւ�
        void Flip()
        {
            //static VECTOR4 Color = {1,0,0,1};
            //static float LineDark=0;
            //static float LineWeight=0;
            //
            //ImGui::Begin("Shader");
            //  ImGui::SliderFloat("Dark",&LineDark,0,10);//�^�[�Q�b�g�X�N���[���̂ӂ��̑���
            //  ImGui::SliderFloat("Weight", &LineWeight, 0, 10);//�^�[�Q�b�g�X�N���[���̂ӂ��̔Z�� 0, 2)
            //  ImGui::ColorEdit4("Color", &Color.x);
            //ImGui::End();
        
        
            //m.targetScreenShader->SetConstant(m.graphics->Get_context(), Color, LineDark, LineWeight);
            //m.targetScreenShader->Render(m.graphics->Get_context());
#if IMGUI
            TK_Lib::Imgui::Render();
#endif
            IDXGISwapChain* sc = m.graphics->Get_swappchain();
            sc->Present(1, 0);
        }

        //�E�B���h�E�̉�ʂ̎擾
        const u_int GetWindowWight() { return m.graphics->GetScreenWight(); };
        const u_int GetWindowHeight() { return m.graphics->GetScreenHeight(); };


    }
    //======================================
    //���[�h�֌W
    //======================================
    namespace Load
    {
        int LoadTexture(const string name)
        {
            int handle=0;
            m.textureResourceManager->Load(m.graphics->Get_device(), name, handle);
            return handle;
        }

        int LoadModel(const string name,const string RegisterKey)
        {
            int handle = 0;
            if (!m.modelResourceManager->Load(m.graphics->Get_device(), name, handle, RegisterKey))
            {
                return -1;
            }
            return handle;
        }
        int CopyModel(int handle)
        {
            int CopyHandle = 0;
            CopyHandle=m.modelResourceManager->Copy(handle);
            return CopyHandle;
        }
        int GetModel(const string SearchKey)
        {
            return m.modelResourceManager->GetModelFromSerchKey(SearchKey);
        }
    }
    //=====================================
    //�폜
    //====================================
    namespace Delete
    {
        void DeleteTexture(const int TextureHandle)
        {
            m.textureResourceManager->Erase(m.graphics->Get_device(), TextureHandle);
        }
        void DeleteModel(const int Handle)
        {
            if (m.modelResourceManager == nullptr)return;
            m.modelResourceManager->Erase(m.graphics->Get_device(), Handle);
        }

    }
    //=================================
    // �u�����_�[
    //=================================
    namespace Blender
    {
        void SetBlender(Bland_state type)
        {
           m.graphics->Get_context()->OMSetBlendState(BlendState::Instance().GetBlendState(type),nullptr, 0xFF);
        }
    }
    //===============================
    //�X�|�b�g���C�g
    //=============================
    namespace SpotLight
    {
        //�|�C���g���C�g�̍쐬
        int  Create(VECTOR3 pos, VECTOR4 color, float range)
        {
            return m.pointLightManager->Create(pos, color, range);
        }
        //�|�C���g���C�g�̐ݒ�
        void Set(int handle, VECTOR3 pos, VECTOR4 color, float range)
        {
            m.pointLightManager->Set(handle,pos, color, range);
        }
        //�n���h���̃|�C���g���C�g�̍폜
        void Delete(int& handle)
        {
            m.pointLightManager->Delete(handle);
        }
        //�S����
        void Clear()
        {
            m.pointLightManager->Clear();
        }
    }
    //===============================
    //�G�t�F�N�g
    //=============================
    namespace Lib_Effect
    {
        //�G�t�F�N�g�̏�����
        void Init(int Num)
        {
            Clear();
            m.effectManager->Init(Num,m.graphics->Get_device());
        }
        //�G�t�F�N�g�̍쐬
        int Load(const string name,int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state)
        {
            int handle=-1;
            m.effectManager->Load(m.graphics->Get_device(), name, handle, Maxnum, TextureChipSize, TextureNum, state);
            return handle;
        }
        //�폜
        void Erase(const  int handle)
        {
            m.effectManager->Erase(m.graphics->Get_device(), handle);
        }

        int GetUseLastEffectIndex(const int handle)
        {
           return  m.effectManager->GetSpriteEffectResource(handle)->GetUseLastEffectIndex();
        }
        //�S����
        void Clear()
        {
            m.effectManager->Clear();
        }
        //�^�C�v�ݒ�
        void SetType(const int handle, int type)
        {
            m.effectManager->SetType(handle, type);
        }
        //�G�t�F�N�g���̎擾
        vector<EffectData>* Geteffects(const int handle)
        {
            return m.effectManager->Geteffects(handle);
        }
        SpriteEffect* GetSpriteEffect(const int handle)
        {
            return m.effectManager->GetSpriteEffectResource(handle);
        }
    }
    //=====================================
    //�`��
    //====================================
    namespace Draw
    {
        void Sprite(const int Texturehandle,  VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color)
        {
            TK_Lib::Draw::Sprite(Texturehandle,0,pos,size, cut,angle,color);
        }
        void SliceUIScaleSprite(const int Texturehandle, VECTOR2 pos, VECTOR2 scale , VECTOR2 Slice, VECTOR2 Slice2, VECTOR2 centerSize, VECTOR4 color)
        {
            TextureResource* tex = m.textureResourceManager->GetTextureResource(Texturehandle);
            VECTOR2 size;

            VECTOR2 Scale;
            Scale.x=(scale.x / 2)* tex->GetWidth();
            Scale.y=(scale.y / 2)* tex->GetHeight();
            

            pos.x = pos.x - Scale.x;
            pos.y = pos.y - Scale.y;

            size.x = scale.x * tex->GetWidth();
            size.y = scale.y * tex->GetHeight();

          


            SliceUISprite(Texturehandle,pos, size, Slice, Slice2, centerSize, color);
        }
       
        void SliceUISprite(const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR2 Slice, VECTOR2 Slice2, VECTOR2 centerSize, VECTOR4 color)
        {
            TextureResource* tex = m.textureResourceManager->GetTextureResource(Texturehandle);
            m.shader->Activate(m.graphics->Get_context());


            VECTOR2 scale1;
            scale1.x = size.x / tex->GetWidth();
            scale1.y = size.y / tex->GetHeight();
            float SaveSlicePosX=0;
            float SaveSlicePosY = 0;

            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    
                    //�ʒu
                    VECTOR2 Position;
                    {
                        switch (x)
                        {
                        case 0:Position.x = 0; break;

                        case 1:Position.x = Slice.x * scale1.x;
                     
                             
                               break;

                        case 2:Position.x = SaveSlicePosX + (Slice2.x-Slice.x) * scale1.x;
                          //  SaveSlicePosX = Slice2.x * scale1.x;
                            break;
                        }

                        switch (y)
                        {
                        case 0:Position.y = 0; break;
                        case 1:Position.y = Slice.y * scale1.y;
                            break;
                        case 2:Position.y = SaveSlicePosY + (Slice2.y-Slice.y) * scale1.y; break;
                        }
                    }
                    Position += pos;
                    //�T�C�Y
                    VECTOR2 Size;
                    {
                        switch (x)
                        {
                        case 0:Size.x = Slice.x* scale1.x; break;
                        case 1:Size.x = (Slice2.x- Slice.x) * scale1.x; 
                          
                            Size.x *= centerSize.x;
                            SaveSlicePosX = Size.x;
                            break;
                        case 2:Size.x = (tex->GetWidth()- Slice2.x)* scale1.x; break;
                        }
        

                        switch (y)
                        {
                        case 0:Size.y = Slice.y * scale1.y; break;
                        case 1:Size.y = (Slice2.y- Slice.y) * scale1.y;
                            Size.y *= centerSize.y;
                            SaveSlicePosY = Size.y;
                            break;
                        case 2:Size.y = (tex->GetHeight()- Slice2.y) * scale1.y; break;
                        }
                    }

                    //�J�b�g�ʒu
                    VECTOR4 Cut;
                    {
                        switch (x)
                        {
                        case 0:Cut.x = 0; 
                               Cut.z = Slice.x;
                            break;
                        case 1:Cut.x = Slice.x;
                               Cut.z = Slice2.x- Slice.x;
                            break;
                        case 2:Cut.x = Slice2.x;
                               Cut.z = tex->GetWidth()- Slice2.x;
                               break;
                        }      

                        switch (y)
                        {
                        case 0:Cut.y = 0;
                               Cut.w = Slice.y;
                            break;
                        case 1:Cut.y = Slice.y;
                               Cut.w = Slice2.y- Slice.y;
                            break;
                        case 2:Cut.y = Slice2.y;
                               Cut.w = tex->GetHeight()- Slice2.y;
                            break;
                        }

                    }
                    


                    TK_Lib::Draw::Sprite(Texturehandle, 0, Position, Size, Cut, 0, color);
                }
            }

          
            m.shader->Inactivate(m.graphics->Get_context());
        }
        void Sprite(const int Texturehandle, const int Shaderhandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color)
        {
            TextureResource* tex = m.textureResourceManager->GetTextureResource(Texturehandle);

            m.shader->Activate(m.graphics->Get_context());
            m.sprite->Render(m.graphics->Get_context(), tex, pos, size, cut, angle, color);
            m.shader->Inactivate(m.graphics->Get_context());
        }
        void Sprite(TextureResource* texture,ShaderResource* shader, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color)
        {
            shader->Activate(m.graphics->Get_context());
            m.sprite->Render(m.graphics->Get_context(), texture, pos, size, cut, angle, color);
            shader->Inactivate(m.graphics->Get_context());
        }


        //����
        void Sprite(TextureResource* Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color)
        {
            m.shader->Activate(m.graphics->Get_context());
            m.sprite->Render(m.graphics->Get_context(), Texturehandle, pos, size, cut, angle, color);
            m.shader->Inactivate(m.graphics->Get_context());
        }
    
        //�p��t�H���g�̕`��
        void Font(std::string text, const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 color, float Space)
        {
            TextureResource* tex = m.textureResourceManager->GetTextureResource(Texturehandle);
            m.shader->Activate(m.graphics->Get_context());
            m.sprite->Font(m.graphics->Get_context(), text, tex, pos, size, color, Space);
            m.shader->Inactivate(m.graphics->Get_context());
        }

        //���{�t�H���g�̕`��
        void JapanFont(std::string text, const VECTOR2 Pos)
        {
            m.japanFont->Begin(m.graphics->Get_context());
           

            int iBufferSize = MultiByteToWideChar(CP_ACP, 0, text.c_str()
                , -1, (wchar_t*)NULL, 0);

            // �o�b�t�@�̎擾
            wchar_t* cpUCS2 = new wchar_t[iBufferSize];

            // SJIS �� wstring
            MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, cpUCS2
                , iBufferSize);

            // string�̐���
            std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);



            m.japanFont->Draw(Pos.x, Pos.y, cpUCS2);

            m.japanFont->End(m.graphics->Get_context());

            // �o�b�t�@�̔j��
            delete[] cpUCS2;
            cpUCS2 = nullptr;

           
   
        }
   
      

        void Model(const int modelhandle, const ShaderType type)
        {
            

            //���f���̕`�悷�郊�X�g�ɒǉ�
            BaseShader* Shaderlist[] =
            {
               m.lambertShader,

               //m.shadowShader,
               m.cascadeShader,
               m.cascadeShader,

               m.outlineshader,
               m.noLightShader,
               m.cascadeShader,
            };

            //���f���̎擾
            ModelResource* model= m.modelResourceManager->GetModelResource(modelhandle);
            if (type == ShaderType::Shader_MakeShadow) { model->SetType(ShadowType::makeShadow); }
            if (type == ShaderType::Shader_DrawShadow) { model->SetType(ShadowType::Drawshadow); }

            //Shader�̎擾
            BaseShader* DrawShader= Shaderlist[static_cast<UINT>(type)];
            _ASSERT_EXPR(DrawShader!=nullptr, L"�`��pShdaer��nullptr");

            //�`��p�̃��f���ɓo�^
            DrawShader->ModelRegister(model);
        }
        void CreateShadow()
        {
            //�V���h�E�C���O�V�F�[�_�[
            //�e�p�̃J����
            XMFLOAT4 CameraPos = { Light::GetPos().x,Light::GetPos().y,Light::GetPos().z,1.0f };
            //�e�̐���
            m.shadowShader->ShadowBegin(m.graphics->Get_context(),
                Light::GetView(), Light::GetProjection(),
                CameraPos,
                XMFLOAT4{ 1.0f,1.0f,0.0f,1.0f }, 
                XMFLOAT4{ 0.4f, 0.4f, 0.4f, 0.5f },
                XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f }
            );
            
            for (ModelResource* model : m.shadowShader->Getlist())
            {
                m.shadowShader->Render(m.graphics->Get_context(), model);
            }
            m.shadowShader->ShadowEnd(m.graphics->Get_context());
        }

        
        //�J�X�P�[�h�V���h�E�}�b�v��p
        void RenderCascade()
        {
            if (m.cascadeShader->Getlist().size() <= 0)return;
            //�J�X�P�[�h�V���h�E�}�b�v�̐���
            m.cascadeShader->CreateShadowTexture(m.graphics->Get_context(), *Camera::GetCamera(), Light::GetCamera(), &m.cascadeShader->Getlist());
            //�J�X�P�[�h�V���h�E�}�b�v�̐����I��
            m.cascadeShader->CreateShadowEnd(m.graphics->Get_context(), m.graphics->Get_targetview(), m.graphics->Get_DepthStencilView());


            //�J�X�P�[�h�V���h�E�̏�����
            m.cascadeShader->CascadeShadowBegin(m.graphics->Get_context(), *Camera::GetCamera(), Light::GetCamera());
            //�J�X�P�[�h�V���h�E�̕`��
            m.cascadeShader->CascadeShadowRender(m.graphics->Get_context(), &m.cascadeShader->Getlist(),ShadowType::NONE);
            //�J�X�P�[�h�V���h�E�I��
            m.cascadeShader->End(m.graphics->Get_context());
        }
        void RenderShadow()
        {
            if (m.shadowShader->Getlist().size() <= 0)return;
            //�e�̐���
            CreateShadow();
            //���f���̕`��
            VECTOR4 LightDirection = { Light::GetFront().x,Light::GetFront().y,Light::GetFront().z,1.0f };
            m.shadowShader->Begin(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection(), LightDirection);
            m.graphics->Get_context()->PSSetShaderResources(1, 1, m.shadowShader->GaussTexture->GetShaderResourceView());
            for (ModelResource* model : m.shadowShader->Getlist())
            {
                m.shadowShader->Render(m.graphics->Get_context(), model);
            }
            m.shadowShader->End(m.graphics->Get_context());


           // m.spriteEffectManager->Render(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection());
            
           
        }
        void RenderLambert()
        {
            if (m.lambertShader->Getlist().size() <= 0)return;
            //�����o�[�h�V�F�[�_�[
            VECTOR4 LightDirection = { Light::GetFront().x,Light::GetFront().y,Light::GetFront().z,1.0f };
            m.lambertShader->Begin(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection(), LightDirection);
            for (ModelResource* model : m.lambertShader->Getlist())
            {
                m.lambertShader->Render(m.graphics->Get_context(), model);
            }
            m.lambertShader->End(m.graphics->Get_context());
        }

        void RenderOutline()
        {
            if (m.outlineshader->Getlist().size() <= 0)return;
            //�֊s���V�F�[�_�[
            VECTOR4 LightDirection = { Light::GetFront().x,Light::GetFront().y,Light::GetFront().z,1.0f };
            m.outlineshader->Begin(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection(), LightDirection);
            for (ModelResource* model : m.outlineshader->Getlist())
            {
                m.outlineshader->Render(m.graphics->Get_context(), model);
            }
            m.outlineshader->End(m.graphics->Get_context());
        }

        void RenderNoLight()
        {
            if (m.noLightShader->Getlist().size() <= 0)return;
            //�֊s���V�F�[�_�[
            VECTOR4 LightDirection = { Light::GetFront().x,Light::GetFront().y,Light::GetFront().z,1.0f };
            m.noLightShader->Begin(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection(), LightDirection);
            for (ModelResource* model : m.noLightShader->Getlist())
            {
                m.noLightShader->Render(m.graphics->Get_context(), model);
            }
            m.noLightShader->End(m.graphics->Get_context());
        }


  

        //�S�Ă�Model�`��pShader���܂킵��
        //�o�^����Ă��郂�f����`�悷��
        void AllModelRender()
        {

            //�e
            RenderShadow();
            //�����o�[�g
            RenderLambert();
            //�֊s���V�F�[�_�[
            RenderOutline();
            //�J�X�P�[�h�V���h�E
            RenderCascade();
            //NoLight
            RenderNoLight();
        
      
        

            //m.effectManager->Update(m.timer.time_interval());

            m.effectManager->Update();

            m.effectManager->Begin(m.graphics->Get_context());
            m.effectManager->Render(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection());
            m.effectManager->End(m.graphics->Get_context());

            TK_Lib::Blender::SetBlender(Bland_state::BS_ALPHA);
        //    m.spriteEffectManager->Update(m.timer.time_interval());
        //
        //    m.spriteEffectManager->Fire({ 0,0,0 }, 50);


          
        }
    }
    //==========================
    //�f�o�b�O�֌W
    //==========================
    //2D
    namespace Debug
    {
        void AllRender()
        {
#if IMGUI
        //    TK_Lib::Imgui::UpdateEnd();
#endif
            TK_Lib::Lib_Fade::FadeUpdate();
            TK_Lib::Lib_Fade::FadeRender();

            //2D�e�N�X�`���̕`��
            TK_Lib::Blender::SetBlender(Bland_state::BS_NONE);

           
            m.primitive2DDebugRender->AllDebugDraw(m.graphics->Get_context());

        
            //3D�v���~�e�B�u�̕`��
            ConstantBuffer data;

            

            //m.lambertShader->Begin(m.graphics->Get_context(), TK_Lib::Camera::GetView(), TK_Lib::Camera::GetProjection(), { 1,0,0,1 });


            //ModelResource* model= m.modelResourceManager->GetModelResource(0);
            //m.lambertShader->Render(m.graphics->Get_context(), model);
            //model = m.modelResourceManager->GetModelResource(1);
            //m.lambertShader->Render(m.graphics->Get_context(), model);

        
            //m.lambertShader->End(m.graphics->Get_context());

            //���[���h�r���[�v���W�F�N�V�����̍쐬
            DirectX::XMFLOAT4X4 view_projection;
               //View�̎擾
            DirectX::XMMATRIX V = DirectX::XMLoadFloat4x4(&TK_Lib::Camera::GetView());
            //Projection�̎擾
            DirectX::XMMATRIX P = DirectX::XMLoadFloat4x4(&TK_Lib::Camera::GetProjection());

            DirectX::XMMATRIX VP = V * P;
            DirectX::XMStoreFloat4x4(&view_projection, VP);
            data.worldViewProjection = view_projection;

            m.primitive3DDebugRender->SetConstantBuffer(m.graphics->Get_context(), data);
            m.primitive3DDebugRender->AllDebugDraw(m.graphics->Get_context());


            


        }
        void Clear()
        {
            m.primitive2DDebugRender->Clear();
            m.primitive3DDebugRender->Clear();
        }
    }
    namespace Debug2D
    {
        void Box(VECTOR2 Pos, VECTOR2 Size, float angle, VECTOR4 color, bool FillFlg)
        {
            m.primitive2DDebugRender->DrawBox(Pos, Size, angle, color, FillFlg);
        }
        void Circle(VECTOR2 pos, float radius, VECTOR4 color, bool FillFlg)
        {
            m.primitive2DDebugRender->DrawCircle(pos, radius, color, FillFlg);
        }
        void Line(VECTOR2 pos, VECTOR2 pos2, VECTOR4 color, bool FillFlg)
        {
            m.primitive2DDebugRender->DrawLine(pos, pos2, color, FillFlg);
        }
    }
    //3D
    namespace Debug3D
    {
        void Box(VECTOR3 Pos, VECTOR3 Size, float angle, VECTOR4 color, bool FillFlg)
        {
      //      m.primitive3DDebugRender->DrawBox(Pos, Size, angle, color, FillFlg);
        }
        void Circle(VECTOR3 pos, float radius, VECTOR4 color, bool FillFlg)
        {
            m.primitive3DDebugRender->DrawCircle(pos, radius, color, FillFlg);
        }
        void Line(VECTOR3 pos, VECTOR3 pos2, VECTOR4 color, bool FillFlg)
        {
        //    m.primitive3DDebugRender->DrawLine(pos, pos2, color, FillFlg);
        }
    }

    namespace Imgui
    {
        void Init()
        {
            //imGui������
// Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

                                                                   // Setup Dear ImGui style
            ImGui::StyleColorsClassic();
            //Imgui�̃t�H���g�̐ݒ���s���BIPA�S�V�b�N 14�|�C���g
            io.Fonts->AddFontFromFileTTF("./External/resource\\ipag.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

            //imGui������
            ImGui_ImplWin32_Init(m.hwnd);
            ImGui_ImplDX11_Init(m.graphics->Get_device(), m.graphics->Get_context());
        }


        void UpdateStart()
        {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
        }

        void Update()
        {
           // ImGui::Begin("sss");
           // //  ImGui::TextColored(ImVec4(1, 1, 0, 1), u8"---------�N���A�J���[---------");
           // //  ImGui::SliderFloat(u8"�A�j���[�V�����̑��x", &anime_speed, -2, 2);
           //
           //   //std::string text = std::to_string(elapsedTime);
           // XMFLOAT3 camera_pos = m.cameralib->GetPos();
           // ImGui::Text("Camera_X:%.1f", camera_pos.x);
           // ImGui::Text("Camera_Y:%.1f", camera_pos.y);
           // ImGui::Text("Camera_Z:%.1f", camera_pos.z);


            // ImGui::Text(u8"size=%d�~%d", m_texture->GetTextureWidth(), m_texture->GetTextureHeight());
             //if (ImGui::Begin(u8"�e�N�X�`��", nullptr, ImGuiWindowFlags_None))
            // {
            //    // for (Texture* m_texture : *TextureManager::Instance().Get_textuise())
            //     {
            //         ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf;
            //       //  TextureIndex++;
            //     //    if (selectionTextureIndex == TextureIndex)
            //     //    {
            //             nodeFlags |= ImGuiTreeNodeFlags_Selected;
            //       //  }
            //
            //                    //���C�h��������}���`�o�C�g�����֕ϊ�
            //         char vs_fullname[256];
            //         memset(vs_fullname, NULL, sizeof(vs_fullname));
            //         size_t len;
            //         wcstombs_s(&len, vs_fullname, sizeof(vs_fullname), m.textureResourceManager->GetTextureResource(test_shader_texture[0])->fileName, _TRUNCATE);
            //
            //
            //         if (ImGui::CollapsingHeader(vs_fullname, ImGuiTreeNodeFlags_DefaultOpen))
            //         {
            //             ImGui::TreeNodeEx("a", nodeFlags, vs_fullname);
            //             ImGui::TreePop();
            //
            //             if (ImGui::IsItemClicked())
            //             {
            //                // selectionTextureIndex = TextureIndex;
            //                // SelectTexture = m_texture;
            //
            //             }
            //             int size_X = m.textureResourceManager->GetTexture(test_shader_texture[0])->GetWidth(); 
            //             int size_Y = m.textureResourceManager->GetTexture(test_shader_texture[0])->GetHeight();
            //             ImGui::Image((void*)m.textureResourceManager->GetTexture(3)->GetRenderTargetView(), ImVec2(100, 100));
            //         ImGui::Text(u8"size=%d�~%d", size_X, size_Y);
            //        // ImGui::Image((void*)m.textureResourceManager->GetTexture(test_shader_texture[0])->GetRenderTargetView(), ImVec2(250, 100));
            //      //   ImGui::Image((void*)m.textureResourceManager->GetTexture(test_shader_texture[0])->GetRenderTargetView(), ImVec2(250, 100));
            //         }
            //
            //     }
            // }
            //
            //
        }

        void UpdateEnd()
        {
            ImGui::End();
        }

        void Render()
        {
            // Rendering
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        }

        void End()
        {
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
        }

    }

    //==========================
    //�Q�[���p�b�h�֌W
    //==========================
    namespace Gamepad
    {
        // �{�^�����͏�Ԃ̎擾
        GamePadButton GetButton() {return  m.gamepad->GetButton(); }

        // �{�^��������Ԃ̎擾
        int GetButtonDown(BTN button) { return  m.gamepad->GetButtonDown(button); }

        // �{�^�������Ԃ̎擾
        GamePadButton GetButtonUp()  { return  m.gamepad->GetButtonUp(); }

        // ���X�e�B�b�NX�����͏�Ԃ̎擾
        float GetAxisLX() { return m.gamepad->GetAxisLX(); }

        // ���X�e�B�b�NY�����͏�Ԃ̎擾
        float GetAxisLY() { return m.gamepad->GetAxisLY(); }

        // �E�X�e�B�b�NX�����͏�Ԃ̎擾
        float GetAxisRX() { return m.gamepad->GetAxisRX(); }

        // �E�X�e�B�b�NY�����͏�Ԃ̎擾
        float GetAxisRY() { return m.gamepad->GetAxisRY(); }

        // ���g���K�[���͏�Ԃ̎擾
        float GetTriggerL()  { return m.gamepad->GetTriggerL(); }

        // �E�g���K�[���͏�Ԃ̎擾
        float GetTriggerR()  { return m.gamepad->GetTriggerR(); }

    }

    namespace Lib_Sound
    {
        //�T�E���h�̒ǉ�
        void RegisterSound(const char* fileName, const char* RegisterName)
        {
            m.soundManager->RegisterSound(fileName,RegisterName);
        }
        //�T�E���h�̊J�n
        void SoundPlay(const char* KeyName, bool loopFlg)
        {
            m.soundManager->GetSound(KeyName)->Play(loopFlg);
        }
        //�X�g�b�v
        void SoundStop(const char* KeyName) {
            m.soundManager->GetSound(KeyName)->Stop();
        }

        void SoundSetVolume(const char* KeyName, const float volume) {
            m.soundManager->GetSound(KeyName)->SetVolume(volume);
        }
        void SoundSetPan(const char* KeyName, const float pan) {
            m.soundManager->GetSound(KeyName)->SetPan(pan);
        }
        void SoundClear()
        {
            m.soundManager->SoundClear();
        }
      
    }


    //=========================
    //�O���t�B�b�N�X
    //=========================
    namespace Lib_Graphics
    {
        IDXGISwapChain*         Get_swappchain() { return m.graphics->Get_swappchain(); };
        ID3D11RenderTargetView* Get_targetview() { return m.graphics->Get_targetview(); };
        ID3D11Texture2D* Get_texture2d() { return m.graphics->Get_texture2d(); };
        ID3D11DepthStencilView* Get_DepthStencilView() { return m.graphics->Get_DepthStencilView(); };
        ID3D11ShaderResourceView* Get_ShaderResourceView() { return m.graphics->Get_ShaderResourceView(); };
    }

    //=========================
  //�t�F�[�h�A�E�g
  //=========================
    namespace Lib_Fade
    {
        void FadeInBegin(float Speed)
        {
            m.fade.fadeSpeed = Speed;
            m.fade.type = Fade::FADE_TYPE::FadeIn;
        }
    
        void FadeOutBegin(float Speed)
        {
            m.fade.fadeSpeed = Speed;
            m.fade.type = Fade::FADE_TYPE::FadeOut;
        }

        void FadeUpdate()
        {
            switch (m.fade.type)
            {
            case Fade::FADE_TYPE::FadeIn:
                m.fade.fadeVolumu += m.fade.fadeSpeed;
                if (m.fade.fadeVolumu >= 1)m.fade.fadeVolumu = 1;
                break;
            case Fade::FADE_TYPE::FadeOut:
                m.fade.fadeVolumu -= m.fade.fadeSpeed;
                if (m.fade.fadeVolumu <= 0) {
                    m.fade.fadeVolumu = 0;
                    m.fade.type = Fade::FADE_TYPE::NONE;
                }
                break;
            case Fade::FADE_TYPE::NONE:
                m.fade.fadeVolumu = 0;
                break;
            case Fade::FADE_TYPE::End:
                break;
            }
        }

        void FadeRender()
        {
            TK_Lib::Draw::Sprite(m.fade.fadeTexture, { 0,0 }, TK_Lib::Window::GetWindowSize(), { 0,0,1920,1080 }, 0, {0,0,0,m.fade.fadeVolumu});
        }


        float GetFadeVolume()
        {
            return m.fade.fadeVolumu;
        }
    }


}
