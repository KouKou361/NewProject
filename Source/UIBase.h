#pragma once
#include "Lib.h"
class UIManager;
class Charactor;
class SceneGame;

//UI�̊�{�I����
class UIBase
{
protected:

	int indexTexture;
	float value = 0;//�ėp�I�Ȑ���
	float value2 = 0;//�ėp�I�Ȑ���
	float angle;

	VECTOR2 pos = { 0,0 };
	VECTOR2 size = { 0,0 };
	VECTOR4 cut = { 0,0,0,0 };
	VECTOR4 color = { 1,1,1,1 };

	string text;//�e�L�X�g
	SceneGame* scene = nullptr;
	UIManager* manager = nullptr;//UI�Ǘ��N���X
	Charactor* chara = nullptr;//�L�����N�^�[
private:
	UIBase* parent = nullptr;//�e
	vector<UIBase*> children;//�q��

public:
	UIBase() {};
	UIBase(UIManager* manager, SceneGame* scene) { this->manager = manager; this->scene = scene; };
	~UIBase() {};
	//������
	virtual void Init() = 0;
	//�X�V����
	virtual void Update() = 0;
	//�`�揈��
	virtual void Render() = 0;
	//�j������
	void Destroy();

	//�e�ݒ�
	void SetParent(UIBase* ui) { parent = ui; }
	//�q���ݒ�
	void SetChildren(UIBase* ui);
	//�����̐ݒ�
	inline void SetValue(const float value) { this->value = value; };
	inline void SetValue2(const float value) { this->value = value2; };
	VECTOR2 WorldToScreen(const VECTOR3 Pos);

	inline void SetTexture(const int indexTexture) { this->indexTexture = indexTexture; };
	inline void SetCharactor(Charactor* chara) { this->chara = chara; }

	virtual void SetText(const string text) { this->text = text; };
	inline string GetText() { return this->text; };

	



};
