#pragma once
#include "ObjectFunctionBase.h"
class FunctionStart:public ObjectFunctionBase
{
public:
	FunctionStart() {};
	FunctionStart(SceneGame* SceneGame) {
		this->sceneGame = SceneGame;
	};
	~FunctionStart() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();

	//判定
	void Judge();
	//開始処理
	void Start();
	//更新処理
	void Run();
	//終了処理
	void End();
};

class FunctionEnd :public ObjectFunctionBase
{
private: 
	int spotLightHandle = -1;
public:
	FunctionEnd() {};
	FunctionEnd(SceneGame* SceneGame) {
		this->sceneGame = SceneGame;
	};
	~FunctionEnd() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();

	//判定
	void Judge();
	//開始処理
	void Start();
	//更新処理
	void Run();
	//終了処理
	void End();
};