#include <stdlib.h>
#include <fstream>
#include <functional>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <WICTextureLoader.h>

#include "Lib_misc.h"
//#include "Logger.h"
#include "Lib_ModelResource.h"
#include "Lib_Blender.h"
#include "lib.h"
#include "Lib_Sampler.h"

// CEREALバージョン定義
CEREAL_CLASS_VERSION(ModelResource::Node, 1)
CEREAL_CLASS_VERSION(ModelResource::Material, 1)
CEREAL_CLASS_VERSION(ModelResource::Subset, 1)
CEREAL_CLASS_VERSION(ModelResource::Vertex, 1)
CEREAL_CLASS_VERSION(ModelResource::Mesh, 1)
CEREAL_CLASS_VERSION(ModelResource::NodeKeyData, 1)
CEREAL_CLASS_VERSION(ModelResource::Keyframe, 1)
CEREAL_CLASS_VERSION(ModelResource::Animation, 1)
CEREAL_CLASS_VERSION(ModelResource, 1)



// シリアライズ
namespace DirectX
{
	template<class Archive>
	void serialize(Archive& archive, XMUINT4& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y),
			cereal::make_nvp("z", v.z),
			cereal::make_nvp("w", v.w)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, XMFLOAT2& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, XMFLOAT3& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y),
			cereal::make_nvp("z", v.z)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, XMFLOAT4& v)
	{
		archive(
			cereal::make_nvp("x", v.x),
			cereal::make_nvp("y", v.y),
			cereal::make_nvp("z", v.z),
			cereal::make_nvp("w", v.w)
		);
	}

	template<class Archive>
	void serialize(Archive& archive, XMFLOAT4X4& m)
	{
		archive(
			cereal::make_nvp("_11", m._11), cereal::make_nvp("_12", m._12), cereal::make_nvp("_13", m._13), cereal::make_nvp("_14", m._14),
			cereal::make_nvp("_21", m._21), cereal::make_nvp("_22", m._22), cereal::make_nvp("_23", m._23), cereal::make_nvp("_24", m._24),
			cereal::make_nvp("_31", m._31), cereal::make_nvp("_32", m._32), cereal::make_nvp("_33", m._33), cereal::make_nvp("_34", m._34),
			cereal::make_nvp("_41", m._41), cereal::make_nvp("_42", m._42), cereal::make_nvp("_43", m._43), cereal::make_nvp("_44", m._44)
		);
	}
}

template<class Archive>
void ModelResource::Node::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(id),
		CEREAL_NVP(name),
		CEREAL_NVP(path),
		CEREAL_NVP(parentIndex),
		CEREAL_NVP(scale),
		CEREAL_NVP(rotate),
		CEREAL_NVP(translate)
	);
}

template<class Archive>
void ModelResource::Material::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(name),
		CEREAL_NVP(textureFilename),
		CEREAL_NVP(color)
	);
}

template<class Archive>
void ModelResource::Subset::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(startIndex),
		CEREAL_NVP(indexCount),
		CEREAL_NVP(materialIndex)
	);
}

template<class Archive>
void ModelResource::Vertex::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(position),
		CEREAL_NVP(normal),
		CEREAL_NVP(tangent),
		CEREAL_NVP(texcoord),
		CEREAL_NVP(color),
		CEREAL_NVP(boneWeight),
		CEREAL_NVP(boneIndex)
	);
}

template<class Archive>
void ModelResource::Mesh::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(vertices),
		CEREAL_NVP(indices),
		CEREAL_NVP(subsets),
		CEREAL_NVP(nodeIndex),
		CEREAL_NVP(nodeIndices),
		CEREAL_NVP(offsetTransforms),
		CEREAL_NVP(boundsMin),
		CEREAL_NVP(boundsMax)
	);
}

template<class Archive>
void ModelResource::NodeKeyData::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(scale),
		CEREAL_NVP(rotate),
		CEREAL_NVP(translate)
	);
}

template<class Archive>
void ModelResource::Keyframe::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(seconds),
		CEREAL_NVP(nodeKeys)
	);
}

template<class Archive>
void ModelResource::Animation::serialize(Archive& archive, int version)
{
	archive(
		CEREAL_NVP(name),
		CEREAL_NVP(secondsLength),
		CEREAL_NVP(keyframes)
	);
}

