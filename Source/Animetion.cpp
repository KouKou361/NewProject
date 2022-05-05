#include "Animetion.h"
#include "Lib.h"
//���f���A�j���[�V�����o�^
void Animetion::Register(const int Animeindex, const string AnimeKey)
{
	//�o�^
	animeData.insert(make_pair(AnimeKey, Animeindex));
}
//���f���A�j���[�V�����ԍ��̎擾
int Animetion::GetIndex(const string AnimeKey)
{
	return animeData.at(AnimeKey);
}
//�A�j���[�V���������ǂ���
bool Animetion::IsAnimetion(const string AnimeKey)
{
	const int AnimeIndex = GetIndex(AnimeKey);
	return TK_Lib::Model::IsPlayAnimetion(AnimeIndex);
}
//���f���A�j���[�V�����̃N���A
void Animetion::Clear()
{
	animeData.clear();
}
void Animetion::AllAnimetionKey(string* Nameregister)
{
	//�A�j���[�V�����̓o�^
	for (int i = 0; End != *Nameregister; i++)
	{
		Register(i, *Nameregister);
		Nameregister++;
	}
}