#pragma once

#include "Vector.h"
#include <string>
#include "Lib_Blender.h"
#include <DirectXMath.h>
#include "Lib_Texture.h"
#include "Lib_EffectManager.h"
#include "Lib_ModelResource.h"
#include "Mathf.h"

#include "imconfig.h"
#include "imgui.h"            
#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "Lib_GamePad.h"


using namespace std;
using namespace DirectX;
class CameraLib;

enum class ShaderType
{
    ShaderLambert,
    Shader_MakeShadow,
    Shader_DrawShadow,
    Shader_Outline,
    Shader_NoLight,
    Shader_Cascade,
    ShaderEnd,
};
class ShaderResource;


namespace TK_Lib
{


    //���C�u����������(1:���O,2:exe��Width,3:exe��Height)
    void LibInit(LPCTSTR caption, int screenWidth, int screenHeight);

    //���C�u�������[�v(1:�t���[���^�C�}�[��\�����邩�ǂ���)
    bool LibLoop(bool isShowFrameRate = false);

    //���C�u�����I���������̏���
    void LibEnd();

    HWND* GetHWND();



    //======================================
    //�E�B���h�E�֌W
    //======================================
    namespace Window
    {
        //�E�B���h�E������
        HWND Init(LPCTSTR caption, int screenWidth, int screenHeight);
        //�E�B���h�E�̃T�C�Y���擾
        VECTOR2 GetWindowSize();
        //elapsedTime�̎擾
        float GetElapsedTime();
    }

    //======================
  //����
  //======================
    namespace Light
    {
        void SetLookAt(const VECTOR3& eye,const VECTOR3& focus, const VECTOR3& up);

        void SetOrthongraphic(float Width, float Height, float Near, float Far);

        const DirectX::XMFLOAT4X4& GetView();

        const DirectX::XMFLOAT4X4& GetProjection();

        // ���_�擾
        const VECTOR3& GetPos();
        // �����_�擾
        const VECTOR3& GetForward();

        // ������擾
        const VECTOR3& GetUp();

        // �O�����擾
        const VECTOR3& GetFront();

        // �E�����擾
        const VECTOR3& GetRight();

    }

    //==========================
    //�J�����֌W
    //==========================
    namespace Camera
    {
        void SetLookAt(
            const VECTOR3& eye,
            const VECTOR3& focus,
            const VECTOR3& up);

        void SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ);

        const DirectX::XMFLOAT4X4& GetView();

        const DirectX::XMFLOAT4X4& GetProjection();

        const CameraLib* GetCamera();

        const VECTOR3& GetPos();

        const VECTOR3& GetTarget();

        const VECTOR3& GetUp();

        const VECTOR3& GetFront();

