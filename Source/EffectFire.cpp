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
//void EffectFire::Init()
//{
//	//pos = VECTOR3{ 11,0,-2 };
//    //	PointLight = TK_Lib::SpotLight::Create(Pos, {1,0,0,1},10);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2({ 0,0,0 }, 2);
//	//
//	//TK_Lib::Lib_Effect::GetSpriteEffect(EffectIndex)->Fire2(Pos, 2);
//}
//�X�V����
//void EffectFire::Update()
//{
//
//	float time = TK_Lib::Window::GetElapsedTime();
//	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);
//	
//	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
//		EffectData* spriteEffect = &spriteEffects->at(i);
//		if (spriteEffect->type < 0) continue;
//		if (!spriteEffect->IsCameraRender())continue;
//
//		spriteEffect->vx +=    spriteEffect->ax * time;
//		spriteEffect->vy +=    spriteEffect->ay * time;
//		spriteEffect->vz +=    spriteEffect->az * time;
//		spriteEffect->x +=     spriteEffect->vx  * time;
//		spriteEffect->y +=     spriteEffect->vy  * time;
//		spriteEffect->z +=     spriteEffect->vz  * time;
//		spriteEffect->timer -= time;
//		spriteEffect->h +=     InitStatus.GetUpdateScale().x * time;
//		spriteEffect->w +=     InitStatus.GetUpdateScale().y * time;
//		spriteEffect->color.w -= InitStatus.GetUpdateAlpha() * time;
//		//��\���ɂ���
//		if (spriteEffect->timer <= 0) {
//			spriteEffect->type = -1;
//		}
//	}
//}