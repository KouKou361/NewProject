#pragma once
#include <math.h>
using GamePadButton = unsigned int;


enum class BTN
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	A,
	B,
	X,
	Y,
	START,
	BACK,
	LS,
	RS,
	LB,
	RB,
	LT,
	RT,
	END,
};
// �Q�[���p�b�h
class GamePad
{
	static const GamePadButton BTN_UP    = (1 << 0);
	static const GamePadButton BTN_RIGHT = (1 << 1);
	static const GamePadButton BTN_DOWN  = (1 << 2);
	static const GamePadButton BTN_LEFT  = (1 << 3);
	static const GamePadButton BTN_A     = (1 << 4);
	static const GamePadButton BTN_B     = (1 << 5);
	static const GamePadButton BTN_X     = (1 << 6);
	static const GamePadButton BTN_Y     = (1 << 7);
	static const GamePadButton BTN_START = (1 << 8);
	static const GamePadButton BTN_BACK  = (1 << 9);
	static const GamePadButton BTN_LS    = (1 << 10);
	static const GamePadButton BTN_RS    = (1 << 11);
	static const GamePadButton BTN_LB    = (1 << 12);
	static const GamePadButton BTN_RB    = (1 << 13);
	static const GamePadButton BTN_LT    = (1 << 14);
	static const GamePadButton BTN_RT    = (1 << 15);
private:
	static GamePad* instance;
	int Buttonstate[static_cast<int>(BTN::END)];
	const float AxisTolerance = 0.1f;
public:

public:
	GamePad();
	~GamePad(){};
	// �X�V
	void Update();

	// �X���b�g�ݒ�
	void SetSlot(int slot) { this->slot = slot; }

	// �{�^�����͏�Ԃ̎擾
	GamePadButton GetButton() const {
		return buttonState[0];
	}

	// �{�^��������Ԃ̎擾
	int GetButtonDown(BTN button) const {
		return Buttonstate[static_cast<int>(button)];
	}

	// �{�^�������Ԃ̎擾
	GamePadButton GetButtonUp() const { return buttonUp; }

	// ���X�e�B�b�NX�����͏�Ԃ̎擾
	float GetAxisLX() const {
		//���͂��Ă��Ȃ��̂ɏ������l�������Ă���̂ł��̏ꍇ��0�ŕԂ�
		if (fabsf(axisLx) - AxisTolerance < 0)return 0;
		return axisLx; }
	

	// ���X�e�B�b�NY�����͏�Ԃ̎擾
	float GetAxisLY() const {		//���͂��Ă��Ȃ��̂ɏ������l�������Ă���̂ł��̏ꍇ��0�ŕԂ�
		if (fabsf(axisLy) - AxisTolerance < 0)return 0;
		return axisLy; }

	// �E�X�e�B�b�NX�����͏�Ԃ̎擾
	float GetAxisRX() const { 
		//���͂��Ă��Ȃ��̂ɏ������l�������Ă���̂ł��̏ꍇ��0�ŕԂ�
		if (fabsf(axisRx) - AxisTolerance < 0)return 0;
		return axisRx; }

	// �E�X�e�B�b�NY�����͏�Ԃ̎擾
	float GetAxisRY() const { 
		//���͂��Ă��Ȃ��̂ɏ������l�������Ă���̂ł��̏ꍇ��0�ŕԂ�
		if (fabsf(axisRy) - AxisTolerance < 0)return 0;
		return axisRy; }

	// ���g���K�[���͏�Ԃ̎擾
	float GetTriggerL() const { return triggerL; }

	// �E�g���K�[���͏�Ԃ̎擾
	float GetTriggerR() const { return triggerR; }

	//�C���X�^���X�擾
	static GamePad& Instance() { return *instance; }

private:
	GamePadButton		buttonState[2] = { 0 };
	GamePadButton		buttonDown = 0;
	GamePadButton		buttonUp = 0;
	float				axisLx = 0.0f;
	float				axisLy = 0.0f;
	float				axisRx = 0.0f;
	float				axisRy = 0.0f;
	float				triggerL = 0.0f;
	float				triggerR = 0.0f;
	int					slot = 0;
};
