#include "UIDerived.h"
#include "Charactor.h"
//初期化
void UITargetCursur::Init()
{

}
//更新処理
void UITargetCursur::Update()
{

}
//描画処理
void UITargetCursur::Render()
{
	if (chara->GetTarget() == nullptr)return;


	VECTOR3 screenPos;
	screenPos = WorldToScreen(chara->GetTarget()->GetPos());

	const float offsetX = -50;
	const float offsetY = -75;
	//目標のカーソル表示
	TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY }, { 100,100 }, { 0,0,256,256 });
}