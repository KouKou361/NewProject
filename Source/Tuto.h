#pragma once
#include "Lib.h"
#include <string>
#include "UIDerived.h"
#include "Export.h"
class SceneGame;
class UI2DDirection;
using namespace std;

class Tuto
{

	
protected:
	SceneGame* sceneGame=nullptr;
	unique_ptr<UITuto>  TutoWindowUI = nullptr;
	std::unique_ptr<UINextMessage> uiNextMessage = nullptr;
	std::vector <string>textes;
	int textIndex = 0;
	float uiTimer = 0;
	std::shared_ptr<UI2DDirection> ui2DDirection = nullptr;
public:
	Tuto() {};
	Tuto(SceneGame* sceneGame);
	~Tuto() {};


	//����������
	virtual void Init();
	//�X�V����
	virtual void Update();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	virtual bool Judge();
	//�`��
	virtual void Render();

	//�e�L�X�g�̒ǉ�
	inline void AddText(const string text) { textes.push_back(text); };
	//�e�L�X�g
	inline void SetText(const string text) { this->TutoWindowUI->SetText(text); }

	inline UITuto* GetUi() { return TutoWindowUI.get(); };

};
class MoveTuto:public Tuto
{
	class ClearCircle
	{
	public:
		VECTOR3 pos = {0,0,0};
		float radius=0;
		float weight = 0;
	};
	ClearCircle circle = {};
public:
	MoveTuto(SceneGame* sceneGame);
	~MoveTuto() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	bool Judge();
	//�`��
	void Render();
};
class GetSiroboTuto :public Tuto
{
public:
	GetSiroboTuto(SceneGame* sceneGame);
	~GetSiroboTuto() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	bool Judge();
	//�`��
	void Render();
private:
	void SummonSirobo();
};
class KillDummyEnemyTuto :public Tuto
{
	enum class TutoStep
	{
		STEP_TARGET_ENEMY,
		STEP_TARGET_CAMERA,
		STEP_ATTACK,
		STEP_END,
	};
private:
	TutoStep attackTutoStep = TutoStep::STEP_TARGET_ENEMY;
	int tutoTexture[static_cast<int>(TutoStep::STEP_END)];
public:
	KillDummyEnemyTuto(SceneGame* sceneGame);
	~KillDummyEnemyTuto() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	bool Judge();
	//�`��
	void Render();
private:
	//�_�~�[�G�̐���
	void SummonDummyEnemy();
};
class ResurectionSiroboTuto :public Tuto
{
public:
	ResurectionSiroboTuto(SceneGame* sceneGame);
	~ResurectionSiroboTuto() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	bool Judge();
	//�`��
	void Render();
};

class KillEnemyTuto :public Tuto
{
public:
	KillEnemyTuto(SceneGame* sceneGame);
	~KillEnemyTuto() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//UI�̍X�V����
	void UiTargetUpdate();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	bool Judge();
	//�`��
	void Render();
private:
	//�G�̐���
	void SummonEnemy();
	//�I�u�W�F�N�g�̐���
	void SummonObject();
};


