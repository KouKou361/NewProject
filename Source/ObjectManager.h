#pragma once
#include "ObjectBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;


class ObjectManager :public Manager
{
public:
	ObjectManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~ObjectManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//モデル描画処理
	void ModelRender();
	//全削除
	void Clear();
	//登録
	void Register(shared_ptr<ObjectBase> enm);
	//破棄処理
	void Destroy(ObjectBase* enm);
	//当たり判定デバッグ
	void CollisionDebug();
	//Objectの数の取得
	int GetObjesSize() { return static_cast<int>(objes.size()); }
	//Objectの数の取得
	ObjectBase* GetObjesIndex(const int& index) { return objes.at(index).get(); }
	//Objectがやられた時、目標にしていたキャラクターの目標のリセット
	void ResetTheTargetCharacter(ObjectBase* enm);
	bool CollisionCircleObject(const VECTOR3 pos, const float weight, const float collisionRadius, VECTOR3& OutPos, ObjectBase*& Saveobj);
	//現在のタワーの数
	int GetTowerNum();

private:
	SceneGame* sceneGame;
	vector<shared_ptr<ObjectBase>>objes;
	vector<shared_ptr<ObjectBase>>remove;
};
