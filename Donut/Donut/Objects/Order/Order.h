#pragma once
#include "../Donuts/Donuts.h"

#define ORDER_X  35
#define ORDER_Y  240
#define ORDER_WIDTH 330
#define ORDER_HEIGHT (680 - ORDER_Y)
#define ORDER_MAX 4

class Order : public GameObject
{
private:
	DonutType order_list[ORDER_MAX]; // オーダーリスト(ドーナツ4種類)
	int order_num[ORDER_MAX];        // それぞれのオーダーの数

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
	// オーダーをランダムに生成(引数：難易度(0～2))
	void SetRandomOrder(int difficulty);

private:
};
