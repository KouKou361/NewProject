#include "UIDerived.h"
#include "Charactor.h"
#include "EnemyBase.h"
//������
void UIMinionAttack::Init()
{
	indexTexture = TK_Lib::Load::LoadTexture("Data/Sprite/fonts/font1.png");
}
//�X�V����
void UIMinionAttack::Update()
{

}
//�`�揈��
void UIMinionAttack::Render()
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



		//�~�j�I�����U�����Ă��鐔
		text= std::to_string(enm->GetNumBeAttacked());
		TK_Lib::Draw::Font(text, indexTexture, { screenPos.x + offsetX * 2,screenPos.y }, { 50,50 }, {1,1,1,1});

		TK_Lib::Draw::Font("/", indexTexture, { screenPos.x+offsetX,screenPos.y }, { 50,50 }, { 1,1,1,1 });

		//�~�j�I�����U���o����ő吔
		text = std::to_string(enm->GetMaxBeAttacked());
		TK_Lib::Draw::Font(text, indexTexture, { screenPos.x,screenPos.y }, { 50,50 }, { 1,1,1,1 });

	}


}