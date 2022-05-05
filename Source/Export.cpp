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

// �V���A���C�Y
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
	//�o�C�i���t�@�C���̓ǂݎ��
	//=====================	
	// �f�V���A���C�Y
	std::ifstream istream(filename, std::ios::binary);
	if (istream.is_open())
	{
		cereal::BinaryInputArchive archive(istream);

		try
		{
			//�쐬�I
			archive(
				CEREAL_NVP(exportActorList)
			);
		//	MessageBox(*TK_Lib::GetHWND(), L"����", L"", 0);
			return;
		}

		catch (...)
		{
			//�f�V���A���C�Y�������I
			MessageBox(*TK_Lib::GetHWND(), L"Data���ǂݍ��߂܂���", L"", 0);
		}

	}
}

//�I�u�W�F�N�g�̔z�u
void Export::ObjectSet()
{
	for (int i = 0; i < exportActorList.size(); i++)
	{
		ExportActor* ExportActor = &exportActorList.at(i);

		if ("ENEMY"      == ExportActor->type)  SetEnemy(ExportActor);      //�G�z�u�̐ݒ��
		if ("OBJECT"     == ExportActor->type)  SetObject(ExportActor);		//�I�u�W�F�N�g�z�u�̐ݒ��
		if ("STAGE"      == ExportActor->type)  SetStage(ExportActor);		//�X�e�[�g�z�u�̐ݒ��
		if ("POINTLIGHT" == ExportActor->type)  SetPointLight(ExportActor);	//�|�C���g���C�g�z�u�̐ݒ��
		if ("FUNCTION"   == ExportActor->type)  SetFunction(ExportActor);	//�֐��z�u�̐ݒ��
		if ("EFFECT"     == ExportActor->type)  SetEffeect(ExportActor);	//�G�t�F�N�g�z�u�̐ݒ��
	}	
}

//�G�̔z�u����
void Export::SetEnemy(ExportActor* exportActor)
{
	EnemyManager* enemyManager = sceneGame->enemyManager.get();
	shared_ptr<EnemyBase> enm=nullptr;

	if ("Slime"       == exportActor->name)enm = std::make_shared<EnemySlime>(sceneGame);	   //�X���C��
	//if ("Boom"        == ExportActor->name)enm = std::make_shared<EnemyBoom> (sceneGame);	   //
	if ("ChestEnemy"  == exportActor->name)enm = std::make_shared<EnemyChest>(sceneGame);	   //�󔠃����X�^�[
	if ("TurtleShell" == exportActor->name)enm = std::make_shared<EnemyTurtleShell>(sceneGame);//�T
	if ("Boss"        == exportActor->name)enm = std::make_shared<EnemyBoss> (sceneGame);	   //�{�X

	//�G��null�̎���return
	if (enm == nullptr) {
		assert(!"���O����������܂���");
		return;
	}

	enm->SetPos(exportActor->pos);
	enemyManager->Register(enm);
}
//�I�u�W�F�N�g�̃Z�b�g����
void Export::SetObject(ExportActor* exportActor)
{
	ObjectManager* objectManager = sceneGame->objectManager.get();
	shared_ptr<ObjectBase> obj = nullptr;

	if ("Wall"  == exportActor->name)obj = std::make_shared<ObjectWall> (objectManager, sceneGame);//��
	if ("Pat"   == exportActor->name)obj = std::make_shared<ObjectPot>  (objectManager, sceneGame);//�|�b�g
	if ("Tower" == exportActor->name)obj = std::make_shared<ObjectTower>(objectManager, sceneGame);//�^���[

	//�G��null�̎���return
	if (obj == nullptr) {
		assert(!"���O����������܂���");
		return;
	}

	obj->SetPos(exportActor->pos);
	objectManager->Register(obj);
}

//�X�e�[�W�̃Z�b�g����
void Export::SetStage(ExportActor* exportActor)
{

}

//�G�̃Z�b�g����
void Export::SetPointLight(ExportActor* exportActor)
{
	//�Ƃ肠�����K���ɃZ�b�g���Ă���
	TK_Lib::SpotLight::Create(exportActor->pos,exportActor->color,exportActor->scale.x);
}

//�G�t�F�N�g�̐ݒ�
void Export::SetEffeect(ExportActor* exportActor)
{

	EffectManager* effectManager = sceneGame->effectManager.get();
	
	int ret=-1;

	if ("Fire" == exportActor->name)ret = 0;
	if ("Destroy" == exportActor->name)ret = 0;

	//�G��null�̎���return
	if (ret == -1) {
		assert(!"���O����������܂���");
		return;
	}
	const int PlayNum = 1;
	effectManager->UpdateEffectRegister(exportActor->pos, exportActor->name, PlayNum);
}

//�֐��̐ݒ�
void Export::SetFunction(ExportActor* exportActor)
{

	ObjectFunctionManager* objectFunctionManager = sceneGame->GetObjectFunctionManager();
	shared_ptr<ObjectFunctionBase> objFunction = nullptr;

	if ("Start" == exportActor->name)objFunction=make_shared<FunctionStart>(sceneGame);
	if ("End" == exportActor->name)objFunction = make_shared<FunctionEnd>(sceneGame);
	//if ("Boom" == ExportActor->name)obj = std::make_shared<EnemyBoom>(objectManager);
	//if ("ChestEnemy" == ExportActor->name)obj = std::make_shared<EnemyChest>(objectManager);
	//if ("TurtleShell" == ExportActor->name)obj = std::make_shared<EnemyTurtleShell>(objectManager);
		//�G��null�̎���return
	if (objFunction == nullptr) {
		assert(!"���O����������܂���");
		return;
	}
	objFunction->SetPos(exportActor->pos);
	objFunction->SetRadius(exportActor->scale.x);

	objectFunctionManager->Register(objFunction);
}





