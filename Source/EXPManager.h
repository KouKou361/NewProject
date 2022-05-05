#pragma once
#include "Manager.h"
#include "Lib.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;
class EXP;

class EXPManager 
{
public:
	EXPManager() {};
	EXPManager(SceneGame* scene) { this->scene = scene; };
	~EXPManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�S�폜
	void Clear();

	//�o�^
	void Register(const shared_ptr<EXP>& exp, const VECTOR3& pos);
	//�j������
	void Destroy(const EXP* exp);
	//EXP�̐��̎擾
	int GetexpesSize() { return static_cast<int>(expes.size()); }
	//EXP�̐��̎擾
	EXP* GetexpesIndex(const int& index) { return expes.at(index).get(); }

private:

	vector<shared_ptr<EXP>>expes;
	vector<shared_ptr<EXP>>remove;

	SceneGame* scene=nullptr;

};
