#include "Export.h"
#include "Scene.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"
#include "ObjectManager.h"

#include "EffectDerived.h"
#include "EffectManager.h"
#include "ObjectDerived.h"
#include "ObjectFunctionDerive.h"

#include "ObjectFunctionManager.h"

#include <stdlib.h>
#include <fstream>
#include <functional>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <WICTextureLoader.h>

#pragma warning(disable : 4996)

// シリアライズ
namespace DirectX
{
	template<class Archive>
	void serialize(Archive& archive, XMUINT4& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y),
			cereal::make_nvp("z", v.z),
			cereal::make_nvp("w", v.w)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, VECTOR2& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, VECTOR3& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y),
			cereal::make_nvp("z", v.z)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, VECTOR4& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y),
			cereal::make_nvp("z", v.z),
			cereal::make_nvp("w", v.w)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, XMFLOAT4X4& m)
	{
		archive(
			cereal::make_nvp("_11", m._11), cereal::make_nvp("_12", m._12), cereal::make_nvp("_13", m._13), cereal::make_nvp("_14", m._14),
			cereal::make_nvp("_21", m._21), cereal::make_nvp("_22", m._22), cereal::make_nvp("_23", m._23), cereal::make_nvp("_24", m._24),
			cereal::make_nvp("_31", m._31), cereal::make_nvp("_32", m._32), cereal::make_nvp("_33", m._33), cereal::make_nvp("_34", m._34),
			cereal::make_nvp("_41", m._41), cereal::make_nvp("_42", m._42), cereal::make_nvp("_43", m._43), cereal::make_nvp("_44", m._44)
		);
	}
}


template<class Archive>
void ExportActor::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(handle),
		CEREAL_NVP(filename),
		CEREAL_NVP(type),
		CEREAL_NVP(name),
		CEREAL_NVP(pos),
		CEREAL_NVP(angle),
		CEREAL_NVP(scale),
		CEREAL_NVP(color),
		CEREAL_NVP(select)
	);
}
void Export::Loading(const std::string filename)
{
	//=====================
	//バイナリファイルの読み取り
	//=====================	
	// デシリアライズ
	std::ifstream istream(filename, std::ios::binary);
	if (istream.is_open())
	{
		cereal::BinaryInputArchive archive(istream);

		try
		{
			//作成！
			archive(
				CEREAL_NVP(exportActorList)
			);
		//	MessageBox(*TK_Lib::GetHWND(), L"成功", L"", 0);
			return;
		}

		catch (...)
		{
			//デシリアライズが無い！
			MessageBox(*TK_Lib::GetHWND(), L"Dataが読み込めません", L"", 0);
		}

	}
}

//オブジェクトの配置
void Export::ObjectSet()
{
	for (int i = 0; i < exportActorList.size(); i++)
	{
		ExportActor* ExportActor = &exportActorList.at(i);

		if ("ENEMY"      == ExportActor->type)  SetEnemy(ExportActor);      //敵配置の設定へ
		if ("OBJECT"     == ExportActor->type)  SetObject(ExportActor);		//オブジェクト配置の設定へ
		if ("STAGE"      == ExportActor->type)  SetStage(ExportActor);		//ステート配置の設定へ
		if ("POINTLIGHT" == ExportActor->type)  SetPointLight(ExportActor);	//ポイントライト配置の設定へ
		if ("FUNCTION"   == ExportActor->type)  SetFunction(ExportActor);	//関数配置の設定へ
		if ("EFFECT"     == ExportActor->type)  SetEffeect(ExportActor);	//エフェクト配置の設定へ
	}	
}

//敵の配置する
void Export::SetEnemy(ExportActor* exportActor)
{
	EnemyManager* enemyManager = sceneGame->enemyManager.get();
	shared_ptr<EnemyBase> enm=nullptr;

	if ("Slime"       == exportActor->name)enm = std::make_shared<EnemySlime>(sceneGame);	   //スライム
	//if ("Boom"        == ExportActor->name)enm = std::make_shared<EnemyBoom> (sceneGame);	   //
	if ("ChestEnemy"  == exportActor->name)enm = std::make_shared<EnemyChest>(sceneGame);	   //宝箱モンスター
	if ("TurtleShell" == exportActor->name)enm = std::make_shared<EnemyTurtleShell>(sceneGame);//亀
	if ("Boss"        == exportActor->name)enm = std::make_shared<EnemyBoss> (sceneGame);	   //ボス

	//敵がnullの時はreturn
	if (enm == nullptr) {
		assert(!"名前が見当たりません");
		return;
	}

	enm->SetPos(exportActor->pos);
	enemyManager->Register(enm);
}
//オブジェクトのセットする
void Export::SetObject(ExportActor* exportActor)
{
	ObjectManager* objectManager = sceneGame->objectManager.get();
	shared_ptr<ObjectBase> obj = nullptr;

	if ("Wall"  == exportActor->name)obj = std::make_shared<ObjectWall> (objectManager, sceneGame);//壁
	if ("Pat"   == exportActor->name)obj = std::make_shared<ObjectPot>  (objectManager, sceneGame);//ポット
	if ("Tower" == exportActor->name)obj = std::make_shared<ObjectTower>(objectManager, sceneGame);//タワー

	//敵がnullの時はreturn
	if (obj == nullptr) {
		assert(!"名前が見当たりません");
		return;
	}

	obj->SetPos(exportActor->pos);
	objectManager->Register(obj);
}

//ステージのセットする
void Export::SetStage(ExportActor* exportActor)
{

}

//敵のセットする
void Export::SetPointLight(ExportActor* exportActor)
{
	//とりあえず適当にセットしておく
	TK_Lib::SpotLight::Create(exportActor->pos,exportActor->color,exportActor->scale.x);
}

//エフェクトの設定
void Export::SetEffeect(ExportActor* exportActor)
{

	EffectManager* effectManager = sceneGame->effectManager.get();
	
	int ret=-1;

	if ("Fire" == exportActor->name)ret = 0;
	if ("Destroy" == exportActor->name)ret = 0;

	//敵がnullの時はreturn
	if (ret == -1) {
		assert(!"名前が見当たりません");
		return;
	}
	const int PlayNum = 1;
	effectManager->UpdateEffectRegister(exportActor->pos, exportActor->name, PlayNum);
}

//関数の設定
void Export::SetFunction(ExportActor* exportActor)
{

	ObjectFunctionManager* objectFunctionManager = sceneGame->GetObjectFunctionManager();
	shared_ptr<ObjectFunctionBase> objFunction = nullptr;

	if ("Start" == exportActor->name)objFunction=make_shared<FunctionStart>(sceneGame);
	if ("End" == exportActor->name)objFunction = make_shared<FunctionEnd>(sceneGame);
	//if ("Boom" == ExportActor->name)obj = std::make_shared<EnemyBoom>(objectManager);
	//if ("ChestEnemy" == ExportActor->name)obj = std::make_shared<EnemyChest>(objectManager);
	//if ("TurtleShell" == ExportActor->name)obj = std::make_shared<EnemyTurtleShell>(objectManager);
		//敵がnullの時はreturn
	if (objFunction == nullptr) {
		assert(!"名前が見当たりません");
		return;
	}
	objFunction->SetPos(exportActor->pos);
	objFunction->SetRadius(exportActor->scale.x);

	objectFunctionManager->Register(objFunction);
}





