#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"

// ポーズボタン
#define PAUSE_LX 1170
#define PAUSE_LY 10
#define PAUSE_RX PAUSE_LX + 100
#define PAUSE_RY PAUSE_LY + 35

// ポーズ画面のボタン(続ける)
#define PAUSE_B1_LX 500
#define PAUSE_B1_LY 250
#define PAUSE_B1_RX PAUSE_B1_LX + 300
#define PAUSE_B1_RY PAUSE_B1_LY + 100

// ポーズ画面のボタン(タイトルに戻る)
#define PAUSE_B2_LX 500
#define PAUSE_B2_LY 400
#define PAUSE_B2_RX PAUSE_B2_LX + 300
#define PAUSE_B2_RY PAUSE_B2_LY + 100


class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // ゲームオブジェクトクラスのオブジェクト
	class Player* player;            // プレイヤークラスのオブジェクト
	class Order* order;              // オーダークラスのオブジェクト
	bool is_gameover;                // ゲームオーバーか？
	class Donuts* donut_collision;   // プレイヤーと当たっているドーナツの情報
	int score;                       // スコア
	bool pause;                      // ポーズフラグ
	bool pause_collision;            // ポーズボタンにプレイヤーカーソルが当たっているか？フラグ
	bool pause_b1_collision;         // ポーズ画面のボタン(続ける)にプレイヤーカーソルが当たっているか？フラグ
	bool pause_b2_collision;         // ポーズ画面のボタン(タイトルに戻る)にプレイヤーカーソルが当たっているか？フラグ

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

private:
	// ドーナツ同士の当たり判定
	void CollisionDonuts();

	// 当たった時の処理
	void ResolveDonutCollision(class Donuts* a, class Donuts* b);

	// 枠内にあるドーナツとプレイヤーの当たり判定処理(戻り値：0→当たってない 1→当たっている)
	void DonutPlayerCollision(class Donuts* donut);

	// プレイヤーカーソルとボタンの当たり判定
	int CheckPlayerButtonCollision(int left,int right,int top,int bottom);


};