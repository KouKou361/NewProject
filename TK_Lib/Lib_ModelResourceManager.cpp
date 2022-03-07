#include "Lib_ModelResourceManager.h"

//����������
void ModelResourceManager::Init(const UINT MaxLoadNum)
{
	models.resize(MaxLoadNum);
	for (int i = 0; i < models.size(); i++)
	{
		models.at(i) = make_shared<ModelResource>();
	}
}
//���[�h(1:device,2:�e�N�X�`���̃p�X,3:�e�N�X�`���̃n���h��)
bool ModelResourceManager::Load(ID3D11Device* device, const string name, int& handle,const string key)
{
	//���ɓǂݍ���ł���e�N�X�`�������邩�ǂ����𒲂ׂ�
	if (DuplicateFind(name, handle) == true)
	{
		
		//textures�̋�ł���v�f�ɓo�^���Ă���
		bool result=Register(device, name, handle);
		ModelIndexResources.insert(make_pair(key, handle));
		return result;
	}
	return true;
}

int ModelResourceManager::Copy(int& handle)
{
	//���f���̓ǂݍ��߂鐔���ő�ɒB���Ă��邩�ǂ���
	assert(LoadNum < models.size());

	//���f���̎擾
	ModelResource* CopyModel = models.at(handle).get();

	for (int i = 0; i < models.size(); i++)
	{
		//�g���Ă��Ȃ��󃂃f���̎擾
		ModelResource* model = models.at(i).get();
		if (-1 < model->handle)continue;
		//��ɓo�^����


		model->Copy(CopyModel);
		model->handle = i;
		LoadNum++;
		return model->handle;
		
	}

	//�ǂݍ��ݎ��s
	assert(LoadNum < models.size());
	return 0;
}

//���f���̍s��X�V����
void ModelResourceManager::Tranceform(ID3D11Device* device, XMFLOAT4X4 W, const int handle)
{
	ModelResource* modelData = GetModelResource(handle);

	DirectX::XMMATRIX World;
	World = DirectX::XMLoadFloat4x4(&W);

	modelData->CalculateLocalTransform();
	modelData->CalculateWorldTransform(World);

}
//���f���̃A�j���[�V����
void ModelResourceManager::UPdateAnimetion(ID3D11Device* device, const int handle, const float elapsedTime)
{
	ModelResource* modelData = GetModelResource(handle);
	modelData->UpdateAnimation(elapsedTime);
}
//���f���̃A�j���[�V�������Đ������ǂ���
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

//�L�[�̖��O����ԍ����擾����
int ModelResourceManager::GetModelFromSerchKey(const string& SearchName)
{
    return ModelIndexResources.at(SearchName);
}
//�m�[�h��������
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

//�m�[�h��������
float ModelResourceManager::GetAnimetionTime(int modelIndex)
{
	ModelResource* modelData = GetModelResource(modelIndex);
	return modelData->GetAnimetionTime();
}


//�폜
void ModelResourceManager::Erase(ID3D11Device* device, const  int handle)
{
	//�e�N�X�`���̎擾
	ModelResource* modelData = GetModelResource(handle);
	//�l���폜
	modelData->handle = -1;
	models.at(handle).reset();
	models.at(handle) = make_shared<ModelResource>();

	//�e�N�X�`���̓ǂݍ��񂾐���-1����
	LoadNum--;
}
//�S����
void ModelResourceManager::Clear()
{
	ModelIndexResources.clear();
	models.clear();

}
//���f�����\�[�X�̎擾
ModelResource* ModelResourceManager::GetModelResource(const int handle)
{
	//�ݒ肳��Ă��Ȃ��܂��͍폜���ꂽ���f�����g�����Ƃ��Ă��邩�ǂ���
	assert(models.at(handle)->handle != -1);
	_ASSERT_EXPR(models.at(handle) != nullptr, L"model��nullptr");
	return models.at(handle).get();
}

//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
bool ModelResourceManager::DuplicateFind(const string name, int& handle)
{
	for (int i = 0; i < models.size(); i++)
	{


		//�e�N�X�`���̎擾
		ModelResource* modelData = models.at(i).get();

		if (-1 >= modelData->handle)continue;

		//�e�N�X�`�����d�����Ă��邩�ǂ���������
		if (name == modelData->filename)
		{
			//�d�����Ă���
			//handle = Copy(modelData->handle);
			
			handle = modelData->handle;
			
			return false;
		}
	}
	return true;
}

//textures�̋�ł���v�f�ɓo�^���Ă���
bool ModelResourceManager::Register(ID3D11Device* device, const string name, int& handle)
{
	//Texture�̓ǂݍ��߂鐔���ő�ɒB���Ă��邩�ǂ���
	assert(LoadNum < models.size());

	for (int i = 0; i < models.size(); i++)
	{
		//�g���Ă��Ȃ��󃂃f���̎擾
		ModelResource* model = models.at(i).get();
		if (-1 < model->handle)continue;


		model->filename = name;
		model->handle = i;
		handle = i;
		LoadNum++;

		//��ɓo�^����
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