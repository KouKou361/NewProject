#pragma once
#include "Lib.h"
class UIManager;
class Charactor;
class SceneGame;

//UIの基本的処理
class UIBase
{
public:
	UIBase() {};
	UIBase(UIManager* manager, SceneGame* scene) { this->manager = manager; this->scene = scene; };
	~UIBase() {};
	//初期化
	virtual void Init() = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Render() = 0;
	//破棄処理
	void Destroy();

	//親設定
	void SetParent(UIBase* ui) { parent = ui; }
	//子供設定
	void SetChildren(UIBase* ui);
	//数字の設定
	void SetValue(float value) { this->value = value; };
	void SetValue2(float value) { this->value = value2; };
	VECTOR2 WorldToScreen(VECTOR3 Pos);

	void SetTexture(int indexTexture) { this->indexTexture = indexTexture; };
	void SetCharactor(Charactor* chara) { this->chara = chara; }

	virtual void SetText(string text) { this->text = text; };
	string GetText() { return this->text; };

	

protected:
	UIManager* manager = nullptr;//UI管理クラス
	Charactor* chara = nullptr;//キャラクター
	int indexTexture;
	float value = 0;//汎用的な数字
	float value2 = 0;//汎用的な数字

	string text;//テキスト
	SceneGame* scene = nullptr;


	VECTOR2 pos = { 0,0 };
	VECTOR2 size = { 0,0 };
	VECTOR4 cut = { 0,0,0,0 };
	float angle;
	VECTOR4 color = { 1,1,1,1 };
private:





	UIBase* parent = nullptr;//親
	vector<UIBase*> children;//子供


};