void ModelResource::Copy(ModelResource* model)
{
	*this = *model;
	// ノード
	const std::vector<ModelResource::Node>& resNodes = model->GetNodes();

	TestresNode.resize(resNodes.size());
	for (size_t nodeIndex = 0; nodeIndex < TestresNode.size(); ++nodeIndex)
	{
		auto&& src = resNodes.at(nodeIndex);
		auto&& dst = TestresNode.at(nodeIndex);

		dst.name = src.name.c_str();
		dst.parent = src.parentIndex >= 0 ? &TestresNode.at(src.parentIndex) : nullptr;
		dst.scale = src.scale;
		dst.rotate = src.rotate;
		dst.translate = src.translate;

		if (dst.parent != nullptr)
		{
			dst.parent->children.emplace_back(&dst);
		}
	}
}
bool ModelResource::Load(ID3D11Device* device, const char* filename)
{
	// ディレクトリパス取得
	char drive[32], dir[256], dirname[256];
	::_splitpath_s(filename, drive, sizeof(drive), dir, sizeof(dir), nullptr, 0, nullptr, 0);
	::_makepath_s(dirname, sizeof(dirname), drive, dir, nullptr, nullptr);

	// デシリアライズ
	std::ifstream istream(filename, std::ios::binary);
	if (istream.is_open())
	{
		cereal::BinaryInputArchive archive(istream);

		try
		{
			//作成！
			archive(
				CEREAL_NVP(nodes),
				CEREAL_NVP(materials),
				CEREAL_NVP(meshes),
				CEREAL_NVP(animations)
			);
		}
		catch (...)
		{
			//デシリアライズが無い！

							//エラー
			MessageBox(*TK_Lib::GetHWND(),L"モデルが生成出来ません", L"", 0);
			return false;
		}

	}
	//モデルの作成
	BuildModel(device, dirname);

	// ノード
	const std::vector<ModelResource::Node>& resNodes = GetNodes();

	TestresNode.resize(resNodes.size());
	for (size_t nodeIndex = 0; nodeIndex < TestresNode.size(); ++nodeIndex)
	{
		auto&& src = resNodes.at(nodeIndex);
		auto&& dst = TestresNode.at(nodeIndex);

		dst.name = src.name.c_str();
		dst.parent = src.parentIndex >= 0 ? &TestresNode.at(src.parentIndex) : nullptr;
		dst.scale = src.scale;
		dst.rotate = src.rotate;
		dst.translate = src.translate;

		if (dst.parent != nullptr)
		{
			dst.parent->children.emplace_back(&dst);
		}
	}
	return true;
}

// ローカル変換行列計算
void ModelResource::CalculateLocalTransform()
{
	for (NodeTest& node : TestresNode)
	{
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&node.rotate));
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(node.translate.x, node.translate.y, node.translate.z);

		DirectX::XMStoreFloat4x4(&node.localTransform, S * R * T);
	}
}


// ワールド変換行列計算
void ModelResource::CalculateWorldTransform(const DirectX::XMMATRIX& WorldTransform)
{
	for (NodeTest& node : TestresNode)
	{
		DirectX::XMMATRIX LocalTransform = DirectX::XMLoadFloat4x4(&node.localTransform);
		if (node.parent != nullptr)
		{
			DirectX::XMMATRIX ParentTransform = DirectX::XMLoadFloat4x4(&node.parent->worldTransform);
			DirectX::XMStoreFloat4x4(&node.worldTransform, LocalTransform * ParentTransform);
		}
		else
		{
			DirectX::XMStoreFloat4x4(&node.worldTransform, LocalTransform * WorldTransform);
		}
	}
	
}
//アニメーション中かどうか
bool ModelResource::IsPlayAnimetion()
{

	if (currentAnimation < 0)return false;
	if (currentAnimation >= GetAnimations().size())return false;
	return true;
}
//アニメーションの再生
void ModelResource::PlayAnimation(int animationIndex, bool loop, float blendSconds)
{
	currentAnimation = animationIndex;
	loopAnimation = loop;
	endAnimation = false;
	currentSeconds = 0.0f;
}

//最終アニメーションタイムの取得
float ModelResource::GetEndAnimetionTime()
{
	const ModelResource::Animation& animation = GetAnimations().at(currentAnimation);
	return animation.secondsLength;
}
//アニメーションタイムの取得
float ModelResource::GetAnimetionTime()
{
	return currentSeconds;
}
//テクスチャの追加
void ModelResource::SetTexture(TextureResource* texture, const int setNum)
{
	AddTexture addtexture;
	addtexture.SetNum = setNum;
	addtexture.textureResource = texture;
	addTextures.push_back(addtexture);
}

void ModelResource::UpdateMaskVolume()
{
	if (maskSpeed == 0)return;
	if (maskVolume >= 1)
	{
		maskVolume = 1;
		maskSpeed = 0;
		return;
	}
	const float Volume = TK_Lib::Window::GetElapsedTime()*maskSpeed;
	maskVolume += Volume;
}

