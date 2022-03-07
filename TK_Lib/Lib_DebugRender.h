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

//プリミティブのデータ
struct PrimitiveData
{
	
	enum PrimitiveType
	{
		BOX,   //四角
		CIRCLE,//円
		LINE,  //線
		END,
	};

	//座標(四角,円,線に使う)
	VECTOR3 pos = {0,0,0};
	//終点座標2(四角,線に使う)
	VECTOR3 pos2 = { 0,0,0 };
	//角度
	float angle=0.0f;
	//半径(円に使う)
	float radius = 0.0f;
	//プリミティブタイプ(タイプ)
	PrimitiveType type= BOX;
	//埋め込みフラグ
	bool fill = false;
	//色
	VECTOR4 color = VECTOR4{0,0,0,0};

};
//定数バッファ
struct ConstantBuffer
{
	XMFLOAT4X4 worldViewProjection;
};

//デバッグ用のスプライト
class Primitive_DebugRender
{
public:
	//1:device,2:頂点の最大数
	Primitive_DebugRender() {};
	Primitive_DebugRender(ID3D11Device* device, u_int MaxVertex);

	~Primitive_DebugRender() {};

	//頂点の最大数を設定
	void SetMaxVertex(u_int MaxVertex);
	//全てのデータを削除する
	void Clear();
protected:

	ComPtr <ID3D11Buffer>            m_vertexBuffer;//頂点バッファ
	ComPtr <ID3D11Buffer>            m_indexBuffer;//インデックバッファ
	ComPtr <ID3D11Buffer>            m_constantBuffer;//インデックバッファ
	ComPtr <ID3D11DepthStencilState> m_depthStencilState;//デプスステンシル

	//Debug専用のshader
	std::shared_ptr<ShaderResource> m_shader;

protected:
	//頂点数の最大数
	static const int Primitive_vertex_num = 200;

	const int Circle_Num = 64;
	//頂点情報の配列
	vector<VERTEXDEBUG> vertices;
	//描画したい情報の配列
	vector<PrimitiveData*> primitiveDatas;
public:

	//頂点バッファに頂点情報を設定する(1:device,2:コピーしたいvertex配列の要素0番目,3:入れ替えたい頂点情報の数)
	void SetVertex(ID3D11DeviceContext* device, VERTEXDEBUG*vertex,u_int vertexSize);

	//四角の描画を登録する
	void DrawBox(VECTOR3 Pos, VECTOR3 Size, float angle = 0, VECTOR4 Color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg=true);
	//円の描画を登録する
	void DrawCircle(VECTOR3 pos, float radius, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);
	//線の描画を登録する
	void DrawLine(VECTOR3 pos, VECTOR3 pos2, VECTOR4 color = VECTOR4{ 1,0,0,0.2f }, bool FillFlg = true);

	//登録している描画データをまとめて描画する
	void AllDebugDraw(ID3D11DeviceContext* device);

private:
	//描画始め
	virtual void Begin(ID3D11DeviceContext* device);
	//描画終了
	virtual void End(ID3D11DeviceContext* device);
	//四角の描画
	virtual void ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data)=0;
	//円の描画
	virtual void ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data) = 0;
	//線の描画
	virtual void ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data) = 0;
};


//2D
class Primitive2D_DebugRender :public Primitive_DebugRender
{
public:
	Primitive2D_DebugRender(ID3D11Device* device, u_int MaxVertex);
	~Primitive2D_DebugRender() {};

	//四角の描画
	void ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data);
	//円の描画
	void ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data);
	//線の描画
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
	//円関係
	//===============
	u_int circle_stacks;//縦列
	u_int circle_slice;//横列
	u_int circle_Indices_num;//円を描画する時のインデックス数

	ComPtr <ID3D11Buffer>            m_CircleIndexBuffer;//円専用のインデックバッファ
	
	//四角のインデックスの作成
	void CreateIndexBox(ID3D11Device* device);

	//球のインデックの作成
	void CreateIndexCircle(ID3D11Device* device, int slice, int stacks);

	//線のインデックの作成
	//いらんやろこれ
	//void CreateIndexCircle();
public:


	void SetConstantBuffer(ID3D11DeviceContext* device, const ConstantBuffer &constant);
	//四角の描画
	void ScreenDrawBox(ID3D11DeviceContext* device, const PrimitiveData& data);
	//球の描画
	void ScreenDrawCircle(ID3D11DeviceContext* device, const PrimitiveData& data);
	//線の描画
	void ScreenDrawLine(ID3D11DeviceContext* device, const PrimitiveData& data);

private:
};