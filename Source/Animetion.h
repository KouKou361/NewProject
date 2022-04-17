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

	//���f���A�j���[�V�����o�^
	void Register(const int animeindex,const string animeKey);
	//���f���A�j���[�V�����ԍ��̎擾
	int GetIndex(const string animeKey);
	//�A�j���[�V���������ǂ���
	bool IsAnimetion(const string animeKey);
	//���f���A�j���[�V�����̃N���A
	void Clear();

};
