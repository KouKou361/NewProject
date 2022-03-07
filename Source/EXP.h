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
	void Init(VECTOR3 Pos);
	//更新処理
	void Update();
	//更新処理
	void Render();

	void Delete();

	VECTOR2 WorldToScreen(VECTOR3 Pos);
protected:
	//エフェクト番号
	int SpriteIndex;

	VECTOR2 Pos;
	VECTOR2 Velocity = { 0,0 };
	VECTOR2 Size = { 50,50 };

	VECTOR2 TargetPos = { 20,20 };

	VECTOR4 Cut;
	float Angle;
	float speed = 0.0f;

	SceneGame* scene;

	float timer;



};