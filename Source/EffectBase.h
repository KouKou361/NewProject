#pragma once
#include <string>
#include "Lib.h"
class SceneGame;
class EffectBase;

//エフェクトの出現する時のステータス
//変数が多いのでこちらに移動した。
class EffectStatus
{
	friend class EffectBase;
private:
	int   effectType=0;	      //エフェクトのタイプ
	float timer = 0;              //生存時間
	float updateAlpha = 0;        //更新処理の透明度の変化量
						      
	VECTOR3 posMax={0,0,0};           //位置乱数の最高値
	VECTOR3 posMix={0,0,0};		      //位置乱数の最低値
						      
	VECTOR3 velocityMax={0,0,0};      //速度乱数の最高値
	VECTOR3 velocityMix={0,0,0};      //速度乱数の最低値
						      
	VECTOR3 accelMax={0,0,0};	      //加速度乱数の最高値
	VECTOR3 accelMix={0,0,0};	      //加速度乱数の最低値

	VECTOR2 scale = { 0,0 };            //大きさ
	VECTOR2 updateScale={0,0};      //更新処理の大きさの変化量
	VECTOR4 color = { 0,0,0,0 };			  //色
public:	

	inline int     GetEffectType()        {return effectType;          };//エフェクト番号の取得
	inline float   GetTimer()             {return timer;               };//生存時間の取得
	inline float   GetUpdateAlpha()       {return updateAlpha;         };//更新処理の透明度の変化量の取得
	inline VECTOR2 GetScale()             {return scale;               };//大きさの取得
	inline VECTOR2 GetUpdateScale()       {return updateScale;         };//更新処理の大きさの変化量の取得


	inline VECTOR3 GetPosMax()            {return posMax;              };//位置乱数の最高値
	inline VECTOR3 GetPosMix()            {return posMix;              };//位置乱数の最低値
	 								                                  
	inline VECTOR3 GetVelocityMax()       {return velocityMax;         };//速度乱数の最高値
	inline VECTOR3 GetVelocityMix()       {return velocityMix;         };//速度乱数の最低値
								
	inline VECTOR3 GetAccelMax()	      {return accelMax;            };//加速度乱数の最高値
	inline VECTOR3 GetAccelMix()	      {return accelMix;            };//加速度乱数の最低値

	inline VECTOR4 GetColor()             {return color;			   };//色の取得


};
//エフェクトの基底クラス
class EffectBase
{
	friend class EffectStatus;
public:
	EffectBase() {};
	~EffectBase() {};

	//初期化処理
	virtual void Init();
	//作成処理
	virtual void Create(const string &textureName,const int &maxNum,const VECTOR2 &textureChipSize,const VECTOR2 &textureNum, const Bland_state &blendstate= Bland_state::BS_ALPHA);
	//実行処理
	virtual void Play(const VECTOR3 &pos,const int &num);
	//更新処理
	virtual void Update();
	//自身がカメラ外の場合、更新処理を行わない
	void NotIsCameraUpdate();
	//自身がカメラ外の場合でも更新処理を行う
	void IsCameraUpdate();
	//パーティクルのステータス更新処理
	void ParticleUpdate(EffectData* spriteEffect);

	void Delete();
	inline VECTOR3 GetPos() { return pos; }
	inline void SetPos(const VECTOR3& pos) { this->pos = pos; };
	//非表示に変換
	void NotRender();

	void SetStatus(SceneGame* sceneGame, const string& searchName);
	//カメラに写っていないが更新処理は呼ばれるかどうかフラグ設定
	inline void SetIsCameraUpdate(const bool Flg) { isCameraUpdateFlg = Flg; };
	//カメラに写っていないが更新処理は呼ばれるかどうかフラグ取得
	inline bool GetIsCameraUpdate() { return isCameraUpdateFlg; };
protected:
	EffectStatus initStatus = {};
	//エフェクト粒子の最大数
	int maxNum=0;
	int effectIndex=-1;
	//カメラに写っていないが更新処理は呼ばれるかどうか
	bool isCameraUpdateFlg = false;
	VECTOR2 textureChipSize = {0,0};
	VECTOR2 textureNum = { 0,0 };
	Bland_state blendState = Bland_state::BS_NONE;


	//エフェクトで使用しているテクスチャの名前
	string textureName="";

	VECTOR3 pos = {0,0,0};
};