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
		CEREAL_NVP(Pos),
		CEREAL_NVP(Angle),
		CEREAL_NVP(Scale),
		CEREAL_NVP(Color),
		CEREAL_NVP(Select)
	);
}
void Export::Loading(std::string filename)
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

void Export::ObjectSet()
{



	for (int i = 0; i < exportActorList.size(); i++)
	{
		ExportActor* ExportActor = &exportActorList.at(i);

		if ("ENEMY" == ExportActor->type)     SetEnemy(ExportActor);
		if ("OBJECT" == ExportActor->type)    SetObject(ExportActor);
		if ("STAGE" == ExportActor->type)     SetStage(ExportActor);
		if ("POINTLIGHT" == ExportActor->type)SetPointLight(ExportActor);
		if ("FUNCTION" == ExportActor->type)  SetFunction(ExportActor);
		if ("EFFECT" == ExportActor->type)    SetEffeect(ExportActor);
	}	
}

//敵のセットする
void Export::SetEnemy(ExportActor* ExportActor)
{
	EnemyManager* enemyManager = sceneGame->enemyManager.get();
	shared_ptr<EnemyBase> enm=nullptr;

	if ("Slime" == ExportActor->name)enm=std::make_shared<EnemySlime>(sceneGame);
	if ("Boom" == ExportActor->name)enm = std::make_shared<EnemyBoom>(sceneGame);
	if ("ChestEnemy" == ExportActor->name)enm = std::make_shared<EnemyChest>(sceneGame);
	if ("TurtleShell" == ExportActor->name)enm = std::make_shared<EnemyTurtleShell>(sceneGame);
	if ("Boss" == ExportActor->name)enm = std::make_shared<EnemyBoss>(sceneGame);

	//敵がnullの時はreturn
	if (enm == nullptr) {
		assert(!"名前が見当たりません");
		return;
	}
	enm->SetPos(ExportActor->Pos);

	enemyManager->Register(enm);
}
//オブジェクトのセットする
void Export::SetObject(ExportActor* ExportActor)
{
	ObjectManager* objectManager = sceneGame->objectManager.get();
	shared_ptr<ObjectBase> obj = nullptr;

	if ("Wall" == ExportActor->name)obj = std::make_shared<ObjectWall>(objectManager,sceneGame);
	if ("Pat" == ExportActor->name)obj = std::make_shared<ObjectPot>(objectManager, sceneGame);
	if ("Tower" == ExportActor->name)obj = std::make_shared<ObjectTower>(objectManager, sceneGame);
	//if ("ChestEnemy" == ExportActor->name)obj = std::make_shared<EnemyChest>(objectManager);
	//if ("TurtleShell" == ExportActor->name)obj = std::make_shared<EnemyTurtleShell>(objectManager);

	//敵がnullの時はreturn
	if (obj == nullptr) {
		assert(!"名前が見当たりません");
		return;
	}
	obj->SetPos(ExportActor->Pos);

	objectManager->Register(obj);
}

//ステージのセットする
void Export::SetStage(ExportActor* ExportActor)
{

}

//敵のセットする
void Export::SetPointLight(ExportActor* ExportActor)
{
	//とりあえず適当にセットしておく
	TK_Lib::SpotLight::Create(ExportActor->Pos,ExportActor->Color,ExportActor->Scale.x);
}

//エフェクトの設定
void Export::SetEffeect(ExportActor* ExportActor)
{

	EffectManager* effectManager = sceneGame->effectManager.get();
	
	int ret=-1;

	if ("Fire" == ExportActor->name)ret = 0;
	if ("Destroy" == ExportActor->name)ret = 0;

	//敵がnullの時はreturn
	if (ret == -1) {
		assert(!"名前が見当たりません");
		return;
	}
	const int PlayNum = 1;
	effectManager->UpdateEffectRegister(ExportActor->Pos, ExportActor->name, PlayNum);
}

//関数の設定
void Export::SetFunction(ExportActor* ExportActor)
{

	ObjectFunctionManager* objectFunctionManager = sceneGame->GetObjectFunctionManager();
	shared_ptr<ObjectFunctionBase> objFunction = nullptr;

	if ("Start" == ExportActor->name)objFunction=make_shared<FunctionStart>(sceneGame);
	if ("End" == ExportActor->name)objFunction = make_shared<FunctionEnd>(sceneGame);
	//if ("Boom" == ExportActor->name)obj = std::make_shared<EnemyBoom>(objectManager);
	//if ("ChestEnemy" == ExportActor->name)obj = std::make_shared<EnemyChest>(objectManager);
	//if ("TurtleShell" == ExportActor->name)obj = std::make_shared<EnemyTurtleShell>(objectManager);
		//敵がnullの時はreturn
	if (objFunction == nullptr) {
		assert(!"名前が見当たりません");
		return;
	}
	objFunction->SetPos(ExportActor->Pos);
	objFunction->SetRadius(ExportActor->Scale.x);

	objectFunctionManager->Register(objFunction);
}





