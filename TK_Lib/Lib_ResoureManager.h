#pragma once

#include <d3d11.h>
#include <memory>
#include <vector>
#include <string>

using namespace std;

//モデルやテクスチャなどの管理クラスを作る時の基底クラス
class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	//初期化処理
	virtual void Init(const UINT MaxLoadNum)=0;
	//ロード(1:device,2:パス,3:ハンドル)
	virtual bool Load(ID3D11Device* device, const string name, int& handle, const string RegisterKey="") = 0;
	//削除
	virtual void Erase(ID3D11Device* device, const  int handle) = 0;
	//全消し
	virtual void Clear() = 0;

protected:
	//現在 読み込んだ数
	u_int LoadNum = 0;

	//既に読み込んでいる同じテクスチャがあるかどうかを調べる
	//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
	virtual bool DuplicateFind(const string name, int& handle) = 0;

	//texturesの空である要素に登録していく
	virtual bool Register(ID3D11Device* device, const string name, int& handle) = 0;

};
