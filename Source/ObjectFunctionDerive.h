#pragma once
#include "ObjectFunctionBase.h"
class FunctionStart:public ObjectFunctionBase
{
public:
	FunctionStart() {};
	FunctionStart(SceneGame* SceneGame) {
		this->sceneGame = SceneGame;
	};
	~FunctionStart() {};

	//����������
	void Init();
	//�X�V����
	void Update();

	//����
	void Judge();
	//�J�n����
	void Start();
	//�X�V����
	void Run();
	//�I������
	void End();
};

class FunctionEnd :public ObjectFunctionBase
{
private: 
	int spotLightHandle = -1;
public:
	FunctionEnd() {};
	FunctionEnd(SceneGame* SceneGame) {
		this->sceneGame = SceneGame;
	};
	~FunctionEnd() {};

	//����������
	void Init();
	//�X�V����
	void Update();

	//����
	void Judge();
	//�J�n����
	void Start();
	//�X�V����
	void Run();
	//�I������
	void End();
};