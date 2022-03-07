#include "Charactor.h"
#include "Collision.h"
#include "Lib_EffectManager.h"

//初期化処理
void Charactor::Init()
{
	pos = { 0,0,0 };
	SetQuaternion({ 0,0,0,1 });
	scale = { 0.01f,0.01f,0.01f };
	SetOldPos(pos);
}
//更新処理
void Charactor::Update()
{
	//無敵時間の更新
	InvincibleTimeUpdate();
	//攻撃クールタイム更新
	AttackCoolTimeUpdate();
	//モデルの行列更新
	if (modelIndex >= 0)
	{
		TK_Lib::Model::Tranceform(modelIndex, pos, GetQuaternion(), scale);
		TK_Lib::Model::AnimetionUpdate(modelIndex);
	}
	
}
//描画処理
void Charactor::ModelRender()
{
	if (modelIndex >= 0)
	{
		//カメラより外にいるなら
		if (TK_Lib::Camera::IsCamera(GetPos()))
		{
			ShaderType shaderType= ShaderType::Shader_MakeShadow;
			//もしカメラから遠い場合、DrawShadowに切り替わる。
			if (SearchPosition(200, TK_Lib::Camera::GetPos())==false)
			{
				shaderType = ShaderType::Shader_DrawShadow;
			}
			TK_Lib::Draw::Model(modelIndex, shaderType);
		}

	}
}
//モデル用の描画処理
void Charactor::Render()
{

}
//デバッグ
void Charactor::CollisionDebug()
{
	//当たり判定
	TK_Lib::Debug3D::Circle(pos, collisionRadius);
	//レイピックの補正

	//レイピック用の当たり判定
	VECTOR3 Start = { pos.x,pos.y + BesideRayPickUP,     pos.z };
	VECTOR3 End =   { pos.x,pos.y - VerticalRayPickUnder, pos.z };
	TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });

	//レイピック用の当たり判定
	Start = { pos.x - moveVec.x, pos.y - moveVec.y + BesideRayPickUP,     pos.z - moveVec.z };
	End =   { pos.x + moveVec.x ,pos.y + moveVec.y + BesideRayPickUP, pos.z + moveVec.z };

	TK_Lib::Debug3D::Line(Start, End, {0,1,0,1});
}
//デバッグ
void Charactor::ParameterDebug()
{
	ImGui::DragFloat3("Pos",&pos.x,0.1f);
	ImGui::DragFloat3("Scale", &scale.x, 0.1f);
}

//Imguiデバッグ
void Charactor::ImguiDebug()
{

	
}
//登れるかどうか
bool Charactor::TryInclined(const VECTOR3 Normal)
{
	XMVECTOR V_up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR V_Normal = XMLoadFloat3(&Normal);
	V_Normal = XMVector3Normalize(V_Normal);

	float dot;
	XMVECTOR Dot;
	Dot=XMVector3Dot(V_up,V_Normal);
	XMStoreFloat(&dot, Dot);
	dot=acosf(dot);
	dot -= XMConvertToRadians(90);
	dot = fabsf(dot);

	ImGui::Begin("aaa");
	ImGui::Text("Radius=%f", dot/0.01754f);
	if (dot >= CanInclined)
	{
		ImGui::Text("OK");
	}
	ImGui::End();

	return (dot >= CanInclined);

	
	
	
}


