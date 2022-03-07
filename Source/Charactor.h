#pragma once
#include "Lib.h"
#include "Actor.h"

class Animetion;

//キャラクタークラス
class Charactor:public Actor
{
private:
	//登れる傾斜角度(この値以下の傾斜ならのばることが出来る)
	float CanInclined = XMConvertToRadians(45);
	//ひとつ前の地点
	VECTOR3 oldPos = { 0,0,0 };

	Actor* targetActor;



protected:



	float spaceVolume = 1.0f;//レイピック時にある程度補正させる大きさ

	float speed = 0.5f;
	float trunSpeed = XMConvertToRadians(10);
	float MaxVelocity = 0.1f;

	bool damageFlg=false;
	bool deadFlg = false;

	//進むベクトル
	VECTOR3 moveVec = { 0,0,0 };
	//速度
	VECTOR3 velocity = { 0,0,0 };

	//無敵時間
	int invincibleTime = 0;

	//攻撃クールタイム
	int attackCoolTime = 0;

public:
	//初期化処理
	virtual void Init();
	//更新処理
	virtual void Update();
	//描画処理
	virtual void ModelRender();
	//モデル用の描画処理
	virtual void Render();
	//デバッグ当たり判定
	virtual void CollisionDebug();
	//デバッグパラメータ
	virtual void ParameterDebug();
	//破棄処理
	virtual void Destroy() {};
	
	//索敵範囲にTargetがいればTRUEを返す
	bool SearchPosition(const float L, VECTOR3 Position);
	//目標に進むベクトルの算出
	bool MoveOnPosition(VECTOR3 Position);
	//回転処理
	void Turn(const VECTOR3& moveVec);
	//縦方向の当たり判定（Y方向）
	void VerticalCollision();
	//横方向の当たり判定（XZ平面）
	void BesideCollision();
	//ステージにはみ出ていないか補正(最終確認)
	void StageOverhang();
	//指定された位置までのベクトルの算出
	XMVECTOR Vector(const VECTOR3 Position);
	//指定された位置までの距離の算出
	float Length(const VECTOR3 Position);
	void SetInvincibleTime(int invincibleTime);
	inline void SetAttackCoolTime(int AttackTime) { attackCoolTime = AttackTime; }
	inline int GetAttackCoolTime() { return attackCoolTime; }
	//動き
	void Move();
	//oldPosの設定
	inline void SetOldPos(VECTOR3 Pos) { this->oldPos = Pos; };
	//oldPosの取得
	inline VECTOR3 GetOldPos() { return this->oldPos; };


	//速度の取得
	inline VECTOR3 GetVelocity() { return this->velocity; };
	//速度に加算
	void AddVelocity(VECTOR3 velocity);
	//無敵時間の更新
	void InvincibleTimeUpdate();

	inline bool GetDamageFlg() {return damageFlg;};
	bool GetDeadFlg() { return deadFlg; };

	virtual void SetDamageFlg(bool flg) { damageFlg = flg; };
	virtual void SetDeadFlg(bool flg)   { deadFlg = flg; };


public:
	Charactor() {};
	virtual ~Charactor() {};


	//ちょっとだけ上の方からレイピックを取る
	float BesideRayPickUP = 5.0f;
	float BesideRayPickUnder = 20.5f;
	//レイピックの判定
	float VerticalRayPickUnder = 2.0f;
	//目標キャラクターの設定
	inline  void SetTarget(Actor* target) { targetActor = target; }
	//目標の取得
	inline  Actor* GetTarget() { return targetActor; }

	shared_ptr<Animetion> anime;
	
	bool AddDamage(int Damage, int MaxinvincibleTime=0);
	
	void AttackCoolTimeUpdate();


	void SetCanInclined(const float CanInclined) { this->CanInclined = CanInclined; };
	void SetMoveVec(VECTOR3 Vec) { moveVec = Vec; }
	//デバッグImgui
	virtual void ImguiDebug();
	//登れるかどうか
	bool TryInclined(const VECTOR3 Normal);


	inline  float GetSpeed() { return speed; }






};