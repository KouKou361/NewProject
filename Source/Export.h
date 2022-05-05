#pragma once
#include "Lib.h"
#include <string>
class SceneGame;
class ExportActor
{
public:
	int handle;//�n���h��
	std::string filename;//�t�@�C���p�X
	std::string name;//���O
	std::string type;
	VECTOR3 pos;//���W
	VECTOR3 angle;//��]
	VECTOR3 scale;//�傫��
	VECTOR4 color;//�F
	bool select;//�I���t���O

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
	//�I�u�W�F�N�g�̔z�u
	void ObjectSet();
	//�G�̔z�u����
	void SetEnemy(ExportActor *exportActor);
	//�I�u�W�F�N�g�z�u
	void SetObject(ExportActor *exportActor);
	//�X�e�[�W�̔z�u
	void SetStage (ExportActor *exportActor);
	//�|�C���g���C�g�̔z�u
	void SetPointLight(ExportActor* exportActor);
	//�G�t�F�N�g�̐ݒ�
	void SetEffeect(ExportActor* exportActor);
	//�֐��̐ݒ�
	void SetFunction(ExportActor* exportActor);

	inline void SetManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };


};