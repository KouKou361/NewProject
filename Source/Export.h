#pragma once
#include "Lib.h"
#include <string>
class SceneGame;
class ExportActor
{
public:
	int handle;//ハンドル
	std::string filename;//ファイルパス
	std::string name;//名前
	std::string type;
	VECTOR3 Pos;//座標
	VECTOR3 Angle;//回転
	VECTOR3 Scale;//大きさ
	VECTOR4 Color;//色
	bool Select;//選択フラグ

public:
	template<class Archive>
	void serialize(Archive& archive, int version);
};
class Export
{

public:
	Export() {};
	~Export() {};
private:
	SceneGame* sceneGame=nullptr;
	std::vector<ExportActor> exportActorList;
public:

	void Loading(std::string filename);
	void ObjectSet();
	//敵のセットする
	void SetEnemy(ExportActor *exportActor);
	//オブジェクト配置
	void SetObject(ExportActor *exportActor);
	//ステージのセット
	void SetStage (ExportActor *exportActor);
	//ポイントライトのセット
	void SetPointLight(ExportActor* exportActor);
	//エフェクトの設定
	void SetEffeect(ExportActor* exportActor);
	//関数の設定
	void SetFunction(ExportActor* exportActor);

	inline void SetManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };


};