ModelResource::NodeTest* ModelResource::FindNode(const char* name)
{

	
	int nodeCount = static_cast<int>(TestresNode.size());
	for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
	{
		NodeTest& node = TestresNode.at(nodeIndex);
		if (strcmp(node.name, name) == 0) {
			return &node;
		}
	}
	return nullptr;
}

//アニメーションの更新処理
void ModelResource::UpdateAnimation(float elapsedTime)
{
	//アニメーションがないなら
	if (currentAnimation < 0)
	{
		return;
	}

	if (GetAnimations().empty())
	{
		return;
	}

	const ModelResource::Animation& animation = GetAnimations().at(currentAnimation);

	const std::vector<ModelResource::Keyframe>& keyframes = animation.keyframes;
	int keyCount = static_cast<int>(keyframes.size());
	for (int keyIndex = 0; keyIndex < keyCount - 1; ++keyIndex)
	{
		// 現在の時間がどのキーフレームの間にいるか判定する
		const ModelResource::Keyframe& keyframe0 = keyframes.at(keyIndex);
		const u_int NextKeyIndex = keyIndex + 1;
		const ModelResource::Keyframe& keyframe1 = keyframes.at(NextKeyIndex);
		if (currentSeconds >= keyframe0.seconds && currentSeconds < keyframe1.seconds)
		{
			float rate = (currentSeconds - keyframe0.seconds / keyframe1.seconds - keyframe0.seconds);

			assert(TestresNode.size() == keyframe0.nodeKeys.size());
			assert(TestresNode.size() == keyframe1.nodeKeys.size());
			int nodeCount = static_cast<int>(TestresNode.size());
			for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
			{
				// ２つのキーフレーム間の補完計算
				const ModelResource::NodeKeyData& key0 = keyframe0.nodeKeys.at(nodeIndex);
				const ModelResource::NodeKeyData& key1 = keyframe1.nodeKeys.at(nodeIndex);

				NodeTest& node = TestresNode[nodeIndex];

				DirectX::XMVECTOR S0 = DirectX::XMLoadFloat3(&key0.scale);
				DirectX::XMVECTOR S1 = DirectX::XMLoadFloat3(&key1.scale);
				DirectX::XMVECTOR R0 = DirectX::XMLoadFloat4(&key0.rotate);
				DirectX::XMVECTOR R1 = DirectX::XMLoadFloat4(&key1.rotate);
				DirectX::XMVECTOR T0 = DirectX::XMLoadFloat3(&key0.translate);
				DirectX::XMVECTOR T1 = DirectX::XMLoadFloat3(&key1.translate);

				DirectX::XMVECTOR S = DirectX::XMVectorLerp(S0, S1, rate);
				DirectX::XMVECTOR R = DirectX::XMQuaternionSlerp(R0, R1, rate);
				DirectX::XMVECTOR T = DirectX::XMVectorLerp(T0, T1, rate);

				DirectX::XMStoreFloat3(&node.scale, S);
				DirectX::XMStoreFloat4(&node.rotate, R);
				DirectX::XMStoreFloat3(&node.translate, T);
			}
			break;
		}
	}

	// 最終フレーム処理
	if (endAnimation)
	{
		endAnimation = false;
		currentAnimation = -1;
		return;
	}

	// 時間経過
	currentSeconds += elapsedTime;
	if (currentSeconds >= animation.secondsLength)
	{
		if (loopAnimation)
		{
			currentSeconds -= animation.secondsLength;
		}
		else
		{
			currentSeconds = animation.secondsLength;
			endAnimation = true;
		}
	}
}

