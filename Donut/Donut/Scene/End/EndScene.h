#pragma once

#include "../SceneBase.h"

class EndScene : public SceneBase
{
private:
	int end_timer; // 終わるまでの時間
	int background_img;

public:
	// コンストラクタ
	EndScene();
	// デストラクタ
	~EndScene();

public:
	// 初期化処理
	virtual void Initialize() override;
	// 更新処理
	virtual eSceneType Update() override;
	// 描画処理
	virtual void Draw() const override;
	// 終了時処理
	virtual void Finalize() override;

public:
	// 現在のシーン情報を返す
	virtual eSceneType GetNowSceneType() const override;
	// 終わるまでの時間経過を返す
	int GetEndTimer() { return end_timer; }
};