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
	VECTOR3 pos;//座標
	VECTOR3 angle;//回転
	VECTOR3 scale;//大きさ
	VECTOR4 color;//色
	bool select;//選択フラグ

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

	void Loading(const std::string filename);
	//オブジェクトの配置
	void ObjectSet();
	//敵の配置する
	void SetEnemy(ExportActor *exportActor);
	//オブジェクト配置
	void SetObject(ExportActor *exportActor);
	//ステージの配置
	void SetStage (ExportActor *exportActor);
	//ポイントライトの配置
	void SetPointLight(ExportActor* exportActor);
	//エフェクトの設定
	void SetEffeect(ExportActor* exportActor);
	//関数の設定
	void SetFunction(ExportActor* exportActor);

	inline void SetManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };


};