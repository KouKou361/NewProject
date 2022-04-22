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
//���N���X
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
	//���f���p�̕`�揈��
	virtual void ModelRender() = 0;
	virtual void End() = 0;



};


class SceneTitle :public Scene
{
private:
	int fontTexture;
	int titleSceneBackTitleTexture;
	int smoke_driftTexture;
	int titleLogoTexture;
	int playerTexture;
	int minionTextue;

public:
	SceneTitle() {};
	~SceneTitle() {};
	//����������
	void Initialize() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;
	//�f�o�b�N��Imgui
	void DegugImgui() override;

	//���f���p�̕`�揈��
	void ModelRender() override;
	//�I������
	void End() override;

};

class SceneLoad : public Scene
{
	enum
	{
		MASK_SIROBO,
		MASK_ENEMY,
		MASK_PLAYER,
		LOADING_ICON,
		SIROBO,
		MASK_END,
	};
private:

	int maskTexture[MASK_END];
	int lineTexture;

	float angle = 0;
	float linePos;
	static constexpr float maskSpeed = 3.0f;
	
	string text;

	unique_ptr<Scene> nextScene;
public:
	SceneLoad(Scene* nextScene)
	{//���[�f�B���O��J�ڂ���V�[����ێ�
		this->nextScene.reset(nextScene);
		//unique�|�C��4�^�[�Ȃ̂�=�ő���ł��Ȃ����Areset���g�p���邱�Ƃŉ\�ɂ��Ă���B
	}
    ~SceneLoad() {}

	//����������
	void Initialize() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;
	//���f���p�̕`�揈��
	void ModelRender() override;
	//�f�o�b�N��Imgui
	void DegugImgui() override;
	//�I������
	void End() override;
private:

	static void LoadingThread(SceneLoad* scene);

};


class SceneGame : public Scene
{
	friend class Export;

public:

	//���f���ԍ�
	enum ModelIndex
	{
		PLAYER_MODEL,
		MINION_PLAYER_MODEL,
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


	int modelTexture[MODEL_END];
	int model[MODEL_END];

	
	unique_ptr<Player> mPlayer;
	unique_ptr<StageManager> stageManager;
	shared_ptr<EnemyManager>enemyManager;
	unique_ptr<CameraManager> cameraManager;
	shared_ptr<EffectManager> effectManager;
	shared_ptr<ObjectManager> objectManager;
	shared_ptr<ObjectFunctionManager> objectFunctionManager;
	shared_ptr<EXPManager>expManager;
	shared_ptr<ExportCSV>exportSCV;

	bool clearFlg = false;

	
	//shared_ptr<UIManager> uiManager;
	
	//�f�o�b�O�p

	enum debugType
	{
		DEBUG_PARAMETER,
		DEBUG_COLLISION,
		DEBUG_SHADER,
		DEBUG_NAV,
		DEBUG_CAMERA,
		DEBUG_END
	};
	bool debugType[DEBUG_END];
public:
	SceneGame() {};
	~SceneGame() {};
	//���f���̓ǂݍ���
	void LoadModel();
	//�T�E���h�̓ǂݍ���
	void LoadSound();
	//�G�t�F�N�g�̓ǂݍ���
	void LoadEffect();
	//����������
	void Initialize() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;
	//�f�o�b�N��Imgui
	void DegugImgui() override;
	//�f�o�b�O�p�����[�^
	void ImguiParameter();
	//�f�o�b�O�����蔻��
	void ImguiCollision();
	//�f�o�b�O�V�F�[�_�[
    void ImguiShader();
	//�f�o�b�O�i�r
	void ImguiNav();
	//�f�o�b�O�J����
	void ImguiCamera();
	//���f���p�̕`�揈��
	void ModelRender() override;

	//�Q�[���I�[�o�[����
	bool GameOver();
	//�Q�[���N���A����
	bool GameClear();

	void SetGameClear(bool flg) { clearFlg = flg; };

	//�I������
	void End() override;

	//�擾�֐�
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
	ExportCSV* GetexportSCV() { return exportSCV.get(); };
};

class SceneClear : public Scene
{
private:
	enum TextureData
	{
		FONT,
		BACK,
		BACK1,
		BACK2,
		BACK3,
		SIROBO_ANIMETION,
		TEXTURE_END,
	};
	int texture[TextureData::TEXTURE_END];
public:
	SceneClear() {};
	~SceneClear() {};
	//����������
	void Initialize() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;
	//�f�o�b�N��Imgui
	void DegugImgui() override;
	//���f���p�̕`�揈��
	void ModelRender() override;
	//�I������
	void End() override;
};

class SceneOver : public Scene
{
private:
	int fontTexture;
public:
	SceneOver() {};
	~SceneOver() {};
	//����������
	void Initialize() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;
	//�f�o�b�N��Imgui
	void DegugImgui() override;
	//���f���p�̕`�揈��
	void ModelRender() override;
	//�I������
	void End() override;


};


//----------------------------------
//SceneManager(�Ǘ�)�N���X
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
	//���f���p�̕`�揈��
	void ModelRender();
	void End();
	void ChangeScene(Scene* newScene);

	//�C���X�^���X�擾
	static SceneManager& Instance()
	{
		return *instance;
	}
};


