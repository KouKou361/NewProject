#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectFunctionManager;
class SceneGame;

//FunctionObject�̏��
enum ObjectFunctionState
{
	State_Start,
	State_Run,
	State_End,
	State_None
};

//�֐��̌Ăяo��
enum IsFunction
{
	IS_TRUE,
	IS_FALSE
};


class ObjectFunctionBase
{
public:
	ObjectFunctionBase(SceneGame* sceneGame) {
		this->sceneGame = sceneGame;
	};
	ObjectFunctionBase() {}
	virtual ~ObjectFunctionBase() {};
protected:
	ObjectFunctionState state;
	IsFunction isFunction;
public:
	//����������
	virtual void Init() = 0;
	//�X�V����
	virtual void Update() = 0;
	//�����蔻��p
	void CollisionRender();
	//ImGui�̃f�o�b�O
	void ImguiDebug();
	//�I�u�W�F�N�g�̔j������
	void Destroy();
	//����
	virtual void Judge()=0;
	//�J�n����
	virtual void Start() = 0;
	//�X�V����
	virtual void Run() = 0;
	//�I������
	virtual void End() = 0;
	//�͈͓��ɓ����Ă��邩�ǂ���
	bool IsCircle(const VECTOR3 Pos);

	VECTOR3 GetPos() { return pos; };
	void SetPos(VECTOR3 pos) { this->pos = pos; };
	void SetRadius(float r) { this->radius=r; };

	void  SetState(ObjectFunctionState state) { this->state = state; };
	ObjectFunctionState GetState() { return this->state; }

	void  SetGetIsFunction(IsFunction isFunction) { this->isFunction = isFunction; };
	IsFunction GetIsFunction() { return this->isFunction; }
private:
	VECTOR3 pos;
protected:
	SceneGame* sceneGame = nullptr;
	float radius = 0;//���a


};
