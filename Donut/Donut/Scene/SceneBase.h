#pragma once

#include "../Utility/Vector2D.h"
#include <vector>
#include <string>

#define WINDOW_WIDTH  1280 // 画面の幅
#define WINDOW_HEIGHT 720  // 画面の高さ

enum class eSceneType
{
	eTitle,
	eGameMain,
	eResult,
	eHelp,
	eRanking,
	eEnd,
	eNone,
};

struct ButtonStyle
{
	int xspacing;
	int yspacing;
	int string_color;
	double xscale;
	double yscale;
};

struct ButtonState 
{
	int lx, rx, ly, ry;
	bool collision = false;
	eSceneType targetScene; // クリックで遷移するシーン
	ButtonStyle style;
	const char* label;      // ボタンに表示する文字列
};

class SceneBase
{
protected:
	int background_image;        // 背景画像データ
	int button_se_handle;        // ボタンをクリックした時の音源データ
	int frame_count;             // フレームカウント
	bool can_click;              // クリックフラグ(false:クリックできない  true:クリックできる)
	int button_string_color;     // ボタンの文字のカラーコード
	int button_string_yspacing;  // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

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
	// 現在のシーン情報を返す処理
	virtual eSceneType  GetNowSceneType() const = 0;

	// プレイヤーカーソルとボタンの当たり判定処理(引数：当たり判定を取りたいボタンの情報　戻り値：0→当たってない 1→当たっている)
	int CheckPlayerButtonCollision(int left, int right, int top, int bottom);

	// ボタン描画処理(引数：ボタンの数)
	void DrawButton(int button_num,const ButtonState* button) const;

	// ボタンの効果音を鳴らす処理
	void PlayButtonSound();
};