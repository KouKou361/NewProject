//#include "UIManager.h"
////����������
//void UIManager::Init()
//{
//	Clear();
//}
////�X�V����
//void UIManager::Update()
//{
//	for (int i = 0; i < GetUIsSize(); i++)
//	{
//		UIBase* ui = GetUIsIndex(i);
//		if (ui->GetUpdateFlg())
//		{
//			ui->Update();	ui->Update();
//		}
//	
//	}
//	//�j������
////�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
//	for (shared_ptr<UIBase> ui : remove)
//	{
//		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
//		std::vector<shared_ptr<UIBase>>::iterator it = std::find(UIs.begin(), UIs.end(), ui);
//		if (it != UIs.end())
//		{
//			UIs.erase(it);
//		}
//	}
//	remove.clear();
//}
////���f���`�揈��
//void UIManager::Render()
//{
//	for (int i = 0;i < GetUIsSize(); i++)
//	{
//		UIBase* ui=GetUIsIndex(i);
//		if (ui->GetRenderFlg())
//		{
//			ui->Render();
//		}
//
//	}
//}
////�S�폜
//void UIManager::Clear()
//{
//	UIs.clear();
//	remove.clear();
//}
////�o�^
//void UIManager::Register(shared_ptr<UIBase> ui)
//{
//	UIs.push_back(ui);
//}
////�j������
//void UIManager::Destroy(UIBase* deleteUi)
//{
//	for (shared_ptr<UIBase> ui : UIs)
//	{
//		std::vector<shared_ptr<UIBase>>::iterator it = std::find(UIs.begin(), UIs.end(), ui);
//		if (it->get() == deleteUi)
//		{
//			shared_ptr<UIBase> destroyUi = ui;
//			remove.emplace_back(destroyUi);
//		}
//	}
//}