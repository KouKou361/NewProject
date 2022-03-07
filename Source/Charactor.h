#pragma once
#include "Lib.h"
#include "Actor.h"

class Animetion;

//�L�����N�^�[�N���X
class Charactor:public Actor
{
private:
	//�o���X�Ίp�x(���̒l�ȉ��̌X�΂Ȃ�̂΂邱�Ƃ��o����)
	float CanInclined = XMConvertToRadians(45);
	//�ЂƂO�̒n�_
	VECTOR3 oldPos = { 0,0,0 };

	Actor* targetActor;



protected:



	float spaceVolume = 1.0f;//���C�s�b�N���ɂ�����x�␳������傫��

	float speed = 0.5f;
	float trunSpeed = XMConvertToRadians(10);
	float MaxVelocity = 0.1f;

	bool damageFlg=false;
	bool deadFlg = false;

	//�i�ރx�N�g��
	VECTOR3 moveVec = { 0,0,0 };
	//���x
	VECTOR3 velocity = { 0,0,0 };

	//���G����
	int invincibleTime = 0;

	//�U���N�[���^�C��
	int attackCoolTime = 0;

public:
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
	
	//���G�͈͂�Target�������TRUE��Ԃ�
	bool SearchPosition(const float L, VECTOR3 Position);
	//�ڕW�ɐi�ރx�N�g���̎Z�o
	bool MoveOnPosition(VECTOR3 Position);
	//��]����
	void Turn(const VECTOR3& moveVec);
	//�c�����̓����蔻��iY�����j
	void VerticalCollision();
	//�������̓����蔻��iXZ���ʁj
	void BesideCollision();
	//�X�e�[�W�ɂ͂ݏo�Ă��Ȃ����␳(�ŏI�m�F)
	void StageOverhang();
	//�w�肳�ꂽ�ʒu�܂ł̃x�N�g���̎Z�o
	XMVECTOR Vector(const VECTOR3 Position);
	//�w�肳�ꂽ�ʒu�܂ł̋����̎Z�o
	float Length(const VECTOR3 Position);
	void SetInvincibleTime(int invincibleTime);
	inline void SetAttackCoolTime(int AttackTime) { attackCoolTime = AttackTime; }
	inline int GetAttackCoolTime() { return attackCoolTime; }
	//����
	void Move();
	//oldPos�̐ݒ�
	inline void SetOldPos(VECTOR3 Pos) { this->oldPos = Pos; };
	//oldPos�̎擾
	inline VECTOR3 GetOldPos() { return this->oldPos; };


	//���x�̎擾
	inline VECTOR3 GetVelocity() { return this->velocity; };
	//���x�ɉ��Z
	void AddVelocity(VECTOR3 velocity);
	//���G���Ԃ̍X�V
	void InvincibleTimeUpdate();

	inline bool GetDamageFlg() {return damageFlg;};
	bool GetDeadFlg() { return deadFlg; };

	virtual void SetDamageFlg(bool flg) { damageFlg = flg; };
	virtual void SetDeadFlg(bool flg)   { deadFlg = flg; };


public:
	Charactor() {};
	virtual ~Charactor() {};


	//������Ƃ�����̕����烌�C�s�b�N�����
	float BesideRayPickUP = 5.0f;
	float BesideRayPickUnder = 20.5f;
	//���C�s�b�N�̔���
	float VerticalRayPickUnder = 2.0f;
	//�ڕW�L�����N�^�[�̐ݒ�
	inline  void SetTarget(Actor* target) { targetActor = target; }
	//�ڕW�̎擾
	inline  Actor* GetTarget() { return targetActor; }

	shared_ptr<Animetion> anime;
	
	bool AddDamage(int Damage, int MaxinvincibleTime=0);
	
	void AttackCoolTimeUpdate();


	void SetCanInclined(const float CanInclined) { this->CanInclined = CanInclined; };
	void SetMoveVec(VECTOR3 Vec) { moveVec = Vec; }
	//�f�o�b�OImgui
	virtual void ImguiDebug();
	//�o��邩�ǂ���
	bool TryInclined(const VECTOR3 Normal);


	inline  float GetSpeed() { return speed; }






};