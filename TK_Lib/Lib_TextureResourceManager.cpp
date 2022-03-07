#include "Lib_TextureResourceManager.h"
//初期化処理
void TextureResourceManager::Init(const UINT MaxLoadNum)
{
	textures.resize(MaxLoadNum);
	for (int i = 0; i < textures.size(); i++)
	{
		textures.at(i) = make_shared<TextureResource>();
	}
}
//ロード(1:device,2:テクスチャのパス,3:テクスチャのハンドル)
bool TextureResourceManager::Load(ID3D11Device* device, const string name, int& handle, const string RegisterKey )
{
	//既に読み込んでいるテクスチャがあるかどうかを調べる
	if (DuplicateFind(name, handle) == true)
	{
		//texturesの空である要素に登録していく
		Register(device, name, handle);
	}

	return true;
	
}
//削除
void TextureResourceManager::Erase(ID3D11Device* device, const  int handle)
{

	//テクスチャの取得
	TextureResource* textureData = GetTextureResource(handle);
	//値を削除
	textureData->handle = -1;
	textures.at(handle).reset();
	textures.at(handle) = make_shared<TextureResource>();

	//テクスチャの読み込んだ数を-1する
	LoadNum--;
}
void TextureResourceManager::Clear()
{
	textures.clear();
}
//テクスチャを生成する
void TextureResourceManager::Create(ID3D11Device* device, int& handle, u_int width, u_int height, DXGI_FORMAT format)
{

}
//テクスチャの取得
TextureResource* TextureResourceManager::GetTextureResource(const int handle)
{
	//設定されていないまたは削除されたテクスチャを使おうとしているかどうか
	assert(textures.at(handle)->handle != -1);
	return textures.at(handle).get();
}

//既に読み込んでいる同じテクスチャがあるかどうかを調べる
//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
bool TextureResourceManager::DuplicateFind(const string name, int& handle)
{
	for (int i = 0; i < textures.size(); i++)
	{


		//テクスチャの取得
		TextureResource* textureData = textures.at(i).get();

		if (-1 >= textureData->handle)continue;

		//テクスチャが重複しているかどうかを検索
		if (name == textureData->filename)
		{
			//重複してるやん
			handle = textureData->handle;
			return false;
		}
	}
	return true;
}

//texturesの空である要素に登録していく
bool TextureResourceManager::Register(ID3D11Device* device, const string name, int& handle)
{
	//Textureの読み込める数が最大に達しているかどうか
	assert(LoadNum < textures.size());

	for (int i = 0; i < textures.size(); i++)
	{
		//テクスチャの取得
		TextureResource* textureData = textures.at(i).get();
		if (-1 < textureData->handle)continue;

		//空に登録する
		textureData->Load(device, name);
		textureData->handle = i;
		handle = i;
		LoadNum++;
		break;

	}
	return true;
}