#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Lib.h"
//初期化
void UINumTower::Init()
{
	TextureIndex = TK_Lib::Load::LoadTexture("Data/Sprite/TowerIcon.png");
	fontUI = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");
	towerSound = true;
}
//更新処理
void UINumTower::Update()
{

	if(scene->GetStageManager()->GetClearJudge()){
		if (towerSound)
		{
			//すべてのタワーを破壊！
			TK_Lib::Lib_Sound::SoundPlay("AllTowerBreak", false);
			towerSound = false;
		}
	}


	if (breakingTimer > 0)
	{
		breakingTimer -= TK_Lib::Window::GetElapsedTime();
	}
	else
	{
		breakingTimer = 0;
	}

	
}
//テキストの表示
void UINumTower::RenderText()
{

	const VECTOR2 screenSize = TK_Lib::Window::GetWindowSize();
	const VECTOR2 FontScreenPos = { 1550,230 };
	const float offsetX = 100;
	//ミニオンが攻撃出来る最大数
	std::string Text;
	Text = std::to_string(scene->GetObjectManager()->GetTowerNum());
	//text = "Tower:";
	//TK_Lib::Draw::Font(text+Text, FontUI, screenPos, { 50,50 }, { 1,1,1,1 }, 30);
	if (scene->GetObjectManager()->GetTowerNum() >= 1)
	{

		TK_Lib::Draw::JapanFont("タワーを壊せ！\n残り" + Text + "個", { FontScreenPos.x + offsetX,FontScreenPos.y });
		return;
	}
	TK_Lib::Draw::JapanFont("ゲームクリア！\n次のステージへ！", FontScreenPos);


}
//描画処理
void UINumTower::Render()
{
	if (static_cast<int>(breakingTimer) % 2 >= 1)return;
	
	const VECTOR2 size = { 200,200 };
	const VECTOR4 cut = { 0,0,256,256 };
	const VECTOR2 UIScreenPos2 = { 1630,0 };

	//ImGui::Begin("test");
	//ImGui::SliderFloat2("Pos1", &FontScreenPos.x, 0,1920);
	//ImGui::SliderFloat2("Pos2",&UIScreenPos2.x, 0, 1920);
	//ImGui::End();
	
	//タワーのアイコン
	TK_Lib::Draw::Sprite(TextureIndex, UIScreenPos2, size, cut);
	//テキストの表示
	RenderText();
	
}

