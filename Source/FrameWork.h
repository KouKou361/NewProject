#pragma once
class FrameWork
{
private:
	static FrameWork* instance;
public:
	FrameWork();
	~FrameWork() {};
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//���f���p�̕`�揈��
	void ModelRender();
	//�I������
	void End();

	//�C���X�^���X�擾
	static FrameWork& Instance()
	{
		return *instance;
	}
};
