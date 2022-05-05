#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//�J�n����
void BossEntry::Start()
{
	//�{�X�̓o�ꃂ�[�V�����̎擾
	const int BossEntryAnimetion=owner->GetAnime()->GetIndex(owner->GetAnime()->BossOpen);
	//�{�X�̓o��A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossEntryAnimetion, false);
	//�T�E���h
	TK_Lib::Lib_Sound::SoundPlay("BossEntry", false);
}

//���s����
ActionBase::State BossEntry::Run()
{
	//�U�����[�V�������Ȃ�
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//�A�j���[�V����
		const float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());
		//�{�X�̓o��T�E���h�J�n
		const float BossTranceformStart = 0.42f;
		//�{�X�̓o��T�E���h�I��
		const float BossTranceformEnd = 0.43f;

		//�{�X�̓o��T�E���h�i���̂��烍�{�b�g�ɕϐg����j
		if (AnimetionRate >= BossTranceformStart && AnimetionRate <= BossTranceformEnd)
		{
			//�{�X�T�E���h�̍Đ�
			TK_Lib::Lib_Sound::SoundPlay("BossTranceform", false);	
		}
		return ActionBase::State::RUN;
	}
	return ActionBase::State::COMPLETE;
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
