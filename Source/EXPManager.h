#pragma once
#include "Manager.h"
#include "Lib.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;
class EXP;

class EXPManager 
{
public:
	EXPManager() {};
	EXPManager(SceneGame* scene) { this->scene = scene; };
	~EXPManager() {};

	//‰Šú‰»ˆ—
	void Init();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render();
	//‘Síœ
	void Clear();

	//“o˜^
	void Register(const shared_ptr<EXP>& exp, const VECTOR3& pos);
	//”jŠüˆ—
	void Destroy(const EXP* exp);
	//EXP‚Ì”‚Ìæ“¾
	int GetexpesSize() { return static_cast<int>(expes.size()); }
	//EXP‚Ì”‚Ìæ“¾
	EXP* GetexpesIndex(const int& index) { return expes.at(index).get(); }

private:

	vector<shared_ptr<EXP>>expes;
	vector<shared_ptr<EXP>>remove;

	SceneGame* scene=nullptr;

};
