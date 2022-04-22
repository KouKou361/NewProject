#pragma once
#include "ObjectManager.h"
#include "Collision.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "CameraController.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"

//����������
void ObjectManager::Init()
{

}
//�X�V����
void ObjectManager::Update()
{
	for (shared_ptr<ObjectBase> obj : objes)
	{
		if (obj)
		{
			obj->Update();
		}

	}
	//�j������
//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<ObjectBase> obj : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<ObjectBase>>::iterator it = std::find(objes.begin(), objes.end(), obj);
		if (it != objes.end())
		{
			objes.erase(it);
		}
	}
	remove.clear();

}
//�`�揈��
void ObjectManager::Render()
{
	//for (shared_ptr<ObjectBase> obj : objes)
	//{
	//	if (obj)
	//	{
	//		obj->Render();
	//
	//		//Imgui
	//		//obj->ImguiDebug();
	//	}
	//}
}
//���f���`�揈��
void ObjectManager::ModelRender()
{
	for (shared_ptr<ObjectBase> obj : objes)
	{
		if (obj)
		{
			obj->ModelRender();
		}
	}
}
//�j������
void ObjectManager::Destroy(ObjectBase* obj)
{
	for (shared_ptr<ObjectBase> m_obj : objes)
	{
		std::vector<shared_ptr<ObjectBase>>::iterator it = std::find(objes.begin(), objes.end(), m_obj);
		if (it->get() == obj)
		{
			shared_ptr<ObjectBase> e = m_obj;
			remove.emplace_back(e);
		}
	}


	//�폜����̂ŖڕW�ɂ��Ă����L�����N�^�[������
	//�ڕW���Z�b�g
	ResetTheTargetCharacter(obj);

}
bool ObjectManager::CollisionObject(const VECTOR3 pos, const float weight, const float collisionRadius, VECTOR3& OutPos, ObjectBase*& Saveobj)
{
	VECTOR3 OutPosB;
	bool hitFlg = false;

	for (int i = 0; i < GetObjesSize(); i++)
	{
		ObjectBase* obj = GetObjesIndex(i);
		if (Collision::Instance().SphereVsSphere(pos, weight, collisionRadius, obj->GetPos(), obj->GetWeight(), obj->GetCollisionRadius(), OutPos, OutPosB))
		{
			//obj->SetPos(OutPosB);
			//pos = OutPosB;
			hitFlg = true; 
			Saveobj = obj;
		}

	}
	return hitFlg;

}
//���݂̃^���[�̐�
int ObjectManager::GetTowerNum()
{
	int PotNum = 0;

	for (int i = 0; i < GetObjesSize(); i++)
	{
		ObjectBase* obj = GetObjesIndex(i);
		if (obj->GetType() == ObjectType::TOWER)
		{
			PotNum++;
		}
	}
	return PotNum;

}


void ObjectManager::CollisionDebug()
 {
	for (shared_ptr<ObjectBase> obj : objes)
	{
		if (obj)
		{
		//	obj->CollisionDebug();
		}
	}
}

//�S�폜
void ObjectManager::Clear()
{
	for (int i = 0; i < GetObjesSize(); i++)
	{
		ObjectBase* obj = GetObjesIndex(i);
		ResetTheTargetCharacter(obj);
	}

	objes.clear();
	remove.clear();
}
//�o�^
void ObjectManager::Register(shared_ptr<ObjectBase> obj)
{
	obj->Init();
	objes.emplace_back(obj);
}
void ObjectManager::ResetTheTargetCharacter(ObjectBase* obj)
{
	//�~�j�I���̖ڕW���Z�b�g
	for (int i = 0; i < sceneGame->GetPlayer()->GetMinionManager()->GetMinionsSize(); i++)
	{
		//�~�j�I���̎擾
		MinionPlayer* minion = sceneGame->GetPlayer()->GetMinionManager()->GetMinionIndex(i);
		//�����~�j�I���̖ڕW���w�肳�ꂽ�G(����)�Ȃ��
		if (minion->GetTarget() == obj)
		{
			//�ڕW�̃��Z�b�g
			minion->SetTarget(nullptr);
		}
	}

	//�v���C���[�̖ڕW�̃��Z�b�g
	if (sceneGame->GetPlayer()->GetTarget() == obj)
	{//�ڕW�̃��Z�b�g
		sceneGame->GetPlayer()->SetTarget(nullptr);
	}

	//�J�����̃��Z�b�g
	if (sceneGame->GetCameraManager()->GetTargetChractor() == obj)
	{//�ڕW�̃��Z�b�g
		sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(sceneGame->GetPlayer()));
	}
}