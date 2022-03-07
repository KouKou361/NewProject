#pragma once
#include "EnemyBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;
class SceneGame;

class EnemyManager :public Manager
{
public:
	EnemyManager() {};
	EnemyManager(SceneGame* scene) { this->scene = scene; };
	~EnemyManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//���f���`�揈��
	void ModelRender();
	//�S�폜
	void Clear();

	//�G�̍s�������邩�ǂ���
	void SetEnemyActive(bool flg);

	//�G�̖ڕW�I�u�W�F�N�g
	void SetTarget(Charactor* Target){ this->Target = Target; }
	//�o�^
	void Register(shared_ptr<EnemyBase> enm);
	//�j������
	void Destroy(EnemyBase* enm);
	//�����蔻��f�o�b�O
	void CollisionDebug();
	//�G�̐��̎擾
	int GetEnemiesSize() { return enemies.size(); }
	//�G�̐��̎擾
	EnemyBase* GetEnemiesIndex(const int &index) { return enemies.at(index).get(); }
	bool CollisionEnemy(const VECTOR3 pos, const float weight, const float collisionRadius, VECTOR3& OutPos, EnemyBase*& OutEnm);

	//�G�����ꂽ���A�ڕW�ɂ��Ă����L�����N�^�[�̖ڕW�̃��Z�b�g
	void ResetTheTargetCharacter(EnemyBase* enm);

	EnemyBase* SearchEnemyTag(const EnemyTag tag);

private:

	vector<shared_ptr<EnemyBase>>enemies;
	vector<shared_ptr<EnemyBase>>remove;
	Charactor* Target;
	SceneGame* scene;

};
