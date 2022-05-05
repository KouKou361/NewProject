#pragma once
#include <string>
#include "Lib.h"
class SceneGame;
class EffectBase;

//�G�t�F�N�g�̏o�����鎞�̃X�e�[�^�X
//�ϐ��������̂ł�����Ɉړ������B
class EffectStatus
{
	friend class EffectBase;
private:
	int   effectType=0;	      //�G�t�F�N�g�̃^�C�v
	float timer = 0;              //��������
	float updateAlpha = 0;        //�X�V�����̓����x�̕ω���
						      
	VECTOR3 posMax={0,0,0};           //�ʒu�����̍ō��l
	VECTOR3 posMix={0,0,0};		      //�ʒu�����̍Œ�l
						      
	VECTOR3 velocityMax={0,0,0};      //���x�����̍ō��l
	VECTOR3 velocityMix={0,0,0};      //���x�����̍Œ�l
						      
	VECTOR3 accelMax={0,0,0};	      //�����x�����̍ō��l
	VECTOR3 accelMix={0,0,0};	      //�����x�����̍Œ�l

	VECTOR2 scale = { 0,0 };            //�傫��
	VECTOR2 updateScale={0,0};      //�X�V�����̑傫���̕ω���
	VECTOR4 color = { 0,0,0,0 };			  //�F
public:	

	inline int     GetEffectType()        {return effectType;          };//�G�t�F�N�g�ԍ��̎擾
	inline float   GetTimer()             {return timer;               };//�������Ԃ̎擾
	inline float   GetUpdateAlpha()       {return updateAlpha;         };//�X�V�����̓����x�̕ω��ʂ̎擾
	inline VECTOR2 GetScale()             {return scale;               };//�傫���̎擾
	inline VECTOR2 GetUpdateScale()       {return updateScale;         };//�X�V�����̑傫���̕ω��ʂ̎擾


	inline VECTOR3 GetPosMax()            {return posMax;              };//�ʒu�����̍ō��l
	inline VECTOR3 GetPosMix()            {return posMix;              };//�ʒu�����̍Œ�l
	 								                                  
	inline VECTOR3 GetVelocityMax()       {return velocityMax;         };//���x�����̍ō��l
	inline VECTOR3 GetVelocityMix()       {return velocityMix;         };//���x�����̍Œ�l
								
	inline VECTOR3 GetAccelMax()	      {return accelMax;            };//�����x�����̍ō��l
	inline VECTOR3 GetAccelMix()	      {return accelMix;            };//�����x�����̍Œ�l

	inline VECTOR4 GetColor()             {return color;			   };//�F�̎擾


};
//�G�t�F�N�g�̊��N���X
class EffectBase
{
	friend class EffectStatus;
public:
	EffectBase() {};
	~EffectBase() {};

	//����������
	virtual void Init();
	//�쐬����
	virtual void Create(const string &textureName,const int &maxNum,const VECTOR2 &textureChipSize,const VECTOR2 &textureNum, const Bland_state &blendstate= Bland_state::BS_ALPHA);
	//���s����
	virtual void Play(const VECTOR3 &pos,const int &num);
	//�X�V����
	virtual void Update();
	//���g���J�����O�̏ꍇ�A�X�V�������s��Ȃ�
	void NotIsCameraUpdate();
	//���g���J�����O�̏ꍇ�ł��X�V�������s��
	void IsCameraUpdate();
	//�p�[�e�B�N���̃X�e�[�^�X�X�V����
	void ParticleUpdate(EffectData* spriteEffect);

	void Delete();
	inline VECTOR3 GetPos() { return pos; }
	inline void SetPos(const VECTOR3& pos) { this->pos = pos; };
	//��\���ɕϊ�
	void NotRender();

	void SetStatus(SceneGame* sceneGame, const string& searchName);
	//�J�����Ɏʂ��Ă��Ȃ����X�V�����͌Ă΂�邩�ǂ����t���O�ݒ�
	inline void SetIsCameraUpdate(const bool Flg) { isCameraUpdateFlg = Flg; };
	//�J�����Ɏʂ��Ă��Ȃ����X�V�����͌Ă΂�邩�ǂ����t���O�擾
	inline bool GetIsCameraUpdate() { return isCameraUpdateFlg; };
protected:
	EffectStatus initStatus = {};
	//�G�t�F�N�g���q�̍ő吔
	int maxNum=0;
	int effectIndex=-1;
	//�J�����Ɏʂ��Ă��Ȃ����X�V�����͌Ă΂�邩�ǂ���
	bool isCameraUpdateFlg = false;
	VECTOR2 textureChipSize = {0,0};
	VECTOR2 textureNum = { 0,0 };
	Bland_state blendState = Bland_state::BS_NONE;


	//�G�t�F�N�g�Ŏg�p���Ă���e�N�X�`���̖��O
	string textureName="";

	VECTOR3 pos = {0,0,0};
};