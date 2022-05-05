#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
//初期化
void UISiroboAttack::Init()
{
	TextureIndex = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");
}
//更新処理
void UISiroboAttack::Update()
{

}
//描画処理
void UISiroboAttack::Render()
{
	if (chara->GetTarget() == nullptr)return;
	EnemyBase *enm=nullptr;
	enm = dynamic_cast<EnemyBase*>(chara->GetTarget());
	if (enm == nullptr)return;


	{

		VECTOR3 screenPos;

		screenPos = WorldToScreen(enm->GetPos());

		const float offsetX = -30;
		const float offsetY = -85;
		const int   Index = 3;
		const int   Indexgage = 4;
		const float OneTextureSize = 127;

		const VECTOR2 size = { 50,50 };

		const VECTOR4 color = { 1,1,1,1 };


		//ミニオンが攻撃している数
		text= std::to_string(enm->GetNumBeAttacked());
		TK_Lib::Draw::Font(text, TextureIndex, { screenPos.x + offsetX * 2,screenPos.y }, size, color);

		TK_Lib::Draw::Font("/", TextureIndex, { screenPos.x+offsetX,screenPos.y }, size, color);

		//ミニオンが攻撃出来る最大数
		text = std::to_string(enm->GetMaxBeAttacked());
		TK_Lib::Draw::Font(text, TextureIndex, { screenPos.x,screenPos.y }, size, color);

	}


}