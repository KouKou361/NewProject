
#pragma once
//���N���X�̃}�l�[�W���[�N���X
class Manager
{
public:
	Manager() {};
	virtual ~Manager() {};

	//����������
	virtual void Init() = 0;
	//�X�V����
	virtual void Update() = 0;
	//�`�揈��
	virtual void Render() = 0;
	//���f���`�揈��
	virtual void ModelRender() = 0;
	//�S����
	virtual void Clear() = 0;
private:


};