//=======================
//モデルの作成
//=======================
void ModelResource::BuildModel(ID3D11Device* device, const char* dirname)
{
	HRESULT hr = S_OK;

	//マテリアルの算出
	for (Material& material : materials)
	{
		// 相対パスの解決
		char filename[256];
		::_makepath_s(filename, 256, nullptr, dirname, material.textureFilename.c_str(), nullptr);

		// マルチバイト文字からワイド文字へ変換
		wchar_t wfilename[256];
		::MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, 256);


		//テクスチャの読み込み
		Microsoft::WRL::ComPtr<ID3D11Resource> resource;

		hr = DirectX::CreateWICTextureFromFile(device, wfilename, resource.GetAddressOf(), material.shaderResourceView.GetAddressOf());

		// 読み込み失敗したらダミーテクスチャを作る
		if (hr!=S_OK)
		{
			const int width = 8;
			const int height = 8;
			UINT pixels[width * height];
			::memset(pixels, 0xFF, sizeof(pixels));

			D3D11_TEXTURE2D_DESC desc = { 0 };
			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			D3D11_SUBRESOURCE_DATA data;
			::memset(&data, 0, sizeof(data));
			data.pSysMem = pixels;
			data.SysMemPitch = width;

			Microsoft::WRL::ComPtr<ID3D11Texture2D>	texture;
			hr = device->CreateTexture2D(&desc, &data, texture.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), L"テクスチャの読み込みのエラー");

			hr = device->CreateShaderResourceView(texture.Get(), nullptr, material.shaderResourceView.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), L"ShaderResourceViewのエラー");
		}
	}
	//Meshの作成
	for (Mesh &mesh:meshes)
	{
		
		//サブセットにあったマテリアル番号
		for (Subset& subset : mesh.subsets)
		{
			subset.material = &materials.at(subset.materialIndex);
		}

		//頂点バッファ
		{
			D3D11_BUFFER_DESC bufferdesc;
			ZeroMemory(&bufferdesc, sizeof(bufferdesc));
			bufferdesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * mesh.vertices.size());
			//bufferdesc.Usage = D3D11_USAGE_DEFAULT;
			bufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
			bufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferdesc.CPUAccessFlags = 0;
			bufferdesc.MiscFlags = false;
			bufferdesc.StructureByteStride = false;

			D3D11_SUBRESOURCE_DATA subresource;
			ZeroMemory(&subresource, sizeof(D3D11_SUBRESOURCE_DATA));
			subresource.pSysMem = mesh.vertices.data();
			subresource.SysMemPitch = false;
			subresource.SysMemSlicePitch = false;
			//頂点バッファの作成
			hr = device->CreateBuffer(&bufferdesc, &subresource, mesh.vertexBuffer.GetAddressOf());
			if (FAILED(hr))
			{
				_ASSERT_EXPR(SUCCEEDED(hr), L"頂点バッファのエラー");
				return;
			}
		}
		//インデックバッファ
		{
			D3D11_BUFFER_DESC bufferDesc = {};
			D3D11_SUBRESOURCE_DATA subresourceData = {};
			::ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
			::ZeroMemory(&subresourceData, sizeof(D3D11_SUBRESOURCE_DATA));

			bufferDesc.ByteWidth = static_cast<UINT>((sizeof(UINT) * mesh.indices.size()));
	//		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bufferDesc.CPUAccessFlags = 0;
			bufferDesc.MiscFlags = 0;
			bufferDesc.StructureByteStride = 0;
			subresourceData.pSysMem = mesh.indices.data();
			subresourceData.SysMemPitch = 0; //Not use for index buffers.
			subresourceData.SysMemSlicePitch = 0; //Not use for index buffers.
			hr = device->CreateBuffer(&bufferDesc, &subresourceData, mesh.indexBuffer.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), L"インデックバッファのエラー");
		}
	}
};

