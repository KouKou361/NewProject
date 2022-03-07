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
	AttackTutoStep = StepTargetEnemy;

	TutoTexture[StepTargetEnemy] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot1.jpg");
	TutoTexture[StepTargetCamera] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot2.jpg");
	TutoTexture[StepAttack] = TK_Lib::Load::LoadTexture("./Data/Sprite/Tuto/tutoScreenShot3.jpg");


}
//����������
void KillDummyEnemyTuto::Init()
{
	ui = make_unique<UITuto>();
	ui->Init();
	TextIndex = 0;
	
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
		AttackTutoStep = StepTargetEnemy;
	}
	else
	{
		AttackTutoStep = StepTargetCamera;
		//�����^�[�Q�b�g�J�����Ɉڍs���Ă���Ȃ�
		if (TK_Lib::Gamepad::GetButtonDown(BTN::LT) >= 1)
		{
			AttackTutoStep = StepAttack;
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
	ui->SetText(textes.at(TextIndex));
	ui->Render();

	ui2DDirection->Render();

	const VECTOR2 pos = { 1200,820 };
	const VECTOR2 pos2 = { 1200,780 };
	const VECTOR2 centerScale = { 2,0.1f };
	const VECTOR4 cut = { 0,0,380,320 };
	const VECTOR2 size = { 200,200 };
		


	switch (AttackTutoStep)
	{
	case StepTargetEnemy:
		TK_Lib::Draw::Sprite(TutoTexture[StepTargetEnemy], pos,size,cut);
		TK_Lib::Draw::JapanFont("�U���ڕW�ɋ߂Â���", pos2);
		break;
	case StepTargetCamera:
		TK_Lib::Draw::Sprite(TutoTexture[StepTargetCamera], pos, size, cut);
		TK_Lib::Draw::JapanFont("L2�������Ȃ���", pos2);
		break;
	case StepAttack:
		TK_Lib::Draw::Sprite(TutoTexture[StepAttack], pos, size, cut);
		TK_Lib::Draw::JapanFont("R2�����ƍU���I(L2�������Ȃ���)", pos2);
		break;
	}

}