
#pragma once
//基底クラスのマネージャークラス
class Manager
{
public:
	Manager() {};
	virtual ~Manager() {};

	//初期化処理
	virtual void Init() = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Render() = 0;
	//モデル描画処理
	virtual void ModelRender() = 0;
	//全消去
	virtual void Clear() = 0;
private:


};
