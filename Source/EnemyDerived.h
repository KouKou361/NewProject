#pragma once
class EnemyBase;
class EnemyManager;
class SceneGame;
//ƒXƒ‰ƒCƒ€“G
class EnemySlime :public EnemyBase
{
public:
	EnemySlime(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemySlime() { };

	//‰Šú‰»ˆ—
	void Init();
};

//‹T“G
class EnemyTurtleShell :public EnemyBase
{

public:
	EnemyTurtleShell(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyTurtleShell() {};

	//‰Šú‰»ˆ—
	void Init();
};

//•‚—V“G
class EnemyBeholder :public EnemyBase
{
public:
	EnemyBeholder(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBeholder() {};

	//‰Šú‰»ˆ—
	void Init();
};

//•ó” “G
class EnemyChest :public EnemyBase
{
public:
	EnemyChest(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyChest() {};

	//‰Šú‰»ˆ—
	void Init();
};

//”š’e“G
class EnemyBoom :public EnemyBase
{
public:
	EnemyBoom(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBoom() {};

	//‰Šú‰»ˆ—
	void Init();
};

//”š’e“G
class EnemyDummy :public EnemyBase
{
public:
	EnemyDummy(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyDummy() {};

	//‰Šú‰»ˆ—
	void Init();
};

//ƒ{ƒX“G
class EnemyBoss :public EnemyBase
{
private:

public:
	EnemyBoss(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemyBoss() {};

	//‰Šú‰»ˆ—
	void Init();

	void Update();

	void TargetComplete();

	//•`‰æˆ—
	void ModelRender();

	//‚à‚µqƒIƒuƒWƒFƒNƒg‚ª€–S‚µ‚Ä‚¢‚é‚È‚ç
	void CheakChildrenDie();
};

//”š’e“G
class EnemySite :public EnemyBase
{
public:
	EnemySite(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	~EnemySite() {};

	//‰Šú‰»ˆ—
	void Init();

	//XVˆ—
	void Update();



	//ƒ_ƒ[ƒW‚ğ”»’è
	bool AddDamage(int Damage, int SetinvincibleTime);
};








