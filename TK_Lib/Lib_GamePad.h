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
// ゲームパッド
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
	// 更新
	void Update();

	// スロット設定
	void SetSlot(int slot) { this->slot = slot; }

	// ボタン入力状態の取得
	GamePadButton GetButton() const {
		return buttonState[0];
	}

	// ボタン押下状態の取得
	int GetButtonDown(BTN button) const {
		return Buttonstate[static_cast<int>(button)];
	}

	// ボタン押上状態の取得
	GamePadButton GetButtonUp() const { return buttonUp; }

	// 左スティックX軸入力状態の取得
	float GetAxisLX() const {
		//入力していないのに小さい値が入っているのでその場合は0で返す
		if (fabsf(axisLx) - AxisTolerance < 0)return 0;
		return axisLx; }
	

	// 左スティックY軸入力状態の取得
	float GetAxisLY() const {		//入力していないのに小さい値が入っているのでその場合は0で返す
		if (fabsf(axisLy) - AxisTolerance < 0)return 0;
		return axisLy; }

	// 右スティックX軸入力状態の取得
	float GetAxisRX() const { 
		//入力していないのに小さい値が入っているのでその場合は0で返す
		if (fabsf(axisRx) - AxisTolerance < 0)return 0;
		return axisRx; }

	// 右スティックY軸入力状態の取得
	float GetAxisRY() const { 
		//入力していないのに小さい値が入っているのでその場合は0で返す
		if (fabsf(axisRy) - AxisTolerance < 0)return 0;
		return axisRy; }

	// 左トリガー入力状態の取得
	float GetTriggerL() const { return triggerL; }

	// 右トリガー入力状態の取得
	float GetTriggerR() const { return triggerR; }

	//インスタンス取得
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
