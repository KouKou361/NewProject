#pragma once
#include "Tuto.h"
#include "Manager.h"
#include <vector>
#include <memory>
class SceneGame;
using namespace std;
class TutoManager :public Manager
{
public:
	TutoManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~TutoManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�S�폜
	void Clear();

	//�G�̐��̎擾
	inline int GetStageSize() { return stages.size(); }
	//�G�̐��̎擾
	inline Tuto* GetStgeIndex(const int& index) { return stages.at(index).get(); }

private:
	SceneGame* sceneGame = nullptr;
	Stage* nowStage = nullptr;
	vector<shared_ptr<Stage>>stages;
};
