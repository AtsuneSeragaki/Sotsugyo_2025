#pragma once

#include "../Utility/Vector2D.h"
#include <vector>

enum class eSceneType
{
	eTitle,
	eGameMain,
	eResult,
	eHelp,
	eEnd,
};

class SceneBase
{
protected:
	int background_image;             // 背景画像データ

public:
	SceneBase();
	virtual ~SceneBase();

public:
	// 初期化処理
	virtual void Initialize();
	// 更新処理
	virtual eSceneType Update();
	// 描画処理
	virtual void Draw() const;
	// 終了時処理
	virtual void Finalize();

public:
	// 現在のシーン情報を返す
	virtual eSceneType  GetNowSceneType() const = 0;
};