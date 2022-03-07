#include "UIDerived.h"
#include "Charactor.h"
//初期化
void UIPlayerHP::Init()
{

}
//更新処理
void UIPlayerHP::Update()
{

}
//描画処理
void UIPlayerHP::Render()
{
	const VECTOR2 SpriteSize = { 150,150 };
	VECTOR2 HPPosition = { 50,50 };

	//プレイヤーの最大HPの表示
	for (int i = 0; i < chara->GetMaxHp(); i++)
	{
		HPPosition.x += 50;
		TK_Lib::Draw::Sprite(indexTexture, HPPosition, SpriteSize, VECTOR4{ 0,0,256,256 });
	}
	//プレイヤーのHPの表示
	HPPosition = { 50,50 };
	for (int i = 0; i < chara->GetHp(); i++)
	{
		HPPosition.x += 50;
		TK_Lib::Draw::Sprite(indexTexture, HPPosition, SpriteSize, VECTOR4{ 256 * 2,256 * 1,256,256 });
	}

}