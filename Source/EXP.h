#pragma once

#include <string>
#include "Lib.h"
//エフェクトの基底クラス
class EXPManager;
class SceneGame;

class EXP
{
public:
	EXP() {};
	~EXP() {};

	void SetManager(SceneGame* sceneGame) { scene = sceneGame; };
	//初期化処理
	void Init(const VECTOR3 &pos);
	//更新処理
	void Update();
	//更新処理
	void Render();

	void Delete();

private:
	//目標地点の算出
	void SetTargetPos();
	//位置の算出
	void SetPos(const VECTOR3& pos);
	//ワールドからスクリーン座標に変換
	VECTOR2 WorldToScreen(const VECTOR3& pos);
	//目標地点に進む
	void ModeToTarget();
	//ある適度時間が過ぎたら消える処理
	void DeleteToTimer();
	//ある適度目標に小さい場合消える処理
	void DeleteMinLength(const float& DeleteLength);

protected:
	//エフェクト番号
	int spriteIndex=-1;

	float angle=0;
	float speed = 0.0f;
	float timer=0;

	VECTOR2 pos = {0,0};
	VECTOR2 velocity = { 0,0 };
	VECTOR2 size = { 50,50 };

	VECTOR2 targetPos = { 20,20 };

	VECTOR4 cut = {0,0,0,0};

	SceneGame* scene=nullptr;



};