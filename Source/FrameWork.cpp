#include "FrameWork.h"
#include "Scene.h"
FrameWork* FrameWork::instance=nullptr;
FrameWork::FrameWork()
{
	instance = this;
}
//����������
void FrameWork::Initialize()
{
	SceneManager::Instance().ChangeScene(new SceneTitle());
}
//�X�V����
void FrameWork::Update()
{
	SceneManager::Instance().Update();
}
//�`�揈��
void FrameWork::Render()
{
	SceneManager::Instance().Render();
}
//���f���p�̕`�揈��
void FrameWork::ModelRender()
{
	SceneManager::Instance().ModelRender();
}
//�I������
void FrameWork::End()
{

}