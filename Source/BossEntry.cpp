#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//�J�n����
void BossEntry::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->BossOpen), false);
	TK_Lib::Lib_Sound::SoundPlay("BossEntry", false);
}

//���s����
ActionBase::State BossEntry::Run()
{
	//�U�����[�V������
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//�T�E���h
		float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

		if (AnimetionRate >= 0.42f)
		{
			if (AnimetionRate <= 0.43f)
			{
				TK_Lib::Lib_Sound::SoundPlay("BossTranceform", false);
			}
		}

		return ActionBase::State::Run;

	}
	return ActionBase::State::Complete;
}

//�I������
void BossEntry::End()
{

}

//�f�o�b�O�p
void BossEntry::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossEntry");
	ImGui::End();
}