//回転処理
void Charactor::Turn(const VECTOR3& moveVec)
{
	VECTOR4 Q = GetQuaternion();
	XMVECTOR Qu = XMLoadFloat4(&Q);

	if (moveVec == VECTOR3{ 0,0,0 })return;
	XMVECTOR Vec;
	//進む方向をXZ平面に変換する
	{
		VECTOR3 vec = moveVec;
		vec.y = 0.0f;
		Vec = DirectX::XMLoadFloat3(&vec);
		XMVECTOR L_moveVec;
		L_moveVec = XMVector3Length(Vec);
		float L;
		XMStoreFloat(&L, L_moveVec);
		if (L <= 0.0f)
		{
			return;
		}
		Vec = XMVector3Normalize(Vec);
	}

	XMVECTOR front;
	//正面ベクトルを
	//XZ平面に変換する
	{
		VECTOR3 Front = GetFront();
		Front.y = 0.0f;
		front = DirectX::XMLoadFloat3(&Front);
		front = XMVector3Normalize(front);
	}
	//回転軸
	XMFLOAT3 Up = GetUp();
	XMVECTOR Axis = DirectX::XMLoadFloat3(&Up);


	//回転量
	XMVECTOR Dot = XMVector3Dot(front, Vec);
	float dot;
	XMStoreFloat(&dot, Dot);
	dot = acosf(dot);//ラジアンに変換

	//二つのベクトルが近似している時は直ぐにreturn
	if (isnan(fabsf(dot))) {
		return;
	}

	//二つのベクトルが近似している時は直ぐにreturn
	if ((fabsf(dot) < XMConvertToRadians(1))) {
		return;
	}

	XMVECTOR q;

	//回転軸の算出
	XMVECTOR Cross;
	{
		Cross = XMVector3Cross(front, Vec);
		Cross = XMVector3Normalize(Cross);
	}
	XMFLOAT3 cross;
	XMStoreFloat3(&cross, Cross);


	if (cross.y < 0)
	{
		q = XMQuaternionRotationAxis(-Axis, dot);
	}
	else
	{
		q = XMQuaternionRotationAxis(Axis, dot);
	}




	q = XMQuaternionMultiply(q, Qu);

	//補完させる
	q = XMQuaternionSlerp(Qu, q, trunSpeed);

	XMStoreFloat4(&Q, q);

	SetQuaternion(Q);


}
//目標に進むベクトルの算出
bool Charactor::MoveOnPosition(VECTOR3 Position)
{
	constexpr float Scale = 0.1f;
	if (SearchPosition(Scale,Position))
	{
		//もう既に登録しているので進む必要がない
		return false;
	}
	VECTOR3 vec = Position - pos;
	vec.y = 0.0f;
	XMVECTOR Vec = XMLoadFloat3(&vec);
	XMVECTOR N_Vec = XMVector3Normalize(Vec);
	//進むベクトル
	XMVECTOR MoveVec = XMVectorScale(N_Vec, speed);
	XMStoreFloat3(&moveVec,MoveVec);
	

	return true;
}

//索敵範囲にTargetがいればTRUEを返す
bool Charactor::SearchPosition(const float L,VECTOR3 Position)
{
	//目標までの距離を算出
	float TargetL;
	{
		VECTOR3 vec = pos - Position;
		XMVECTOR Vec = XMLoadFloat3(&vec);
		Vec = XMVector3Length(Vec);
		XMStoreFloat(&TargetL, Vec);
	}
	//目標までの距離と比べる
	return TargetL <= L;

}