void  ModelResource::RayPick(const XMFLOAT3& start,const XMFLOAT3& end, RayOut& ray)
{
	XMVECTOR WorldStart = XMLoadFloat3(&start);
	XMVECTOR WorldEnd = XMLoadFloat3(&end);
	XMVECTOR WorldRayVec = XMVectorSubtract(WorldEnd, WorldStart);
	XMVECTOR WorldRayLength = XMVector3Length(WorldRayVec);
	//ワールド座標のレイの長さ
	XMStoreFloat(&ray.distance, WorldRayLength);

	bool hit = false;
	for (const ModelResource::Mesh& mesh : GetMeshes())
	{
		//メッシュノード取得
		const NodeTest& node = TestresNode.at(mesh.nodeIndex);

		//レイをワールド空間かわローカル空間に変換する
		XMMATRIX WorldTranceform = XMLoadFloat4x4(&node.worldTransform);
		XMMATRIX InverseWorldTranceform = XMMatrixInverse(nullptr, WorldTranceform);
		//ローカル空間
		XMVECTOR Start = XMVector3TransformCoord(WorldStart, InverseWorldTranceform);
		XMVECTOR End = XMVector3TransformCoord(WorldEnd, InverseWorldTranceform);
		XMVECTOR Vec = XMVectorSubtract(End, Start);
		XMVECTOR Dir = XMVector3Normalize(Vec);
		XMVECTOR Length = XMVector3Length(Vec);
		//レイの長さ
		float neart;
		XMStoreFloat(&neart, Length);

		//三角形（面）との当たり判定
		const std::vector<ModelResource::Vertex>& vetices = mesh.vertices;
		const std::vector<UINT> indices = mesh.indices;

		int materialIndex = -1;
		XMVECTOR HitPosition;
		XMVECTOR HitNormalize;
		XMVECTOR PolygonPostion[3];

		for (const ModelResource::Subset& subset : mesh.subsets)
		{
			for (UINT i = 0; i < subset.indexCount; i += 3)
			{

				const UINT Index = subset.startIndex + i;
				const UINT NextIndex = Index + 1;
				const UINT Next2Index = NextIndex + 1;
				//三角形の頂点情報を算出する
				const ModelResource::Vertex& a = vetices.at(indices.at(Index));
				const ModelResource::Vertex& b = vetices.at(indices.at(NextIndex));
				const ModelResource::Vertex& c = vetices.at(indices.at(Next2Index));



				XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
				XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
				XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

				//三角形の三辺ベクトルを算出
				XMVECTOR AB = XMVectorSubtract(B, A);
				XMVECTOR BC = XMVectorSubtract(C, B);
				XMVECTOR CA = XMVectorSubtract(A, C);
				//三角形の法線ベクトルの算出
				XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(AB, BC));
				//XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(BC,AB));
				//内積の値がプラスなら裏向き
				XMVECTOR Dot = XMVector3Dot(Dir, Normal);
				float dot;
				XMStoreFloat(&dot, Dot);
				if (dot >= 0)continue;//裏向き

				//レイと平面の交差点
				XMVECTOR d1 = XMVector3Dot(XMVectorSubtract(A, Start), Normal);
				//XMVECTOR d2 = XMVector3Dot(Normal, Dir);
				XMVECTOR T = XMVectorDivide(d1, Dot);
				float t;
				XMStoreFloat(&t, T);
				//交点までの距離が今までに計算した最近距離よりも大きいときはスキップ
				if (t<0.0f || t>neart)continue;
				XMVECTOR Position = XMVectorMultiply(Dir, T);
				Position = XMVectorAdd(Position, Start);
				XMFLOAT3 pos;
				XMStoreFloat3(&pos, Position);

				//交点が三角形の内側にあるか判定
				//1
				{
					XMVECTOR V1 = XMVectorSubtract(Position, A);
					XMVECTOR Cross = XMVector3Cross(AB, V1);
				//	XMVECTOR Cross = XMVector3Cross(V1,AB);
					XMVECTOR Dot1 = XMVector3Dot(Cross, Normal);
					float dot1;
					XMStoreFloat(&dot1, Dot1);
					if (dot1 < 0)continue;
				}

				//2
				{
					XMVECTOR V2 = XMVectorSubtract(Position, B);
					XMVECTOR Cross2 = XMVector3Cross(BC, V2);
					//XMVECTOR Cross2 = XMVector3Cross(V2, BC);
					XMVECTOR Dot2 = XMVector3Dot(Cross2, Normal);
					float dot2;
					XMStoreFloat(&dot2, Dot2);
					if (dot2 < 0)continue;

				}


				//3
				{
					XMVECTOR V3 = XMVectorSubtract(Position, C);
					XMVECTOR Cross3 = XMVector3Cross(CA, V3);
					//XMVECTOR Cross3 = XMVector3Cross(V3,CA );
					XMVECTOR Dot3 = XMVector3Dot(Cross3, Normal);
					float dot3;
					XMStoreFloat(&dot3, Dot3);
					if (dot3 < 0)continue;

				}

				//最短距離を更新する
				neart = t;
				//交点と法線を更新
				HitPosition = Position;
				HitNormalize = Normal;
				materialIndex = subset.materialIndex;
				PolygonPostion[0] = A;
				PolygonPostion[1] = B;
				PolygonPostion[2] = C;
			}

		}



		if (materialIndex >= 0)
		{
			//ローカル空間からワールド空間に変換する
			XMVECTOR WorldPosition = XMVector3TransformCoord(HitPosition, WorldTranceform);
			XMVECTOR WorldCrossVec = XMVectorSubtract(WorldPosition, WorldStart);
			XMVECTOR WorldCrossLength = XMVector3Length(WorldCrossVec);
			float distance;
			XMStoreFloat(&distance, WorldCrossLength);

			//保存
			if (ray.distance > distance)
			{
				XMVECTOR WorldNormal = XMVector3TransformNormal(HitNormalize, WorldTranceform);

				XMVECTOR WorldPolygonPostion[3];
				WorldPolygonPostion[0] = XMVector3TransformCoord(PolygonPostion[0], WorldTranceform);
				WorldPolygonPostion[1] = XMVector3TransformCoord(PolygonPostion[1], WorldTranceform);
				WorldPolygonPostion[2] = XMVector3TransformCoord(PolygonPostion[2], WorldTranceform);

				ray.distance = distance;
				ray.materialIndex = materialIndex;
				XMStoreFloat3(&ray.Pos, WorldPosition);
				XMStoreFloat3(&ray.Normal, XMVector3Normalize(WorldNormal));

				XMStoreFloat3(&ray.PolygonPos[0], WorldPolygonPostion[0]);
				XMStoreFloat3(&ray.PolygonPos[1], WorldPolygonPostion[1]);
				XMStoreFloat3(&ray.PolygonPos[2], WorldPolygonPostion[2]);
				hit = true;
			}
		}
	}

}

