#include "Tuto.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "ObjectManager.h"
#include "ObjectDerived.h"
#include "EnemyManager.h"

KillDummyEnemyTuto::KillDummyEnemyTuto(SceneGame* sceneGame)
{
	ui = make_unique<UITuto>();
	ui->Init();



	this->sceneGame = sceneGame;
	attackTutoStep = STEP_TARGET_ENEMY;

	tutoTexture[STEP_TARGET_ENEMY] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot1.jpg");
	tutoTexture[STEP_TARGET_CAMERA] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot2.jpg");
	tutoTexture[STEP_ATTACK] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot3.jpg");


}
//����������
void KillDummyEnemyTuto::Init()
{
	ui = make_unique<UITuto>();
	ui->Init();
	textIndex = 0;
	
	for (int i = 0; i < 2; i++)
	{
		shared_ptr<EnemyDummy> enm;
		enm = make_shared<EnemyDummy>(sceneGame);
		enm->SetPos({ 20+static_cast<float>(30*i),0,20 });
		sceneGame->GetEnemyManager()->Register(enm);
	}
	VECTOR3 pos = { 0,0,0 };
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() > 0)
	{
		pos = sceneGame->GetEnemyManager()->GetEnemiesIndex(0)->GetPos();
	}
	
	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos(pos);
	}

//	shared_ptr<ObjectPot> obj;
//	obj = make_shared<ObjectPot>(sceneGame->GetObjectManager(),sceneGame);
//	obj->SetPos({120,0,150 });
//	sceneGame->GetObjectManager()->Register(obj);



}
void KillDummyEnemyTuto::Update()
{

	//�����v���C���[���^�[�Q�b�g��ߑ����Ă��Ȃ��Ȃ�
	if (sceneGame->GetPlayer()->GetTarget() == nullptr)
	{
		attackTutoStep = STEP_TARGET_ENEMY;
	}
	else
	{
		attackTutoStep = STEP_TARGET_CAMERA;
		//�����^�[�Q�b�g�J�����Ɉڍs���Ă���Ȃ�
		if (TK_Lib::Gamepad::GetButtonDown(BTN::LT) >= 1)
		{
			attackTutoStep = STEP_ATTACK;
		}

	}

	VECTOR3 pos = { 0,0,0 };
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() > 0)
	{
		pos = sceneGame->GetEnemyManager()->GetEnemiesIndex(0)->GetPos();
	}
	ui2DDirection->SetTargetPos(pos);
	ui->Update();
}

//����������
bool KillDummyEnemyTuto::Judge()
{
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() <= 0) {
		TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
		return true;

	}
	return  false;
}
//�`��
void KillDummyEnemyTuto::Render()
{
	ui->SetText(textes.at(textIndex));
	ui->Render();

	ui2DDirection->Render();

	const VECTOR2 pos = { 1200,820 };
	const VECTOR2 pos2 = { 1200,780 };
	const VECTOR2 centerScale = { 2,0.1f };
	const VECTOR4 cut = { 0,0,380,320 };
	const VECTOR2 size = { 200,200 };
		


	switch (attackTutoStep)
	{
	case STEP_TARGET_ENEMY:
		TK_Lib::Draw::Sprite(tutoTexture[STEP_TARGET_ENEMY], pos,size,cut);
		TK_Lib::Draw::JapanFont("�U���ڕW�ɋ߂Â���", pos2);
		break;
	case STEP_TARGET_CAMERA:
		TK_Lib::Draw::Sprite(tutoTexture[STEP_TARGET_CAMERA], pos, size, cut);
		TK_Lib::Draw::JapanFont("L2�������Ȃ���", pos2);
		break;
	case STEP_ATTACK:
		TK_Lib::Draw::Sprite(tutoTexture[STEP_ATTACK], pos, size, cut);
		TK_Lib::Draw::JapanFont("R2�����ƍU���I(L2�������Ȃ���)", pos2);
		break;
	}

}