//縦方向の当たり判定（Y方向）
void Charactor::VerticalCollision()
{
	VECTOR3 Start = { pos.x,pos.y + BesideRayPickUP, pos.z };
	VECTOR3 End = { pos.x,pos.y - BesideRayPickUnder, pos.z };
	RayOut ray;
	Collision::Instance().RayPick(Start, End, ray);
	//ImGui::Begin("a");
	//ImGui::Text("%f,%f,%f", ray.Normal.x, ray.Normal.y, ray.Normal.z);
	//ImGui::End();
	if (ray.materialIndex >= 0)
	{
		pos.y = ray.Pos.y;
	}

}
//横方向の当たり判定（XZ平面）
void Charactor::BesideCollision()
{
	VECTOR3 Start = { pos.x - moveVec.x,pos.y - moveVec.y + BesideRayPickUP, pos.z - moveVec.z };
	VECTOR3 End = { pos.x + moveVec.x,pos.y + moveVec.y + BesideRayPickUnder, pos.z + moveVec.z };
	//レイピックに当たった位置の情報
	RayOut ray;
	//補正位置
	VECTOR3 Position=GetPos();

	//半径を考慮したレイピック
	//Collision::Instance().RadiusRayPick(Start, End, ray,1.0f);
	Collision::Instance().RayPick(Start, End, ray);
	//もし当たっているなら
	if (ray.materialIndex >= 0)
	{
		////補正位置の計算
		//XMVECTOR start = XMLoadFloat3(&Start);
		//XMVECTOR end = XMLoadFloat3(&End);
		////壁の法線
		//XMVECTOR Normal = XMLoadFloat3(&ray.Normal);
		////はみ出たベクトル
		//XMVECTOR V = XMVectorSubtract(end, XMLoadFloat3(&ray.Pos));
		////入射ベクトルを法線に射影
		//XMVECTOR Dot = XMVector3Dot(Normal, XMVectorNegate(V));
		//float dot;
		//XMStoreFloat(&dot, Dot);
		//
		//XMVECTOR vec = XMVectorScale(Normal, dot);
		//XMVECTOR Pos = XMVectorAdd(vec, V);
		//XMFLOAT3 Ve;
		//XMStoreFloat3(&Ve, Pos);
		//
		////進行ベクトルを求める
		//Position.x += Ve.x;
		//Position.z += Ve.z;
		//はみ出たベクトルの算出
		XMVECTOR V_RayHitPositionEnd;
		{
			VECTOR3 rayHitposition;
			rayHitposition = ray.Pos - End;
			V_RayHitPositionEnd = XMLoadFloat3(&rayHitposition);
		}
		
		//法線
		XMVECTOR RayHitNormal;
		{
			RayHitNormal = XMLoadFloat3(&ray.Normal);
			RayHitNormal = XMVector3Normalize(RayHitNormal);
		}
		
		//かべずり補正位置の算出
		VECTOR3 WallPosition;
		{
			XMVECTOR Dot;
			Dot = XMVector3Dot(V_RayHitPositionEnd, RayHitNormal);
			Dot=XMVector3Length(Dot);
			float dot;
			XMStoreFloat(&dot, Dot);
			XMVECTOR Vec = XMVectorScale(RayHitNormal, dot);
			VECTOR3 vec;
			XMStoreFloat3(&vec, Vec);
		
			WallPosition = End + vec;
			//Position = End + vec;
		}
		
		//半径分、補正位置を変える
		{
			//VECTOR3 rayHitposition;
			//rayHitposition = pos - ray.Pos;
			//XMVECTOR V_HitEnd = XMLoadFloat3(&rayHitposition);
			//XMVECTOR Dot = XMVector3Dot(V_HitEnd, RayHitNormal);
			//float dot;
			//XMStoreFloat(&dot, Dot);
			//MEMO こっちの方がいいかも
			//Position = WallPosition + ray.Normal * radius;
			Position = WallPosition;
			//でもX座標横向き方向も考えるげきなので現段階ではこれに応用している
		//	Position = WallPosition + ray.Normal * dot;
		}
		//壁にめり込んでしまうのでそれを考慮する
		//レイピックに当たった位置の情報
		RayOut ray2;
		Start = { pos.x,pos.y + BesideRayPickUP,pos.z };
		End = { Position.x ,Position.y, Position.z };
		Collision::Instance().RayPick(Start, End, ray2);
		//めり込みしていかどうか
		if (ray2.materialIndex >= 0)
		{
			//めり込み発生
		
			//乗り越えるとこができるか？
			if (TryInclined(ray2.Normal))
			{
				pos.x = Position.x;
				pos.z = Position.z;
			}
		}
		else
		{
			pos.x = Position.x;
			pos.z = Position.z;
		}
		

	}
	else
	{
		Move();
	}


	////過去の位置から今回の位置まで各方向にレイピックを行う
	//if (oldPos.x >= pos.x)
	//{
	//	Start = { pos.x + speed ,pos.y + BesideRayPickUP, pos.z}; 
	//	End   = { pos.x - speed ,pos.y + BesideRayPickUP, pos.z};
	//}
	//else
	//{
	//	Start = { pos.x - speed ,pos.y + BesideRayPickUP, pos.z}; 
	//	End   = { pos.x + speed ,pos.y + BesideRayPickUP, pos.z};
	//}
	////ここはある程度ゆとりを取らせて補正させる
	//
	//
	//
	//TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });
	////X軸補正
	//Collision::Instance().RayPick(Start, End, ray);
	////もし当たっているなら
	//if (ray.materialIndex >= 0)
	//{
	//	pos.x = ray.Pos.x+(ray.Normal.x*speed);
	//}
	//
	//
	////Z軸補正
	//
	////過去の位置から今回の位置まで各方向にレイピックを行う
	//if (oldPos.z >= pos.z)
	//{
	//	Start = { pos.x  ,pos.y + BesideRayPickUP, pos.z + speed };
	//	End = { pos.x  ,pos.y + BesideRayPickUP, pos.z - speed };
	//}
	//else
	//{
	//	Start = { pos.x  ,pos.y + BesideRayPickUP, pos.z - speed };
	//	End = { pos.x  ,pos.y + BesideRayPickUP, pos.z + speed };
	//}
	//
	//TK_Lib::Debug3D::Line(Start, End, { 0,0,1,1 });
	//
	//Collision::Instance().RayPick(Start, End, ray);
	////もし当たっているなら
	//if (ray.materialIndex >= 0)
	//{
	//	pos.z = ray.Pos.z + (ray.Normal.z * speed);
	//}



}

