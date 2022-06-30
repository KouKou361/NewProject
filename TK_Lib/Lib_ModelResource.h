#pragma once
#include <string>
#include <vector>
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>
#include "Lib_ShaderResource.h"
#include "Vector.h"


using namespace Microsoft::WRL;
class TextureResource;
//using namespace DirectX;
class RayOut
{
public:
	VECTOR3 Pos;
	VECTOR3 Normal;
	VECTOR3 PolygonPos[3];//�|���S���̈ʒu
	float distance = 0.0f;//���C�̎��_�����_�܂ŋ���
	int materialIndex = -1;//�Փ˂����|���S���̃}�e���A���ԍ�
};
enum class ShadowType
{
	makeShadow,
	Drawshadow,
	NONE,
};

class ModelResource
{
private:
	ShadowType shadowType = ShadowType::NONE;
public:
	inline ShadowType GetType() { return shadowType; };
	inline void SetType(ShadowType type) { shadowType = type; };

	//�R���X�g���N�^
	ModelResource() {};
	//
	virtual ~ModelResource() {}

	using NodeId = UINT64;

	//�n���h��
	int handle = -1;
	//�t�@�C����
	std::string filename;
	////���f���̕���
	////�Ⴆ�΃��f���̎�Ȃ�name��hand���ē���
	////mdl�̃G�f�B�^�[��������킩��
	//struct Node
	//{
	////	NodeId				id;
	//	std::string			name;//�����̖��O
	//	std::string			path;//�����̃p�X
	//	int					parentIndex;//
	//	DirectX::XMFLOAT3	scale;//�����̑傫��
	//	DirectX::XMFLOAT4	rotate;//�����̊p�x
	//	DirectX::XMFLOAT3	translate;//�����̈ʒu
	//
	//	//�����Œl������
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//
	////MEMO:�����肢���Ƃ�����class Texture�ɓ����邩���H
	////�e�N�X�`���̃f�[�^
	//struct Material
	//{
	////	std::string			name;//�e�N�X�`���̖��O
	//	std::string			textureFilename;//�e�N�X�`���̃p�X
	//	DirectX::XMFLOAT4	color = { 0.8f, 0.8f, 0.8f, 1.0f };//�e�N�X�`���̐F
	//
	//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	//
	//	//�����Œl������
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//
	////�e�T�u�Z�b�g�̏��
	//struct Subset
	//{
	//	UINT		startIndex = 0;//�����n�߂̃C���f�b�N�X�ԍ�
	//	UINT		indexCount = 0;//�C���f�b�N�X��
	//	int			materialIndex = 0;//�}�e���A���̔ԍ�
	//
	//	//�e�N�X�`�����
	//	Material* material = nullptr;
	//
	//	//�����Œl������
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	////MEMO:�����VERTEX�Ɠ����Ȃ̂�
	////�K���ł��邩�������
	//struct Vertex
	//{
	//	DirectX::XMFLOAT3	position = { 0, 0, 0 };
	//	DirectX::XMFLOAT3	normal = { 0, 0, 0 };
	//	//DirectX::XMFLOAT3	tangent = { 0, 0, 0 };
	//	DirectX::XMFLOAT2	texcoord = { 0, 0 };
	////	DirectX::XMFLOAT4	color = { 1, 1, 1, 1 };
	//	DirectX::XMFLOAT4	boneWeight = { 1, 0, 0, 0 };
	//	DirectX::XMUINT4	boneIndex = { 0, 0, 0, 0 };
	//
	//	//�����Œl������
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//struct Mesh
	//{
	//	std::vector<Vertex>						vertices;
	//	std::vector<UINT>						indices;
	//	std::vector<Subset>						subsets;
	//
	//	int										nodeIndex;
	//	std::vector<int>						nodeIndices;
	//	std::vector<DirectX::XMFLOAT4X4>		offsetTransforms;
	//
	////	DirectX::XMFLOAT3						boundsMin;
	////	DirectX::XMFLOAT3						boundsMax;
	//
	//	Microsoft::WRL::ComPtr<ID3D11Buffer>	vertexBuffer;
	//	Microsoft::WRL::ComPtr<ID3D11Buffer>	indexBuffer;
	//
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//struct NodeKeyData
	//{
	//	DirectX::XMFLOAT3	scale;
	//	DirectX::XMFLOAT4	rotate;
	//	DirectX::XMFLOAT3	translate;
	//
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//struct Keyframe
	//{
	//	float						seconds;
	//	std::vector<NodeKeyData>	nodeKeys;
	//
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//struct Animation
	//{
	//	std::string					name;
	//	float						secondsLength;
	//	std::vector<Keyframe>		keyframes;
	//
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};


