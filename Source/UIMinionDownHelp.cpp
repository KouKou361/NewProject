#include "UIDerived.h"
#include "Charactor.h"
//初期化
void UIMinionDownHelp::Init()
{

}
//更新処理
void UIMinionDownHelp::Update()
{

}
//描画処理
void UIMinionDownHelp::Render()
{
	{

		VECTOR3 screenPos;

		screenPos = WorldToScreen(chara->GetPos());

		const float offsetX = -30;
		const float offsetY = -85;
		const int Index = 3;
		const int Indexgage = 4;
		const float OneTextureSize = 256;

		const float ResurectionRalt = (value / 60);
		const float size = 50.0f;

		TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY }, { size,size }, { 0,0,OneTextureSize,OneTextureSize });

		TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY -ResurectionRalt* size + size }, { size,size * ResurectionRalt }, { OneTextureSize,0, OneTextureSize,OneTextureSize });
		////ふちの描画
		//TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY }, { 50,50 }, { OneTextureSize * (Index + 2),0,OneTextureSize,OneTextureSize });
		////青メーター
		//TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY }, { 50,50 }, { OneTextureSize * (Index + 1),0,OneTextureSize,(value / 60) * OneTextureSize });
		////□の描画
		//TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY }, { 50,50 }, { OneTextureSize * Index,0,OneTextureSize,OneTextureSize });

	}


}