//#include "UIManager.h"
////初期化処理
//void UIManager::Init()
//{
//	Clear();
//}
////更新処理
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
//	//破棄処理
////更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
//	for (shared_ptr<UIBase> ui : remove)
//	{
//		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
//		std::vector<shared_ptr<UIBase>>::iterator it = std::find(UIs.begin(), UIs.end(), ui);
//		if (it != UIs.end())
//		{
//			UIs.erase(it);
//		}
//	}
//	remove.clear();
//}
////モデル描画処理
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
////全削除
//void UIManager::Clear()
//{
//	UIs.clear();
//	remove.clear();
//}
////登録
//void UIManager::Register(shared_ptr<UIBase> ui)
//{
//	UIs.push_back(ui);
//}
////破棄処理
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