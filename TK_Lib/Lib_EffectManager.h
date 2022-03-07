#pragma once
#include "Lib_SpriteEffect.h"
#include "Lib_ResoureManager.h"
#include "Vector.h"
#include "Lib_ShaderResource.h"
#include <map>

using namespace std;
class Lib_EffectManager
{
private:
	unique_ptr<ShaderResource>    PointSpriteshader = nullptr;
public:
	Lib_EffectManager() {};
	~Lib_EffectManager() {};


	//初期化処理
	void Init(const UINT MaxLoadNum,ID3D11Device* device);
	//ロード(1:device,2:テクスチャのパス,3:テクスチャのハンドル)
	void Load(ID3D11Device* device, const string name, int& handle, int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state);
	//削除
	void Erase(ID3D11Device* device, const  int handle);
	//全消し
	void Clear();
	//更新処理
	void Update();
	//アニメーション処理
	void Animation(float elapsedtimer, const  int handle,int Starttype, int Endtype, float Animetionspeed);
	void SetType(const int handle, int type);

	//エフェクトの描画開始処理
	void Begin(ID3D11DeviceContext* device);
	//描画処理
	void Render(ID3D11DeviceContext* device, XMFLOAT4X4 view, XMFLOAT4X4 projection);
	//エフェクトの描画開始処理
	void End(ID3D11DeviceContext* device);

	SpriteEffect* GetSpriteEffectResource(const int handle);
	vector<EffectData>* Geteffects(const int handle);

protected:

	//エフェクトの配列
	vector<std::shared_ptr<SpriteEffect>> SpriteEffects;


	//現在 読み込んだ数
	u_int LoadNum = 0;

	//既に読み込んでいる同じテクスチャがあるかどうかを調べる
	//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
	bool DuplicateFind(const string name, int& handle);

	//texturesの空である要素に登録していく
	void Register(ID3D11Device* device, const string name, int& handle, int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state);
	

};