#pragma once
#include "../Donuts/Donuts.h"

#define ORDER_LX  50               // オーダーの枠X座標(左上)
#define ORDER_LY  260              // オーダーの枠Y座標(左上)
#define ORDER_RX  ORDER_LX + 300   // オーダーの枠X座標(右下)
#define ORDER_RY  680              // オーダーの枠Y座標(右下)
#define ORDER_MAX 4                // オーダーの数
#define DIFFICULTY_MAX 5           // 難易度MAXの数            

class Order : public GameObject
{
private:
	DonutType order_list[ORDER_MAX]; // オーダーリスト(ドーナツ4種類)
	int order_num[ORDER_MAX];        // それぞれのオーダーの個数
	bool complete_order;             // オーダー全てクリアしたか？フラグ
	int difficulty;                  // 難易度
	int clear_timer;                 //	クリアの文字を出す時間

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

private:
};
