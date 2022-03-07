#include "Lib_Light.h"

LightController::LightController()
{
	shadowCamera = make_unique<CameraLib>();
}
void LightController::SetLookAt(const VECTOR3& pos, const VECTOR3& forward, const VECTOR3& up)
{
	shadowCamera->SetLookAt(pos, forward, up);
}

void LightController::SetOrthongraphic(float Width, float Height, float Near, float Far)
{
	shadowCamera->SetOrthongraphic(Width, Height, Near, Far);
}


