#pragma once
class EnemyBase;
class EnemyManager;
class SceneGame;
//スライム敵
class EnemySlime :public EnemyBase
{
public:
	EnemySlime(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemySlime() { };

	//初期化処理
	void Init();
};

//亀敵
class EnemyTurtleShell :public EnemyBase
{

public:
	EnemyTurtleShell(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyTurtleShell() {};

	//初期化処理
	void Init();
};

//浮遊敵
class EnemyBeholder :public EnemyBase
{
public:
	EnemyBeholder(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBeholder() {};

	//初期化処理
	void Init();
};

//宝箱敵
class EnemyChest :public EnemyBase
{
public:
	EnemyChest(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyChest() {};

	//初期化処理
	void Init();
};

//爆弾敵
class EnemyBoom :public EnemyBase
{
public:
	EnemyBoom(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBoom() {};

	//初期化処理
	void Init();
};

//爆弾敵
class EnemyDummy :public EnemyBase
{
public:
	EnemyDummy(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyDummy() {};

	//初期化処理
	void Init();
};

//ボス敵
class EnemyBoss :public EnemyBase
{
private:

public:
	EnemyBoss(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBoss() {};

	//初期化処理
	void Init();

	void Update();

	void TargetComplete();

	//描画処理
	void ModelRender();

	//もし子オブジェクトが死亡しているなら
	void CheakChildrenDie();
};

//爆弾敵
class EnemySite :public EnemyBase
{
public:
	EnemySite(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemySite() {};

	//初期化処理
	void Init();

	//更新処理
	void Update();



	//ダメージを判定
	bool AddDamage(int Damage, int SetinvincibleTime);
};








