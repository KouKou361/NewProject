#include "Animetion.h"
#include "Lib.h"
//モデルアニメーション登録
void Animetion::Register(const int Animeindex, const string AnimeKey)
{
	//登録
	animeData.insert(make_pair(AnimeKey, Animeindex));
}
//モデルアニメーション番号の取得
int Animetion::GetIndex(const string AnimeKey)
{
	return animeData.at(AnimeKey);
}
//アニメーション中かどうか
bool Animetion::IsAnimetion(const string AnimeKey)
{
	const int AnimeIndex = GetIndex(AnimeKey);
	return TK_Lib::Model::IsPlayAnimetion(AnimeIndex);
}
//モデルアニメーションのクリア
void Animetion::Clear()
{
	animeData.clear();
}
void Animetion::AllAnimetionKey(string* Nameregister)
{
	//アニメーションの登録
	for (int i = 0; End != *Nameregister; i++)
	{
		Register(i, *Nameregister);
		Nameregister++;
	}
}