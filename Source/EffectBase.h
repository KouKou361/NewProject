#pragma once
#include <string>
#include "Lib.h"
//エフェクトの基底クラス
class EffectBase
{
public:
	EffectBase() {};
	~EffectBase() {};

	//初期化処理
	virtual void Init()=0;
	//作成処理
	virtual void Create(string Texturename,int MaxNum,VECTOR2 TextureChipSize,VECTOR2 TextureNum, Bland_state blendstate= Bland_state::BS_ALPHA);
	//実行処理
	virtual void Play(VECTOR3 Pos,int Num) = 0;
	//更新処理
	virtual void Update() = 0;

	void Delete();

	void SetPos(VECTOR3 pos) { Pos = pos; };
	void NotRender();
protected:
	//エフェクト番号
	int EffectIndex;
	//エフェクトで使用しているテクスチャの名前
	string Texturename;
	//エフェクト粒子の最大数
	int MaxNum;

	VECTOR2 TextureChipSize;
	VECTOR2 TextureNum;
	Bland_state blendstate;

	VECTOR3 Pos;


};