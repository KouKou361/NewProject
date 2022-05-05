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
	VECTOR3 pos;//位置
	string name;//名前
	int playNum;//だす数
};

class EffectBase;

//エフェクト管理クラス
class EffectManager :public Manager
{
public:
	EffectManager() {};
	~EffectManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	virtual void Render() {};
	//モデル描画処理
	virtual void ModelRender() {};

	//全削除
	void Clear();
	//ステージのリセット
	void StageReset();
	//毎フレームエフェクトをだすデータ登録
	void UpdateEffectRegister(const VECTOR3 &pos, const string &name, const int &num);
	//毎フレームエフェクトをだすエフェクトの更新処理
	void PlayUpdateEffect();
	//全て非表示
	void NotRender();

	//登録
	void Register(const shared_ptr<EffectBase>& effect,const string &registerName);
	//破棄処理
	void Destroy(const EffectBase* effect);
	//エフェクトの数の取得
	int GetEffectsSize() { return static_cast<int>(effects.size()); }
	//エフェクトの数の取得
	EffectBase* GetEffectsIndex(const int& index) { return effects.at(index).get(); }
	//キーの名前からエフェクトを取得する
	EffectBase* GetEffectFromSerchKey(const string& searchName);

private:

	//毎フレーム出すエフェクト（炎エフェクトなど）
	vector<UpdatePlayEffect> updatePlayEffectPoses;
	//エフェクト
	vector<shared_ptr<EffectBase>>effects;
	//削除エフェクト
	vector<shared_ptr<EffectBase>>remove;
	//キーの名前からエフェクトを取得する用
	map<string, EffectBase*> effectIndexResources;

};
