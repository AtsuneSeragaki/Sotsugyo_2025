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
	int score;  // スコア
	ButtonState button[RESULT_BUTTON_NUM]; // ボタン情報
	int background_img; // 背景画像
	int line_img; // 波線画像
	int receipt_img; // レシート画像

	float receipt_y; // レシートY座標

	int donut_img[MAX_DONUT_NUM]; // ドーナツ画像
	float donut1_x;  // 落下ドーナツ（左側）のX座標
	float donut1_y;  // 落下ドーナツ（左側）のY座標
	float donut2_x;  // 落下ドーナツ（右側）のX座標
	float donut2_y;  // 落下ドーナツ（右側）のY座標
	double rotation1;  // 落下ドーナツ（左側）の角度
	double rotation2;  // 落下ドーナツ（右側）の角度
	int donut_number[2]; // 落下ドーナツの種類
	int donut_count[6]; // 消したドーナツの数をカウント
	
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
	// 背景でドーナツを流す
	void DrawDonut() const;
	// ドーナツの落下処理
	void MoveDonut();
};