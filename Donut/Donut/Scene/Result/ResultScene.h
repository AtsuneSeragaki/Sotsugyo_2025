#pragma once

#include "../SceneBase.h"

// ボタン共通情報
#define BUTTON_WIDTH   300  // ボタンの幅
#define BUTTON_HEIGHT  70   // ボタンの高さ
#define BUTTON_SPACING 70   // ボタン同士の間隔
#define BUTTON_NUM 2        // ボタンの数
#define BUTTON_LY  610                       // ボタン左上Y座標
#define BUTTON_RY  BUTTON_LY + BUTTON_HEIGHT // ボタン右下Y座標

// リスタートボタン
#define RESTART_BUTTON_LX 305                               // リスタートボタン左上X座標
#define RESTART_BUTTON_RX  RESTART_BUTTON_LX + BUTTON_WIDTH // リスタートボタン右下X座標(左上X座標＋ボタンの幅)

// タイトルボタン
#define TITLE_BUTTON_LX RESTART_BUTTON_RX + BUTTON_SPACING // タイトルボタン左上X座標(リスタートボタン右下X座標＋ボタン同士の間隔)
#define TITLE_BUTTON_RX TITLE_BUTTON_LX  + BUTTON_WIDTH    // タイトルボタン右下X座標(左上X座標＋ボタンの高さ)

class ResultScene : public SceneBase
{
private:
	int score;             // スコア
	ButtonState button[BUTTON_NUM]; // ボタン情報
	
public:
	// コンストラクタ
	ResultScene(int score);
	// デストラクタ
	~ResultScene();

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