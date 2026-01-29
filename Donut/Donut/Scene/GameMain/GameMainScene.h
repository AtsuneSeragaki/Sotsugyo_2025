#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Donuts/Donuts.h"
#include <vector>

#define GAMEMAIN_BUTTON_NUM 3  // ボタンの数

// ポーズボタン
#define PAUSE_WIDTH  100                  // ポーズボタンの幅
#define PAUSE_HEIGHT 35                   // ポーズボタンの高さ
#define PAUSE_LX 1170                     // ポーズボタン左上X座標
#define PAUSE_LY 10                       // ポーズボタン左上Y座標
#define PAUSE_RX PAUSE_LX + PAUSE_WIDTH   // ポーズボタン右下X座標(左上X座標＋ボタンの幅)
#define PAUSE_RY PAUSE_LY + PAUSE_HEIGHT  // ポーズボタン右下Y座標(左上Y座標＋ボタンの高さ)

// ポーズ画面のボタン
#define PAUSE_B1B2_WIDTH   300  // ポーズ画面のボタンの幅
#define PAUSE_B1B2_HEIGHT  100  // ポーズ画面のボタンの高さ
#define PAUSE_B1B2_SPACING 60   // ポーズ画面のボタン同士の間隔

#define PAUSE_B1B2_LY 340                               // ポーズ画面ボタン左上X座標
#define PAUSE_B1B2_RY PAUSE_B1B2_LY + PAUSE_B1B2_HEIGHT // ポーズ画面ボタン右下X座標(左上X座標＋ボタンの幅)

// ポーズ画面のボタン(続ける)
#define PAUSE_B1_LX 310                              // ポーズ画面ボタン「続ける」左上Y座標
#define PAUSE_B1_RX PAUSE_B1_LX + PAUSE_B1B2_WIDTH  // ポーズ画面ボタン「続ける」右下Y座標(左上Y座標＋ボタンの高さ)

// ポーズ画面のボタン(タイトルに戻る)
#define PAUSE_B2_LX PAUSE_B1_RX + PAUSE_B1B2_SPACING // ポーズ画面ボタン「タイトルに戻る」左上Y座標(「続ける」ボタンの右下Y座標＋ボタン同士の間隔)
#define PAUSE_B2_RX PAUSE_B2_LX + PAUSE_B1B2_WIDTH  // ポーズ画面ボタン「タイトルに戻る」右下Y座標(左上Y座標＋ボタンの高さ)

class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;       // ゲームオブジェクトクラスのオブジェクト
	class Player* player;                 // プレイヤークラスのオブジェクト
	class RankingData* ranking_data;      // ランキングデータクラスのオブジェクト
	std::vector<Donuts*> donut_collision; // プレイヤーと当たっているドーナツの情報
	std::vector<Donuts*> donut_list;      // 画面にある全てのドーナツ情報
	class Order* order;                   // オーダークラスのオブジェクト
	bool is_gameover;                     // ゲームオーバーフラグ(false:ゲームオーバーじゃない  true:ゲームオーバー)
	bool pause;                           // ポーズフラグ(false:ポーズ状態じゃない  true:ポーズ状態)
	static int score;                     // スコア
	int gameover_timer;                   // ゲームオーバーになってから、次の画面に遷移するまでの時間
	int marge_se;                         // ドーナツが合体する時の効果音データ
	int drop_se;                          // ドーナツを落とす時の効果音データ
	int delete_se;                        // ドーナツを消す時の効果音データ
	bool donut_creat_flg;                 // ドーナツを生成できるかフラグ（false:できない true:できる）
	int donut_creat_count;                // 次のドーナツを生成できる時間のカウント
	ButtonState button[GAMEMAIN_BUTTON_NUM];  // ボタン情報(0:ポーズボタン 1:「続ける」ボタン 2:「タイトルに戻る」ボタン)
	bool can_check_gameover;              // ゲームオーバー判定してもいいかフラグ（false:だめ true:してもいい）
	int donut_image[MAX_DONUT_NUM];
	bool is_donutgraphloaded;
	int circle_image;
	int background_img;
	int pause_img;
	static int delete_donut_count[6]; // 消したドーナツの数をカウント
	int gameover_y;
	int gameover_y_cnt;
	int gameover_se;

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

	int* GetDeleteDonutCount() { return delete_donut_count; }

private:
	// ドーナツ同士の当たり判定
	void CollisionDonuts();

	// ドーナツ同士が当たった時の処理(引数：ドーナツ1(仮)の情報、ドーナツ2(仮)の情報)
	void ResolveDonutCollision(Donuts* a,Donuts* b);

	// ドーナツとプレイヤーが当たった時の処理
	void HitDonutPlayerCollision();

	// 枠内にあるドーナツとプレイヤーの当たり判定処理(引数：当たり判定を取りたいドーナツの情報　戻り値：0→当たってない 1→当たっている)
	int CheckDonutPlayerCollision(Donuts* donut);

	// ポーズ状態の時の更新処理(戻り値：シーンタイプ)
	eSceneType PauseUpdate();

	// ポーズ状態の時の描画処理
	void PauseDraw() const;

	// スコア加算(引数：スコア加算するドーナツ情報)
	void AddScore(Donuts* donut);

	// ドーナツ落下処理(戻り値：シーンタイプ)
	void FallDonut();

	// ポーズボタンの当たり判定処理
	void PauseButtonCollision();

	// プレイヤーがクリックした時の処理(ポーズ状態じゃないとき)
	void OnPlayerClick();

	// ドーナツリストを作成する処理
	void MakeDonutList();

	// スコア描画処理
	void DrawScore()const;

	// ドーナツが枠からはみ出していないか確認する処理
	void CheckDonutOutOfFrame(Donuts* donut);

	// 次のドーナツを生成できる時間をカウントする処理
	void CountDonutCreateTime();

	// 引数で渡された場所のカウントを+1する
	void SetDonutCount(int donut_num) { delete_donut_count[donut_num]++; }

	// 引数で渡された場所のカウントを取得する
	int GetDonutCount(int donut_num) const { return delete_donut_count[donut_num]; }

	// ゲームメイン描画(基本)
	void DrawNormal() const;
};