#include "Scene.h"
#include "Lib.h"
//初期化処理
void SceneOver::Initialize()
{
	FontTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/fonts/font0.png");

}
//更新処理
void SceneOver::Update()
{
	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		SceneManager::Instance().ChangeScene(new SceneTitle);
	}
}
//デバック
void SceneOver::DegugImgui()
{
	ImGui::Begin(u8"ゲームオーバー");
	ImGui::End();
}
//描画処理
void SceneOver::Render()
{
	TK_Lib::Draw::Font("OVER", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 }, 20);

}
//モデル用の処理
void SceneOver::ModelRender()
{

}
//終了処理
void SceneOver::End()
{
	TK_Lib::Delete::DeleteTexture(FontTexture);

}