void  ModelResource::RadiusRayPick(const XMFLOAT3& start, const XMFLOAT3& end, RayOut& ray,float radius)
{
	XMVECTOR WorldStart = XMLoadFloat3(&start);
	XMVECTOR WorldEnd = XMLoadFloat3(&end);
	XMVECTOR WorldRayVec = XMVectorSubtract(WorldEnd, WorldStart);
	XMVECTOR WorldRayLength = XMVector3Length(WorldRayVec);
	//ワールド座標のレイの長さ
	XMStoreFloat(&ray.distance, WorldRayLength);

	bool hit = false;
	for (const ModelResource::Mesh& mesh : GetMeshes())
	{
		//メッシュノード取得
		const NodeTest& node = TestresNode.at(mesh.nodeIndex);

		//scaleを変換する
		float scale;
		//{
		//	//仮置きベクトル
		//	XMVECTOR N = XMVectorSet(1, 1, 1, 1);
		//	N = XMVector3Normalize(N);//念のため正規化
		//	N = XMVectorScale(N, radius);
		//
		//	// ワールド行列の更新
		//	XMMATRIX S = XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
		//	XMMATRIX R = XMMatrixRotationRollPitchYaw(0, 0, 0);
		//	XMMATRIX T = XMMatrixTranslation(0, 0, 0);
		//
		//	XMMATRIX W = S * R * T;
		//
		//	XMVECTOR Vec = XMVector3TransformCoord(N, XMMatrixInverse(nullptr,S));
		//	XMStoreFloat(&scale ,Vec);
		//}
		//

			
			//仮置きベクトル
		{
			XMVECTOR N = XMVectorSet(1, 1, 1, 1);
			N = XMVector3Normalize(N);//念のため正規化
		
		
			// ワールド行列の更新
			XMMATRIX S = XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
			XMMATRIX R = XMMatrixRotationRollPitchYaw(0, 0, 0);
			XMMATRIX T = XMMatrixTranslation(0, 0, 0);
		
			XMMATRIX W = S * R * T;
		
			XMVECTOR Vec = XMVector3TransformCoord(N, XMMatrixInverse(nullptr,W));
			XMVECTOR Divide = XMVectorDivide(Vec, N);//割り算して比率をだす
			XMStoreFloat(&scale, Divide);
			scale *= radius;
			int a = 0;
		}
		
		//	XMStoreFloat(&scale ,Vec);
		




		//レイをワールド空間かわローカル空間に変換する
		XMMATRIX WorldTranceform = XMLoadFloat4x4(&node.worldTransform);
		XMMATRIX InverseWorldTranceform = XMMatrixInverse(nullptr, WorldTranceform);
		//ローカル空間
		XMVECTOR Start = XMVector3TransformCoord(WorldStart, InverseWorldTranceform);
		XMVECTOR End = XMVector3TransformCoord(WorldEnd, InverseWorldTranceform);
		XMVECTOR Vec = XMVectorSubtract(End, Start);
		XMVECTOR Dir = XMVector3Normalize(Vec);
		XMVECTOR Length = XMVector3Length(Vec);
		//レイの長さ
		float neart;
		XMStoreFloat(&neart, Length);

		//三角形（面）との当たり判定
		const std::vector<ModelResource::Vertex>& vetices = mesh.vertices;
		const std::vector<UINT> indices = mesh.indices;

		int materialIndex = -1;
		XMVECTOR HitPosition;
		XMVECTOR HitNormalize;
		XMVECTOR PolygonPostion[3];

		for (const ModelResource::Subset& subset : mesh.subsets)
		{
			for (UINT i = 0; i < subset.indexCount; i += 3)
			{
				const UINT Index = subset.startIndex + i;
				const UINT NextIndex = Index + 1;
				const UINT Next2Index = NextIndex + 1;
				//三角形の頂点情報を算出する
				const ModelResource::Vertex& a = vetices.at(indices.at(Index));
				const ModelResource::Vertex& b = vetices.at(indices.at(NextIndex));
				const ModelResource::Vertex& c = vetices.at(indices.at(Next2Index));



				XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
				XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
				XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

				//三角形の三辺ベクトルを算出
				XMVECTOR AB = XMVectorSubtract(B, A);
				XMVECTOR BC = XMVectorSubtract(C, B);
				XMVECTOR CA = XMVectorSubtract(A, C);
				//三角形の法線ベクトルの算出
				XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(AB, BC));

				//ここで半径を考慮したレイピック
				

					XMVECTOR RadiusStart = XMVectorAdd(Start, XMVectorScale(XMVectorNegate(Normal), scale));
					XMVECTOR RadiusEnd = XMVectorAdd(End, XMVectorScale(XMVectorNegate(Normal) , scale));
					XMVECTOR RadiusVec = Vec;
					XMVECTOR RadiusDir = Dir;

				

					//RadiusStart = Start;
					//RadiusEnd   = End;
					//RadiusVec   = Vec;
					//RadiusDir   = Dir;

				//XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(BC,AB));
				//内積の値がプラスなら裏向き
				XMVECTOR Dot = XMVector3Dot(RadiusDir, Normal);
				float dot;
				XMStoreFloat(&dot, Dot);
				if (dot >= 0)continue;//裏向き

				//レイと平面の交差点
				XMVECTOR d1 = XMVector3Dot(XMVectorSubtract(A, RadiusStart), Normal);
				//XMVECTOR d2 = XMVector3Dot(Normal, Dir);
				XMVECTOR T = XMVectorDivide(d1, Dot);
				float t;
				XMStoreFloat(&t, T);
				//交点までの距離が今までに計算した最近距離よりも大きいときはスキップ
				if (t<0.0f || t>neart)continue;
				XMVECTOR Position = XMVectorMultiply(RadiusDir, T);
				Position = XMVectorAdd(Position, RadiusStart);
				XMFLOAT3 pos;
				XMStoreFloat3(&pos, Position);

				//交点が三角形の内側にあるか判定
				//1
				{
					XMVECTOR V1 = XMVectorSubtract(Position, A);
					XMVECTOR Cross = XMVector3Cross(AB, V1);
					//	XMVECTOR Cross = XMVector3Cross(V1,AB);
					XMVECTOR Dot1 = XMVector3Dot(Cross, Normal);
					float dot1;
					XMStoreFloat(&dot1, Dot1);
					if (dot1 < 0)continue;
				}

				//2
				{
					XMVECTOR V2 = XMVectorSubtract(Position, B);
					XMVECTOR Cross2 = XMVector3Cross(BC, V2);
					//XMVECTOR Cross2 = XMVector3Cross(V2, BC);
					XMVECTOR Dot2 = XMVector3Dot(Cross2, Normal);
					float dot2;
					XMStoreFloat(&dot2, Dot2);
					if (dot2 < 0)continue;

				}


				//3
				{
					XMVECTOR V3 = XMVectorSubtract(Position, C);
					XMVECTOR Cross3 = XMVector3Cross(CA, V3);
					//XMVECTOR Cross3 = XMVector3Cross(V3,CA );
					XMVECTOR Dot3 = XMVector3Dot(Cross3, Normal);
					float dot3;
					XMStoreFloat(&dot3, Dot3);
					if (dot3 < 0)continue;

				}

				//最短距離を更新する
				neart = t;
				//交点と法線を更新
				HitPosition = Position;
				HitNormalize = Normal;
				materialIndex = subset.materialIndex;
				PolygonPostion[0] = A;
				PolygonPostion[1] = B;
				PolygonPostion[2] = C;
			}

		}



		if (materialIndex >= 0)
		{
			//ローカル空間からワールド空間に変換する
			XMVECTOR WorldPosition = XMVector3TransformCoord(HitPosition, WorldTranceform);
			XMVECTOR WorldCrossVec = XMVectorSubtract(WorldPosition, WorldStart);
			XMVECTOR WorldCrossLength = XMVector3Length(WorldCrossVec);
			float distance;
			XMStoreFloat(&distance, WorldCrossLength);

			//保存
			if (ray.distance > distance)
			{
				XMVECTOR WorldNormal = XMVector3TransformNormal(HitNormalize, WorldTranceform);

				XMVECTOR WorldPolygonPostion[3];
				WorldPolygonPostion[0] = XMVector3TransformCoord(PolygonPostion[0], WorldTranceform);
				WorldPolygonPostion[1] = XMVector3TransformCoord(PolygonPostion[1], WorldTranceform);
				WorldPolygonPostion[2] = XMVector3TransformCoord(PolygonPostion[2], WorldTranceform);

				ray.distance = distance;
				ray.materialIndex = materialIndex;
				XMStoreFloat3(&ray.Normal, XMVector3Normalize(WorldNormal));

				XMStoreFloat3(&ray.Pos, WorldPosition);
				ray.Pos += (ray.Normal * radius);

				XMStoreFloat3(&ray.PolygonPos[0], WorldPolygonPostion[0]);
				XMStoreFloat3(&ray.PolygonPos[1], WorldPolygonPostion[1]);
				XMStoreFloat3(&ray.PolygonPos[2], WorldPolygonPostion[2]);
				hit = true;
			}
		}
	}

}