        const VECTOR3& GetRight();
        //�J�����ɉf���Ă��邩�ǂ���
        const bool IsCamera(const VECTOR3& Position,const float R=35.0f);

    }

    //=======================
    //���f���֌W 
    //======================

	namespace Model
	{
		void AnimetionUpdate(const int handle);
		void Tranceform(const int handle, XMFLOAT4X4 W);
		void Tranceform(const int handle, VECTOR3 Positoin, VECTOR3 Angle, VECTOR3 Scale);
        void Tranceform(const int handle, VECTOR3 Positoin, VECTOR4 Quoatanion, VECTOR3 Scale);
		void PlayAnimation(const int handle, int animationIndex, bool loop);
        bool IsPlayAnimetion(const int handle);
        vector<std::shared_ptr<ModelResource>>& GetModels();
        void LayPick(const int index, const VECTOR3& start, const VECTOR3& end, RayOut& ray);
        void RadiusLayPick(const int index, const VECTOR3& start, const VECTOR3& end, RayOut& ray, const float R);
        ModelResource::NodeTest* FindNode(int modelIndex, const char* name);
        float GetEndAnimetionTime(int modelIndex);
        float GetAnimetionTime(int modelIndex);
        float IsPlayAnimetionRate(int modelIndex);

        void SetModelTexture(const string ModelName, const string textureName, const int setNum);
        void SetModelTexture(const int setModel, const int TextureIndex, const int setNum);

        void UpdateMask(const int handle);
        void  MaskStart(const int TextureIndex,const float maskSpeed);
        float GetMaskVolume(const int TextureIndex);
	}




    //======================================
    //�X�N���[���֌W
    //======================================
    namespace Screen
    {
        //�r���[�|�[�g�̐ݒ�
        void SetViewPort(VECTOR2 Size= TK_Lib::Window::GetWindowSize());
        //�X�N���[���̃N���A�i���Z�b�g�j
        void Clear(VECTOR4 color = VECTOR4{ 0.5f,0.5f,0.5f,1.0f });
        //�X�N���[���̐؂�ւ�
        void Flip();

    }
    //======================================
    //���[�h�֌W
    //======================================
    namespace Load
    {
        int LoadTexture(const string name);
        int LoadModel(const string name, const string RegisterKey);
        int CopyModel(int handle);
        int GetModel(const string Key);
    }
    //=====================================
    //�폜
    //====================================
    namespace Delete
    {
        void DeleteTexture(const int handle);
        void DeleteModel(const int Handle);

    }
    //=====================================
    //�`��
    //====================================
    namespace Draw
    {
        void Sprite(const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle = 0, VECTOR4 color = { 1,1,1,1 });
        void SliceUIScaleSprite(const int Texturehandle, VECTOR2 pos, VECTOR2 scale, VECTOR2 Slice, VECTOR2 Slice2, VECTOR2 centerSize = { 1,1 }, VECTOR4 color = { 1,1,1,1 });
        void SliceUISprite(const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR2 Slice, VECTOR2 Slice2, VECTOR2 centerSize = {1,1}, VECTOR4 color = { 1,1,1,1 });
        //����
        void Sprite(TextureResource* Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color);
        void Sprite(const int Texturehandle, const int Shaderhandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color);
        void Sprite(TextureResource* texture, ShaderResource* shader, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color);
        void Font(std::string text, const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 color, float Space = 10);
        void JapanFont(std::string text, const VECTOR2 Pos);
        //���f���̕`�悷�郊�X�g�ɒǉ�
        void Model(const int modelhandle, const ShaderType type);
        void AllModelRender();
    }
    //=================================
    // �u�����_�[
    //=================================
    namespace Blender
    {
        void SetBlender(Bland_state type);
    }
    //===============================
    //�X�|�b�g���C�g
    //=============================
    namespace SpotLight
    {
        //�|�C���g���C�g�̍쐬
        int  Create(VECTOR3 pos, VECTOR4 color, float range);
        //�|�C���g���C�g�̐ݒ�
        void Set(int handle, VECTOR3 pos, VECTOR4 color, float range);
        //�n���h���̃|�C���g���C�g�̍폜
        void Delete(int& handle);
        //�S����
        void Clear();
    }
    //===============================
    //�G�t�F�N�g
    //=============================
    namespace Lib_Effect
    {
         //�G�t�F�N�g�̏�����
        void Init(int Num);
         //�G�t�F�N�g�̍쐬
         int Load(const string name,  int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state);
         //�폜
         void Erase(const  int handle);

         int GetUseLastEffectIndex(const int handle);
         //�S����
         void Clear();
         //�^�C�v�ݒ�
         void SetType(const int handle, int type);
         //�G�t�F�N�g���̎擾
         vector<EffectData>* Geteffects(const int handle);
         //�G�t�F�N�g�̓Z�߂Ă�����̎擾
         SpriteEffect* GetSpriteEffect(const int handle);
    }

    //==========================
    //�f�o�b�O�֌W
    //==========================
    namespace Debug
    {
        void AllRender();
        //�o�^����Ă���f�o�b�O�����폜����
        void Clear();
    }
    namespace Debug2D
    {
        void Box(VECTOR2 Pos, VECTOR2 Size, float angle = 0, VECTOR4 Color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);
        void Circle(VECTOR2 pos, float radius, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);
        void Line(VECTOR2 pos, VECTOR2 pos2, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);
    }
    namespace Debug3D
    {
        void Box(VECTOR3 Pos, VECTOR3 Size, float angle = 0, VECTOR4 Color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = false);
        void Circle(VECTOR3 pos, float radius, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = false);
        void Line(VECTOR3 pos, VECTOR3 pos2, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = false);
    }
    //=========================
    //Imgui
    //=========================
    namespace Imgui
    {
        void Init();

        void UpdateStart();

        void Update();

        void UpdateEnd();

        void Render();

        void End();
    }
    //==========================
    //�Q�[���p�b�h�֌W
    //==========================
    namespace Gamepad
    {
        // �{�^�����͏�Ԃ̎擾
        GamePadButton GetButton();

        // �{�^��������Ԃ̎擾
        int GetButtonDown(BTN Button);

        // �{�^�������Ԃ̎擾
        GamePadButton GetButtonUp();

        // ���X�e�B�b�NX�����͏�Ԃ̎擾
        float GetAxisLX();

        // ���X�e�B�b�NY�����͏�Ԃ̎擾
        float GetAxisLY();

        // �E�X�e�B�b�NX�����͏�Ԃ̎擾
        float GetAxisRX();

        // �E�X�e�B�b�NY�����͏�Ԃ̎擾
        float GetAxisRY();

        // ���g���K�[���͏�Ԃ̎擾
        float GetTriggerL();

        // �E�g���K�[���͏�Ԃ̎擾
        float GetTriggerR();

    }
    //=========================
    //�T�E���h
    //=========================
    namespace Lib_Sound
    {
        //�T�E���h�̒ǉ�
        void RegisterSound(const char* fileName, const char* RegisterName);
        //�T�E���h�̊J�n
        void SoundPlay(const char* KeyName,bool loopFlg);
        //�X�g�b�v
        void SoundStop(const char* KeyName);

        void SoundSetVolume(const char* KeyName,const float volume);
        void SoundSetPan(const char* KeyName, const float pan);
        void SoundClear();
    }

    //=========================
    //�O���t�B�b�N�X
    //=========================
    namespace Lib_Graphics
    {
        IDXGISwapChain* Get_swappchain();
        ID3D11RenderTargetView* Get_targetview();
        ID3D11Texture2D* Get_texture2d();
        ID3D11DepthStencilView* Get_DepthStencilView();
        ID3D11ShaderResourceView* Get_ShaderResourceView();
    }
    

    //=========================
    //�t�F�[�h�A�E�g
    //=========================
    namespace  Lib_Fade
    {
        void FadeInBegin(float Speed);
        void FadeOutBegin(float Speed);

        void FadeUpdate();
        void FadeRender();

        float GetFadeVolume();
    }

}