#pragma once
#include "UIBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;
//
//class UIManager :public Manager
//{
//public:
//	UIManager() {};
//	UIManager(SceneGame* scene) { this->scene = scene; };
//	~UIManager() {};
//
//	//‰Šú‰»ˆ—
//	void Init();
//	//XVˆ—
//	void Update();
//	//•`‰æˆ—
//	void Render();
//	//ƒ‚ƒfƒ‹•`‰æˆ—
//	void ModelRender() {};
//	//‘Síœ
//	void Clear();
//	//“o˜^
//	void Register(shared_ptr<UIBase> ui);
//	//”jŠüˆ—
//	void Destroy(UIBase* ui);
//	//UI‚Ì”‚Ìæ“¾
//	int GetUIsSize() { return UIs.size(); }
//	//UI‚Ì”‚Ìæ“¾
//	UIBase* GetUIsIndex(const int& index) { return UIs.at(index).get(); }
//
//private:
//
//	vector<shared_ptr<UIBase>>UIs;
//	vector<shared_ptr<UIBase>>remove;
//	SceneGame* scene;
//
//};
