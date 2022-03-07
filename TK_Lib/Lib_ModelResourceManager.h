#pragma once
#include "Lib_ModelResource.h"
#include "Lib_ResoureManager.h"
#include <map>
class ModelResourceManager:public ResourceManager
{
public:
	ModelResourceManager() {};
	~ModelResourceManager() {};

	//初期化処理
	void Init(const UINT MaxLoadNum);
	//ロード(1:device,2:テクスチャのパス,3:テクスチャのハンドル)
	bool Load(ID3D11Device* device, const string name, int& handle, const string key);
	//モデルのコピー
	int Copy(int& handle);
	//削除
	void Erase(ID3D11Device* device, const  int handle);
	//全消し
	void Clear();
	//モデルリソースの取得
	ModelResource* GetModelResource(const int index);
	//モデルの配列の取得
	vector<std::shared_ptr<ModelResource>>& GetModel() { return models; };

	//モデルの行列更新処理
	void Tranceform(ID3D11Device* device, XMFLOAT4X4 W, const int handle);
	//モデルのアニメーション
	void UPdateAnimetion(ID3D11Device* device, const int handle, const float elapsedTime);
	//モデルのアニメーションが再生中かどうか
	bool IsPlayAnimetion(const int handle);
	//モデルのアニメーション再生
	void PlayAnimation(const int handle, int animationIndex, bool loop);
	//キーの名前から番号を取得する
	int GetModelFromSerchKey(const string& SearchName);
	//アニメーションタイムの
	float GetEndAnimetionTime(int modelIndex);
	float GetAnimetionTime(int modelIndex);

	//ノード検索する
	ModelResource::NodeTest* FindNode(int modelIndex, const char* name);
private:
	//モデル保存の配列
	vector<std::shared_ptr<ModelResource>> models;

	////算出用　モデル番号と呼び出す時のキー
	map<string, int> ModelIndexResources;

	//既に読み込んでいる同じテクスチャがあるかどうかを調べる
	//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
	bool DuplicateFind(const string name, int& handle);

	//texturesの空である要素に登録していく
	bool Register(ID3D11Device* device, const string name, int& handle);
};
