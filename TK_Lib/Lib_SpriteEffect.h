#pragma once

#include "Lib_Texture.h"
#include "Lib_DirectXFunctions.h"
#include "Lib_Blender.h"

#include <vector>
#include <d3d11.h>
#include <memory>


using namespace std;

struct VERTEXParticle;

class EffectData
{
public:
	float x, y, z;//座標
	float w, h;//大きさ
	float aw, ah;
	float vx, vy, vz;
	float ax, ay, az;
	float alpha;//アルファ
	float timer;//生存時間
	float anime_timer;//アニメーションの切り替わる時間
	int type;//タイプ(-1で削除)
	VECTOR4 color = { 1,1,1,1 };
	bool renderflg = false;
	void Set(int type, float timer,
		DirectX::XMFLOAT3 p, DirectX::XMFLOAT3 v, DirectX::XMFLOAT3 f, DirectX::XMFLOAT2 size, VECTOR4 color = {1,1,1,1});
	bool IsCameraRender();
};

class SpriteEffect
{
public:
	SpriteEffect() {};
	SpriteEffect(ID3D11Device* device, int Num,std::string name);
	~SpriteEffect() {};
public:
	int handle = -1;
	int UseLastEffectIndex = -1;
	Bland_state BlenderType = Bland_state::BS_ALPHA;
	
private:
	unique_ptr<TextureResource> Texture = nullptr;
	
	vector<EffectData> spriteEffects;
	vector<VERTEXParticle> vertices;
	// 頂点データ
	ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
	// 定数バッファ
	ComPtr<ID3D11Buffer> m_constantBuffer = nullptr;


	//定数バッファ構造体定義(パーティクル)
	struct ConstantBufferForPerFrame
	{
		XMFLOAT4X4 view;//ビュー変換用行列
		XMFLOAT4X4 projection;//透視変換用行列
		XMFLOAT2 TextureSize;//一チップ当たりの大きさ(UV座標)
		XMFLOAT2 TextureNum;//テクスチャのチップの数(X,Y);
	};

	ConstantBufferForPerFrame cb =
	{
		XMFLOAT4X4{0,0,0,0,   0,0,0,0, 0,0,0,0, 0,0,0,0},
		XMFLOAT4X4{0,0,0,0,   0,0,0,0, 0,0,0,0, 0,0,0,0},
		XMFLOAT2{0,0},
		XMFLOAT2{0,0}
	};

private:
	void SetNum(int MaxNum);
public:
	void Create(ID3D11Device* device, int Num, std::string name, VECTOR2 TextureChipSize, VECTOR2 TextureNum);
	void SetConstant(VECTOR2 TextureChipSize, VECTOR2 TextureNum);
	void Fire(DirectX::XMFLOAT3 pos, int max);
	void Fire2(DirectX::XMFLOAT3 pos, int max);
	
	//void Update(float timer);
	void Animation(float elapsedtimer, int Starttype,int Endtype,float Animetionspeed);
	void Set(ID3D11DeviceContext* context);
	void UpdateConstantBuffer(ID3D11DeviceContext* context, XMFLOAT4X4 view, XMFLOAT4X4 projection);
	void Render(ID3D11DeviceContext* context);
	//現在使用しているエフェクトの最後の番号
	void  SetUseLastEffectIndex();
	inline int GetUseLastEffectIndex() { return UseLastEffectIndex; };
	inline vector<EffectData>* Geteffects() { return &spriteEffects; };
	inline const string GetTextureName() { return Texture->GetFilename(); };
};

