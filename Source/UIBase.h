#pragma once
#include "Lib.h"
class UIManager;
class Charactor;
class SceneGame;

//UI�̊�{�I����
class UIBase
{
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
	void SetValue(float value) { this->value = value; };
	void SetValue2(float value) { this->value = value2; };
	VECTOR2 WorldToScreen(VECTOR3 Pos);

	void SetTexture(int indexTexture) { this->indexTexture = indexTexture; };
	void SetCharactor(Charactor* chara) { this->chara = chara; }

	virtual void SetText(string text) { this->text = text; };
	string GetText() { return this->text; };

	

protected:
	UIManager* manager = nullptr;//UI�Ǘ��N���X
	Charactor* chara = nullptr;//�L�����N�^�[
	int indexTexture;
	float value = 0;//�ėp�I�Ȑ���
	float value2 = 0;//�ėp�I�Ȑ���

	string text;//�e�L�X�g
	SceneGame* scene = nullptr;


	VECTOR2 pos = { 0,0 };
	VECTOR2 size = { 0,0 };
	VECTOR4 cut = { 0,0,0,0 };
	float angle;
	VECTOR4 color = { 1,1,1,1 };
private:





	UIBase* parent = nullptr;//�e
	vector<UIBase*> children;//�q��


};
