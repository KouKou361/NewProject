#pragma once
#include "Navigation.h"
using namespace std;
class Actor;
//�����蔻��̃��f���^�C�v
enum ModelCollisionType
{
	CollisionModel,//���C�s�b�N�Ɏg��Model
	NavModel,//�L�����N�^�[AI�ɑ΂���i�rModel
};
//�����蔻��̃��f��
class ModelCollsion
{
public:
	ModelCollisionType type;
	Actor* actorModel;
	int modelIndex;
};

class Collision
{
private:
	//���f���̓����蔻�胊�X�g
	vector<ModelCollsion> CollisionModels;
	//�i�r����
	unique_ptr<NavCollision> navCollision;

	static Collision* instance;
	//���傢��̕����烌�C�����Ă邽�߂̋���
	static constexpr float RayUP = 3.0f;
	//���C��Y�����̏I�_�ʒu����
	static constexpr float RayUnder = 3.0f;
public:
	Collision();
	~Collision() {}
	//�����蔻�胂�f���̓o�^
	void RegisterModel(const int model, const ModelCollisionType type,Actor* actor);
	//
	bool SearchRoat(const VECTOR3& Pos,VECTOR3 & OutPos);
	//�~�̉~�Ƃ̓����蔻��
	bool SphereVsSphere(const VECTOR3& posA, const float& weghtA, const float& radiusA, const VECTOR3& posB, const float& weghtB, const float& radiusB, VECTOR3& outPosA, VECTOR3& outPosB);

	void SetTarget(const VECTOR3& Pos);
	//���C�s�b�N
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray);

	//�Ԃ�����Actor�I�u�W�F�N�g�̎Z�o���C�s�b�N
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,Actor*& actorModel);

	//���a�����l���������C�s�b�N
	void RadiusRayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,float radius);
	//�폜
	void Clear();
	//�e�X�g�p
	void NavRender();
	void CollisionRender();


	//AI�̂��߂̃X�e�[�W�\��
	void NacStageBuild();
	//�����蔻��̃��f���̍폜
	void DeleteCollisionModel(int model);
	//�C���X�^���X�擾
	static Collision& Instance()
	{
		return *instance;
	}
	//�X�e�[�W�̃��X�g�擾
	vector<ModelCollsion> *GetCollisionModels() { return &CollisionModels; };
	

};