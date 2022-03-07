#pragma once
//#include "EffectBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Lib.h"
using namespace std;

//毎フレームエフェクトをだすデータ
class UpdatePlayEffect
{
public:
	VECTOR3 Pos;//位置
	string name;//名前
	int playNum;//だす数
};

class EffectBase;

class EffectManager :public Manager
{
public:
	EffectManager() {};
	~EffectManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//全削除
	void Clear();
	//ステージのリセット
	void StageReset();
	//毎フレームエフェクトをだすデータ登録
	void UpdateEffectRegister(VECTOR3 Pos,string name,int num);
	//毎フレームエフェクトをだすエフェクトの更新処理
	void PlayUpdateEffect();

	void NotRender();
	//描画処理
	virtual void Render() {};
	//モデル描画処理
	virtual void ModelRender() {};
	//登録
	void Register(shared_ptr<EffectBase> effect,const string RegisterName);
	//破棄処理
	void Destroy(EffectBase* effect);
	//エフェクトの数の取得
	int GetEffectsSize() { return effects.size(); }
	//エフェクトの数の取得
	EffectBase* GetEffectsIndex(const int& index) { return effects.at(index).get(); }
	//キーの名前からエフェクトを取得する
	EffectBase* GetEffectFromSerchKey(const string& SearchName);

private:

	//この
	vector<UpdatePlayEffect> UpdatePlayEffectPoses;

	vector<shared_ptr<EffectBase>>effects;
	vector<shared_ptr<EffectBase>>remove;

	map<string, EffectBase*> EffectIndexResources;

};
