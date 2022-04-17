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
	int spriteIndex;

	VECTOR2 pos;
	VECTOR2 velocity = { 0,0 };
	VECTOR2 size = { 50,50 };

	VECTOR2 targetPos = { 20,20 };

	VECTOR4 cut;
	float angle;
	float speed = 0.0f;

	SceneGame* scene;

	float timer;



};