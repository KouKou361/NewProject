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
class ExportCSV;
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
	int fontTexture=0;
	int titleSceneBackTitleTexture = 0;
	int smoke_driftTexture = 0;
	int titleLogoTexture = 0;
	int playerTexture = 0;
	int siroboTextue = 0;

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
private:
	//テクスチャの読み込み
	void LoadTexture();
	//サウンドの読み込み
	void LoadSound();
	//バックスクリーン
	void RenderBackScreen();
	//シロボ
	void RenderSirobo();
	//プレイヤー
	void RenderPlayer();
	//シロボ２
	void RenderSirobo2();
	//煙
	void RenderSmoke();
	//タイトルフォント
	void RenderTitleFont();
	//スタートフォント
	void RenderStartFont();
};

class SceneLoad : public Scene
{
//	enum class TextureNum
//	{
//		MASK_SIROBO,
//		MASK_ENEMY,
//		MASK_PLAYER,
//		LOADING_ICON,
//		SIROBO,
//		MASK_END,
//	};
	enum class TextureNum
	{
		LOADING_ICON,
		SIROBO,
		TEXTURE_END,
	};
private:
	int Texture[static_cast<int>(TextureNum::TEXTURE_END)] = {};
//	int lineTexture=0;
//
//	float angle = 0;
//	float linePos=0;
//	static constexpr float maskSpeed = 3.0f;
	

	string text = "";
	unique_ptr<Scene> nextScene=nullptr;
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

	void TextUpdate();
};


class SceneGame : public Scene
{
	friend class Export;

public:

	//モデル番号
	enum class ModelIndex
	{
		PLAYER_MODEL,
		SIROBO_PLAYER_MODEL,
		ENEMY_SLIME_MODEL,
		ENEMY_TURTLESHELL_MODEL,
		ENEMY_BEKOLDER_MODEL,
		ENEMY_CHEST_MODEL,
		ENEMY_BOOM_MODEL,
		//EnemyBoss,
		STAGE_MODEL1,
		STAGE_COLLISION_MODEL1,
		STAGE_NAV1,
		STAGE_MODEL2,
		STAGE_COLLISION_MODEL2,
		STAGE_NAV2,
		PAT,
		TRANING_DUMMY,
		WALL,
		MODEL_END,
	};

	int stageIndex1 = -1;
	int stageIndex2 = -1;
	int stageIndex3 = -1;
private:


	int modelTexture[static_cast<int>(ModelIndex::MODEL_END)] = {};
	int model[static_cast<int>(ModelIndex::MODEL_END)] = {};

	
	unique_ptr<Player> player=nullptr;
	unique_ptr<StageManager> stageManager = nullptr;
	shared_ptr<EnemyManager>enemyManager = nullptr;
	unique_ptr<CameraManager> cameraManager = nullptr;
	shared_ptr<EffectManager> effectManager = nullptr;
	shared_ptr<ObjectManager> objectManager = nullptr;
	shared_ptr<ObjectFunctionManager> objectFunctionManager = nullptr;
	shared_ptr<EXPManager>expManager = nullptr;
	shared_ptr<ExportCSV>exportSCV = nullptr;

	bool clearFlg = false;

	
	//shared_ptr<UIManager> uiManager;
	
	//デバッグ用

	enum class debugType
	{
		DEBUG_PARAMETER,
		DEBUG_COLLISION,
		DEBUG_SHADER,
		DEBUG_NAV,
		DEBUG_CAMERA,
		DEBUG_END
	};
	bool debugType[static_cast<int>(debugType::DEBUG_END)] = {};
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

	void SetGameClear(bool flg) { clearFlg = flg; };

	//終了処理
	void End() override;

	//取得関数
	Player* GetPlayer() { return player.get(); };
	EnemyManager* GetEnemyManager(){ return enemyManager.get(); };
	CameraManager* GetCameraManager() { return cameraManager.get(); };
	EffectManager* GetEffectManager() { return effectManager.get(); };
	ObjectManager* GetObjectManager() { return objectManager.get(); };
	ObjectFunctionManager* GetObjectFunctionManager() { return objectFunctionManager.get(); };
	StageManager* GetStageManager() { return stageManager.get(); };
	//UITimer* GetUiTimer() { return uiTimer.get(); }
	EXPManager* GetExpManager() { return expManager.get(); }
	//UIManager* GetUiManager() { return uiManager.get(); };
	ExportCSV* GetexportSCV() { return exportSCV.get(); };
};

class SceneClear : public Scene
{
private:
	enum class TextureData
	{
		CLEAR_TITLE,
		BACK,
		BACK1,
		BACK2,
		BACK3,
		SIROBO_ANIMETION,
		TEXTURE_END,
	};
	int texture[static_cast<int>(TextureData::TEXTURE_END)] = {};
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
private:
	//サウンドの読み込み
	void CreateSound();

	//シロボの描画
	void RenderSirobo();
};

class SceneOver : public Scene
{
private:
	int fontTexture=0;
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


