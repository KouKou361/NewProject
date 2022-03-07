#pragma once
#include <map>
#include <string>
using namespace std;
class Animetion
{
public:
	Animetion() { Clear(); };
	~Animetion() { Clear(); };

	//���f���A�j���[�V�����o�^
	void Register(const int Animeindex,const string AnimeKey);
	//���f���A�j���[�V�����ԍ��̎擾
	int GetIndex(const string AnimeKey);
	//�A�j���[�V���������ǂ���
	bool IsAnimetion(const string AnimeKey);
	//���f���A�j���[�V�����̃N���A
	void Clear();

	const string Idle = "Idle";
	const string Run  = "Run";
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
	map<string,int> AnimeData;
	
};
