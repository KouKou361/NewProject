#pragma once
#include "Lib.h"
#include "Actor.h"

class Animetion;

//�L�����N�^�[�N���X
class Charactor:public Actor
{
private:


	//�o���X�Ίp�x(���̒l�ȉ��̌X�΂Ȃ�̂΂邱�Ƃ��o����)
	float canInclined = XMConvertToRadians(45);
	//�ЂƂO�̒n�_
	VECTOR3 oldPos = { 0,0,0 };
	Actor* targetActor=nullptr;
protected:


	//������Ƃ�����̕����烌�C�s�b�N�����
	const float BesideRayPickUP = 5.0f;
	const float BesideRayPickUnder = 50.5f;
	//���C�s�b�N�̔���
	const float VerticalRayPickUnder = 2.0f;

	float spaceVolume = 1.0f;//���C�s�b�N���ɂ�����x�␳������傫��
	float speed = 0.5f;
	float trunSpeed = XMConvertToRadians(10);
	float maxVelocity = 0.1f;

	bool damageFlg=false;
	bool deadFlg = false;

	//���G����
	float invincibleTime = 0;
	//�U���N�[���^�C��
	float attackCoolTime = 0;

	//�i�ރx�N�g��
	VECTOR3 moveVec = { 0,0,0 };
	//���x
	VECTOR3 velocity = { 0,0,0 };
	//���f���̃A�j���f�[�^
	shared_ptr<Animetion> anime;



public:
	Charactor() {};
	virtual ~Charactor() {};
	//����������
	virtual void Init();
	//�X�V����
	virtual void Update();
	//�`�揈��
	virtual void ModelRender();
	//���f���p�̕`�揈��
	virtual void Render();
	//�f�o�b�O�����蔻��
	virtual void CollisionDebug();
	//�f�o�b�O�p�����[�^
	virtual void ParameterDebug();
	//�j������
	virtual void Destroy() {};
	//�}�X�N�X�^�[�g
	void MaskStart(const float speed);
	//�}�X�N�傫���擾
	float GetMaskVolume();

	//��]����
	void Turn(const VECTOR3& moveVec);
	//�c�����̓����蔻��iY�����j
	void VerticalCollision();
	//�������̓����蔻��iXZ���ʁj
	void BesideCollision();
	//�X�e�[�W�ɂ͂ݏo�Ă��Ȃ����␳(�ŏI�m�F)
	void StageOverhang();
	//���G���Ԃ̐ݒ�
	void SetInvincibleTime(const float& invincibleTime);
	//���x�ɉ��Z
	void AddVelocity(const VECTOR3& velocity);
	//���G���Ԃ̍X�V
	void InvincibleTimeUpdate();
	//����
	void Move();
	//�U���N�[���^�C���X�V����
	void AttackCoolTimeUpdate();
	//�f�o�b�OImgui
	virtual void ImguiDebug();

	//���G�͈͂�Target�������TRUE��Ԃ�
	bool SearchPosition(const float& L, const VECTOR3& position);
	//�ڕW�ɐi�ރx�N�g���̎Z�o
	bool MoveOnPosition(const VECTOR3& position);
	//�_���[�W�󂯂����̊֐�
	bool AddDamage(const int& damage, const float& maxInvincibleTime=0);
	//�o��邩�ǂ���
	bool TryInclined(const VECTOR3& normal);

	//�w�肳�ꂽ�ʒu�܂ł̃x�N�g���̎Z�o
	XMVECTOR Vector(const VECTOR3& position);

	//�w�肳�ꂽ�ʒu�܂ł̋����̎Z�o
	float Length(const VECTOR3& position);
	//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
	virtual void SetStatus(const string &searchName);




	//==================================
	//�Z�b�^�[�A�Q�b�^�[
	//==================================
	
	//�ڕW�L�����N�^�[
	inline void SetTarget(Actor* target) { targetActor = target; }
	inline Actor* GetTarget() { return targetActor; }
	//�U���N�[���^�C��
	inline void SetAttackCoolTime(const float attackTime) { attackCoolTime = attackTime; }
	inline float GetAttackCoolTime() { return attackCoolTime; }
	//�_���[�W�t���O
	inline bool GetDamageFlg() { return damageFlg; };
	virtual void SetDamageFlg(const bool flg) { damageFlg = flg; };
	//���S�t���O
	inline bool GetDeadFlg() { return deadFlg; };
	virtual void SetDeadFlg(const bool flg) { deadFlg = flg; };
	//oldPos
	inline void SetOldPos(const VECTOR3 position) { this->oldPos = position; };
	inline VECTOR3 GetOldPos() { return this->oldPos; };
	//�����x
	inline VECTOR3 GetVelocity() { return this->velocity; };
	//���x
	inline float GetSpeed() { return speed; }
	inline void SetSpeed(const float speed) { this->speed; }
	//�o���l�ݒ�
	inline void SetCanInclined(const float canInclined) { this->canInclined = canInclined; };
	//�i�ޕ����ݒ�
	inline void SetMoveVec(const VECTOR3 vec) { moveVec = vec; }
	//�A�j���f�[�^�擾
	inline Animetion* GetAnime() { return anime.get(); };
};