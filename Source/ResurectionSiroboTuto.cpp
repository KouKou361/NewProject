#include "Tuto.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "SiroboPlayer.h"
ResurectionSiroboTuto::ResurectionSiroboTuto(SceneGame* sceneGame)
{
	TutoWindowUI = make_unique<UITuto>();
	TutoWindowUI->Init();


	this->sceneGame = sceneGame;
}
//����������
void ResurectionSiroboTuto::Init()
{
	//ui = make_unique<UITuto>();
	TutoWindowUI->Init();
	TutoWindowUI->Update();

	uiTimer = 0;



}
void ResurectionSiroboTuto::Update()
{
	TutoWindowUI->Update();


}

//�����������i�V���{�B���S�����������ꍇ�Freturn true�j
bool ResurectionSiroboTuto::Judge()
{
	int SiroboNum = 0;
	for (int i = 0; i < sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboIndex(i);
		if (Sirobo::StateType::TYPE_STAND_BY == sirobo->GetState())
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
void ResurectionSiroboTuto::Render()
{
	TutoWindowUI->SetText(textes.at(textIndex));
	TutoWindowUI->Render();


}