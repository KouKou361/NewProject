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

	// パースペクティブ設定
	void SetOrthongraphic(float Width, float Height, float Near, float Far);

	CameraLib* GetCamera() { return shadowCamera.get(); }


	const DirectX::XMFLOAT4X4& GetView() const { return shadowCamera->GetView(); }

	const DirectX::XMFLOAT4X4& GetProjection() const { return shadowCamera->GetProjection(); }

	// 視点取得
	const VECTOR3& GetPos() const { return shadowCamera->GetPos(); }

	// 注視点取得
	const VECTOR3& GetForward() const { return shadowCamera->GetTarget(); }

	// 上方向取得
	const VECTOR3& GetUp() const { return shadowCamera->GetUp(); }

	// 前方向取得
	const VECTOR3& GetFront() const { return shadowCamera->GetFront(); }

	// 右方向取得
	const VECTOR3& GetRight() const { return shadowCamera->GetRight(); }


};
