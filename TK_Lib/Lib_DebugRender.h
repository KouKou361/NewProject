#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <memory>
#include <vector>

#include "Lib_ShaderResource.h"
#include "Lib_DirectXFunctions.h"
#include "vector.h"

using namespace std;
using namespace Microsoft::WRL;

//�v���~�e�B�u�̃f�[�^
struct PrimitiveData
{
	
	enum PrimitiveType
	{
		BOX,   //�l�p
		CIRCLE,//�~
		LINE,  //��
		END,
	};

	//���W(�l�p,�~,���Ɏg��)
	VECTOR3 pos = {0,0,0};
	//�I�_���W2(�l�p,���Ɏg��)
	VECTOR3 pos2 = { 0,0,0 };
	//�p�x
	float angle=0.0f;
	//���a(�~�Ɏg��)
	float radius = 0.0f;
	//�v���~�e�B�u�^�C�v(�^�C�v)
	PrimitiveType type= BOX;
	//���ߍ��݃t���O
	bool fill = false;
	//�F
	VECTOR4 color = VECTOR4{0,0,0,0};

};
//�萔�o�b�t�@
struct ConstantBuffer
{
	XMFLOAT4X4 worldViewProjection;
};

//�f�o�b�O�p�̃X�v���C�g
class Primitive_DebugRender
{
public:
	//1:device,2:���_�̍ő吔
	Primitive_DebugRender() {};
	Primitive_DebugRender(ID3D11Device* device, u_int MaxVertex);

	~Primitive_DebugRender() {};

	//���_�̍ő吔��ݒ�
	void SetMaxVertex(u_int MaxVertex);
	//�S�Ẵf�[�^���폜����
	void Clear();
protected:

	ComPtr <ID3D11Buffer>            m_vertexBuffer;//���_�o�b�t�@
	ComPtr <ID3D11Buffer>            m_indexBuffer;//�C���f�b�N�o�b�t�@
	ComPtr <ID3D11Buffer>            m_constantBuffer;//�C���f�b�N�o�b�t�@
	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//�f�v�X�X�e���V��

	//Debug��p��shader
	std::shared_ptr<ShaderResource> m_shader;

protected:
	//���_���̍ő吔
	static const int Primitive_vertex_num = 200;

	const int Circle_Num = 64;
	//���_���̔z��
	vector<VERTEXDEBUG> vertices;
	//�`�悵�������̔z��
	vector<PrimitiveData*> primitiveDatas;
public:

	//���_�o�b�t�@�ɒ��_����ݒ肷��(1:device,2:�R�s�[������vertex�z��̗v�f0�Ԗ�,3:����ւ��������_���̐�)
	void SetVertex(ID3D11DeviceContext* device, VERTEXDEBUG*vertex,u_int vertexSize);

	//�l�p�̕`���o�^����
	void DrawBox(VECTOR3 Pos, VECTOR3 Size, float angle = 0, VECTOR4 Color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg=true);
	//�~�̕`���o�^����
	void DrawCircle(VECTOR3 pos, float radius, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);
	//���̕`���o�^����
	void DrawLine(VECTOR3 pos, VECTOR3 pos2, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);

	//�o�^���Ă���`��f�[�^���܂Ƃ߂ĕ`�悷��
	void AllDebugDraw(ID3D11DeviceContext* device);

private:
	//�`��n��
	virtual void Begin(ID3D11DeviceContext* device);
	//�`��I��
	virtual void End(ID3D11DeviceContext* device);
	//�l�p�̕`��
	virtual void ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data)=0;
	//�~�̕`��
	virtual void ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data) = 0;
	//���̕`��
	virtual void ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data) = 0;
};


//2D
class Primitive2D_DebugRender :public Primitive_DebugRender
{
public:
	Primitive2D_DebugRender(ID3D11Device* device, u_int MaxVertex);
	~Primitive2D_DebugRender() {};

	//�l�p�̕`��
	void ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data);
	//�~�̕`��
	void ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data);
	//���̕`��
	void ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data);
private:

};
//3D
class Primitive3D_DebugRender :public Primitive_DebugRender
{
public:
	Primitive3D_DebugRender(ID3D11Device* device, u_int MaxVertex);
	~Primitive3D_DebugRender() {};
private:
	//===============
	//�~�֌W
	//===============
	u_int circle_stacks;//�c��
	u_int circle_slice;//����
	u_int circle_Indices_num;//�~��`�悷�鎞�̃C���f�b�N�X��

	ComPtr <ID3D11Buffer>            m_CircleIndexBuffer;//�~��p�̃C���f�b�N�o�b�t�@
	
	//�l�p�̃C���f�b�N�X�̍쐬
	void CreateIndexBox(ID3D11Device* device);

	//���̃C���f�b�N�̍쐬
	void CreateIndexCircle(ID3D11Device* device, int slice, int stacks);

	//���̃C���f�b�N�̍쐬
	//������낱��
	//void CreateIndexCircle();
public:


	void SetConstantBuffer(ID3D11DeviceContext* device, const ConstantBuffer &constant);
	//�l�p�̕`��
	void ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data);
	//���̕`��
	void ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data);
	//���̕`��
	void ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data);

private:
};