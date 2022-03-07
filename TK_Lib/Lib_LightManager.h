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
	//初期化(保存する数)
	void Init(int MaxNum);
	//ポイントライトの作成
	int  Create(VECTOR3 pos, VECTOR4 color, float range);
	//ポイントライトの設定
	void Set(int handle, VECTOR3 pos, VECTOR4 color,float range);
	//ハンドルのポイントライトの削除
	void Delete(int& handle);
	//全消し
	void Clear();

};

