#pragma once

#include "../SceneBase.h"

// ボタン共通情報
#define RANKING_BUTTON_WIDTH   300  // ボタンの幅
#define RANKING_BUTTON_HEIGHT  70   // ボタンの高さ
#define RANKING_BUTTON_NUM 1        // ボタンの数
#define RANKING_BUTTON_LY  610                       // ボタン左上Y座標
#define RANKING_BUTTON_RY  RANKING_BUTTON_LY + RANKING_BUTTON_HEIGHT // ボタン右下Y座標

// タイトルボタン
#define RANKING_TITLE_BUTTON_LX 500 // タイトルボタン左上X座標(リスタートボタン右下X座標＋ボタン同士の間隔)
#define RANKING_TITLE_BUTTON_RX RANKING_TITLE_BUTTON_LX  + RANKING_BUTTON_WIDTH    // タイトルボタン右下X座標(左上X座標＋ボタンの高さ)

class RankingScene : public SceneBase
{
private:
	ButtonState button[RANKING_BUTTON_NUM]; // ボタン情報
	int background_img; // 背景画像
	int effect_img[2];  // キラキラエフェクト画像
	int effect_alpha[3]; // エフェクトの透明度
	int effect_num[3]; // エフェクトの番号
	int effect_reverse[3]; // エフェクトの透明度減らすか増やすか
	
public:
	// コンストラクタ
	RankingScene();
	// デストラクタ
	~RankingScene();

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
