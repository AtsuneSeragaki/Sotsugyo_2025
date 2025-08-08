#include "Order.h"
#include "DxLib.h"

Order::Order()
{
	order_list[0] = DonutType::DONUT_PON_DE_RING;
	order_list[1] = DonutType::DONUT_HALF_STRAWBERRY;
	order_list[2] = DonutType::DONUT_HALF_CHOCOLATE;
	order_list[3] = DonutType::DONUT_COCONUT_CHOCOLATE;

	for (int i = 0; i < ORDER_MAX; i++)
	{
		order_num[i] = 1;
	}
}

Order::~Order()
{
}

void Order::Initialize()
{
}

void Order::Update()
{
}

void Order::Draw() const
{
	// オーダーの枠を表示
	DrawBox(ORDER_X, ORDER_Y, ORDER_X + ORDER_WIDTH, ORDER_Y + ORDER_HEIGHT, 0xffffff, TRUE);
	SetFontSize(20);
	DrawString(ORDER_X + 130, ORDER_Y + 15, "オーダー", 0x000000);

	for (int i = 0; i < ORDER_MAX; i++)
	{
		DrawCircle(ORDER_X + 95, ORDER_Y + 95 + 95 * i, 40, 0xffff00, TRUE);
		Donuts* donut = new Donuts(order_list[i]);
		SetFontSize(20);
		DrawFormatString(ORDER_X + 90, ORDER_Y + 95 + 95 * i + 10, 0x000000, "%d", donut->GetDonutNumber(order_list[i]));
		SetFontSize(40);
		DrawFormatString(ORDER_X + 160, ORDER_Y + 80 + 95 * i, 0x000000, "x %d個", order_num[i]);
	}
}

void Order::Finalize()
{
}
