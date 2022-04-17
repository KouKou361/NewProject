#pragma once
#include <map>
#include <string>
using namespace std;
class Animetion
{
public:
	const string Idle = "Idle";
	const string Run = "Run";
	const string Attack1 = "Attack1";
	const string Damage = "Damage";
	const string Die = "Die";
	const string End = "End";

	const string BossOpen = "Open";
	const string BossOpenGoToRoll = "OpenGoToRoll";
	const string BossCloseStopRoll = "CloseStopRoll";
	const string BossWalk = "Walk";
	const string BossClose_RollLoop = "Close_RollLoop";
	const string BossClose = "Close";
private:
	map<string, int> animeData;

public:
	Animetion() { Clear(); };
	~Animetion() { Clear(); };

	//モデルアニメーション登録
	void Register(const int animeindex,const string animeKey);
	//モデルアニメーション番号の取得
	int GetIndex(const string animeKey);
	//アニメーション中かどうか
	bool IsAnimetion(const string animeKey);
	//モデルアニメーションのクリア
	void Clear();

};
