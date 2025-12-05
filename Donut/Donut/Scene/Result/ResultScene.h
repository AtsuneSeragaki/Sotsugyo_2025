#pragma once

#include "../SceneBase.h"

// ボタン共通情報
#define RESULT_BUTTON_WIDTH   300  // ボタンの幅
#define RESULT_BUTTON_HEIGHT  70   // ボタンの高さ
#define RESULT_BUTTON_SPACING 100   // ボタン同士の間隔
#define RESULT_BUTTON_NUM 2        // ボタンの数
#define RESULT_BUTTON_LY  610                       // ボタン左上Y座標
#define RESULT_BUTTON_RY  RESULT_BUTTON_LY + RESULT_BUTTON_HEIGHT // ボタン右下Y座標

// リスタートボタン
#define RESULT_RESTART_BUTTON_LX 305                               // リスタートボタン左上X座標
#define RESULT_RESTART_BUTTON_RX  RESULT_RESTART_BUTTON_LX + RESULT_BUTTON_WIDTH // リスタートボタン右下X座標(左上X座標＋ボタンの幅)

// タイトルボタン
#define RESULT_TITLE_BUTTON_LX RESULT_RESTART_BUTTON_RX + RESULT_BUTTON_SPACING // タイトルボタン左上X座標(リスタートボタン右下X座標＋ボタン同士の間隔)
#define RESULT_TITLE_BUTTON_RX RESULT_TITLE_BUTTON_LX + RESULT_BUTTON_WIDTH    // タイトルボタン右下X座標(左上X座標＋ボタンの高さ)

class ResultScene : public SceneBase
{
private:
	int score;  // スコア
	ButtonState button[RESULT_BUTTON_NUM]; // ボタン情報
	int background_img;
	
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

private:
	// スコア描画処理
	void DrawScore() const;
	// ランキング描画処理
	void DrawRanking() const;
};