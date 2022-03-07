#include <windows.h>
#include "Framework.h"
#include "Lib.h"
#include "Scene.h"
#include "Export.h"
#include "Collision.h"


LONG SCREEN_WIDTH = 1920;
LONG SCREEN_HEIGHT = 1080;

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

	VECTOR2 Size=TK_Lib::Window::GetWindowSize();
	float aspect = static_cast<float>(Size.x) / static_cast<float>(Size.y);
	//TK_Lib::Camera::SetPerspectiveFov(XMConvertToRadians(30), aspect, 5.0f, 500.0f);
	TK_Lib::Camera::SetPerspectiveFov(XMConvertToRadians(30), aspect, 5.0f, 1000.0f);

	TK_Lib::Camera::SetLookAt({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });

	//sceneManager = make_unique<SceneManager>();
	sceneManager = new SceneManager;
	sceneManager->ChangeScene(new SceneTitle());
	//framework = make_unique<FrameWork>();
	m_export= make_unique<Export>();
	m_collision= make_unique<Collision>();

	//FrameWork::Instance().Initialize();
	//ループ
	while (TK_Lib::LibLoop(true))
	{
	
		//スクリーンのクリア（リセット）
		TK_Lib::Screen::Clear(VECTOR4{0,0,0,1});

		TK_Lib::Blender::SetBlender(Bland_state::BS_ALPHA);

		sceneManager->Update();
		//FrameWork::Instance().Update();

		//VECTOR3 Pos = TK_Lib::Light::GetPos();
		//
		//if (GetKeyState('L') < 0) Pos.x += 0.5f;
		//if (GetKeyState('J') < 0)  Pos.x -= 0.5f;
		//
		//if (GetKeyState('I') < 0)   Pos.y += 0.5f;
		//if (GetKeyState('K') < 0) Pos.y -= 0.5f;
		//
		//if (GetKeyState('U') < 0) Pos.z += 0.5f;
		//if (GetKeyState('O') < 0) Pos.z -= 0.5f;
		//
		//TK_Lib::Light::SetLookAt(Pos, { 0,0,0 }, { 0,1,0 });

		//VECTOR3 scale, angle, pos;
		//scale = { 0.01f,0.01f,0.01f };
		//angle = { 0,0,0 };
		//pos = { 0,0,0 };
	


		sceneManager->ModelRender();
	
		//FrameWork::Instance().ModelRender();
		//全てのモデルの描画
		TK_Lib::Draw::AllModelRender();

		sceneManager->Render();
		//FrameWork::Instance().Render();

		//全てのデバッグの描画
		TK_Lib::Debug::AllRender();
		//TK_Lib::Debug::Clear();
		//スクリーンの切り替え
		TK_Lib::Screen::Flip();
	}

	sceneManager->End();
	delete sceneManager;
	sceneManager = nullptr;
	//f.End();
	TK_Lib::LibEnd();

	return 0;
}