//�m�[�h�@���
struct Node
{
	NodeId				id=0;
	std::string			name="";
	std::string			path="";
	int					parentIndex=0;
	DirectX::XMFLOAT3	scale = {0,0,0};
	DirectX::XMFLOAT4	rotate = { 0,0,0,0 };
	DirectX::XMFLOAT3	translate = { 0,0,0 };
	//template Archive����Œ��ɓK���������̂�����΂悢
	template<class Archive>
	void serialize(Archive& archive, int version);
};


struct NodeTest
{
	const char* name="";
	NodeTest* parent=nullptr;
	DirectX::XMFLOAT3	scale = {0,0,0};
	DirectX::XMFLOAT4	rotate = {0,0,0,0};
	DirectX::XMFLOAT3	translate = { 0,0,0 };
	DirectX::XMFLOAT4X4	localTransform= {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
	DirectX::XMFLOAT4X4	worldTransform= {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

	std::vector<NodeTest*>	children;
};

//�e�N�X�`�����
struct Material
{
	std::string			name;
	std::string			textureFilename;
	DirectX::XMFLOAT4	color = { 0.8f, 0.8f, 0.8f, 1.0f };

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;

	template<class Archive>
	void serialize(Archive& archive, int version);
};

//�ǉ��e�N�X�`��
struct AddTexture
{
	int SetNum = 0;//�Z�b�g����ԍ�
	TextureResource* textureResource=nullptr;
};

//�C���f�b�N�X���
struct Subset
{
	UINT		startIndex = 0;
	UINT		indexCount = 0;
	int			materialIndex = 0;

	Material* material = nullptr;

	template<class Archive>
	void serialize(Archive& archive, int version);
};

struct Vertex
{
	DirectX::XMFLOAT3	position = { 0,0,0 };
	DirectX::XMFLOAT3	normal = { 0,0,0 };
	DirectX::XMFLOAT3	tangent = { 0, 0, 0 };
	DirectX::XMFLOAT2	texcoord = {0,0};
	DirectX::XMFLOAT4	color = { 1, 1, 1, 1 };
	DirectX::XMFLOAT4	boneWeight = { 0,0,0,0 };
	DirectX::XMUINT4	boneIndex = {0,0,0,0};

	template<class Archive>
	void serialize(Archive& archive, int version);
};

struct Mesh
{
	std::vector<Vertex>						vertices;
	std::vector<UINT>						indices;
	std::vector<Subset>						subsets;

	int										nodeIndex=0;
	std::vector<int>						nodeIndices;
	std::vector<DirectX::XMFLOAT4X4>		offsetTransforms;

	DirectX::XMFLOAT3						boundsMin = { 0,0,0 };
	DirectX::XMFLOAT3						boundsMax = { 0,0,0 };

	Microsoft::WRL::ComPtr<ID3D11Buffer>	vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	indexBuffer;

	template<class Archive>
	void serialize(Archive& archive, int version);
};

struct NodeKeyData
{
	DirectX::XMFLOAT3	scale = { 0,0,0 };
	DirectX::XMFLOAT4	rotate = { 0,0,0,0 };
	DirectX::XMFLOAT3	translate = { 0,0,0 };

	template<class Archive>
	void serialize(Archive& archive, int version);
};

struct Keyframe
{
	float						seconds=0;
	std::vector<NodeKeyData>	nodeKeys;

	template<class Archive>
	void serialize(Archive& archive, int version);
};
struct Animation
{
	std::string					name;
	float						secondsLength=0;
	std::vector<Keyframe>		keyframes;

	template<class Archive>
	void serialize(Archive& archive, int version);
};


	// �e��f�[�^�擾
	inline const std::vector<Mesh>& GetMeshes() const { return meshes; }
	inline const std::vector<Node>& GetNodes() const { return nodes; }
	inline const std::vector<Animation>& GetAnimations() const { return animations; }
	inline const std::vector<NodeTest>& GetNodetest() const { return TestresNode; }
	inline const std::vector<AddTexture>& GetAddTextures() const { return addTextures; }

	

	static const int MaxBones = 128;

	struct CbScene
	{
		DirectX::XMFLOAT4X4	VP;
		DirectX::XMFLOAT4	lightDirection;
	};



	struct Constant2
	{
		DirectX::XMFLOAT4X4 LightVP;
		DirectX::XMFLOAT4 ShadowColor;
		DirectX::XMFLOAT4 EyePos;
		DirectX::XMFLOAT4 LightColor;
	};

	struct CbMesh
	{
		DirectX::XMFLOAT4X4	boneTransforms[MaxBones];
	};

//	struct CbSubset
//	{
//		DirectX::XMFLOAT4	materialColor;
//	};
//

public:
	bool Load(ID3D11Device* device, const char* filename = nullptr);
	void Copy(ModelResource* model);

	void SetTexture(TextureResource* texture, const int setNum);
	//void SetConstant(ID3D11DeviceContext* device,  DirectX::XMFLOAT4X4 WVP, DirectX::XMFLOAT4 lightDir);
	//void SetConstant2(
	//	ID3D11DeviceContext* device,
	//	DirectX::XMFLOAT4X4 LightViewProjection,
	//	DirectX::XMFLOAT4 ShadowColor,
	//	DirectX::XMFLOAT4  EyePos,
	//	DirectX::XMFLOAT4 LightColor
	//);
	// ���f���Z�b�g�A�b�v
	void BuildModel(ID3D11Device* device, const char* dirname);
	//�`��
	//void Render(ID3D11DeviceContext* device);

	// �s��v�Z
	void CalculateLocalTransform();
	void CalculateWorldTransform(const DirectX::XMMATRIX& WorldTransform);
	//�A�j���[�V���������ǂ���
	bool IsPlayAnimetion();
	//�A�j���[�V�����̍Đ�
	void PlayAnimation(int animationIndex, bool loop, float blendSconds = 0.2f);
	//�A�j���[�V�����̍X�V����
	void UpdateAnimation(float elapsedTime);
	//�m�[�h��������
	NodeTest* FindNode(const char* name);
	//�A�j���[�V�����^�C���̎擾
	float GetEndAnimetionTime();

	float GetAnimetionTime();
	void RayPick(const XMFLOAT3& start,const XMFLOAT3& end, RayOut& ray);
	//���a�̃��C�s�b�N
	void RadiusRayPick(const XMFLOAT3& start, const XMFLOAT3& end, RayOut& ray, const float radius);

	void UpdateMaskVolume();
	void MaskStart(const float maskSpeed) { this->maskSpeed = maskSpeed; };
	inline const float GetMaskVolume() const { return this->maskVolume; };
private:
	std::vector<Node>		nodes;
	std::vector<Material>	materials;
	std::vector<Mesh>		meshes;
	std::vector<Animation>	animations;
	std::vector<AddTexture>	addTextures;
	//�A�j���[�V�����p��Node (�������̂܂ܒ��_����������͔̂����Ă���Ǝv��)
	std::vector<NodeTest>	TestresNode;

	int								currentAnimation = -1;
	float							currentSeconds = 0.0f;
	bool							loopAnimation = false;
	bool							endAnimation = false;

	//�⊮�p
	float animetionBlendTime = 0.0f;
	float animetionBlendSeconds = 0.0f;

	float maskVolume = 0.0f;
	float maskSpeed = 0.0f;
};
