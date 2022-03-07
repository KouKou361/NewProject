#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectManager;
class SceneGame;
enum ObjectType
{
	Wall,
	Pot,
	Tower,
};



class ObjectBase :public Actor
{
public:
	ObjectBase(ObjectManager* ObjectManager, SceneGame* scene) {
		this->objectManager = ObjectManager;
		this->scene = scene;
	};
	ObjectBase() {}
	virtual ~ObjectBase() {};
protected:
public:
	//当たり判定用のモデル
	void SetCollisionModel(string CollisionModelKey);
	//初期化処理
	virtual void Init()=0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	void ModelRender();
	//当たり判定用
	void CollisionRender();
	//ImGuiのデバッグ
	void ImguiDebug();
	//オブジェクトの破棄処理
	void Destroy();
	//オブジェクトの死亡処理
	virtual void Dead();
	//オブジェクトのダメージ処理
	void Damage();

	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	bool AddDamage(int Damage, int MaxinvincibleTime = 0);

	ObjectType GetType() { return objectType; }
protected:
	int collisionModel = -1;
	ObjectManager* objectManager = nullptr;
	SceneGame* scene = nullptr;

	ObjectType objectType;
};
