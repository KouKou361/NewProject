#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectManager;
class SceneGame;
enum ObjectType
{
	Wall,
	Pot,
	Tower,
};



class ObjectBase :public Actor
{
public:
	ObjectBase(ObjectManager* ObjectManager, SceneGame* scene) {
		this->objectManager = ObjectManager;
		this->scene = scene;
	};
	ObjectBase() {}
	virtual ~ObjectBase() {};
protected:
public:
	//�����蔻��p�̃��f��
	void SetCollisionModel(string CollisionModelKey);
	//����������
	virtual void Init()=0;
	//�X�V����
	virtual void Update() = 0;
	//�`�揈��
	void ModelRender();
	//�����蔻��p
	void CollisionRender();
	//ImGui�̃f�o�b�O
	void ImguiDebug();
	//�I�u�W�F�N�g�̔j������
	void Destroy();
	//�I�u�W�F�N�g�̎��S����
	virtual void Dead();
	//�I�u�W�F�N�g�̃_���[�W����
	void Damage();

	void HPRender(const int SpriteIndex, const VECTOR2 Pos);
	bool AddDamage(int Damage, int MaxinvincibleTime = 0);

	ObjectType GetType() { return objectType; }
protected:
	int collisionModel = -1;
	ObjectManager* objectManager = nullptr;
	SceneGame* scene = nullptr;

	ObjectType objectType;
};
