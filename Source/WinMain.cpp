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
	//����������
	TK_Lib::LibInit(L"TK���C�u����", SCREEN_WIDTH, SCREEN_HEIGHT);
	//���C�g�̐ݒ�
	TK_Lib::Light::SetLookAt({ 60,60,-60 }, { 0,0,0 }, { 0,1,0 });
	TK_Lib::Light::SetOrthongraphic(350.0f, 350.0f, 0.1f, 1500.0f);

    const VECTOR2 Size=TK_Lib::Window::GetWindowSize();
	float aspect = static_cast<float>(Size.x) / static_cast<float>(Size.y);

	TK_Lib::Camera::SetPerspectiveFov(XMConvertToRadians(30), aspect, 5.0f, 1000.0f);
	TK_Lib::Camera::SetLookAt({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });

	//�V�[���؂�ւ�
	sceneManager = new SceneManager;
	sceneManager->ChangeScene(new SceneTitle());

	
	m_export= make_unique<Export>();
	m_collision= make_unique<Collision>();

	//���C�����[�v
	while (TK_Lib::LibLoop(true))
	{
		//�X�V����
		sceneManager->Update();

		//���f���̕`�悷����̂�o�^���鏈��
		sceneManager->ModelRender();

		//�S�Ẵ��f���̕`��
		TK_Lib::Draw::AllModelRender();

		//2D�e�N�X�`���̓ǂݍ���
		sceneManager->Render();

		//�S�Ẵf�o�b�O�̕`��
		TK_Lib::Debug::AllRender();

		//�X�N���[���̐؂�ւ�
		TK_Lib::Screen::Flip();
	}

	//�Q�[���I���̏����i��n���j
	sceneManager->End();

	delete sceneManager;
	sceneManager = nullptr;

	//�����Ń��C�u�����[�̌�n��
	TK_Lib::LibEnd();

	return 0;
}