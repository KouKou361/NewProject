#pragma once
#include "ActionBase.h"
class MinionPlayer;

//行動処理基底クラス
class  MinionActionBase:public ActionBase
{
public:
	MinionActionBase(){}
	MinionActionBase(MinionPlayer* minion) :minionOwner(minion) {};
	~MinionActionBase(){}
	// 実行情報
	enum class State
	{
		Run,//実行中
		Failed,		// 実行失敗
		Complete,	// 実行成功
	};

	//実行開始処理
	virtual void Start() = 0;

	//実行処理
	virtual ActionBase::State Run() = 0;

	//実行終了処理
	virtual void End() = 0;

	//Imgui
	virtual void DebugImgui() = 0;

	//もし目標物が消えてしまった場合
	virtual ActionBase::State DeleteTarget();

protected:
	MinionPlayer* minionOwner = nullptr;
};

