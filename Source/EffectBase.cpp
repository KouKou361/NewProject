#include "EffectBase.h"
#include "ExportScript.h"
#include "Scene.h"

//初期化設定
void EffectBase::Init()
{
	//全てのパーティクルを非表示に
	NotRender();
}

//エフェクトの生成
void EffectBase::Create(const string& textureName, const int& maxNum, const VECTOR2& textureChipSize, const VECTOR2& textureNum, const Bland_state& blendstate)
{
	//設定を保存しておく（保存する必要ないと思うが、念のために保存！）
	{
		//エフェクトで使用しているテクスチャの名前
		this->textureName = textureName;
		//エフェクト粒子の最大数
		this->maxNum = maxNum;
		//一つあたりのチップサイズ
		this->textureChipSize = textureChipSize;
		//チップがいくつあるかどうか（X、Y）
		this->textureNum = textureNum;
		//ブレンドの種類
		this->blendState = blendstate;
	}
	

	//エフェクトのロード
	effectIndex =TK_Lib::Lib_Effect::Load(this->textureName, this->maxNum, this->textureChipSize, this->textureNum, this->blendState);
}

//全てのパーティクルを非表示に
void EffectBase::NotRender()
{
	//パーティクル配列情報の取得
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	//全て非表示
	for (int j = 0; j < spriteEffects->size(); j++)
	{
		EffectData* spriteEffect = &spriteEffects->at(j);
		//非表示にする
		if (spriteEffect->type >= 0)
		{
			spriteEffect->type = -1;
		}
	}


	
}
//エフェクトの削除関数
void EffectBase::Delete()
{
	TK_Lib::Lib_Effect::Erase(effectIndex);
}

//csvデータからステータスの設定をする
void EffectBase::SetStatus(SceneGame* sceneGame, const string& SearchName)
{
	//エフェクトのデータ取得
	EffectStatusData* data = sceneGame->GetexportSCV()->GetEffectStatusDataSearchName(SearchName);


	this->initStatus.effectType        = data->GetEffectType();                 //エフェクトのタイプ
	this->initStatus.timer             = data->GetTimer();                      //生存時間
	this->initStatus.updateAlpha       = data->GetUpdateAlpha();                //更新処理の透明度の変化量
	
	this->initStatus.posMax            = data->GetPosMax();		                //位置乱数の最高値
	this->initStatus.posMix            = data->GetPosMix();	                    //位置乱数の最低値

	this->initStatus.velocityMax       = data->GetVelocityMax();	            //速度乱数の最高値
	this->initStatus.velocityMix       = data->GetVelocityMix();                //速度乱数の最低値

	this->initStatus.accelMax          = data->GetAccelMax();	                //加速度乱数の最高値
	this->initStatus.accelMix          = data->GetAccelMix();	                //加速度乱数の最低値

	this->initStatus.scale             = { data->GetScale(),data->GetScale() };	//大きさ

	this->initStatus.color             = data->GetColor();                      //色
																																							
	this->initStatus.updateScale       = { data->GetUpdateScale(),data->GetUpdateScale() };//更新処理の大きさの変化量																	
														
}			
//エフェクトの出現処理
void EffectBase::Play(const VECTOR3& pos, const int &num)
{
	//パーティクル配列情報の取得
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);


	for (int i = 0; i < num; i++) {
		for (int j = 0; j < spriteEffects->size(); j++)
		{
			EffectData* spriteEffect = &spriteEffects->at(j);
			if (spriteEffect->type >= 0)continue;

			VECTOR3 p = { 0,0,0 };      //位置
			VECTOR3 v = { 0,0,0 };	    //速度
			VECTOR3 f = { 0,0,0 };	    //加速度		  
			VECTOR2 s = { 0,0 };
			VECTOR4 color = { 0,0,0,0 };

			//大きさ
			{
				s = initStatus.GetScale();
			}
			//位置の算出
			{
				p.x = pos.x + Mathf::RandomRange(initStatus.GetPosMix().x, initStatus.GetPosMax().x);
				p.y = pos.y + Mathf::RandomRange(initStatus.GetPosMix().y, initStatus.GetPosMax().y);
				p.z = pos.z + Mathf::RandomRange(initStatus.GetPosMix().z, initStatus.GetPosMax().z);
			}

			//速度の算出
			{
				v.x = Mathf::RandomRange(initStatus.GetVelocityMix().x, initStatus.GetVelocityMax().x);
				v.y = Mathf::RandomRange(initStatus.GetVelocityMix().y, initStatus.GetVelocityMax().y);
				v.z = Mathf::RandomRange(initStatus.GetVelocityMix().z, initStatus.GetVelocityMax().z);
			}

			//加速度の算出
			{
				f.x = Mathf::RandomRange(initStatus.GetAccelMix().x, initStatus.GetAccelMax().x);
				f.y = Mathf::RandomRange(initStatus.GetAccelMix().y, initStatus.GetAccelMax().y);
				f.z = Mathf::RandomRange(initStatus.GetAccelMix().z, initStatus.GetAccelMax().z);
			}

			//色
			{
				color.x = initStatus.GetColor().x;
				color.y = initStatus.GetColor().y;
				color.z = initStatus.GetColor().z;
				color.w = initStatus.GetColor().w;
			}




			//設定関数	
			spriteEffect->Set(
				initStatus.GetEffectType(),
				initStatus.GetTimer(),
				p, v, f, s,color);
			break;
		}


	}
}

