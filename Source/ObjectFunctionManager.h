#pragma once
#include "ObjectFunctionBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;


class ObjectFunctionManager
{
public:
	ObjectFunctionManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~ObjectFunctionManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//全削除
	void Clear();
	//登録
	void Register(shared_ptr<ObjectFunctionBase> objectFunction);
	//破棄処理
	void Destroy(ObjectFunctionBase* objectFunction);
	//当たり判定デバッグ
	void CollisionDebug();
	//ObjectFunctionの数の取得
	int GetobjectFunctionesSize() { return objectFunctiones.size(); }
	//ObjecttFunctionの数の取得
	ObjectFunctionBase* GetobjectFunctionesIndex(const int& index) { return objectFunctiones.at(index).get(); }
	SceneGame* GetSceneGama() { return sceneGame; };
private:
	SceneGame* sceneGame;
	vector<shared_ptr<ObjectFunctionBase>>objectFunctiones;
	vector<shared_ptr<ObjectFunctionBase>>remove;
};
