#pragma once
#include "Lib.h"
#include "Actor.h"

class Animetion;

//キャラクタークラス
class Charactor:public Actor
{
private:


	//登れる傾斜角度(この値以下の傾斜ならのばることが出来る)
	float canInclined = XMConvertToRadians(45);
	//ひとつ前の地点
	VECTOR3 oldPos = { 0,0,0 };
	Actor* targetActor=nullptr;
protected:


	//ちょっとだけ上の方からレイピックを取る
	const float BesideRayPickUP = 5.0f;
	const float BesideRayPickUnder = 50.5f;
	//レイピックの判定
	const float VerticalRayPickUnder = 2.0f;

	float spaceVolume = 1.0f;//レイピック時にある程度補正させる大きさ
	float speed = 0.5f;
	float trunSpeed = XMConvertToRadians(10);
	float maxVelocity = 0.1f;

	bool damageFlg=false;
	bool deadFlg = false;

	//無敵時間
	float invincibleTime = 0;
	//攻撃クールタイム
	float attackCoolTime = 0;

	//進むベクトル
	VECTOR3 moveVec = { 0,0,0 };
	//速度
	VECTOR3 velocity = { 0,0,0 };
	//モデルのアニメデータ
	shared_ptr<Animetion> anime;



public:
	Charactor() {};
	virtual ~Charactor() {};
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
	//マスクスタート
	void MaskStart(const float speed);
	//マスク大きさ取得
	float GetMaskVolume();

	//回転処理
	void Turn(const VECTOR3& moveVec);
	//縦方向の当たり判定（Y方向）
	void VerticalCollision();
	//横方向の当たり判定（XZ平面）
	void BesideCollision();
	//ステージにはみ出ていないか補正(最終確認)
	void StageOverhang();
	//無敵時間の設定
	void SetInvincibleTime(const float& invincibleTime);
	//速度に加算
	void AddVelocity(const VECTOR3& velocity);
	//無敵時間の更新
	void InvincibleTimeUpdate();
	//動き
	void Move();
	//攻撃クールタイム更新処理
	void AttackCoolTimeUpdate();
	//デバッグImgui
	virtual void ImguiDebug();

	//索敵範囲にTargetがいればTRUEを返す
	bool SearchPosition(const float& L, const VECTOR3& position);
	//目標に進むベクトルの算出
	bool MoveOnPosition(const VECTOR3& position);
	//ダメージ受けた時の関数
	bool AddDamage(const int& damage, const float& maxInvincibleTime=0);
	//登れるかどうか
	bool TryInclined(const VECTOR3& normal);

	//指定された位置までのベクトルの算出
	XMVECTOR Vector(const VECTOR3& position);

	//指定された位置までの距離の算出
	float Length(const VECTOR3& position);
	//CSVからデータを取り出して、ステータスの設定する。
	virtual void SetStatus(const string &searchName);




	//==================================
	//セッター、ゲッター
	//==================================
	
	//目標キャラクター
	inline void SetTarget(Actor* target) { targetActor = target; }
	inline Actor* GetTarget() { return targetActor; }
	//攻撃クールタイム
	inline void SetAttackCoolTime(const float attackTime) { attackCoolTime = attackTime; }
	inline float GetAttackCoolTime() { return attackCoolTime; }
	//ダメージフラグ
	inline bool GetDamageFlg() { return damageFlg; };
	virtual void SetDamageFlg(const bool flg) { damageFlg = flg; };
	//死亡フラグ
	inline bool GetDeadFlg() { return deadFlg; };
	virtual void SetDeadFlg(const bool flg) { deadFlg = flg; };
	//oldPos
	inline void SetOldPos(const VECTOR3 position) { this->oldPos = position; };
	inline VECTOR3 GetOldPos() { return this->oldPos; };
	//加速度
	inline VECTOR3 GetVelocity() { return this->velocity; };
	//速度
	inline float GetSpeed() { return speed; }
	inline void SetSpeed(const float speed) { this->speed; }
	//登れる値設定
	inline void SetCanInclined(const float canInclined) { this->canInclined = canInclined; };
	//進む方向設定
	inline void SetMoveVec(const VECTOR3 vec) { moveVec = vec; }
	//アニメデータ取得
	inline Animetion* GetAnime() { return anime.get(); };
};