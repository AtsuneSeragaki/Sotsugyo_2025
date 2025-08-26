#pragma once

#include "../SceneBase.h"


#define BUTTON_WIDTH   300  // ボタンの幅
#define BUTTON_HEIGHT  70   // ボタンの高さ
#define BUTTON_SPACING 70   // ボタン同士の間隔

#define BUTTON_LX  505                       // ボタン左上X座標
#define BUTTON_RX  BUTTON_LX + BUTTON_WIDTH  // ボタン右下X座標(左上X座標＋ボタンの幅)

// スタートボタン
#define START_BUTTON_LY 270                             // スタートボタン左上Y座標
#define START_BUTTON_RY START_BUTTON_LY + BUTTON_HEIGHT // スタートボタン右下Y座標(左上Y座標＋ボタンの高さ)

// ヘルプボタン
#define HELP_BUTTON_LY START_BUTTON_RY + BUTTON_SPACING  // ヘルプボタン左上Y座標(スタートボタン右下Y座標＋ボタン同士の間隔)
#define HELP_BUTTON_RY HELP_BUTTON_LY  + BUTTON_HEIGHT   // ヘルプボタン右下Y座標(左上Y座標＋ボタンの高さ)

// エンドボタン
#define END_BUTTON_LY HELP_BUTTON_RY + BUTTON_SPACING // エンドボタン左上Y座標(ヘルプボタン右下Y座標＋ボタン同士の間隔)
#define END_BUTTON_RY END_BUTTON_LY  + BUTTON_HEIGHT  // エンドボタン右下Y座標(左上Y座標＋ボタンの高さ)

class TitleScene : public SceneBase
{
private:
	bool start_btn_collision; // スタートボタンとプレイヤーカーソルの当たり判定フラグ(false:当たっていない  true:当たっている)
	bool help_btn_collision;  // ヘルプボタンとプレイヤーカーソルの当たり判定フラグ(false:当たっていない  true:当たっている)
	bool end_btn_collision;   // エンドボタンとプレイヤーカーソルの当たり判定フラグ(false:当たっていない  true:当たっている)
	bool canClick;            // クリックフラグ(false:クリックできない  true:クリックできる)
	int frame_count;          // フレームカウント

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

private:
	// プレイヤーカーソルとボタンの当たり判定(引数：当たり判定を取りたいボタンの情報　戻り値：0→当たってない 1→当たっている)
	int CheckPlayerButtonCollision(int left, int right, int top, int bottom);
};