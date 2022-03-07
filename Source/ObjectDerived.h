#pragma once
#include "ObjectBase.h"
class ObjectManager;

class ObjectWall:public ObjectBase
{
public:
	ObjectWall() {}
	ObjectWall(ObjectManager* ObjectManager, SceneGame* scene) {
		this->objectManager = ObjectManager;
		this->scene = scene;
	};
	~ObjectWall() {};
public:
	//初期化処理
	void Init();
	//更新処理
	void Update();

};

class ObjectPot :public ObjectBase
{

public:
	ObjectPot() {}
	ObjectPot(ObjectManager* ObjectManager, SceneGame* scene) {
		this->objectManager = ObjectManager;
		this->scene = scene;
	};
	~ObjectPot() {};
public:
	//初期化処理
	void Init();
	//更新処理
	void Update();

	bool AddDamage(int Damage, int MaxinvincibleTime);

};


class ObjectTower :public ObjectBase
{
	int spotLightHandle=-1;
	float spotLightRadius = 30.0f;
	float timer=0;
public:
	ObjectTower() {}
	ObjectTower(ObjectManager* ObjectManager, SceneGame* scene) {
		this->objectManager = ObjectManager;
		this->scene = scene;
	};
	~ObjectTower() {};
public:
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//オブジェクトの死亡処理
	void Dead();

};


