#pragma once
#include <memory>
#include "Player.h"
#include "CameraController.h"
#include "EnemyBase.h"
#include "StageManager.h"


class EnemyManager;
class EffectManager;
class ObjectManager;
//class UIManager;
class ObjectFunctionManager;
class EXPManager;
//基底クラス
class Scene
{
private:
	friend class SceneLoad;
	friend class SceneManager;

	bool initialized = false;
protected:
	float timer = 0;
public:
	Scene() {};
	virtual ~Scene() {};
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void DegugImgui() = 0;
	//モデル用の描画処理
	virtual void ModelRender() = 0;
	virtual void End() = 0;



};


class SceneTitle :public Scene
{
private:
	int FontTexture;
	int TitleSceneBackTitleTexture;
	int smoke_driftTexture;
	int TitleLogoTexture;
	int PlayerTexture;
	int MinionTextue;

public:
	SceneTitle() {};
	~SceneTitle() {};
	//初期化処理
	void Initialize() override;
	//更新処理
	void Update() override;
	//描画処理
	void Render() override;
	//デバックのImgui
	void DegugImgui() override;

	//モデル用の描画処理
	void ModelRender() override;
	//終了処理
	void End() override;

};

class SceneLoad : public Scene
{
	enum
	{
		MaskSIROBO,
		MaskEnemy,
		MaskPlayer,
		LoadingIcon,
		Sirobo,
		MaskEnd,
	};
private:

	int MaskTexture[MaskEnd];
	int LineTexture;

	float angle = 0;
	float LinePos;
	static constexpr float MaskSpeed = 3.0f;
	
	string text;

	unique_ptr<Scene> nextScene;
public:
	SceneLoad(Scene* nextScene)
	{//ローディング後遷移するシーンを保持
		this->nextScene.reset(nextScene);
		//uniqueポイン4ターなので=で代入できないが、resetを使用することで可能にしている。
	}
    ~SceneLoad() {}

	//初期化処理
	void Initialize() override;
	//更新処理
	void Update() override;
	//描画処理
	void Render() override;
	//モデル用の描画処理
	void ModelRender() override;
	//デバックのImgui
	void DegugImgui() override;
	//終了処理
	void End() override;
private:

	static void LoadingThread(SceneLoad* scene);

};


class SceneGame : public Scene
{
	friend class Export;

public:

	//モデル番号
	enum ModelIndex
	{
		PlayerModel,
		MinionPlayerModel,
		EnemySlimeModel,
		EnemyTurtleShellModel,
		EnemyBeholderModel,
		EnemyChestModel,
		EnemyBoomModel,
		//EnemyBoss,
		StageModel1,
		StageCollisionModel1,
		StageNav1,
		StageModel2,
		StageCollisionModel2,
		StageNav2,
		Pat,
		Traning_Dummy,
		Wall,
		ModelEnd,
	};

	int stageIndex1 = -1;
	int stageIndex2 = -1;
	int stageIndex3 = -1;
private:


	int ModelTexture[ModelEnd];
	int Model[ModelEnd];

	
	unique_ptr<Player> mPlayer;
	unique_ptr<StageManager> stageManager;
	shared_ptr<EnemyManager>enemyManager;
	unique_ptr<CameraManager> cameraManager;
	shared_ptr<EffectManager> effectManager;
	shared_ptr<ObjectManager> objectManager;
	shared_ptr<ObjectFunctionManager> objectFunctionManager;
	shared_ptr<EXPManager>expManager;

	bool ClearFlg = false;

	
	//shared_ptr<UIManager> uiManager;
	
	//デバッグ用

	enum debugType
	{
		DebugParameter,
		DebugCollision,
		DebugShader,
		DebugNav,
		DebugCamera,
		DebugEnd
	};
	bool debugType[DebugEnd];
public:
	SceneGame() {};
	~SceneGame() {};
	//モデルの読み込み
	void LoadModel();
	//サウンドの読み込み
	void LoadSound();
	//エフェクトの読み込み
	void LoadEffect();
	//初期化処理
	void Initialize() override;
	//更新処理
	void Update() override;
	//描画処理
	void Render() override;
	//デバックのImgui
	void DegugImgui() override;
	//デバッグパラメータ
	void ImguiParameter();
	//デバッグ当たり判定
	void ImguiCollision();
	//デバッグシェーダー
    void ImguiShader();
	//デバッグナビ
	void ImguiNav();
	//デバッグカメラ
	void ImguiCamera();
	//モデル用の描画処理
	void ModelRender() override;

	//ゲームオーバー処理
	bool GameOver();
	//ゲームクリア処理
	bool GameClear();

	void SetGameClear(bool flg) { ClearFlg = flg; };

	//終了処理
	void End() override;

	//取得関数
	Player* GetPlayer() { return mPlayer.get(); };
	EnemyManager* GetEnemyManager(){ return enemyManager.get(); };
	CameraManager* GetCameraManager() { return cameraManager.get(); };
	EffectManager* GetEffectManager() { return effectManager.get(); };
	ObjectManager* GetObjectManager() { return objectManager.get(); };
	ObjectFunctionManager* GetObjectFunctionManager() { return objectFunctionManager.get(); };
	StageManager* GetStageManager() { return stageManager.get(); };
	//UITimer* GetUiTimer() { return uiTimer.get(); }
	EXPManager* GetExpManager() { return expManager.get(); }
	//UIManager* GetUiManager() { return uiManager.get(); };

};

class SceneClear : public Scene
{
private:
	enum TextureData
	{
		Font,
		Back,
		Back1,
		Back2,
		Back3,
		SiroboAnimetion,
		TextureEnd,
	};
	int Texture[TextureData::TextureEnd];
public:
	SceneClear() {};
	~SceneClear() {};
	//初期化処理
	void Initialize() override;
	//更新処理
	void Update() override;
	//描画処理
	void Render() override;
	//デバックのImgui
	void DegugImgui() override;
	//モデル用の描画処理
	void ModelRender() override;
	//終了処理
	void End() override;
};

class SceneOver : public Scene
{
private:
	int FontTexture;
public:
	SceneOver() {};
	~SceneOver() {};
	//初期化処理
	void Initialize() override;
	//更新処理
	void Update() override;
	//描画処理
	void Render() override;
	//デバックのImgui
	void DegugImgui() override;
	//モデル用の描画処理
	void ModelRender() override;
	//終了処理
	void End() override;


};


//----------------------------------
//SceneManager(管理)クラス
//----------------------------------
class SceneManager
{
private:

	std::unique_ptr<Scene> currentScene=nullptr;
	static SceneManager* instance;
public:
	SceneManager();
	~SceneManager() {}
	void Update();
	void Render();
	//モデル用の描画処理
	void ModelRender();
	void End();
	void ChangeScene(Scene* newScene);

	//インスタンス取得
	static SceneManager& Instance()
	{
		return *instance;
	}
};