////コンスタントバッファに設定
//void ModelResource::SetConstant(ID3D11DeviceContext* device, DirectX::XMFLOAT4X4 VP, DirectX::XMFLOAT4 lightDir)
//{
//	CbScene cbscene;
//	cbscene.lightDirection = lightDir;
//	cbscene.VP=VP;
//
//	device->UpdateSubresource(m_constantBuffer.Get(), 0, 0, &cbscene, 0, 0);
//}
////コンスタントバッファ2設定
//void ModelResource::SetConstant2(
//	ID3D11DeviceContext* device, 
//	DirectX::XMFLOAT4X4 LightViewProjection,
//	DirectX::XMFLOAT4 ShadowColor,
//	DirectX::XMFLOAT4  EyePos,
//    DirectX::XMFLOAT4 LightColor
//	)
//{
//	Constant2 constant;
//	constant.EyePos = EyePos;
//	constant.LightColor = LightColor;
//	constant.LightVP = LightViewProjection;
//	constant.ShadowColor = ShadowColor;
//
//	device->UpdateSubresource(m_constantBuffer2.Get(), 0, 0, &constant, 0, 0);
//}
//
////描画
//void ModelResource::Render(ID3D11DeviceContext* device)
//{
//	test_shader->Activate(device);
//
//	//ここで定数バッファを送り込んでいる
//	ID3D11Buffer* constantBuffers[] =
//	{
//		m_constantBuffer.Get(),
//		m_meshConstantBuffer.Get(),
//		m_subsetConstantBuffer.Get(),
//	//	m_constantBuffer2.Get()
//	};
//	device->VSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);
//	device->PSSetConstantBuffers(0, ARRAYSIZE(constantBuffers), constantBuffers);
//
//	const float blend_factor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	device->OMSetBlendState(blendState.Get(), blend_factor, 0xFFFFFFFF);
//	device->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
//	device->RSSetState(m_fillRasterizerState.Get());
//	device->PSSetSamplers(0, 1, Sampler::Instance().m_samplerState[Sampler::Sampler_WRAP].GetAddressOf());
//	//device->PSSetSamplers(1, 1, m_samplerState[1].GetAddressOf());
//	for (const Mesh& mesh : meshes)
//	{
//
//		// メッシュ用定数バッファ更新
//		CbMesh cbMesh;
//		::memset(&cbMesh, 0, sizeof(cbMesh));
//		if (mesh.nodeIndices.size() > 0)
//		{
//			for (size_t i = 0; i < mesh.nodeIndices.size(); ++i)
//			{
//				DirectX::XMMATRIX worldTransform = DirectX::XMLoadFloat4x4(&TestresNode.at(mesh.nodeIndices.at(i)).worldTransform);
//				DirectX::XMMATRIX offsetTransform = DirectX::XMLoadFloat4x4(&mesh.offsetTransforms.at(i));
//				DirectX::XMMATRIX boneTransform = offsetTransform*worldTransform;
//				DirectX::XMStoreFloat4x4(&cbMesh.boneTransforms[i], boneTransform);
//			}
//		}
//		else
//		{
//			cbMesh.boneTransforms[0] = TestresNode.at(mesh.nodeIndex).worldTransform;
//			//DirectX::XMStoreFloat4x4(&cbMesh.boneTransforms[0], DirectX::XMMatrixIdentity());
//			//cbMesh.boneTransforms[0] = DirectX::XMMatrixInverse();
//		}
//		device->UpdateSubresource(m_meshConstantBuffer.Get(), 0, 0, &cbMesh, 0, 0);
//	
//		UINT stride = sizeof(ModelResource::Vertex);
//		UINT offset = 0;
//		device->IASetVertexBuffers(0, 1, mesh.vertexBuffer.GetAddressOf(), &stride, &offset);
//		device->IASetIndexBuffer(mesh.indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
//		device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//
//
//
//		//メッシュに会ったマテリアルの設定
//		for (const ModelResource::Subset& subset : mesh.subsets)
//		{
//			CbSubset cbSubset;
//			cbSubset.materialColor = subset.material->color;
//			device->UpdateSubresource(m_subsetConstantBuffer.Get(), 0, 0, &cbSubset, 0, 0);
//
//			device->PSSetShaderResources(0, 1, subset.material->shaderResourceView.GetAddressOf());
//		//	device->PSSetSamplers(0, 1, m_samplerState[0].GetAddressOf());
//
//			device->DrawIndexed(subset.indexCount, subset.startIndex, 0);
//		}
//	}
//	test_shader->Inactivate(device);
//}