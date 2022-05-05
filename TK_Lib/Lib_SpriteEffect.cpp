#include "Lib_SpriteEffect.h"

#include "Lib_Rasterizer.h"
#include "Lib_DepthStencil.h"
#include "Lib_Blender.h"
#include "Lib.h"

void EffectData::Set(int type, float timer,
	DirectX::XMFLOAT3 p, DirectX::XMFLOAT3 v, DirectX::XMFLOAT3 f, DirectX::XMFLOAT2 size,VECTOR4 color)
{
	this->type = type;
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	this->vx = v.x;
	this->vy = v.y;
	this->vz = v.z;
	this->ax = f.x;
	this->ay = f.y;
	this->az = f.z;
	this->w = size.x;
	this->h = size.y;
	this->alpha = 1.0f;
	this->timer = timer;
	this->color = color;

}
bool EffectData::IsCameraRender()
{

	VECTOR3 P = { x ,y ,z };
	if (!TK_Lib::Camera::IsCamera(P))
	{
		renderflg = false;
		return false;
	}
	renderflg = true;
	return true;
}
SpriteEffect::SpriteEffect(ID3D11Device* device,int Num, std::string name)
{

}
void SpriteEffect::Create(ID3D11Device* device, int Num, std::string name, VECTOR2 TextureChipSize, VECTOR2 TextureNum)
{
	SetNum(Num);


	Texture = make_unique<TextureResource>();
	Texture->Load(device, name);

	for (int i = 0; i < spriteEffects.size(); i++)
	{
		spriteEffects.at(i).type = -1;
	}
	//頂点バッファ作成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	//頂点数分のバッファ
	bd.ByteWidth =static_cast< UINT>(sizeof(VERTEXParticle) * vertices.size());
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = device->CreateBuffer(&bd, NULL, m_vertexBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	// 定数バッファ生成
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(ConstantBufferForPerFrame);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = 0;

	hr = device->CreateBuffer(&cbd, nullptr, m_constantBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	SetConstant(TextureChipSize, TextureNum);
}
void SpriteEffect::SetConstant(VECTOR2 TextureChip, VECTOR2 TextureNum)
{
	cb.TextureSize.x = static_cast<float>(TextureChip.x) / static_cast<float>(Texture.get()->GetWidth());
	cb.TextureSize.y = static_cast<float>(TextureChip.y) / static_cast<float>(Texture.get()->GetHeight());
	//cb.TextureSize.x = 0.25f;
	//cb.TextureSize.y = 0.25f;
	cb.TextureNum.x = TextureNum.x;
	cb.TextureNum.y = TextureNum.x;
}
void SpriteEffect::SetNum(int MaxNum)
{
	spriteEffects.resize(MaxNum);
	vertices.resize(MaxNum);
}
//現在使用しているエフェクトの最後の番号
void SpriteEffect::SetUseLastEffectIndex()
{
	int i=0;
	for (i = static_cast<int>(spriteEffects.size())-1; i > 0; i--) {
		EffectData* spriteEffect = &spriteEffects.at(i);
		if (spriteEffect->type >= 0) break;
	}
	if (i + 1 >= spriteEffects.size())
	{
		UseLastEffectIndex = i;
		return;
	}
	UseLastEffectIndex = i+1;
}
//
//void SpriteEffect::Update(float time)
//{
//
//	for (int i = 0; i < spriteEffects.size(); i++) {
//		EffectData* spriteEffect = &spriteEffects.at(i);
//		if (spriteEffect->type < 0) continue;
//
//		    spriteEffect->vx += spriteEffect->ax * time;
//		    spriteEffect->vy += spriteEffect->ay * time;
//		    spriteEffect->vz += spriteEffect->az * time;
//		    spriteEffect->x += spriteEffect->vx * time;
//		    spriteEffect->y += spriteEffect->vy * time;
//		    spriteEffect->z += spriteEffect->vz * time;
//		    spriteEffect->timer -= time;
//		    spriteEffect->alpha = spriteEffect->timer / 0.2f;
//
//			if (spriteEffect->timer <= 0) {
//				spriteEffect->type = -1;
//			}
//	}
//
//}

void SpriteEffect::Animation(float elapsedtimer, int Starttype, int Endtype, float Animetionspeed)
{
	for (int i = 0; i < GetUseLastEffectIndex(); i++) {
		EffectData* data = &spriteEffects.at(i);
		if (data->type < 0) continue;

		 data->anime_timer += elapsedtimer;
		// data->color.x = 0.0f;
		// data->color.y = 0.0f;
		 data->color.w -= 0.0f;

		if (data->anime_timer > Animetionspeed) {
			data->anime_timer = 0.0f;
		//	data->type += 1;
		
			if (data->type >= Endtype+1)
			{
				data->type = Starttype;
				
			}
		}
	}

}

//コンスタントバッファの更新
void SpriteEffect::UpdateConstantBuffer(ID3D11DeviceContext* context, XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	//定数バッファの更新
	cb.view = view;
	cb.projection = projection;
	context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);

	context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	context->GSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

}

void SpriteEffect::Set(ID3D11DeviceContext* context)
{
	for (int i = 0; i < GetUseLastEffectIndex(); i++)
	{

		EffectData* spriteEffect = &spriteEffects.at(i);
		if (spriteEffect->type >= 0) continue;
		spriteEffect->x = (rand() % 1001 - 500) * 0.01f;
		spriteEffect->y = (rand() % 1001 - 500) * 0.01f;
		spriteEffect->z = (rand() % 1001 - 500) * 0.01f;
		XMFLOAT3 v = { 0,0,0 };
		XMFLOAT3 f = { 1,1,1 };
		XMFLOAT2 size = { 1,1 };
		float timer = 100.0f;
		spriteEffect->type = 0;

		spriteEffect->vx = v.x;
		spriteEffect->vy = v.y;
		spriteEffect->vz = v.z;

		spriteEffect->ax = f.x;
		spriteEffect->ay = f.y;
		spriteEffect->az = f.z;

		spriteEffect->w = size.x;
		spriteEffect->h = size.y;

		spriteEffect->alpha = 1.0f;

		spriteEffect->timer = timer;
	}
	//頂点データ更新
	context->UpdateSubresource(m_vertexBuffer.Get(), 0, nullptr, spriteEffects.data(), 0, 0);

}
void SpriteEffect::Fire(DirectX::XMFLOAT3 pos, int max)
{
	for (int i = 0; i < max; i++) {
		for (int j = 0; j < GetUseLastEffectIndex(); j++)
		{
			EffectData* spriteEffect = &spriteEffects.at(j);
			if (spriteEffect->type >= 0)continue;
			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 v = { 0,0,0 };
			DirectX::XMFLOAT3 f = { 0,-2.0f,0 };
			DirectX::XMFLOAT2 s = { .4f,.4f };

			p.x = pos.x + (rand() % 10001 - 5000) * 0.00005f;
			p.y = pos.y + (rand() % 10001) * 0.0001f + 0.2f;
			p.z = pos.z + (rand() % 10001 - 5000) * 0.00005f;

			v.x = (rand() % 10001 - 5000) * 0.0002f;
			v.y = (rand() % 10001) * 0.0004f + 0.005f;
			v.z = (rand() % 10001 - 5000) * 0.0002f;

			spriteEffect->Set(0, 5, p, v, f, s);
			break;
		}
		

	}
}

void SpriteEffect::Fire2(DirectX::XMFLOAT3 pos, int max)
{
	for (int i = 0; i < max; i++) {
		for (int j = 0; j < GetUseLastEffectIndex(); j++)
		{
			EffectData* spriteEffect = &spriteEffects.at(j);
			if (spriteEffect->type >= 0)continue;
			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 v = { 0,0,0 };
			DirectX::XMFLOAT3 f = { 0,-2.0f,0 };
			DirectX::XMFLOAT2 s = { .4f,.4f };

			p.x = pos.x + (rand() % 10001 - 5000) * 0.00005f;
			p.y = pos.y + (rand() % 10001) * 0.0001f + 0.2f;
			p.z = pos.z + (rand() % 10001 - 5000) * 0.00005f;

			v.x = (rand() % 10001 - 5000) * 0.0002f;
			v.y = (rand() % 10001) * 0.0004f + 0.005f;
			v.z = (rand() % 10001 - 5000) * 0.0002f;

			spriteEffect->Set(13, 1, p, v, f, s);
			break;
		}


	}
}
void SpriteEffect::Render(ID3D11DeviceContext* context)
{

	_ASSERT_EXPR(Texture.get(), L"テクスチャがセットされていません");
	_ASSERT_EXPR((cb.TextureSize.x >= 0), L"TextureSizeが設定されていません。SetConstantを使ってください");
	//テクスチャ設定
	if (Texture.get()) {
		Texture.get()->Set(context, 0);
	}

	//コンスタントバッファ更新
	int n = 0; //パーティクル発生数
	for (int i = 0; i < GetUseLastEffectIndex(); i++)
	{
		EffectData* spriteEffect = &spriteEffects.at(i);

		if (spriteEffect->type < 0) continue;
		if (spriteEffect->renderflg == false)continue;
		VERTEXParticle& vertex = vertices.at(n);

		//UV座標

		//float u = static_cast<float>(static_cast<int>(vertex.color.x) % 4) * 0.25f;
		//float v = static_cast<float>(static_cast<int>(vertex.color.x) / 4) * 0.25f;

		vertex.pos.x = spriteEffect->x;//位置X
		vertex.pos.y = spriteEffect->y;//位置Y
		vertex.pos.z = spriteEffect->z;//位置Z
		vertex.size.x = spriteEffect->w;//大きさX
		vertex.size.y = spriteEffect->h;//大きさY
		vertex.tex.x = (float)spriteEffect->type;//タイプ
		vertex.tex.y = 0.0f;//空のデータ
		vertex.tex.z = 0.0f;//空のデータ
		vertex.tex.w = 0.0f;//空のデータ
		vertex.color = spriteEffect->color;
		++n;


	};
	context->UpdateSubresource(m_vertexBuffer.Get(), 0, NULL, vertices.data(), 0, 0);



	//頂点バッファをセット
	UINT stride = sizeof(VERTEXParticle);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->OMSetBlendState(BlendState::Instance().GetBlendState(BlenderType), nullptr, 0xFF);

	//レンダリング
	context->Draw(n, 0);

};