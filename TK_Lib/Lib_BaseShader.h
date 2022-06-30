#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <memory>
#include <vector>
#include "Lib_ShaderResource.h"
#include "Lib_ModelResource.h"
#include "Lib_Texture.h"
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;
//MEMO:

class BaseShader
{
protected:
	unique_ptr<ShaderResource> m_shader;
	//�`�悷�郂�f���f�[�^
	vector<ModelResource*> modelList;
	//�}�X�N����
	unique_ptr<TextureResource> maskTexture;
	
public:
	BaseShader() {};
	~BaseShader() {};
	//���f���f�[�^�o�^
	void ModelRegister(ModelResource* model) { modelList.push_back(model); }
	//�ۑ����Ă��郂�f���̑S�폜
	void ModelClear() { modelList.clear(); }
	const vector<ModelResource*>& Getlist() const { return modelList; }

	virtual void Begin(ID3D11DeviceContext* context, const DirectX::XMFLOAT4X4& view,
	const DirectX::XMFLOAT4X4& projection, const DirectX::XMFLOAT4& lightDirection) = 0;
	virtual void Render(ID3D11DeviceContext* context,const ModelResource* model) = 0;
	virtual void End(ID3D11DeviceContext* context)=0;
};
