#include "EffectDerived.h"

//�����̉���
//============================================
//�G�t�F�N�g�̔h���N���X�͑S�ăR�����g�A�E�g���܂����B
//����S�����N���X�Ŋ����ł��鎖�ɋC�����Ĕh���N���X�̊֐���S�ď��ł����܂����I
//�܂��Acsv����f�[�^�擾���Ă���̂ł���cpp����v��Ȃ��B
//�ł������������`�Ղ��c�������̂ŃR�����g�A�E�g�łƂǂ߂Ă���B
//�����K�v�Ȃ�Q�l�ɂ��āB
//=============================================



//����������
//void EffectAttack::Init()
//{
//	//pos = VECTOR3{ 11,0,-2 };
//	//PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
//}
////�X�V����
//void EffectAttack::Play(VECTOR3 Pos, int Num)
//{
//
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	for (int i = 0; i < Num; i++) {
//		for (int j = 0; j < spriteEffects->size(); j++)
//		{
//			EffectData* spriteEffect = &spriteEffects->at(j);
//			if (spriteEffect->type >= 0)continue;
//			if (!spriteEffect->IsCameraRender())continue;
//			DirectX::XMFLOAT3 p;
//			DirectX::XMFLOAT3 v = { 0,0,0 };	                  //���x
//			DirectX::XMFLOAT3 f = { 0,0,0 };	                  //�����x
//			DirectX::XMFLOAT2 s = { .006f,.006f };                //�傫��
//		
//			p.x = Pos.x + (rand() % 10001 - 5000) * 0.00031f;     //�ʒu�̎Z�o
//			p.y = Pos.y + (rand() % 10001 - 5000) * 0.00031f+2.0f;//�ʒu�̎Z�o
//			p.z = Pos.z + (rand() % 10001 - 5000) * 0.00031f;	  //�ʒu�̎Z�o
//
//			v.x = (rand() % 10001 - 5000) * 0.0002f;              //���x�̎Z�o
//			v.y = (rand() % 10001 - 5000) * 0.0002f;              //���x�̎Z�o
//			v.z = (rand() % 10001 - 5000) * 0.0002f;              //���x�̎Z�o
//													              
//			f.x = (rand() % 10001 - 5000) * 0.0002f;              //�����x�̎Z�o
//			f.y = (rand() % 10001 - 5000) * 0.0002f;              //�����x�̎Z�o
//			f.z = (rand() % 10001 - 5000) * 0.0002f;              //�����x�̎Z�o
//
//			//�ݒ�
//			spriteEffect->Set(2, 0.3f, p, v, f, s);
//			
//			break;
//		}
//
//
//	}
//}
//�X�V����
//void EffectAttack::Update()
//{
//	float time = TK_Lib::Window::GetElapsedTime();
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//
//	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//
//		spriteEffect->vx += spriteEffect->ax * time;
//		spriteEffect->vy += spriteEffect->ay * time;
//		spriteEffect->vz += spriteEffect->az * time;
//		spriteEffect->x += spriteEffect->vx * time;
//		spriteEffect->y += spriteEffect->vy * time;
//		spriteEffect->z += spriteEffect->vz * time;
//		spriteEffect->timer -= time;
//		spriteEffect->alpha = spriteEffect->timer / AlphaRate;
//		spriteEffect->h += UpdateScale;
//		spriteEffect->w += UpdateScale;
//
//		//��\���ɂ���
//		if (spriteEffect->timer <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//}