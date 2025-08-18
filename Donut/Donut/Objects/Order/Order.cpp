#include "Order.h"
#include "DxLib.h"
#include <random>

Order::Order()
{
    // オーダーを設定
    SetRandomOrder(0);
}

Order::~Order()
{
}

void Order::Initialize()
{
}

void Order::Update()
{
    // オーダーのドーナツの個数が全て0になったらクリアしたことにする
    if (order_num[0] <= 0 && order_num[1] <= 0 && order_num[2] <= 0 && order_num[3] <= 0)
    {
        complete_order = true;
    }
}

void Order::Draw() const
{
	// オーダーの枠を表示
	DrawBox(ORDER_LX, ORDER_LY, ORDER_RX, ORDER_RY, 0xffffff, TRUE);
	SetFontSize(20);
	DrawString(ORDER_LX + 115, ORDER_LY + 15, "オーダー", 0x000000);

    // オーダーのドーナツを表示
	for (int i = 0; i < ORDER_MAX; i++)
	{
        // ドーナツ表示
		DrawCircle(ORDER_LX + 85, ORDER_LY + 85 + 95 * i, 40, 0xffff00, TRUE);
		Donuts* donut = new Donuts(order_list[i]);
		SetFontSize(20);
		DrawFormatString(ORDER_LX + 80, ORDER_LY + 85 + 95 * i + 10, 0x000000, "%d", donut->GetDonutNumber(order_list[i]));
		
        // ドーナツの個数を表示
        SetFontSize(40);
		DrawFormatString(ORDER_LX + 150, ORDER_LY + 70 + 95 * i, 0x000000, "x %d個", order_num[i]);
	}
}

void Order::Finalize()
{

}

// オーダーをランダムに生成(引数：難易度(0～2))
void Order::SetRandomOrder(int difficulty)
{
    // 難易度に応じた選択可能なインデックス数
    int available_types = Clamp(difficulty + 4, 4, 6); // 4〜6種類から選べる

    DonutType menu_list[6] =
    {
        DonutType::DONUT_OLD_FASHIONED_VAR,
        DonutType::DONUT_GOLDEN_CHOCOLATE,
        DonutType::DONUT_COCONUT_CHOCOLATE,
        DonutType::DONUT_HALF_CHOCOLATE,
        DonutType::DONUT_HALF_STRAWBERRY,
        DonutType::DONUT_PON_DE_RING
    };

    // オーダークリアをリセット
    complete_order = false;

    // シャッフル用にコピーを作成
    std::vector<DonutType> shuffled_menu(menu_list, menu_list + available_types);

    // シャッフル
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(shuffled_menu.begin(), shuffled_menu.end(), gen);

    // 最初の4つを order_list に設定
    for (int i = 0; i < ORDER_MAX; ++i)
    {
        order_list[i] = shuffled_menu[i];
    }

    // 難易度に応じた個数の範囲を設定
    int min_count = 1;
    int max_count = 2;

    switch (difficulty)
    {
    case 0:
        min_count = 1;
        max_count = 1;
        break;
    case 1:
        min_count = 1;
        max_count = 2;
        break;
    case 2:
    default:
        min_count = 1;
        max_count = 2;
        break;
    }

    // 個数をランダムに設定
    for (int i = 0; i < ORDER_MAX; ++i)
    {
        order_num[i] = min_count + gen() % (max_count - min_count + 1);
    }

    // 難易度順に並べ替え（menu_list のインデックスが大きい順）
    struct OrderItem 
    {
        DonutType type;
        int count;
    };

    // ペア構造でまとめる
    std::vector<OrderItem> items;
    for (int i = 0; i < ORDER_MAX; ++i) 
    {
        items.push_back({ order_list[i], order_num[i] });
    }

    // DonutType の menu_list 添え字を使ってソート
    auto get_index_in_menu = [](DonutType type) -> int 
        {
            switch (type)
            {
                case DonutType::DONUT_OLD_FASHIONED_VAR: return 0;
                case DonutType::DONUT_GOLDEN_CHOCOLATE:  return 1;
                case DonutType::DONUT_COCONUT_CHOCOLATE: return 2;
                case DonutType::DONUT_HALF_CHOCOLATE:    return 3;
                case DonutType::DONUT_HALF_STRAWBERRY:   return 4;
                case DonutType::DONUT_PON_DE_RING:       return 5;
                default: return -1; // 安全のため
            }
        };

    std::sort(items.begin(), items.end(), [&](const OrderItem& a, const OrderItem& b)
        {
            return get_index_in_menu(a.type) > get_index_in_menu(b.type); // 降順
        });

    // 結果を order_list / order_num に戻す
    for (int i = 0; i < ORDER_MAX; ++i) 
    {
        order_list[i] = items[i].type;
        order_num[i] = items[i].count;
    }
}

// ドーナツの数を減らす
void Order::DecrementDonutNum(DonutType type)
{
    int num = 0;

    // 減らすドーナツの要素番号を探す
    for (int i = 0; i < ORDER_MAX; i++)
    {
        if (order_list[i] == type)
        {
            num = i;
            break;
        } 
    }

    // 残り個数が0より大きかったら、デクリメントする
    if (order_num[num] > 0) 
    {
        order_num[num]--;
    }
}

int Order::GetDonutOrder(DonutType type)
{
    for (int i = 0; i < ORDER_MAX; i++)
    {
        if (order_list[i] == type)
        {
            return 1;
        }
    }

    return 0;
}

int Order::GetDonutOrderNum(DonutType type)
{
    for (int i = 0; i < ORDER_MAX; i++)
    {
        if (order_list[i] == type)
        {
            return order_num[i];
        }
    }

    return 0;
}
