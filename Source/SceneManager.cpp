#include "Scene.h"
SceneManager* SceneManager::instance=nullptr;
SceneManager::SceneManager()
{
	instance = this;
}

//更新処理
void SceneManager::Update()
{
	currentScene->Update();
}

//2D描画処理
void SceneManager::Render()
{
	currentScene->Render();
	//デバッグ
	currentScene->DegugImgui();
}
//3D描画処理
void SceneManager::ModelRender()
{
	currentScene->ModelRender();
}
void SceneManager::End()
{
	currentScene->End();
}
//シーン切り替え
void SceneManager::ChangeScene(Scene* newScene)
{
	if (currentScene != nullptr)
	{
		currentScene->End();
	}
	currentScene.reset(newScene);
	if (!newScene->initialized) {
		currentScene->Initialize();
	}
	
}