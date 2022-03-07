#pragma once
#include "EnemyBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;

class EnemyManager :public Manager
{
public:
	EnemyManager() {};
	EnemyManager(SceneGame* scene) { this->scene = scene; };
	~EnemyManager() {};

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

	//敵の行動をするかどうか
	void SetEnemyActive(bool flg);

	//敵の目標オブジェクト
	void SetTarget(Charactor* Target){ this->Target = Target; }
	//登録
	void Register(shared_ptr<EnemyBase> enm);
	//破棄処理
	void Destroy(EnemyBase* enm);
	//当たり判定デバッグ
	void CollisionDebug();
	//敵の数の取得
	int GetEnemiesSize() { return enemies.size(); }
	//敵の数の取得
	EnemyBase* GetEnemiesIndex(const int &index) { return enemies.at(index).get(); }
	bool CollisionEnemy(const VECTOR3 pos, const float weight, const float collisionRadius, VECTOR3& OutPos, EnemyBase*& OutEnm);

	//敵がやられた時、目標にしていたキャラクターの目標のリセット
	void ResetTheTargetCharacter(EnemyBase* enm);

	EnemyBase* SearchEnemyTag(const EnemyTag tag);

private:

	vector<shared_ptr<EnemyBase>>enemies;
	vector<shared_ptr<EnemyBase>>remove;
	Charactor* Target;
	SceneGame* scene;

};
