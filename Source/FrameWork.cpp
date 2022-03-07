#include "FrameWork.h"
#include "Scene.h"
FrameWork* FrameWork::instance=nullptr;
FrameWork::FrameWork()
{
	instance = this;
}
//初期化処理
void FrameWork::Initialize()
{
	SceneManager::Instance().ChangeScene(new SceneTitle());
}
//更新処理
void FrameWork::Update()
{
	SceneManager::Instance().Update();
}
//描画処理
void FrameWork::Render()
{
	SceneManager::Instance().Render();
}
//モデル用の描画処理
void FrameWork::ModelRender()
{
	SceneManager::Instance().ModelRender();
}
//終了処理
void FrameWork::End()
{

}