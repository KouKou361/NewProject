#include "UIDerived.h"
#include "Charactor.h"
//������
void UITargetCursur::Init()
{
	size = { 100,100 };
	cut = { 0,0,256,256 };
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

	VECTOR2 pos = { screenPos.x + offsetX,screenPos.y + offsetY };
	//�ڕW�̃J�[�\���\��
	TK_Lib::Draw::Sprite(TextureIndex, pos, size, cut);
}