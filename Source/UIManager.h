#pragma once
#include "UIBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;
//
//class UIManager :public Manager
//{
//public:
//	UIManager() {};
//	UIManager(SceneGame* scene) { this->scene = scene; };
//	~UIManager() {};
//
//	//����������
//	void Init();
//	//�X�V����
//	void Update();
//	//�`�揈��
//	void Render();
//	//���f���`�揈��
//	void ModelRender() {};
//	//�S�폜
//	void Clear();
//	//�o�^
//	void Register(shared_ptr<UIBase> ui);
//	//�j������
//	void Destroy(UIBase* ui);
//	//UI�̐��̎擾
//	int GetUIsSize() { return UIs.size(); }
//	//UI�̐��̎擾
//	UIBase* GetUIsIndex(const int& index) { return UIs.at(index).get(); }
//
//private:
//
//	vector<shared_ptr<UIBase>>UIs;
//	vector<shared_ptr<UIBase>>remove;
//	SceneGame* scene;
//
//};
