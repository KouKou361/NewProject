#pragma once

#include "Lib.h"
#include <string>
#include "Export.h"
class SceneGame;
class Tuto;
class UINumTower;
class UITimer;
class EnemyBase;
class CameraBossEntry;

using namespace std;

class Stage
{
protected:

	//�X�e�[�W�^�C�v
	enum class StageType
	{
		RENDER_MODEL,//�`��
		NO_MAKE_SHADOW_MODEL,//�e�𐶐����Ȃ��`��
		COLISION_MODEL,//�����蔻��
		NAV_MODEL,//�i�r���b�V��
		END_MODEL,
	};

	int StageIndex[static_cast<int>(StageType::END_MODEL)] = {};
	int skyModel = 0;

	SceneGame* sceneGame=nullptr;

	unique_ptr<Export> stageExport=nullptr;
	std::shared_ptr<UINumTower> uiNumTower = nullptr;
	std::shared_ptr<UITimer> uiTimer = nullptr;



public:
	Stage() {};
	Stage(const string renderModel, const string noShadowRenderModel, const string collisionModel, const string navModel,
		const VECTOR3 pos, const VECTOR3 angle, const VECTOR3 scale, const string setData, SceneGame* scene);
	~Stage() {};
	//����������
	virtual void Init();
	//�X�V����
	virtual void Update();
	//�`��
	virtual void Render();
	//�`��
	virtual void ModelRender();
	//�I������
	virtual void End();
	//�N���A����
	virtual bool ClearJudge();



	inline UITimer* GetUiTimer() { return uiTimer.get(); }
	inline UINumTower* GetNumTower() { return uiNumTower.get(); }
protected:
	//���S���̋~�ϑ[�u
	void DeadIsResurection();
private:
	//�X�J�C�h�[���̐���
	void CreateSky();
	//�V���{�̐���
	void SummonSirobo();
};

class TutoStage: public Stage
{
private:
	int tutoIndex = 0;
	std::vector<shared_ptr<Tuto>> tutoManager;
	shared_ptr<Tuto> nowTuto=nullptr;

	const int renderUiNumTower = 9;
public:
	TutoStage(){}
	TutoStage(const string renderModel, const string noShadowRenderModel, const string collisionModel, const string navModel,
		const VECTOR3 pos, const VECTOR3 angle, const VECTOR3 scale, const string setData, SceneGame* scene);
	~TutoStage() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`��
	void Render();
	//�`��
	void ModelRender();
	//�I������
	void End();
	//���̃`���[�g���A���ֈڍs����B
	void NextTuto();

	//�N���A����
	bool ClearJudge();
private:
	//�Q�[���I�[�o�[�^�C�}�[����
	void ResurectionGameOverTime(const float time);

};

enum class EventState
{
	LOOK_PLAYER,//�v���C���[������
	TURN_CAMERA_LOOK_FRONT,//�J��������]���Đ��ʂ�����
	LOOK_ENEMY,
	BACK_CAMERA,
	NONE,
	END
};



class BossStage : public Stage
{
private:
	float timer = 0;
	
	int smoke_driftTexture = -1;
	EventState eventState= EventState::NONE;
	int tutoIndex = 0;
	std::vector<shared_ptr<Tuto>> tutoManager;
	shared_ptr<Tuto> nowTuto = nullptr;

	const int RenderUiNumTower = 9;
	//Boss
	EnemyBase* enm = nullptr;
	//�J����
	CameraBossEntry* camera = nullptr;
public:
	BossStage() {}
	BossStage(const string renderModel, const string noShadowRenderModel, const string collisionModel, const string navModel,
		const VECTOR3 pos, const VECTOR3 angle, const VECTOR3 scale, const string setData, SceneGame* scene);
	~BossStage() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`��
	void Render();
	//�`��
	void ModelRender();
	//�I������
	void End();
	//�N���A����
	bool ClearJudge();

	//���ݐi�s���̃C�x���g��Ԃ�
	inline EventState GetEventState() { return eventState; }
private:
	//UI�̍쐬
	void CreateUI();
	//�X�J�C�h�[���̍쐬
	void CreateSky();
	//�{�X�J�����̏����ݒ�
	void InitBossCamera();
	//�V���{�̏���
	void SummonSirobo();
};
