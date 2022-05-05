#pragma once
#include "ObjectBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;


class ObjectManager :public Manager
{
public:
	ObjectManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~ObjectManager() {};

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
	//�o�^
	void Register(shared_ptr<ObjectBase> enm);
	//�j������
	void Destroy(ObjectBase* enm);
	//�����蔻��f�o�b�O
	void CollisionDebug();
	//Object�̐��̎擾
	int GetObjesSize() { return static_cast<int>(objes.size()); }
	//Object�̐��̎擾
	ObjectBase* GetObjesIndex(const int& index) { return objes.at(index).get(); }
	//Object�����ꂽ���A�ڕW�ɂ��Ă����L�����N�^�[�̖ڕW�̃��Z�b�g
	void ResetTheTargetCharacter(ObjectBase* enm);
	bool CollisionCircleObject(const VECTOR3 pos, const float weight, const float collisionRadius, VECTOR3& OutPos, ObjectBase*& Saveobj);
	//���݂̃^���[�̐�
	int GetTowerNum();

private:
	SceneGame* sceneGame;
	vector<shared_ptr<ObjectBase>>objes;
	vector<shared_ptr<ObjectBase>>remove;
};
