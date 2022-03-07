#include "UIDerived.h"
#include "Charactor.h"
//初期化
void UITargetHP::Init()
{
	indexTexture=TK_Lib::Load::LoadTexture("./Data/Sprite/HP_gage.png");
}
//更新処理
void UITargetHP::Update()
{

}
//描画処理
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
	const  float TargetHpRatio = (static_cast<float>(chara->GetTarget()->GetHp()) / static_cast<float>(chara->GetTarget()->GetMaxHp())) * HpSize;
	//黒
	TK_Lib::Draw::Sprite(indexTexture, { screenPos.x,screenPos.y }, VECTOR2{ HpSize       ,10 }, VECTOR4{ 0,(60 / 4) * 3,942 / 3,60 / 4 });
	//ゲージ
	TK_Lib::Draw::Sprite(indexTexture, { screenPos.x,screenPos.y }, VECTOR2{ TargetHpRatio,10 }, VECTOR4{ 0,0,942 / 3,60 / 4 });
}