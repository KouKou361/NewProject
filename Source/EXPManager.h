#pragma once
#include "Manager.h"
#include "Lib.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;
class EXP;

class EXPManager 
{
public:
	EXPManager() {};
	EXPManager(SceneGame* scene) { this->scene = scene; };
	~EXPManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//全削除
	void Clear();

	//登録
	void Register(shared_ptr<EXP> exp, VECTOR3 Pos);
	//破棄処理
	void Destroy(EXP* exp);
	//EXPの数の取得
	int GetexpesSize() { return expes.size(); }
	//EXPの数の取得
	EXP* GetexpesIndex(const int& index) { return expes.at(index).get(); }

private:

	vector<shared_ptr<EXP>>expes;
	vector<shared_ptr<EXP>>remove;

	SceneGame* scene;

};
