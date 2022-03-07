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
		RenderModel,//�`��
		NoMakeShadowModel,//�e�𐶐����Ȃ��`��
		CollisionModel,//�����蔻��
		NavModel,//�i�r���b�V��
		EndModel,
	};

	int StageIndex[StageType::EndModel];
	unique_ptr<Export> stageExport;
	SceneGame* sceneGame;

	std::shared_ptr<UINumTower> uiNumTower;

	std::shared_ptr<UITimer> uiTimer;

	int SkyModel = 0;

public:
	Stage() {};
	Stage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel,
		VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale,string SetData, SceneGame* scene);
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

	UITimer* GetUiTimer() { return uiTimer.get(); }
	UINumTower* GetNumTower() { return uiNumTower.get(); }
};

class TutoStage: public Stage
{
private:
	int TutoIndex = 0;
	std::vector<shared_ptr<Tuto>> TutoManager;
	shared_ptr<Tuto> nowTuto=nullptr;

	const int RenderUiNumTower = 9;
public:
	TutoStage(){}
	TutoStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel,
		VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene);
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
	LookPlayer,//�v���C���[������
	TurnCameraLookFront,//�J��������]���Đ��ʂ�����
	LookEnemy,
	BackCamera,
	End
};



class BossStage : public Stage
{
private:
	float timer = 0;
	
	int smoke_driftTexture = -1;
	EventState eventState;
	int TutoIndex = 0;
	std::vector<shared_ptr<Tuto>> TutoManager;
	shared_ptr<Tuto> nowTuto = nullptr;

	const int RenderUiNumTower = 9;
	//Boss
	EnemyBase* enm = nullptr;
	//�J����
	CameraBossEntry* camera = nullptr;
public:
	BossStage() {}
	BossStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel,
		VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene);
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
	EventState GetEventState() { return eventState; }
};
