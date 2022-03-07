#pragma once
#include "Lib_Texture.h"
#include "Lib_ResoureManager.h"
class TextureResourceManager:public ResourceManager
{
public:
	TextureResourceManager() {};
	~TextureResourceManager() {};

	//初期化処理
	void Init(const UINT MaxLoadNum);
	//ロード(1:device,2:テクスチャのパス,3:テクスチャのハンドル)
	bool Load(ID3D11Device* device, const string name, int& handle,const string RegisterKey = "");
	//削除
	void Erase(ID3D11Device* device, const  int handle);
	//テクスチャを生成する
	void Create(ID3D11Device* device, int& handle, u_int width, u_int height, DXGI_FORMAT format);
	//テクスチャの取得
	TextureResource* GetTextureResource(const int index);
	//全消し
	void Clear();
private:
	//テクスチャの配列
	vector<std::shared_ptr<TextureResource>> textures;

private:

	//既に読み込んでいる同じテクスチャがあるかどうかを調べる
	//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
	 bool DuplicateFind(const string name, int& handle);

	//texturesの空である要素に登録していく
	 bool Register(ID3D11Device* device, const string name, int& handle);

};
