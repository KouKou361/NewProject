#pragma once
#include "Lib_PointLight.h"
#include <wrl.h>
#include <memory>
#include <vector>

class Lib_PointLightManager
{
	ComPtr<ID3D11Buffer> m_Constantbuffer;
	static Lib_PointLightManager* instance;

public:
	Lib_PointLightManager(ID3D11Device *device);
	~Lib_PointLightManager() {};
private:
	vector<Lib_PointLight> pointLight;
	Lib_PointLight* GetPointlight(int handle);
public:
	static Lib_PointLightManager& Instance()
	{
		return *instance;
	}
	void Active(ID3D11DeviceContext* context);
	//������(�ۑ����鐔)
	void Init(int MaxNum);
	//�|�C���g���C�g�̍쐬
	int  Create(VECTOR3 pos, VECTOR4 color, float range);
	//�|�C���g���C�g�̐ݒ�
	void Set(int handle, VECTOR3 pos, VECTOR4 color,float range);
	//�n���h���̃|�C���g���C�g�̍폜
	void Delete(int& handle);
	//�S����
	void Clear();

};

