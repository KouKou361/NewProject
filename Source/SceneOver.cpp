#include "Scene.h"
#include "Lib.h"
//����������
void SceneOver::Initialize()
{
	FontTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/fonts/font0.png");

}
//�X�V����
void SceneOver::Update()
{
	if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	{
		SceneManager::Instance().ChangeScene(new SceneTitle);
	}
}
//�f�o�b�N
void SceneOver::DegugImgui()
{
	ImGui::Begin(u8"�Q�[���I�[�o�[");
	ImGui::End();
}
//�`�揈��
void SceneOver::Render()
{
	TK_Lib::Draw::Font("OVER", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 }, 20);

}
//���f���p�̏���
void SceneOver::ModelRender()
{

}
//�I������
void SceneOver::End()
{
	TK_Lib::Delete::DeleteTexture(FontTexture);

}