#include "Scene.h"
SceneManager* SceneManager::instance=nullptr;
SceneManager::SceneManager()
{
	instance = this;
}
void SceneManager::Update()
{
	currentScene->Update();
}
void SceneManager::Render()
{
	currentScene->Render();
	//デバッグ
	currentScene->DegugImgui();
}
void SceneManager::ModelRender()
{
	currentScene->ModelRender();
}
void SceneManager::End()
{
	currentScene->End();
}
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