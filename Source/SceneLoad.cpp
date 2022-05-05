#include "Scene.h"
#include "Lib.h"
#include <thread>
#include "EnemyBase.h"
void SceneLoad::LoadingThread(SceneLoad* scene)
{

    if (scene->nextScene->initialized)return;
    scene->nextScene->Initialize();//ここが長い
    scene->nextScene->initialized = true;
}
//初期化処理
void SceneLoad::Initialize()
{
    text = "ロード中";

    Texture[static_cast<int>(TextureNum::LOADING_ICON)] = TK_Lib::Load::LoadTexture("./Data/Sprite/ScreenLoad/LoadingIcon.png");
    Texture[static_cast<int>(TextureNum::SIROBO)]       = TK_Lib::Load::LoadTexture("./Data/Sprite/ScreenLoad/SiroboAnimetion.png");
    
    //フェードアウト
    const float FadeVulome = 0.02f;
    TK_Lib::Lib_Fade::FadeOutBegin(FadeVulome);

    //スレッド開始
    std::thread thread(LoadingThread, this);
  
    //この関数が抜けてもLoadingThead()を実行させるために手放す
    thread.detach();//終了
}
//更新処理
void SceneLoad::Update()
{
    //テキストの更新処理
    TextUpdate();

    if (nextScene->initialized)
    {
        TK_Lib::Lib_Fade::FadeInBegin(0.02f);
        if (TK_Lib::Lib_Fade::GetFadeVolume() >= 1.0f)
        {
            SceneManager::Instance().ChangeScene(nextScene.release());
        }
    }


  //  linePos += maskSpeed;
   // VECTOR2 ScreenSize = TK_Lib::Window::GetWindowSize();
   // if (linePos >= ScreenSize.x) {
   //     linePos = -ScreenSize.x;
   // }

 
 
}
//描画処理
void SceneLoad::Render()
{
    VECTOR2 ScreenSize = TK_Lib::Window::GetWindowSize();
    //  TK_Lib::Draw::Sprite(LineTexture, { LinePos,0 }, ScreenSize, { 0,0,1920,1080 }, 0);
    //  TK_Lib::Draw::Sprite(LineTexture, { LinePos,0 }, ScreenSize, { 0,0,1920,1080 }, 0);
    //  TK_Lib::Draw::Sprite(MaskTexture[MaskSIROBO], { 0,0 }, ScreenSize, {0,0,1920,1080},0);

      //TK_Lib::Draw::Font("Load", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 }, 20);
     // TK_Lib::Draw::Font(text, FontTexture, { ScreenSize.x-900,ScreenSize.y - 300 }, { 64,64 }, { 1,1,1,1 }, 40);
    const int LoadIconIndex = (static_cast<int>(timer * 60) / 10) % 16;
    const float LoadPos = static_cast<float> (48 * LoadIconIndex);

   // TK_Lib::Draw::JapanFont("シロボ軍団", { 100,100 });

    TK_Lib::Draw::Sprite(Texture[static_cast<int>(TextureNum::LOADING_ICON)], { ScreenSize.x - 100,ScreenSize.y-100 }, { 48,48 }, { LoadPos,0,48,48 });

    const float LoadSiroboIconIndexX = static_cast<float>(static_cast<int>((timer*60) / 5) / 7 )* 256;
    const float LoadSiroboIconIndexY = static_cast<float>(static_cast<int>((timer*60) / 5) % 6 )*256;
 //   const float LoadPos = static_cast<float> (48 * LoadIconI)ndex);
    TK_Lib::Draw::Sprite(Texture[static_cast<int>(TextureNum::SIROBO)], { ScreenSize.x - 500,ScreenSize.y - 150 }, { 100,100 }, { LoadSiroboIconIndexX,LoadSiroboIconIndexY,256,256 });

 

    TK_Lib::Draw::JapanFont(text, { ScreenSize.x-400,ScreenSize.y-100 });
}
//デバック
void SceneLoad::DegugImgui()
{
    ImGui::Begin(u8"ゲームロード");
    ImGui::End();
}
//モデル用の処理
void SceneLoad::ModelRender()
{

}
//終了処理
void SceneLoad::End()
{

}

//テキストの更新処理
void SceneLoad::TextUpdate()
{
    //一秒
    const float Seconds = 60.0f;
    //シロボが描画される時間
    const float AddText = 10.0f;

    timer += TK_Lib::Window::GetElapsedTime();
    if (static_cast<int>(timer * Seconds) % static_cast<int>(AddText) == 1)
    {
        text += ".";
    }

    if (static_cast<int>(timer * Seconds) % static_cast<int>(Seconds) == 1)
    {
        text = "ロード中";
    }
}