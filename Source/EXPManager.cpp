#include "EXPManager.h"
#include "EXP.h"
//����������
void EXPManager::Init()
{

}
//�X�V����
void EXPManager::Update()
{
	for (shared_ptr<EXP> exp : expes)
	{
		if (exp)
		{
			//�X�V����
			exp->Update();
		}

	}

	//�j������
//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<EXP> exp : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<EXP>>::iterator it = std::find(expes.begin(), expes.end(), exp);
		if (it != expes.end())
		{
			expes.erase(it);
		}
	}
	remove.clear();
}
//�`�揈��
void EXPManager::Render()
{
	for (shared_ptr<EXP> exp : expes)
	{
		if (exp)
		{
			exp->Render();

			//Imgui
			//exp->ImguiDebug();
		}
	}
}
//�S�폜
void EXPManager::Clear()
{
	for (int i = 0; i < GetexpesSize(); i++)
	{
		EXP* exp = GetexpesIndex(i);
	}

	expes.clear();
	remove.clear();
}

//�o�^
void EXPManager::Register(const shared_ptr<EXP> &exp, const VECTOR3 &pos)
{
	exp->Init(pos);
	exp->SetManager(scene);
	expes.emplace_back(exp);
}

//�j������
void EXPManager::Destroy(const EXP* m_exp)
{
	for (shared_ptr<EXP> exp : expes)
	{
		std::vector<shared_ptr<EXP>>::iterator it = std::find(expes.begin(), expes.end(), exp);
		if (it->get() == m_exp)
		{
			shared_ptr<EXP> e = exp;
			remove.emplace_back(e);
		}
	}
}