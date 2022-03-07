#pragma once
#include "Stage.h"
#include "Manager.h"
#include <vector>
#include <memory>
class SceneGame;
using namespace std;
class StageManager :public Manager
{
public:
	StageManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~StageManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//���f���`�揈��
	void ModelRender();
	//�S�폜
	void Clear();
	//�o�^(�Ԃ�l��)
	int Register(shared_ptr<Stage> enm);
	//�X�e�[�W�̕ύX
	void ChangeStage(int StageIndex);
	//���̃X�e�[�W�ֈڍs
	void GoNextStage();
	//���݂̃X�e�[�W�̃Q�[���N���A���Ă��邩�ǂ���
	bool GetClearJudge() { return nowStage->ClearJudge(); }

	//�G�̐��̎擾
	int GetStageSize() { return stages.size(); }
	//�G�̐��̎擾
	Stage* GetStgeIndex(const int& index) { return stages.at(index).get(); }

	Stage* GetNowStage() { return nowStage; };


private:
	SceneGame* sceneGame = nullptr;
	Stage* nowStage=nullptr;
	vector<shared_ptr<Stage>>stages;
};
