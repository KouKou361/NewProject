#include "Lib_ModelResourceManager.h"

//初期化処理
void ModelResourceManager::Init(const UINT MaxLoadNum)
{
	models.resize(MaxLoadNum);
	for (int i = 0; i < models.size(); i++)
	{
		models.at(i) = make_shared<ModelResource>();
	}
}
//ロード(1:device,2:テクスチャのパス,3:テクスチャのハンドル)
bool ModelResourceManager::Load(ID3D11Device* device, const string name, int& handle,const string key)
{
	//既に読み込んでいるテクスチャがあるかどうかを調べる
	if (DuplicateFind(name, handle) == true)
	{
		
		//texturesの空である要素に登録していく
		bool result=Register(device, name, handle);
		ModelIndexResources.insert(make_pair(key, handle));
		return result;
	}
	return true;
}

int ModelResourceManager::Copy(int& handle)
{
	//モデルの読み込める数が最大に達しているかどうか
	assert(LoadNum < models.size());

	//モデルの取得
	ModelResource* CopyModel = models.at(handle).get();

	for (int i = 0; i < models.size(); i++)
	{
		//使っていない空モデルの取得
		ModelResource* model = models.at(i).get();
		if (-1 < model->handle)continue;
		//空に登録する


		model->Copy(CopyModel);
		model->handle = i;
		LoadNum++;
		return model->handle;
		
	}

	//読み込み失敗
	assert(LoadNum < models.size());
	return 0;
}

//モデルの行列更新処理
void ModelResourceManager::Tranceform(ID3D11Device* device, XMFLOAT4X4 W, const int handle)
{
	ModelResource* modelData = GetModelResource(handle);

	DirectX::XMMATRIX World;
	World = DirectX::XMLoadFloat4x4(&W);

	modelData->CalculateLocalTransform();
	modelData->CalculateWorldTransform(World);

}
//モデルのアニメーション
void ModelResourceManager::UPdateAnimetion(ID3D11Device* device, const int handle, const float elapsedTime)
{
	ModelResource* modelData = GetModelResource(handle);
	modelData->UpdateAnimation(elapsedTime);
}
//モデルのアニメーションが再生中かどうか
bool ModelResourceManager::IsPlayAnimetion(const int handle)
{
	ModelResource* modelData = GetModelResource(handle);
	return modelData->IsPlayAnimetion();
}

void ModelResourceManager::PlayAnimation(const int handle, int animationIndex, bool loop)
{
	ModelResource* modelData = GetModelResource(handle);
	modelData->PlayAnimation(animationIndex, loop);
}

//キーの名前から番号を取得する
int ModelResourceManager::GetModelFromSerchKey(const string& SearchName)
{
    return ModelIndexResources.at(SearchName);
}
//ノード検索する
ModelResource::NodeTest* ModelResourceManager::FindNode(int modelIndex,const char* name)
{
	ModelResource* modelData = GetModelResource(modelIndex);
	return modelData->FindNode(name);
}


float ModelResourceManager::GetEndAnimetionTime(int modelIndex)
{
	ModelResource* modelData = GetModelResource(modelIndex);
	return modelData->GetEndAnimetionTime();
}

//ノード検索する
float ModelResourceManager::GetAnimetionTime(int modelIndex)
{
	ModelResource* modelData = GetModelResource(modelIndex);
	return modelData->GetAnimetionTime();
}


//削除
void ModelResourceManager::Erase(ID3D11Device* device, const  int handle)
{
	//テクスチャの取得
	ModelResource* modelData = GetModelResource(handle);
	//値を削除
	modelData->handle = -1;
	models.at(handle).reset();
	models.at(handle) = make_shared<ModelResource>();

	//テクスチャの読み込んだ数を-1する
	LoadNum--;
}
//全消し
void ModelResourceManager::Clear()
{
	ModelIndexResources.clear();
	models.clear();

}
//モデルリソースの取得
ModelResource* ModelResourceManager::GetModelResource(const int handle)
{
	//設定されていないまたは削除されたモデルを使おうとしているかどうか
	assert(models.at(handle)->handle != -1);
	_ASSERT_EXPR(models.at(handle) != nullptr, L"modelがnullptr");
	return models.at(handle).get();
}

//既に読み込んでいる同じテクスチャがあるかどうかを調べる
//もし既に読み込んでいる同じテクスチャ場合handleに値が入ります
bool ModelResourceManager::DuplicateFind(const string name, int& handle)
{
	for (int i = 0; i < models.size(); i++)
	{


		//テクスチャの取得
		ModelResource* modelData = models.at(i).get();

		if (-1 >= modelData->handle)continue;

		//テクスチャが重複しているかどうかを検索
		if (name == modelData->filename)
		{
			//重複してるやん
			//handle = Copy(modelData->handle);
			
			handle = modelData->handle;
			
			return false;
		}
	}
	return true;
}

//texturesの空である要素に登録していく
bool ModelResourceManager::Register(ID3D11Device* device, const string name, int& handle)
{
	//Textureの読み込める数が最大に達しているかどうか
	assert(LoadNum < models.size());

	for (int i = 0; i < models.size(); i++)
	{
		//使っていない空モデルの取得
		ModelResource* model = models.at(i).get();
		if (-1 < model->handle)continue;


		model->filename = name;
		model->handle = i;
		handle = i;
		LoadNum++;

		//空に登録する
		bool result= model->Load(device, name.c_str());
		if (result==false)
		{
			Erase(device, model->handle);
		}
		return result;

	
		break;

	}
	return false;
}