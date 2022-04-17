#pragma once
#include "Navigation.h"
using namespace std;
class Actor;
//�����蔻��̃��f���^�C�v
enum ModelCollisionType
{
	COLLISION_MODEL,//���C�s�b�N�Ɏg��Model
	NAV_MODEL,//�L�����N�^�[AI�ɑ΂���i�rModel
};
//�����蔻��̃��f��
class ModelCollsion
{
public:
	ModelCollisionType type;
	Actor* actorModel;
	int modelIndex;
};
//�����蔻�N���X
class Collision
{
private:
	//���f���̓����蔻�胊�X�g
	vector<ModelCollsion> collisionModels;
	//�i�r����
	unique_ptr<NavCollision> navCollision;

	static Collision* instance;
	//���傢��̕����烌�C�����Ă邽�߂̋���
	static constexpr float rayUP = 3.0f;
	//���C��Y�����̏I�_�ʒu����
	static constexpr float rayUnder = 3.0f;
public:
	Collision();
	~Collision() {}
	//�����蔻�胂�f���̓o�^
	void RegisterModel(const int model, const ModelCollisionType type,Actor* actor);
	//�i�r���b�V���ɂ�铞���ڕW�̈ʒu
	void SetTarget(const VECTOR3& pos);
	//���C�s�b�N
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray);
	//�Ԃ�����Actor�I�u�W�F�N�g�̎Z�o���C�s�b�N
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,Actor*& actorModel);
	//���a�����l���������C�s�b�N
	void RadiusRayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,float radius);
	//�폜
	void Clear();
	//�i�r�̕`��
	void NavRender();
	//�����蔻��̕`��
	void CollisionRender();
	//AI�̂��߂̃X�e�[�W�\��
	void NacStageBuild();
	//�����蔻��̃��f���̍폜
	void DeleteCollisionModel(int model);

	//�i�r���b�V���ɂ��o�H�T��
	bool SearchRoat(const VECTOR3& pos, VECTOR3& outPos);
	//�~�̉~�Ƃ̓����蔻��
	bool SphereVsSphere(const VECTOR3& posA, const float& weghtA, const float& radiusA, const VECTOR3& posB, const float& weghtB, const float& radiusB, VECTOR3& outPosA, VECTOR3& outPosB);

	//�X�e�[�W�̃��X�g�擾
	inline vector<ModelCollsion> *GetCollisionModels() { return &collisionModels; };

	//�C���X�^���X�擾
	static Collision& Instance()
	{
		return *instance;
	}
	

};