#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObject.h"

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

#define MAX_PAGE_NUM 2

struct Vec2 {
	float x, y;
};

//{ DonutType::DONUT_BASIC, 15.0f, 0, "Resource/Images/gamemain/donut/donut1.png", 1 },
//{ DonutType::DONUT_COCONUT_CHOCOLATE,20.0f, 20, "Resource/Images/gamemain/donut/donut2.png",2 },
//{ DonutType::DONUT_HALF_CHOCOLATE,25.0f, 50, "Resource/Images/gamemain/donut/donut3.png",3 },
//{ DonutType::DONUT_STRAWBERRY,30.0f, 70, "Resource/Images/gamemain/donut/donut4.png",4 },
//{ DonutType::DONUT_CHOCOLATE,35.0f, 100, "Resource/Images/gamemain/donut/donut5.png",5 },
//{ DonutType::DONUT_FRENCH_CRULLER,45.0f, 200, "Resource/Images/gamemain/donut/donut6.png",6 },
//{ DonutType::DONUT_FRENCH_CRULLER_VAR,55.0f, 350, "Resource/Images/gamemain/donut/donut7.png",7 },
//{ DonutType::DONUT_PON_DE_RING,65.0f, 500, "Resource/Images/gamemain/donut/donut8.png",8 },
//{ DonutType::DONUT_PON_DE_RING_MATCHA,75.0f, 650, "Resource/Images/gamemain/donut/donut9.png",9 },
//{ DonutType::DONUT_PON_DE_RING_CHOCOLATE,85.0f, 800, "Resource/Images/gamemain/donut/donut10.png",10 },
//{ DonutType::DONUT_GOLDEN_CHOCOLATE,95.0f, 1000, "Resource/Images/gamemain/donut/donut11.png",11 }

class HelpScene : public SceneBase
{
private:
	ButtonState button[HELP_BUTTON_NUM]; // ボタン情報
	int background_img[MAX_PAGE_NUM];    // 背景画像
	int triangle_img;                    // 三角形ボタン画像
	int donut_img[MAX_DONUT_NUM];        // ドーナツ画像
	int donut_shadow_img[3];             // ドーナツの影画像
	int page_num;                        // 現在のページ番号
	bool triangle_collision;             // 三角形ボタンとプレイヤーが当たっているか？(true:当たっている false:当たっていない)

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

private:
	// 内積を求める処理
	float Dot(const Vec2& a, const Vec2& b);
	// 正規化処理
	Vec2 Normalize(const Vec2& v);
	// 辺から法線を作る(左法線)処理
	Vec2 GetNormal(const Vec2& a, const Vec2& b);
	// 多角形を軸に投影する処理
	void Project(const std::vector<Vec2>& poly, const Vec2& axis, float& minOut, float& maxOut);
	// SAT判定処理
	bool CheckSAT(const std::vector<Vec2>& polyA, const std::vector<Vec2>& polyB);
	// プレイヤーと三角の当たり判定処理
	bool TrianglePlayerCollision();
};