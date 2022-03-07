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
	SceneGame* sceneGame;
	unique_ptr<UITuto>  ui;
	std::unique_ptr<UINextMessage> uiNextMessage;
	std::vector <string>textes;
	int TextIndex = 0;
	int uiTimer = 0;
	std::shared_ptr<UI2DDirection> ui2DDirection;
public:
	Tuto() {};
	Tuto(SceneGame* sceneGame);
	~Tuto() {};
	//����������
	virtual void Init();
	//�X�V����
	virtual void Update();
	//�e�L�X�g
	void SetText(string text) { this->ui->SetText(text); }
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	virtual bool Judge();
	//�`��
	virtual void Render();
	//�e�L�X�g�̒ǉ�
	void AddText(string text) { textes.push_back(text); };

	UITuto* GetUi() { return ui.get(); };

};
class MoveTuto:public Tuto
{
	class ClearCircle
	{
	public:
		VECTOR3 Pos;
		float Radius;
		float Weight;
	};
	ClearCircle circle;
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
class GetMinionTuto :public Tuto
{
public:
	GetMinionTuto(SceneGame* sceneGame);
	~GetMinionTuto() {};
	//����������
	void Init();
	//�X�V����
	void Update();
	//���̃e�L�X�g�Ɉڍs�A�I�����菈��
	bool Judge();
	//�`��
	void Render();
};
class KillDummyEnemyTuto :public Tuto
{
	enum
	{
		StepTargetEnemy,
		StepTargetCamera,
		StepAttack,
		StepEnd,
	};
private:
	int AttackTutoStep = 0;
	int TutoTexture[StepEnd];
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
};
class ResurectionMinionTuto :public Tuto
{
public:
	ResurectionMinionTuto(SceneGame* sceneGame);
	~ResurectionMinionTuto() {};
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
};

