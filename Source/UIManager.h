//#pragma once
//#include "UIBase.h"
//#include "Manager.h"
//#include <vector>
//#include <memory>
//using namespace std;
//class SceneGame;
//
//class UIManager :public Manager
//{
//public:
//	UIManager() {};
//	UIManager(SceneGame* scene) { this->scene = scene; };
//	~UIManager() {};
//
//	//初期化処理
//	void Init();
//	//更新処理
//	void Update();
//	//描画処理
//	void Render();
//	//モデル描画処理
//	void ModelRender() {};
//	//全削除
//	void Clear();
//	//登録
//	void Register(shared_ptr<UIBase> ui);
//	//破棄処理
//	void Destroy(UIBase* ui);
//	//UIの数の取得
//	int GetUIsSize() { return UIs.size(); }
//	//UIの数の取得
//	UIBase* GetUIsIndex(const int& index) { return UIs.at(index).get(); }
//
//private:
//
//	vector<shared_ptr<UIBase>>UIs;
//	vector<shared_ptr<UIBase>>remove;
//	SceneGame* scene;
//
//};
