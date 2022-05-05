#include "UIDerived.h"
#include "Charactor.h"
//èâä˙âª
void UITargetHP::Init()
{
	TextureIndex=TK_Lib::Load::LoadTexture("./Data/Sprite/HP_gage.png");

	const float CutX = 0;
	const VECTOR2 ChipSize = { 314,15 };

	GageblackCut = VECTOR4{ CutX,ChipSize.y * 3,   ChipSize.x,ChipSize.y };
	GageCut      = VECTOR4{ CutX,             0,   ChipSize.x,ChipSize.y };
}
//çXêVèàóù
void UITargetHP::Update()
{

}
//ï`âÊèàóù
void UITargetHP::Render()
{
	if (chara->GetTarget() == nullptr)return;


	VECTOR3 screenPos;
	screenPos = WorldToScreen(chara->GetTarget()->GetPos());

	const  float offsetX = 50;
	const  float offsetY = 80;

	screenPos.x -= offsetX;
	screenPos.y -= offsetY;

	const float HpSize = 70;
	const float TargetHpRatio = (static_cast<float>(chara->GetTarget()->GetHp()) / static_cast<float>(chara->GetTarget()->GetMaxHp())) * HpSize;
	const VECTOR2 GaugeChipSize = VECTOR2{ 314,15 };
	const float SizeY = 10.0f;
	//çï
	TK_Lib::Draw::Sprite(TextureIndex, { screenPos.x,screenPos.y }, VECTOR2{ HpSize       ,SizeY }, VECTOR4{ 0,GaugeChipSize.y * 3,GaugeChipSize.x,GaugeChipSize.y });
	//ÉQÅ[ÉW																																	
	TK_Lib::Draw::Sprite(TextureIndex, { screenPos.x,screenPos.y }, VECTOR2{ TargetHpRatio,SizeY }, VECTOR4{ 0,                  0,GaugeChipSize.x,GaugeChipSize.y });
}