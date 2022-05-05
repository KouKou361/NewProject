#include <windows.h>
#include "Framework.h"
#include "Lib.h"
#include "Scene.h"
#include "Export.h"
#include "Collision.h"


const LONG SCREEN_WIDTH = 1920;
const LONG SCREEN_HEIGHT = 1080;

using namespace DirectX;
SceneManager* sceneManager;
std::unique_ptr<FrameWork> framework;
std::unique_ptr<Export> m_export;
std::unique_ptr<Collision> m_collision;


INT WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_  HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
	//初期化処理
	TK_Lib::LibInit(L"TKライブラリ", SCREEN_WIDTH, SCREEN_HEIGHT);
	//ライトの設定
	TK_Lib::Light::SetLookAt({ 60,60,-60 }, { 0,0,0 }, { 0,1,0 });
	TK_Lib::Light::SetOrthongraphic(350.0f, 350.0f, 0.1f, 1500.0f);

    const VECTOR2 Size=TK_Lib::Window::GetWindowSize();
	float aspect = static_cast<float>(Size.x) / static_cast<float>(Size.y);

	TK_Lib::Camera::SetPerspectiveFov(XMConvertToRadians(30), aspect, 5.0f, 1000.0f);
	TK_Lib::Camera::SetLookAt({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });

	//シーン切り替え
	sceneManager = new SceneManager;
	sceneManager->ChangeScene(new SceneTitle());

	
	m_export= make_unique<Export>();
	m_collision= make_unique<Collision>();

	//メインループ
	while (TK_Lib::LibLoop(true))
	{
		//更新処理
		sceneManager->Update();

		//モデルの描画するものを登録する処理
		sceneManager->ModelRender();

		//全てのモデルの描画
		TK_Lib::Draw::AllModelRender();

		//2Dテクスチャの読み込み
		sceneManager->Render();

		//全てのデバッグの描画
		TK_Lib::Debug::AllRender();

		//スクリーンの切り替え
		TK_Lib::Screen::Flip();
	}

	//ゲーム終了の処理（後始末）
	sceneManager->End();

	delete sceneManager;
	sceneManager = nullptr;

	//ここでライブラリーの後始末
	TK_Lib::LibEnd();

	return 0;
}