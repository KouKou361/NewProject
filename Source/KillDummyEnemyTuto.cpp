#include "Tuto.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "ObjectManager.h"
#include "ObjectDerived.h"
#include "EnemyManager.h"

KillDummyEnemyTuto::KillDummyEnemyTuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();



	this->sceneGame = sceneGame;
	attackTutoStep = TutoStep::STEP_TARGET_ENEMY;

	tutoTexture[static_cast<int>(TutoStep::STEP_TARGET_ENEMY)] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot1.jpg");
	tutoTexture[static_cast<int>(TutoStep::STEP_TARGET_CAMERA)] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot2.jpg");
	tutoTexture[static_cast<int>(TutoStep::STEP_ATTACK)] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot3.jpg");
}
//����������
void KillDummyEnemyTuto::Init()
{
	TutoWindowUI->Init();
	TutoWindowUI->Update();

	textIndex = 0;
	
	//�_�~�[�G�̐���
	SummonDummyEnemy();


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
		attackTutoStep = TutoStep::STEP_TARGET_ENEMY;
	}
	else
	{
		attackTutoStep = TutoStep::STEP_TARGET_CAMERA;
		//�����^�[�Q�b�g�J�����Ɉڍs���Ă���Ȃ�
		if (TK_Lib::Gamepad::GetButtonDown(BTN::LT) >= 1)
		{
			attackTutoStep = TutoStep::STEP_ATTACK;
		}

	}

	VECTOR3 pos = { 0,0,0 };
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() > 0)
	{
		pos = sceneGame->GetEnemyManager()->GetEnemiesIndex(0)->GetPos();
	}

	//UI�̍X�V����
	ui2DDirection->Update();
	TutoWindowUI->Update();
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
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();

	ui2DDirection->Render();

	const VECTOR2 pos = { 1200,820 };
	const VECTOR2 pos2 = { 1200,780 };
	const VECTOR2 centerScale = { 2,0.1f };
	const VECTOR4 cut = { 0,0,380,320 };
	const VECTOR2 size = { 200,200 };
		


	switch (attackTutoStep)
	{
	case TutoStep::STEP_TARGET_ENEMY:
		TK_Lib::Draw::Sprite(tutoTexture[static_cast<int>(TutoStep::STEP_TARGET_ENEMY)], pos,size,cut);
		TK_Lib::Draw::JapanFont("�U���ڕW�ɋ߂Â���", pos2);
		break;
	case TutoStep::STEP_TARGET_CAMERA:
		TK_Lib::Draw::Sprite(tutoTexture[static_cast<int>(TutoStep::STEP_TARGET_CAMERA)], pos, size, cut);
		TK_Lib::Draw::JapanFont("L2�������Ȃ���", pos2);
		break;
	case TutoStep::STEP_ATTACK:
		TK_Lib::Draw::Sprite(tutoTexture[static_cast<int>(TutoStep::STEP_ATTACK)], pos, size, cut);
		TK_Lib::Draw::JapanFont("R2�����ƍU���I(L2�������Ȃ���)", pos2);
		break;
	}

}

//�_�~�[�G�̐���
void KillDummyEnemyTuto::SummonDummyEnemy()
{
	for (int i = 0; i < 2; i++)
	{
		shared_ptr<EnemyDummy> enm;
		enm = make_shared<EnemyDummy>(sceneGame);
		enm->SetPos({ 20 + static_cast<float>(30 * i),0,20 });
		sceneGame->GetEnemyManager()->Register(enm);
	}
	VECTOR3 pos = { 0,0,0 };
	if (sceneGame->GetEnemyManager()->GetEnemiesSize() > 0)
	{
		pos = sceneGame->GetEnemyManager()->GetEnemiesIndex(0)->GetPos();
	}

	ui2DDirection = make_shared<UI2DDirection>(sceneGame);
	ui2DDirection->Init();
	ui2DDirection->SetTargetPos(pos);

}