//更新処理
void EffectBase::Update()
{
	//エフェクトには2つのタイプがいる。
	//まず１つ目はカメラ外は消えない更新処理タイプ
	//２つ目はカメラ外は消える更新処理タイプ（軽量化の為）
	//その為の分岐処理↓

	if (isCameraUpdateFlg)
	{
		//自身がカメラ外の場合でも消える更新処理を行う
		IsCameraUpdate();
	}
	else
	{
		//自身がカメラ外の場合、消えない更新処理を行わない
		NotIsCameraUpdate();
	}
}

//自身がカメラ外の場合、消える更新処理を行わない
void EffectBase::NotIsCameraUpdate()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);

		if (spriteEffect->type < 0) continue;
		if (!spriteEffect->IsCameraRender())continue;//カメラ外なので処理を行わない

		//パーティクルのステータス更新処理
		ParticleUpdate(spriteEffect);

		spriteEffect->color.w -= initStatus.GetUpdateAlpha() * time;

		//消える処理
		if (spriteEffect->color.w <= 0)	spriteEffect->type = -1;
		if (spriteEffect->timer <= 0)spriteEffect->type = -1;
	}
}
//自身がカメラ外の場合でも消える更新処理を行う
void EffectBase::IsCameraUpdate()
{
	float time = TK_Lib::Window::GetElapsedTime();
	vector<EffectData>* spriteEffects = TK_Lib::Lib_Effect::Geteffects(effectIndex);

	for (int i = 0; i < TK_Lib::Lib_Effect::GetUseLastEffectIndex(effectIndex); i++) {
		EffectData* spriteEffect = &spriteEffects->at(i);

		if (spriteEffect->type < 0) continue;

		spriteEffect->color.w -= initStatus.GetUpdateAlpha() * time;

		//消える処理
		if (spriteEffect->color.w <= 0)	spriteEffect->type = -1;
		if (spriteEffect->timer <= 0)spriteEffect->type = -1;

		if (!spriteEffect->IsCameraRender())continue;//カメラ外なので処理を行わない

		//パーティクルのステータス更新処理
		ParticleUpdate(spriteEffect);

	}

}
//パーティクルのステータス更新処理
void EffectBase::ParticleUpdate(EffectData* spriteEffect)
{
	float time = TK_Lib::Window::GetElapsedTime();

	spriteEffect->vx += spriteEffect->ax * time;//速度の更新処理
	spriteEffect->vy += spriteEffect->ay * time;//速度の更新処理
	spriteEffect->vz += spriteEffect->az * time;//速度の更新処理

	spriteEffect->x += spriteEffect->vx * time;//位置の更新処理
	spriteEffect->y += spriteEffect->vy * time;//位置の更新処理
	spriteEffect->z += spriteEffect->vz * time;//位置の更新処理

	spriteEffect->timer -= time;
	spriteEffect->h += initStatus.GetUpdateScale().x * time;
	spriteEffect->w += initStatus.GetUpdateScale().y * time;
}
