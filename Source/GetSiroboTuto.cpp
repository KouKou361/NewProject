#include "Tuto.h"
#include "Collision.h"
#include "Charactor.h"
#include "Scene.h"
#include "SiroboPlayer.h"

GetSiroboTuto::GetSiroboTuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();
	this->sceneGame = sceneGame;
}

//����������
void GetSiroboTuto::Init()
{
	//ui = make_unique<UITuto>();
	TutoWindowUI->Init();
	TutoWindowUI->Update();

	textIndex = 0;

	{
		ui2DDirection = make_shared<UI2DDirection>(sceneGame);
		ui2DDirection->Init();
		ui2DDirection->SetTargetPos({ 100,0,100 });
	}

	//�V���{�̐���
	SummonSirobo();

}

//�X�V����
void GetSiroboTuto::Update()
{
	TutoWindowUI->Update();

	//�ڕW�ʒu�̍X�V����
	ui2DDirection->Update();

}

//���ʏ���(�S�ẴV���{����������ꍇ�Freturn true)
bool GetSiroboTuto::Judge()
{
	int SiroboNum = 0;
	for (int i = 0; i < sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboIndex(i);
		if (Sirobo::StateType::TYPE_IDLE != sirobo->GetState())
		{
			SiroboNum++;
		}
	}
	//�V���{�̐�
	const int MaxSiroboNum = sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboSize();

	if (SiroboNum >= MaxSiroboNum)
	{
		TK_Lib::Lib_Sound::SoundPlay("TutoMisstionClear", false);
		return true;
	}
	return false;
}

//�`��
void GetSiroboTuto::Render()
{
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();
	ui2DDirection->Render();
}

//�V���{�̐���
void GetSiroboTuto::SummonSirobo()
{
	const float PosX = 100.0f;
	const float PosY = 100.0f;

	const int SiroboNum = 3;
	for (int i = 0; i < SiroboNum; i++)
	{
		shared_ptr<Sirobo>sirobo;
		sirobo = make_shared<Sirobo>();
		sirobo->Init(sceneGame->GetPlayer());
		sirobo->SetPos({ PosX,0,static_cast<float>(i * 8) + PosY });
		sceneGame->GetPlayer()->GetSiroboManager()->Register(sirobo);
	}

}