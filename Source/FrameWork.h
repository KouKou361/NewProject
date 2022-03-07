#pragma once
class FrameWork
{
private:
	static FrameWork* instance;
public:
	FrameWork();
	~FrameWork() {};
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//モデル用の描画処理
	void ModelRender();
	//終了処理
	void End();

	//インスタンス取得
	static FrameWork& Instance()
	{
		return *instance;
	}
};
