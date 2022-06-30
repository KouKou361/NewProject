#pragma once
#include "Actor.h"
#include <string>
using namespace std;
class ObjectManager;
class SceneGame;
enum class ObjectType
{
	WALL,
	POT,
	TOWER,
	NONE,
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
	void SetCollisionModel(const string& CollisionModelKey);
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

	//�X�e�[�^�X�̐ݒ�
	void SetStatus(const string& name);

	void HPRender(const int &spriteIndex, const VECTOR2 &pos);
	bool AddDamage(const int& damage, const float& maxInvincibleTime);

	//�}�X�N�X�^�[�g
	void MaskStart(const float speed);
	//�}�X�N�傫���擾
	float GetMaskVolume();

	inline ObjectType GetType() { return static_cast<ObjectType>(objectType); }
protected:
	int collisionModel = -1;
	ObjectManager* objectManager = nullptr;
	SceneGame* scene = nullptr;

	ObjectType objectType= ObjectType::NONE;
};
