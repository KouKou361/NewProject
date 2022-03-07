#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectFunctionManager;
class SceneGame;

//FunctionObjectの状態
enum ObjectFunctionState
{
	State_Start,
	State_Run,
	State_End,
	State_None
};

//関数の呼び出し
enum IsFunction
{
	IS_TRUE,
	IS_FALSE
};


class ObjectFunctionBase
{
public:
	ObjectFunctionBase(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	ObjectFunctionBase() {}
	virtual ~ObjectFunctionBase() {};
protected:
	ObjectFunctionState state;
	IsFunction isFunction;
public:
	//初期化処理
	virtual void Init() = 0;
	//更新処理
	virtual void Update() = 0;
	//当たり判定用
	void CollisionRender();
	//ImGuiのデバッグ
	void ImguiDebug();
	//オブジェクトの破棄処理
	void Destroy();
	//判定
	virtual void Judge()=0;
	//開始処理
	virtual void Start() = 0;
	//更新処理
	virtual void Run() = 0;
	//終了処理
	virtual void End() = 0;
	//範囲内に入っているかどうか
	bool IsCircle(const VECTOR3 Pos);

	VECTOR3 GetPos() { return pos; };
	void SetPos(VECTOR3 pos) { this->pos = pos; };
	void SetRadius(float r) { this->radius=r; };

	void  SetState(ObjectFunctionState state) { this->state = state; };
	ObjectFunctionState GetState() { return this->state; }

	void  SetGetIsFunction(IsFunction isFunction) { this->isFunction = isFunction; };
	IsFunction GetIsFunction() { return this->isFunction; }
private:
	VECTOR3 pos;
protected:
	SceneGame* sceneGame = nullptr;
	float radius = 0;//半径


};
