#pragma once
#include "Lib.h"
class UIManager;
class Charactor;
class SceneGame;

//UIの基本的処理
class UIBase
{
protected:

	int indexTexture;
	float value = 0;//汎用的な数字
	float value2 = 0;//汎用的な数字
	float angle;

	VECTOR2 pos = { 0,0 };
	VECTOR2 size = { 0,0 };
	VECTOR4 cut = { 0,0,0,0 };
	VECTOR4 color = { 1,1,1,1 };

	string text;//テキスト
	SceneGame* scene = nullptr;
	UIManager* manager = nullptr;//UI管理クラス
	Charactor* chara = nullptr;//キャラクター
private:
	UIBase* parent = nullptr;//親
	vector<UIBase*> children;//子供

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
	inline void SetValue(const float value) { this->value = value; };
	inline void SetValue2(const float value) { this->value = value2; };
	VECTOR2 WorldToScreen(const VECTOR3 Pos);

	inline void SetTexture(const int indexTexture) { this->indexTexture = indexTexture; };
	inline void SetCharactor(Charactor* chara) { this->chara = chara; }

	virtual void SetText(const string text) { this->text = text; };
	inline string GetText() { return this->text; };

	



};
