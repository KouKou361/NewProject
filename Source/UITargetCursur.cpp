#include "UIDerived.h"
#include "Charactor.h"
//������
void UITargetCursur::Init()
{

}
//�X�V����
void UITargetCursur::Update()
{

}
//�`�揈��
void UITargetCursur::Render()
{
	if (chara->GetTarget() == nullptr)return;


	VECTOR3 screenPos;
	screenPos = WorldToScreen(chara->GetTarget()->GetPos());

	const float offsetX = -50;
	const float offsetY = -75;
	//�ڕW�̃J�[�\���\��
	TK_Lib::Draw::Sprite(indexTexture, VECTOR2{ screenPos.x + offsetX,screenPos.y + offsetY }, { 100,100 }, { 0,0,256,256 });
}