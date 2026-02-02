#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObject.h"

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
	ButtonState button[RESULT_BUTTON_NUM]; // ボタン情報
	int score;                    // スコア
	int background_img;           // 背景画像
	int line_img;                 // 波線画像
	int receipt_img;              // レシート画像
	float receipt_y;              // レシートY座標
	int donut_img[MAX_DONUT_NUM]; // ドーナツ画像
	int donut_count[6];           // 消したドーナツの数をカウント
	int receipt_se;               // レシート効果音
	bool receipt_se_flg;          // レシート効果音流れているか？(true:流れている false:流れていない)
	char time_buf[64];            // 現在の日時データ
	int rank_img[4];              // ランク画像
	double rank_scale;            // ランク画像拡大率
	int rank_se;                  // ランク効果音
	int high_score_img;           // ハイスコア画像
	bool high_score_flg;          // ハイスコアか？(ture:ハイスコア false:ハイスコアじゃない)
	double high_score_scale;      // ハイスコア画像拡大率
	bool rank_moved_flg;          // ランクアニメーションが終わったか？(true:終わった false:終わってない)
	bool high_score_moved_flg;    // ハイスコアアニメーションが終わったか？(true:終わった false:終わってない)
	bool receipt_moved_flg;       // レシートアニメーションが終わったか？(true:終わった false:終わってない)
	
public:
	// コンストラクタ
	ResultScene(int score,int* delete_donut_count);
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
	// 現在の日時を取得する処理
	void GetNowTime();
	// レシートアニメーション処理
	void ReceiptAnim();
	// ランクアニメーション処理
	void RankAnim();
	// ハイスコアアニメーション処理
	void HighScoreAnim();
};