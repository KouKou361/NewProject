#include "UIDerived.h"
#include "Charactor.h"
//������
void UIPlayerHP::Init()
{

}
//�X�V����
void UIPlayerHP::Update()
{

}
//�`�揈��
void UIPlayerHP::Render()
{
	const VECTOR2 SpriteSize = { 150,150 };
	VECTOR2 HPPosition = { 50,50 };

	//�v���C���[�̍ő�HP�̕\��
	for (int i = 0; i < chara->GetMaxHp(); i++)
	{
		HPPosition.x += 50;
		TK_Lib::Draw::Sprite(indexTexture, HPPosition, SpriteSize, VECTOR4{ 0,0,256,256 });
	}
	//�v���C���[��HP�̕\��
	HPPosition = { 50,50 };
	for (int i = 0; i < chara->GetHp(); i++)
	{
		HPPosition.x += 50;
		TK_Lib::Draw::Sprite(indexTexture, HPPosition, SpriteSize, VECTOR4{ 256 * 2,256 * 1,256,256 });
	}

}