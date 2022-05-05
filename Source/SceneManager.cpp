#include "Scene.h"
SceneManager* SceneManager::instance=nullptr;
SceneManager::SceneManager()
{
	instance = this;
}

//�X�V����
void SceneManager::Update()
{
	currentScene->Update();
}

//2D�`�揈��
void SceneManager::Render()
{
	currentScene->Render();
	//�f�o�b�O
	currentScene->DegugImgui();
}
//3D�`�揈��
void SceneManager::ModelRender()
{
	currentScene->ModelRender();
}
void SceneManager::End()
{
	currentScene->End();
}
//�V�[���؂�ւ�
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