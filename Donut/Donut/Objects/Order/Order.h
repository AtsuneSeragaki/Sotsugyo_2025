#pragma once
// #include "../GameObject.h" // リリース時はこれ
#include "../Donuts/Donuts.h" // デバッグ時はこれ

#define ORDER_LX  50               // オーダーの枠X座標(左上)
#define ORDER_LY  260              // オーダーの枠Y座標(左上)
#define ORDER_RX  ORDER_LX + 300   // オーダーの枠X座標(右下)
#define ORDER_RY  680              // オーダーの枠Y座標(右下)
#define ORDER_MAX 4                // オーダーの数
#define DIFFICULTY_MAX 5           // 難易度MAXの数
#define FIRST_BOX_X -220.0f        // (アニメーション用)箱の初期X座標
#define MAX_BOX_X 30.0f            // (アニメーション用)箱の最終的なX座標
#define FIRST_DONUT_Y 60.0f        // (アニメーション用)ドーナツの初期Y座標
#define MAX_DONUT_Y 250.0f         // (アニメーション用)ドーナツの最終的なY座標
#define FIRST_STRING_SCALE 1.27    // (アニメーション用)文字の初期拡大率

class Order : public GameObject
{
private:
	DonutType order_list[ORDER_MAX]; // オーダーリスト(ドーナツ4種類)
	int order_num[ORDER_MAX];        // それぞれのオーダーの個数
	int difficulty;                  // 難易度
	int clear_timer;                 //	クリアの文字を出す時間
	int next_order_se;               // 次のオーダーに変わる時の効果音データ
	int donut_img[ORDER_MAX];        // ドーナツ画像
	int box_img;                     // 箱画像
	int donut_num;                   // アニメーションするドーナツの番号
	float donut_y;                   // アニメーションするドーナツのY座標
	float box_x;                     // 箱のX座標
	bool clear_anim_flg;             // クリアアニメーション中か？
	int clear_img;                   // クリア文字画像
	double clear_extend;             // クリア文字画像の大きさ
	bool box_moved_flg;              // 箱が動き終わったか？
	bool donut_anim_flg;             // ドーナツのアニメーションが終わったか？
	int clear_se[3];                 // クリアアニメーション効果音

public:
	// コンストラクタ
	Order();

	// デストラクタ
	~Order();

public:
	// 初期化処理
	virtual void Initialize() override;

	// 更新処理
	virtual void Update() override;

	// 描画処理
	virtual void Draw() const override;

	// 終了時処理
	virtual void Finalize() override;

public:
	// オーダーをランダムに生成する処理(引数：難易度(0～2))
	void SetRandomOrder(int difficulty);

	// ドーナツの数を減らす処理(引数：減らしたいドーナツの種類)
	void DecrementDonutNum(DonutType type);

	// オーダーにあるドーナツか判定(引数：ドーナツの種類　戻り値：0→オーダーにない 1→オーダーにある)
	int CheckDonutOrder(DonutType type);

	// オーダーにあるドーナツの個数を返す処理(引数：ドーナツの種類　戻り値：ドーナツの個数)
	int GetDonutOrderNum(DonutType type);

	// オーダーリストにあるドーナツ画像を設定
	void SetDonutImage();

	// オーダークリアした時のアニメーション処理
	void ClearAnim();

	// 箱の移動処理(クリアアニメーション)
	void ClearMoveBox();

	// ドーナツの移動処理(クリアアニメーション)
	void ClearDonutMove();

	// 文字のアニメーション処理(クリアアニメーション)
	void ClearStringAnim();

	// クリアアニメーションの変数を全てリセット
	void ClearAnimReset();
};
