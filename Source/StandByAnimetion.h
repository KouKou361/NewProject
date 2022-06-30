#pragma once
//ここのクラスの意味はシロボが待機中の時に適切なアニメーションにする為にある
class Sirobo;

class BaseStandByAnimetion
{
public:
	BaseStandByAnimetion(){}
	BaseStandByAnimetion(Sirobo* sirobo) :siroboOwner(sirobo) {};
	~BaseStandByAnimetion(){}
protected:
	Sirobo* siroboOwner = nullptr;
public:
	virtual void Init()=0;
	virtual bool Judge(const float Speed) = 0;
};

//歩く
class WalkStandByAnimetion:public BaseStandByAnimetion
{
public:
	WalkStandByAnimetion() {}
	WalkStandByAnimetion(Sirobo* sirobo) :BaseStandByAnimetion(sirobo) {};
	~WalkStandByAnimetion() {};
public:
	//切り替わった時の処理
	void Init();
	//切り替わり処理
	bool Judge(const float Speed);
};
//走る
class RunStandByAnimetion :public BaseStandByAnimetion
{
public:
	RunStandByAnimetion() {};
	RunStandByAnimetion(Sirobo* sirobo) :BaseStandByAnimetion(sirobo) {};
	~RunStandByAnimetion() {};
public:
	//切り替わった時の処理
	void Init();
	//切り替わり処理
	bool Judge(const float Speed);
};
//止まる
class IdelStandByAnimetion :public BaseStandByAnimetion
{
public:
	IdelStandByAnimetion() {};
	IdelStandByAnimetion(Sirobo* sirobo) :BaseStandByAnimetion(sirobo) {};
	~IdelStandByAnimetion() {};
public:
	//切り替わった時の処理
	void Init();
	//切り替わり処理
	bool Judge(const float Speed);
};