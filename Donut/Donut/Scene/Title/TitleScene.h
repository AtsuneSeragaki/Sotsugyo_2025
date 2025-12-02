#pragma once

#include "../SceneBase.h"

// ボタン共通情報
#define TITLE_BUTTON_WIDTH   300  // ボタンの幅
#define TITLE_BUTTON_HEIGHT  70   // ボタンの高さ
#define TITLE_BUTTON_SPACING 30   // ボタン同士の間隔
#define TITLE_BUTTON_NUM 4        // ボタンの数
#define TITLE_BUTTON_LX  505                       // ボタン左上X座標
#define TITLE_BUTTON_RX  TITLE_BUTTON_LX + TITLE_BUTTON_WIDTH  // ボタン右下X座標(左上X座標＋ボタンの幅)

// スタートボタン
#define TITLE_START_BUTTON_LY 270                             // スタートボタン左上Y座標
#define TITLE_START_BUTTON_RY TITLE_START_BUTTON_LY + TITLE_BUTTON_HEIGHT // スタートボタン右下Y座標(左上Y座標＋ボタンの高さ)

// ヘルプボタン
#define TITLE_HELP_BUTTON_LY TITLE_START_BUTTON_RY + TITLE_BUTTON_SPACING  // ヘルプボタン左上Y座標(スタートボタン右下Y座標＋ボタン同士の間隔)
#define TITLE_HELP_BUTTON_RY TITLE_HELP_BUTTON_LY  + TITLE_BUTTON_HEIGHT   // ヘルプボタン右下Y座標(左上Y座標＋ボタンの高さ)

// ランキングボタン
#define TITLE_RANKING_BUTTON_LY TITLE_HELP_BUTTON_RY + TITLE_BUTTON_SPACING   // ランキングボタン左上Y座標(ヘルプボタン右下Y座標＋ボタン同士の間隔)
#define TITLE_RANKING_BUTTON_RY TITLE_RANKING_BUTTON_LY + TITLE_BUTTON_HEIGHT // ランキングボタン右下Y座標(左上Y座標＋ボタンの高さ)

// エンドボタン
#define TITLE_END_BUTTON_LY TITLE_RANKING_BUTTON_RY + TITLE_BUTTON_SPACING // エンドボタン左上Y座標(ランキングボタン右下Y座標＋ボタン同士の間隔)
#define TITLE_END_BUTTON_RY TITLE_END_BUTTON_LY + TITLE_BUTTON_HEIGHT     // エンドボタン右下Y座標(左上Y座標＋ボタンの高さ)

class TitleScene : public SceneBase
{
private:
	ButtonState button[TITLE_BUTTON_NUM] = {};  // ボタン情報
	int background_img; // 背景画像

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
};