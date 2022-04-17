#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
//èâä˙âª
void UITuto::Init()
{
	indexTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/MessageWindow.png");
	//NextWindow = TK_Lib::Load::LoadTexture("./Data/Sprite/NotificationWindow.png");



	pos = { 100,700 };
	centerScale = { 1,2 };
	cut = {0,0,256,256};
	size = { 256,256 };

	s1 = { 256 / 3,256 / 3 };
	s2 = { (256 / 3) * 2,(256 / 3) * 2 };

	
}
//çXêVèàóù
void UITuto::Update()
{
	constexpr float MaxCenterScaleX=18.0f;
	centerScale.x += 0.3f;
	if (centerScale.x >= MaxCenterScaleX)
	{
		centerScale.x = MaxCenterScaleX;
	}



}
//ï`âÊèàóù
void UITuto::Render()
{
//	static VECTOR2 P = { 200,400 };
//	static VECTOR2 S = { 256,256 };
//
//	static VECTOR2 S1 = { 256 / 3,256 / 3 };
//	static VECTOR2 S2 = { (256 / 3) * 2,(256 / 3) * 2 };
//	static VECTOR2 S3 = { 1,1 };
//
//	static VECTOR2 centerScale = {1,1};
//
//	ImGui::Begin("Slice");
//	ImGui::SliderFloat2("Pos", &P.x,0,1000);
//	ImGui::SliderFloat2("Size", &S.x, 0, 1000);
//
//	ImGui::SliderFloat2("Slice1", &S1.x, 0, 100);
//	ImGui::SliderFloat2("Slice2", &S2.x, 0, 100);
//	ImGui::SliderFloat2("Slice3", &S3.x, 0, 5);
//	ImGui::SliderFloat2("centerScale", &centerScale.x, 0, 20);
//	ImGui::End();


	
	//WindowÇÃï`âÊ
	TK_Lib::Draw::SliceUISprite(indexTexture, pos, size, s1, s2, centerScale);
	TK_Lib::Draw::JapanFont(text,pos+ fontOffset);



}
