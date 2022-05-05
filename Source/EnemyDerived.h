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

private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
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
private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
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
private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
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
private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
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
private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
};

//トレーニングダミー
class EnemyDummy :public EnemyBase
{
public:
	EnemyDummy(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyDummy() {};

	//初期化処理
	void Init();
private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
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



private:
	//アニメション設定
	void SetAnimetion();
	//部位の追加
	void AddSite(string setSiteName);
	//もし子オブジェクトが死亡しているなら
	void CheakChildrenDie();
	//部位達の位置更新処理
	void UpdateAllSiteSetPosition();
	//behaviorTreeの設定
	void SetBehaviorTree();

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
	bool AddDamage(int damage, float setinvincibleTime);
	
	//部位あたる名前
	string siteName;
private:
	//アニメション設定
	void SetAnimetion();
	//behaviorTreeの設定
	void SetBehaviorTree();
};








