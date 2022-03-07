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
	int FontTexture;
	int TitleSceneBackTitleTexture;
	int smoke_driftTexture;
	int TitleLogoTexture;
	int PlayerTexture;
	int MinionTextue;

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
	
	//�f�o�b�O�p

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

	void SetGameClear(bool flg) { ClearFlg = flg; };

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
	int FontTexture;
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


