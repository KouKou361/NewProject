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
	VECTOR3 Pos;//���W
	VECTOR3 Angle;//��]
	VECTOR3 Scale;//�傫��
	VECTOR4 Color;//�F
	bool Select;//�I���t���O

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
	//�G�̃Z�b�g����
	void SetEnemy(ExportActor *exportActor);
	//�I�u�W�F�N�g�z�u
	void SetObject(ExportActor *exportActor);
	//�X�e�[�W�̃Z�b�g
	void SetStage (ExportActor *exportActor);
	//�|�C���g���C�g�̃Z�b�g
	void SetPointLight(ExportActor* exportActor);
	//�G�t�F�N�g�̐ݒ�
	void SetEffeect(ExportActor* exportActor);
	//�֐��̐ݒ�
	void SetFunction(ExportActor* exportActor);

	inline void SetManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };


};