#pragma once

#include "../SceneBase.h"

// ボタン共通情報
#define HELP_BUTTON_WIDTH   300  // ボタンの幅
#define HELP_BUTTON_HEIGHT  70   // ボタンの高さ
#define HELP_BUTTON_SPACING 100   // ボタン同士の間隔
#define HELP_BUTTON_NUM 2        // ボタンの数
#define HELP_BUTTON_LY  610                       // ボタン左上Y座標
#define HELP_BUTTON_RY  HELP_BUTTON_LY + HELP_BUTTON_HEIGHT // ボタン右下Y座標

// スタートボタン
#define HELP_START_BUTTON_LX 305                              // スタートボタン左上X座標
#define HELP_START_BUTTON_RX  HELP_START_BUTTON_LX + HELP_BUTTON_WIDTH  // スタートボタン右下X座標(左上X座標＋ボタンの幅)

// タイトルボタン
#define HELP_TITLE_BUTTON_LX HELP_START_BUTTON_RX + HELP_BUTTON_SPACING // タイトルボタン左上X座標(スタートボタン右下X座標＋ボタン同士の間隔)
#define HELP_TITLE_BUTTON_RX HELP_TITLE_BUTTON_LX + HELP_BUTTON_WIDTH  // タイトルボタン右下X座標(左上X座標＋ボタンの高さ)

class HelpScene : public SceneBase
{
private:
	ButtonState button[HELP_BUTTON_NUM]; // ボタン情報

public:
	// コンストラクタ
	HelpScene();
	// デストラクタ
	~HelpScene();

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