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


    //ライブラリ初期化(1:名前,2:exeのWidth,3:exeのHeight)
    void LibInit(LPCTSTR caption, int screenWidth, int screenHeight);

    //ライブラリループ(1:フレームタイマーを表示するかどうか)
    bool LibLoop(bool isShowFrameRate = false);

    //ライブラリ終了した時の処理
    void LibEnd();

    HWND* GetHWND();



    //======================================
    //ウィンドウ関係
    //======================================
    namespace Window
    {
        //ウィンドウ初期化
        HWND Init(LPCTSTR caption, int screenWidth, int screenHeight);
        //ウィンドウのサイズを取得
        VECTOR2 GetWindowSize();
        //elapsedTimeの取得
        float GetElapsedTime();
    }

    //======================
  //光源
  //======================
    namespace Light
    {
        void SetLookAt(const VECTOR3& eye,const VECTOR3& focus, const VECTOR3& up);

        void SetOrthongraphic(float Width, float Height, float Near, float Far);

        const DirectX::XMFLOAT4X4& GetView();

        const DirectX::XMFLOAT4X4& GetProjection();

        // 視点取得
        const VECTOR3& GetPos();
        // 注視点取得
        const VECTOR3& GetForward();

        // 上方向取得
        const VECTOR3& GetUp();

        // 前方向取得
        const VECTOR3& GetFront();

        // 右方向取得
        const VECTOR3& GetRight();

    }

    //==========================
    //カメラ関係
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
        //カメラに映っているかどうか
        const bool IsCamera(const VECTOR3& Position,const float R=35.0f);

    }

    //=======================
    //モデル関係 
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
    //スクリーン関係
    //======================================
    namespace Screen
    {
        //ビューポートの設定
        void SetViewPort(VECTOR2 Size= TK_Lib::Window::GetWindowSize());
        //スクリーンのクリア（リセット）
        void Clear(VECTOR4 color = VECTOR4{ 0.5f,0.5f,0.5f,1.0f });
        //スクリーンの切り替え
        void Flip();

    }
    //======================================
    //ロード関係
    //======================================
    namespace Load
    {
        int LoadTexture(const string name);
        int LoadModel(const string name, const string RegisterKey);
        int CopyModel(int handle);
        int GetModel(const string Key);
    }
    //=====================================
    //削除
    //====================================
    namespace Delete
    {
        void DeleteTexture(const int handle);
        void DeleteModel(const int Handle);

    }
    //=====================================
    //描画
    //====================================
    namespace Draw
    {
        void Sprite(const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle = 0, VECTOR4 color = { 1,1,1,1 });
        void SliceUIScaleSprite(const int Texturehandle, VECTOR2 pos, VECTOR2 scale, VECTOR2 Slice, VECTOR2 Slice2, VECTOR2 centerSize = { 1,1 }, VECTOR4 color = { 1,1,1,1 });
        void SliceUISprite(const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR2 Slice, VECTOR2 Slice2, VECTOR2 centerSize = {1,1}, VECTOR4 color = { 1,1,1,1 });
        //代わり
        void Sprite(TextureResource* Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color);
        void Sprite(const int Texturehandle, const int Shaderhandle, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color);
        void Sprite(TextureResource* texture, ShaderResource* shader, VECTOR2 pos, VECTOR2 size, VECTOR4 cut, float angle, VECTOR4 color);
        void Font(std::string text, const int Texturehandle, VECTOR2 pos, VECTOR2 size, VECTOR4 color, float Space = 10);
        void JapanFont(std::string text, const VECTOR2 Pos);
        //モデルの描画するリストに追加
        void Model(const int modelhandle, const ShaderType type);
        void AllModelRender();
    }
    //=================================
    // ブレンダー
    //=================================
    namespace Blender
    {
        void SetBlender(Bland_state type);
    }
    //===============================
    //スポットライト
    //=============================
    namespace SpotLight
    {
        //ポイントライトの作成
        int  Create(VECTOR3 pos, VECTOR4 color, float range);
        //ポイントライトの設定
        void Set(int handle, VECTOR3 pos, VECTOR4 color, float range);
        //ハンドルのポイントライトの削除
        void Delete(int& handle);
        //全消し
        void Clear();
    }
    //===============================
    //エフェクト
    //=============================
    namespace Lib_Effect
    {
         //エフェクトの初期化
        void Init(int Num);
         //エフェクトの作成
         int Load(const string name,  int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state);
         //削除
         void Erase(const  int handle);

         int GetUseLastEffectIndex(const int handle);
         //全消し
         void Clear();
         //タイプ設定
         void SetType(const int handle, int type);
         //エフェクト情報の取得
         vector<EffectData>* Geteffects(const int handle);
         //エフェクトの纏めている情報の取得
         SpriteEffect* GetSpriteEffect(const int handle);
    }

    //==========================
    //デバッグ関係
    //==========================
    namespace Debug
    {
        void AllRender();
        //登録されているデバッグ情報を削除する
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
    //ゲームパッド関係
    //==========================
    namespace Gamepad
    {
        // ボタン入力状態の取得
        GamePadButton GetButton();

        // ボタン押下状態の取得
        int GetButtonDown(BTN Button);

        // ボタン押上状態の取得
        GamePadButton GetButtonUp();

        // 左スティックX軸入力状態の取得
        float GetAxisLX();

        // 左スティックY軸入力状態の取得
        float GetAxisLY();

        // 右スティックX軸入力状態の取得
        float GetAxisRX();

        // 右スティックY軸入力状態の取得
        float GetAxisRY();

        // 左トリガー入力状態の取得
        float GetTriggerL();

        // 右トリガー入力状態の取得
        float GetTriggerR();

    }
    //=========================
    //サウンド
    //=========================
    namespace Lib_Sound
    {
        //サウンドの追加
        void RegisterSound(const char* fileName, const char* RegisterName);
        //サウンドの開始
        void SoundPlay(const char* KeyName,bool loopFlg);
        //ストップ
        void SoundStop(const char* KeyName);

        void SoundSetVolume(const char* KeyName,const float volume);
        void SoundSetPan(const char* KeyName, const float pan);
        void SoundClear();
    }

    //=========================
    //グラフィックス
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
    //フェードアウト
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