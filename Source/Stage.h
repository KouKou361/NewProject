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
	enum StageType
	{
		RENDER_MODEL,//�`��
		NO_MAKE_SHADOW_MODEL,//�e�𐶐����Ȃ��`��
		COLISION_MODEL,//�����蔻��
		NAV_MODEL,//�i�r���b�V��
		END_MODEL,
	};

	int StageIndex[StageType::END_MODEL];
	int skyModel = 0;

	SceneGame* sceneGame;

	unique_ptr<Export> stageExport;
	std::shared_ptr<UINumTower> uiNumTower;
	std::shared_ptr<UITimer> uiTimer;



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
};

enum class EventState
{
	LOOK_PLAYER,//�v���C���[������
	TURN_CAMERA_LOOK_FRONT,//�J��������]���Đ��ʂ�����
	LOOK_ENEMY,
	BACK_CAMERA,
	END
};



class BossStage : public Stage
{
private:
	float timer = 0;
	
	int smoke_driftTexture = -1;
	EventState eventState;
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
};
