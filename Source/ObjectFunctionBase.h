#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectFunctionManager;
class SceneGame;

//FunctionObjectの状態
enum class ObjectFunctionState
{
	STATE_START,
	STATE_RUN,
	STATE_END,
	STATE_NONE
};

//関数の呼び出し
enum class IsFunction
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
	VECTOR3 pos = {0,0,0};
protected:
	SceneGame* sceneGame = nullptr;
	float radius = 0;//半径
	//現在の状態
	ObjectFunctionState state=static_cast<ObjectFunctionState>(ObjectFunctionState::STATE_NONE);
	//関数オブジェクトに入っているかどうか
	IsFunction isFunction = static_cast<IsFunction>(IsFunction::IS_FALSE);

};
