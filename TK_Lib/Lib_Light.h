#pragma once
#include "Lib_CameraLib.h"
#include <memory>
using namespace std;
class LightController
{
private:
	unique_ptr<CameraLib> shadowCamera;
public:
	LightController();
	~LightController() {};

	void SetLookAt(const VECTOR3& pos,const VECTOR3& forward,const VECTOR3& up);

	// �p�[�X�y�N�e�B�u�ݒ�
	void SetOrthongraphic(float Width, float Height, float Near, float Far);

	CameraLib* GetCamera() { return shadowCamera.get(); }


	const DirectX::XMFLOAT4X4& GetView() const { return shadowCamera->GetView(); }

	const DirectX::XMFLOAT4X4& GetProjection() const { return shadowCamera->GetProjection(); }

	// ���_�擾
	const VECTOR3& GetPos() const { return shadowCamera->GetPos(); }

	// �����_�擾
	const VECTOR3& GetForward() const { return shadowCamera->GetTarget(); }

	// ������擾
	const VECTOR3& GetUp() const { return shadowCamera->GetUp(); }

	// �O�����擾
	const VECTOR3& GetFront() const { return shadowCamera->GetFront(); }

	// �E�����擾
	const VECTOR3& GetRight() const { return shadowCamera->GetRight(); }


};
