#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Lib.h"
//������
void UINumTower::Init()
{
	indexTexture = TK_Lib::Load::LoadTexture("Data/Sprite/TowerIcon.png");
	FontUI = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");
	TowerSound = true;
}
//�X�V����
void UINumTower::Update()
{

	if(scene->GetStageManager()->GetClearJudge()){
		if (TowerSound)
		{
			//���ׂẴ^���[��j��I
			TK_Lib::Lib_Sound::SoundPlay("AllTowerBreak", false);
			TowerSound = false;
		}
	}


	if (BlinkingTimer > 0)
	{
		BlinkingTimer -= TK_Lib::Window::GetElapsedTime();
	}
	else
	{
		BlinkingTimer = 0;
	}

	
}
//�`�揈��
void UINumTower::Render()
{
	if (static_cast<int>(BlinkingTimer) % 2 >= 1)return;
	
	const  float X = 100;
	const  float offsetX = 50;
	const  float offsetY = 80;
	const  float Size = 700;
	const VECTOR2 screenSize = TK_Lib::Window::GetWindowSize();
	static VECTOR2 FontScreenPos = { 1550,230 };
	static VECTOR2 UIScreenPos2 = { 1630,0 };

	ImGui::Begin("test");
	ImGui::SliderFloat2("Pos1", &FontScreenPos.x, 0,1920);
	ImGui::SliderFloat2("Pos2",&UIScreenPos2.x, 0, 1920);
	ImGui::End();

	TK_Lib::Draw::Sprite(indexTexture, UIScreenPos2, VECTOR2{ 200,200 }, VECTOR4{ 0,0,256,256 });

	//�~�j�I�����U���o����ő吔
	std::string Text;
	Text = std::to_string(scene->GetObjectManager()->GetTowerNum());
	//text = "Tower:";
	//TK_Lib::Draw::Font(text+Text, FontUI, screenPos, { 50,50 }, { 1,1,1,1 }, 30);
	if (scene->GetObjectManager()->GetTowerNum() >= 1)
	{

			TK_Lib::Draw::JapanFont("�^���[���󂹁I\n�c��" + Text + "��", { FontScreenPos.x + 100,FontScreenPos.y });
		
	
		return;
	}
		TK_Lib::Draw::JapanFont("�Q�[���N���A�I\n���̃X�e�[�W�ցI", FontScreenPos);
	

}