//ステージにはみ出ていないか補正(最終確認)
void Charactor::StageOverhang()
{
	//過去の位置から今の位置までをレイピック

//	VECTOR3 Start = { oldPos.x,   oldPos.y+BesideRayPickUP, oldPos.z } ;
//	VECTOR3 End =   { pos.x,      pos.y   +BesideRayPickUP, pos.z };
//	TK_Lib::Debug3D::Line(Start, End);
//	//レイピックに当たった位置の情報
//	RayOut ray;
//
//	//半径を考慮したレイピック
//	Collision::Instance().RayPick(Start, End, ray);
//	//Collision::Instance().RadiusRayPick(Start, End, ray,speed);
//	if (ray.materialIndex >= 0)
//	{
//		pos.z = oldPos.z;
//		pos.x = oldPos.x;
//	}
}
//指定された位置までのベクトルの算出
XMVECTOR Charactor::Vector(const VECTOR3 Position)
{
	XMVECTOR PosA,PosB,Vec;
	PosA = XMLoadFloat3(&pos);
	PosB = XMLoadFloat3(&Position);
	//引き算した値を返す
	return XMVectorSubtract(PosB,PosA);
}
//指定された位置までの距離の算出
float Charactor::Length(const VECTOR3 Position)
{
	float L;
	XMVECTOR Vec=Vector(Position);
	Vec = XMVector3Length(Vec);
	XMStoreFloat(&L,Vec);
	return L;
}

void Charactor::Move()
{
	pos.x += moveVec.x * speed;
	pos.z += moveVec.z * speed;
}
//速度に加算
void Charactor::AddVelocity(VECTOR3 velocity)
{
	this->velocity += velocity;

	XMVECTOR Velocity = XMLoadFloat3(&this->velocity);
	float L;
	XMStoreFloat(&L, Velocity);
	//もし速度がMaxVelocityより大きさなら
	if (L >= MaxVelocity)
	{
		Velocity = XMVector3Normalize(Velocity);
		Velocity = XMVectorScale(Velocity,MaxVelocity);
		//速度がMaxVelocityになる
		XMStoreFloat3(&this->velocity, Velocity);
	}
}
void Charactor::SetInvincibleTime(int invincibleTime)
{
	this->invincibleTime = invincibleTime;
}

//更新処理
void Charactor::AttackCoolTimeUpdate()
{
	if (attackCoolTime >= 1)
	{
		attackCoolTime--;
	}
}

//更新処理
void Charactor::InvincibleTimeUpdate()
{
	if (invincibleTime >= 1)
	{
		invincibleTime--;
	}
}
//ダメージを判定
bool Charactor::AddDamage(int Damage,int SetinvincibleTime)
{
	//体力が0以下なら
	if (GetHp()<= 0)return false;
	//無敵中なら
	if (invincibleTime > 0)return false;

	invincibleTime = SetinvincibleTime;
	hp -= Damage;
	
	//もし生き残っていたなら
	if (hp>=1)
	{//ダメージフラグのオン
		SetDamageFlg(true);

	}
	else//死亡しているなら
	{
		//ダメージフラグのオン
		SetDeadFlg(true);
	}
	return true;
}
