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

struct ButtonState {
	int lx, rx, ly, ry;
	bool collision = false;
	eSceneType targetScene; // クリックで遷移するシーン
};

class SceneBase
{
protected:
	int background_image; // 背景画像データ
	int frame_count;      // フレームカウント
	bool can_click;       // クリックフラグ(false:クリックできない  true:クリックできる)

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

	// プレイヤーカーソルとボタンの当たり判定(引数：当たり判定を取りたいボタンの情報　戻り値：0→当たってない 1→当たっている)
	int CheckPlayerButtonCollision(int left, int right, int top, int bottom);
};