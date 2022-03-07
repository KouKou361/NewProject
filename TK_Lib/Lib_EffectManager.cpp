#include "Lib_EffectManager.h"
#include "Lib_Rasterizer.h"
#include "Lib_DepthStencil.h"

//初期化処理
void Lib_EffectManager::Init(const UINT MaxLoadNum, ID3D11Device* device)
{
	SpriteEffects.resize(MaxLoadNum);
	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		SpriteEffects.at(i) = make_shared<SpriteEffect>();
	}

	PointSpriteshader = make_unique<ShaderResource>();
	PointSpriteshader->Create(device, "./Shader/PointSprite_vs.cso", "./Shader/PointSprite_gs.cso", "./Shader/PointSprite_ps.cso", ShaderResource::TYPELayout::TYPE_layoutPointSprite);
}
//ロード(1:device,2:テクスチャのパス,3:エフェクトのハンドル)
void Lib_EffectManager::Load(ID3D11Device* device, const string name, int& handle, int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state)
{
	//既に読み込んでいるテクスチャがあるかどうかを調べる
	if (DuplicateFind(name, handle) == true)
	{
		//texturesの空である要素に登録していく
		Register(device, name, handle,Maxnum,TextureChipSize,TextureNum, state);
	}
}
//削除
void Lib_EffectManager::Erase(ID3D11Device* device, const  int handle)
{
	//テクスチャの取得
	SpriteEffect* textureData = GetSpriteEffectResource(handle);
	//値を削除
	textureData->handle = -1;
	SpriteEffects.at(handle).reset();

	//テクスチャの読み込んだ数を-1する
	LoadNum--;
}
void Lib_EffectManager::Clear()
{
	SpriteEffects.clear();
}
//テクスチャの取得
SpriteEffect* Lib_EffectManager::GetSpriteEffectResource(const int handle)
{
	//設定されていないまたは削除されたテクスチャを使おうとしているかどうか
	assert(SpriteEffects.at(handle)->handle != -1);
	return SpriteEffects.at(handle).get();
}
//更新処理
void Lib_EffectManager::Update()
{
	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		SpriteEffects.at(i)->SetUseLastEffectIndex();
	}
}
//アニメーション処理
void Lib_EffectManager::Animation(float elapsedtimer, const  int handle, int Starttype, int Endtype, float Animetionspeed)
{
	SpriteEffect* efc= SpriteEffects.at(handle).get();
	if (efc->handle <= -1)return;
	efc->Animation(elapsedtimer, Starttype, Endtype, Animetionspeed);
}
void Lib_EffectManager::SetType(const int handle, int type)
{
	for (int i = 0; i < GetSpriteEffectResource(handle)->Geteffects()->size(); i++)
	{
		GetSpriteEffectResource(handle)->Geteffects()->at(i).type = type;
	}

}



//エフェクトの描画開始処理
void Lib_EffectManager::Begin(ID3D11DeviceContext* context)
{

	//シェーダー有効化
	PointSpriteshader->Activate(context);
	//ラスタライザー設定
	context->RSSetState(Rasterizer::Instance().m_rasterizer[Rasterizer::RasterizerFill_TRUE].Get());
	//デプスステンシル
	context->OMSetDepthStencilState(DepthStencil::Instance().m_depthState[DepthStencil::DS_WRITE_FALSE].Get(), 1);
	//プリミティブトポロジーをセット
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
}
//描画処理
void Lib_EffectManager::Render(ID3D11DeviceContext* context, XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	string oldTextureFileName="";
	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		if (SpriteEffects.at(i)->handle <= -1)continue;

		if (strcmp(oldTextureFileName.c_str(), SpriteEffects.at(i)->GetTextureName().c_str()) != 0)
		{
			SpriteEffects.at(i)->UpdateConstantBuffer(context,view,projection);
		}

		oldTextureFileName = SpriteEffects.at(i)->GetTextureName();


		SpriteEffects.at(i)->Render(context);
	}
}
//エフェクトの描画開始処理
void Lib_EffectManager::End(ID3D11DeviceContext* context)
{
	//デプスステンシル設定
	context->OMSetDepthStencilState(DepthStencil::Instance().m_depthState[DepthStencil::DS_FALSE].Get(), 1);
	//シェーダーの無効化
	PointSpriteshader->Inactivate(context);
}

//既に読み込んでいる同じテクスチャがあるかどうかを調べる
//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
bool Lib_EffectManager::DuplicateFind(const string name, int& handle)
{
//	for (int i = 0; i < SpriteEffects.size(); i++)
//	{
//
//
//		//テクスチャの取得
//		SpriteEffect* textureData = SpriteEffects.at(i).get();
//
//		if (-1 >= textureData->handle)continue;
//
//		//テクスチャが重複しているかどうかを検索
//		if (name == textureData->filename)
//		{
//			//重複してるやん
//			handle = textureData->handle;
//			return false;
//		}
//	}
	return true;
}

//texturesの空である要素に登録していく
void Lib_EffectManager::Register(ID3D11Device* device, const string name, int& handle,int Maxnum,VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state)
{
	//Textureの読み込める数が最大に達しているかどうか
	assert(LoadNum < SpriteEffects.size());

	for (int i = 0; i < SpriteEffects.size(); i++)
	{
		//テクスチャの取得
		SpriteEffect* efc = SpriteEffects.at(i).get();
		if (-1 < efc->handle)continue;

		//空に登録する
		efc->Create(device,Maxnum, name,TextureChipSize,TextureNum);
		efc->handle = i;
		efc->BlenderType = state;
		handle = i;
		LoadNum++;
		break;

	}
}
vector<EffectData>* Lib_EffectManager::Geteffects(const int handle)
{
	_ASSERT_EXPR(SpriteEffects.at(handle)->handle > -1, "生成していないエフェクトを使用しました");
	return SpriteEffects.at(handle)->Geteffects();
}