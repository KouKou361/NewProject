#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectManager;
class SceneGame;
enum class ObjectType
{
	WALL,
	POT,
	TOWER,
	NONE,
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
	void SetCollisionModel(const string& CollisionModelKey);
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

	//ステータスの設定
	void SetStatus(const string& name);

	void HPRender(const int &spriteIndex, const VECTOR2 &pos);
	bool AddDamage(const int& damage, const float& maxInvincibleTime);

	//マスクスタート
	void MaskStart(const float speed);
	//マスク大きさ取得
	float GetMaskVolume();

	inline ObjectType GetType() { return static_cast<ObjectType>(objectType); }
protected:
	int collisionModel = -1;
	ObjectManager* objectManager = nullptr;
	SceneGame* scene = nullptr;

	ObjectType objectType= ObjectType::NONE;
};
