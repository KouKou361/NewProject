#include "EffectDerived.h"


//�����̉���
//============================================
//�G�t�F�N�g�̔h���N���X�͑S�ăR�����g�A�E�g���܂����B
//����S�����N���X�Ŋ����ł��鎖�ɋC�����Ĕh���N���X�̊֐���S�ď��ł����܂����I
//�܂��Acsv����f�[�^�擾���Ă���̂ł���cpp����v��Ȃ��B
//�ł������������`�Ղ��c�������̂ŃR�����g�A�E�g�łƂǂ߂Ă���B
//�����K�v�Ȃ�Q�l�ɂ��āB
//=============================================


////����������
//void EffectEnemyDestroy::Init()
//{
//
//}



//�X�V����
//void EffectEnemyDestroy::Update()
//{
//
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	float time = TK_Lib::Window::GetElapsedTime();
//
//	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//		spriteEffect->color.w -= InitStatus.GetUpdateAlpha() * time;
//
//		if (!spriteEffect->IsCameraRender())continue;
//
//		spriteEffect->vx += spriteEffect->ax * time;
//		spriteEffect->vy += spriteEffect->ay * time;
//		spriteEffect->vz += spriteEffect->az * time;
//										
//		spriteEffect->x += spriteEffect->vx  * time;
//		spriteEffect->y += spriteEffect->vy  * time;
//		spriteEffect->z += spriteEffect->vz  * time;
//
//		spriteEffect->h += InitStatus.GetUpdateScale().x * time;
//		spriteEffect->w += InitStatus.GetUpdateScale().y * time;
//
//	//	spriteEffect->alpha = spriteEffect->timer / 0.2f;
//
//		//��\���ɂ���
//		if (spriteEffect->color.w <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//
//	
//}