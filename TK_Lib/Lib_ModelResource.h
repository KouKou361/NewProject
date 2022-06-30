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
	VECTOR3 PolygonPos[3];//ポリゴンの位置
	float distance = 0.0f;//レイの視点から交点まで距離
	int materialIndex = -1;//衝突したポリゴンのマテリアル番号
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

	//コンストラクタ
	ModelResource() {};
	//
	virtual ~ModelResource() {}

	using NodeId = UINT64;

	//ハンドル
	int handle = -1;
	//ファイル名
	std::string filename;
	////モデルの部分
	////例えばモデルの手ならnameにhandって入る
	////mdlのエディターを見たらわかる
	//struct Node
	//{
	////	NodeId				id;
	//	std::string			name;//部分の名前
	//	std::string			path;//部分のパス
	//	int					parentIndex;//
	//	DirectX::XMFLOAT3	scale;//部分の大きさ
	//	DirectX::XMFLOAT4	rotate;//部分の角度
	//	DirectX::XMFLOAT3	translate;//部分の位置
	//
	//	//ここで値を入れる
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//
	////MEMO:これ上手いことしたらclass Textureに入れれるかも？
	////テクスチャのデータ
	//struct Material
	//{
	////	std::string			name;//テクスチャの名前
	//	std::string			textureFilename;//テクスチャのパス
	//	DirectX::XMFLOAT4	color = { 0.8f, 0.8f, 0.8f, 1.0f };//テクスチャの色
	//
	//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	//
	//	//ここで値を入れる
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	//
	////各サブセットの情報
	//struct Subset
	//{
	//	UINT		startIndex = 0;//書き始めのインデックス番号
	//	UINT		indexCount = 0;//インデックス数
	//	int			materialIndex = 0;//マテリアルの番号
	//
	//	//テクスチャ情報
	//	Material* material = nullptr;
	//
	//	//ここで値を入れる
	//	template<class Archive>
	//	void serialize(Archive& archive, int version);
	//};
	//
	////MEMO:これもVERTEXと同じなので
	////適応できるかもしれん
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
	//	//ここで値を入れる
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


//ノード　情報
struct Node
{
	NodeId				id=0;
	std::string			name="";
	std::string			path="";
	int					parentIndex=0;
	DirectX::XMFLOAT3	scale = {0,0,0};
	DirectX::XMFLOAT4	rotate = { 0,0,0,0 };
	DirectX::XMFLOAT3	translate = { 0,0,0 };
	//template Archiveこれで中に適応したものを入れればよい
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

//テクスチャ情報
struct Material
{
	std::string			name;
	std::string			textureFilename;
	DirectX::XMFLOAT4	color = { 0.8f, 0.8f, 0.8f, 1.0f };

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;

	template<class Archive>
	void serialize(Archive& archive, int version);
};

//追加テクスチャ
struct AddTexture
{
	int SetNum = 0;//セットする番号
	TextureResource* textureResource=nullptr;
};

//インデックス情報
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


	// 各種データ取得
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
	// モデルセットアップ
	void BuildModel(ID3D11Device* device, const char* dirname);
	//描画
	//void Render(ID3D11DeviceContext* device);

	// 行列計算
	void CalculateLocalTransform();
	void CalculateWorldTransform(const DirectX::XMMATRIX& WorldTransform);
	//アニメーション中かどうか
	bool IsPlayAnimetion();
	//アニメーションの再生
	void PlayAnimation(int animationIndex, bool loop, float blendSconds = 0.2f);
	//アニメーションの更新処理
	void UpdateAnimation(float elapsedTime);
	//ノード検索する
	NodeTest* FindNode(const char* name);
	//アニメーションタイムの取得
	float GetEndAnimetionTime();

	float GetAnimetionTime();
	void RayPick(const XMFLOAT3& start,const XMFLOAT3& end, RayOut& ray);
	//半径のレイピック
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
	//アニメーション用のNode (多分そのまま頂点をいじくるのは避けていると思う)
	std::vector<NodeTest>	TestresNode;

	int								currentAnimation = -1;
	float							currentSeconds = 0.0f;
	bool							loopAnimation = false;
	bool							endAnimation = false;

	//補完用
	float animetionBlendTime = 0.0f;
	float animetionBlendSeconds = 0.0f;

	float maskVolume = 0.0f;
	float maskSpeed = 0.0f;
};
