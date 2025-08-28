#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Objects/Player/Player.h"
#include <vector>

// ポーズボタン
#define PAUSE_LX 1170             // ポーズボタン左上X座標
#define PAUSE_LY 10               // ポーズボタン左上Y座標
#define PAUSE_RX PAUSE_LX + 100   // ポーズボタン右下X座標(左上X座標＋ボタンの幅)
#define PAUSE_RY PAUSE_LY + 35    // ポーズボタン右下Y座標(左上Y座標＋ボタンの高さ)

// ポーズ画面のボタン
#define PAUSE_B1B2_WIDTH   300  // ポーズ画面のボタンの幅
#define PAUSE_B1B2_HEIGHT  100  // ポーズ画面のボタンの高さ
#define PAUSE_B1B2_SPACING 50   // ポーズ画面のボタン同士の間隔

#define PAUSE_B1B2_LX 500                               // ポーズ画面ボタン左上X座標
#define PAUSE_B1B2_RX PAUSE_B1B2_LX + PAUSE_B1B2_WIDTH  // ポーズ画面ボタン右下X座標(左上X座標＋ボタンの幅)

// ポーズ画面のボタン(続ける)
#define PAUSE_B1_LY 250                              // ポーズ画面ボタン「続ける」左上Y座標
#define PAUSE_B1_RY PAUSE_B1_LY + PAUSE_B1B2_HEIGHT  // ポーズ画面ボタン「続ける」右下Y座標(左上Y座標＋ボタンの高さ)

// ポーズ画面のボタン(タイトルに戻る)
#define PAUSE_B2_LY PAUSE_B1_RY + PAUSE_B1B2_SPACING // ポーズ画面ボタン「タイトルに戻る」左上Y座標(「続ける」ボタンの右下Y座標＋ボタン同士の間隔)
#define PAUSE_B2_RY PAUSE_B2_LY + PAUSE_B1B2_HEIGHT  // ポーズ画面ボタン「タイトルに戻る」右下Y座標(左上Y座標＋ボタンの高さ)

class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // ゲームオブジェクトクラスのオブジェクト
	class Player* player;            // プレイヤークラスのオブジェクト
	std::vector<Donuts*> donut_collision;   // プレイヤーと当たっているドーナツの情報
	class Order* order;              // オーダークラスのオブジェクト
	bool is_gameover;                // ゲームオーバーフラグ(false:ゲームオーバーじゃない  true:ゲームオーバー)
	bool pause;                      // ポーズフラグ(false:ポーズ状態じゃない  true:ポーズ状態)
	bool pause_collision;            // ポーズボタンとプレイヤーカーソルの当たり判定フラグ(false:当たっていない  true:当たっている)
	bool pause_b1_collision;         // ポーズ画面ボタン「続ける」とプレイヤーカーソルの当たり判定フラグ(false:当たっていない  true:当たっている)
	bool pause_b2_collision;         // ポーズ画面ボタン「タイトルに戻る」とプレイヤーカーソルの当たり判定フラグ(false:当たっていない  true:当たっている)
	static int score;                // スコア

public:
	// コンストラクタ
	GameMainScene();

	// デストラクタ
	~GameMainScene();

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

	// スコアを返す処理(戻り値：スコア)
	int GetScore(){ return score; }

private:
	// ドーナツ同士の当たり判定
	void CollisionDonuts();

	// ドーナツ同士が当たった時の処理(引数：ドーナツ1(仮)の情報、ドーナツ2(仮)の情報)
	void ResolveDonutCollision(class Donuts* a, class Donuts* b);

	// 枠内にあるドーナツとプレイヤーの当たり判定処理(戻り値：0→当たってない 1→当たっている)
	int CheckDonutPlayerCollision(class Donuts* donut);
};