#pragma once
#include "ObjectFunctionBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;


class ObjectFunctionManager
{
public:
	ObjectFunctionManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~ObjectFunctionManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�S�폜
	void Clear();
	//�o�^
	void Register(shared_ptr<ObjectFunctionBase> objectFunction);
	//�j������
	void Destroy(ObjectFunctionBase* objectFunction);
	//�����蔻��f�o�b�O
	void CollisionDebug();
	//ObjectFunction�̐��̎擾
	int GetobjectFunctionesSize() { return static_cast<int>(objectFunctiones.size()); }
	//ObjecttFunction�̐��̎擾
	ObjectFunctionBase* GetobjectFunctionesIndex(const int& index) { return objectFunctiones.at(index).get(); }
	SceneGame* GetSceneGama() { return sceneGame; };
private:
	//Judge��True�̏ꍇ
	void FunctionIsTrue(ObjectFunctionBase* obj);
	//Judge��False�̏ꍇ
	void FunctionIsFalse(ObjectFunctionBase* obj);
private:
	SceneGame* sceneGame;
	vector<shared_ptr<ObjectFunctionBase>>objectFunctiones;
	vector<shared_ptr<ObjectFunctionBase>>remove;
};
