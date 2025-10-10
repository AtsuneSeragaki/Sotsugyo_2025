#include "Order.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include <random>

// コンストラクタ
Order::Order()
{
    difficulty = 0;
    // オーダーを設定
    SetRandomOrder(difficulty);
    complete_order = false;
    clear_timer = 0;

    ResourceManager* rm = ResourceManager::GetInstance();
    clear_se = rm->GetSounds("Resource/Sounds/GameMain/clear_se.mp3");

    next_order_se = rm->GetSounds("Resource/Sounds/button_se.mp3");
}

// デストラクタ
Order::~Order()
{
}

// 初期化処理
void Order::Initialize()
{
    difficulty = 0;
    // オーダーを設定
    SetRandomOrder(difficulty);
    complete_order = false;
    clear_timer = 0;
}

// 更新処理
void Order::Update()
{
    // オーダーのドーナツの個数が全て0になったらクリアしたことにする
    if (order_num[0] <= 0 && order_num[1] <= 0 && order_num[2] <= 0 && order_num[3] <= 0)
    {
        complete_order = true;
    }

    // オーダーを全てクリアしたら、次のオーダーを設定
    if (complete_order)
    {
        if (clear_timer <= 80)
        {
            if (clear_timer == 0)
            {
                PlaySoundMem(clear_se, DX_PLAYTYPE_BACK, TRUE);
            }

            clear_timer++;
        }
        else
        {
            // 難易度MAXじゃなかったら、難易度を1上げる
            if (difficulty < DIFFICULTY_MAX)
            {
                difficulty++;
            }

            SetRandomOrder(difficulty);

            //PlaySoundMem(next_order_se, DX_PLAYTYPE_BACK, TRUE);

            clear_timer = 0;
        }
    }
}

// 描画処理
void Order::Draw() const
{
	// オーダーの枠を表示
	DrawBox(ORDER_LX, ORDER_LY, ORDER_RX, ORDER_RY, 0xffffff, TRUE);
	SetFontSize(20);
	DrawString(ORDER_LX + 130, ORDER_LY + 15, "ORDER", 0x000000);

    // オーダーのドーナツを表示
	for (int i = 0; i < ORDER_MAX; i++)
	{
        // ドーナツ表示
		DrawCircle(ORDER_LX + 110, ORDER_LY + 85 + 95 * i, 40, 0xD6A15D, TRUE);
		Donuts* donut = new Donuts(order_list[i]);
		SetFontSize(20);
		DrawFormatString(ORDER_LX + 105, ORDER_LY + 85 + 95 * i + 10, 0x000000, "%d", donut->GetDonutNumber(order_list[i]));
		
        // ドーナツの個数を表示
        SetFontSize(40);
		DrawFormatString(ORDER_LX + 170, ORDER_LY + 70 + 95 * i, 0x000000, "x %d", order_num[i]);
	}

    if (complete_order && clear_timer <= 80)
    {
        SetFontSize(80);
        DrawString(ORDER_LX + 33, ORDER_LY + 170, "Clear!", 0xff5555);
    }

    /*SetFontSize(20);
    DrawFormatString(0, 100, 0x000000, "%dlevel", difficulty + 1);*/

}

// 終了時処理
void Order::Finalize()
{

}

// オーダーをランダムに生成(引数：難易度(0～2))
void Order::SetRandomOrder(int difficulty)
{
    // 全ドーナツ
    DonutType all_menu[6] =
    {
        DonutType::DONUT_OLD_FASHIONED_VAR,
        DonutType::DONUT_GOLDEN_CHOCOLATE,
        DonutType::DONUT_COCONUT_CHOCOLATE,
        DonutType::DONUT_HALF_CHOCOLATE,
        DonutType::DONUT_HALF_STRAWBERRY,
        DonutType::DONUT_PON_DE_RING
    };

    // デバック用簡単版
    /*DonutType all_menu[6] =
    {
        DonutType::DONUT_MINI_BASIC,
        DonutType::DONUT_MINI_VARIANT,
        DonutType::DONUT_FRENCH_CRULLER,
        DonutType::DONUT_FRENCH_CRULLER_VAR,
        DonutType::DONUT_OLD_FASHIONED,
        DonutType::DONUT_OLD_FASHIONED_VAR,
    };*/
   

    // 難易度ごとの使用可能範囲・個数幅
    int min_index = 0, max_index = 5;
    int min_count = 1, max_count = 1;

    if (difficulty <= 0) { min_index = 0; max_index = 3; min_count = 1; max_count = 1; }
    else if (difficulty == 1) { min_index = 1; max_index = 4; min_count = 1; max_count = 1; }
    else if (difficulty == 2) { min_index = 1; max_index = 4; min_count = 1; max_count = 1; }
    else if (difficulty == 3) { min_index = 2; max_index = 5; min_count = 1; max_count = 2; }
    else if (difficulty == 4) { min_index = 2; max_index = 5; min_count = 1; max_count = 2; }
    else                      { min_index = 2; max_index = 5; min_count = 2; max_count = 3; }

    int available_types = max_index - min_index + 1;

    complete_order = false;

    // 使用可能な種類だけコピー
    std::vector<DonutType> menu_vec(all_menu + min_index, all_menu + max_index + 1);

    // シャッフル
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(menu_vec.begin(), menu_vec.end(), gen);

    // ORDER_MAX個選択（種類が少ない場合はループ）
    for (int i = 0; i < ORDER_MAX; ++i)
        order_list[i] = menu_vec[i % available_types];

    // 個数をランダム設定
    for (int i = 0; i < ORDER_MAX; ++i)
        order_num[i] = min_count + gen() % (max_count - min_count + 1);

    // 難易度順に並べ替え
    struct OrderItem { DonutType type; int count; };
    std::vector<OrderItem> items;
    for (int i = 0; i < ORDER_MAX; ++i)
        items.push_back({ order_list[i], order_num[i] });

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
            default: return -1;
            }
        };

    // デバック用簡単版
   /* auto get_index_in_menu = [](DonutType type) -> int
        {
            switch (type)
            {
            case DonutType::DONUT_MINI_BASIC:         return 0;
            case DonutType::DONUT_MINI_VARIANT:       return 1;
            case DonutType::DONUT_FRENCH_CRULLER:     return 2;
            case DonutType::DONUT_FRENCH_CRULLER_VAR: return 3;
            case DonutType::DONUT_OLD_FASHIONED:      return 4;
            case DonutType::DONUT_OLD_FASHIONED_VAR:  return 5;
            default: return -1;
            }
        };*/

    std::sort(items.begin(), items.end(), [&](const OrderItem& a, const OrderItem& b)
        {
            return get_index_in_menu(a.type) > get_index_in_menu(b.type);
        });

    for (int i = 0; i < ORDER_MAX; ++i)
    {
        order_list[i] = items[i].type;
        order_num[i] = items[i].count;
    }
}

// ドーナツの数を減らす処理(引数：減らしたいドーナツの種類)
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

// オーダーにあるドーナツか判定(引数：ドーナツの種類　戻り値：0→オーダーにない 1→オーダーにある)
int Order::CheckDonutOrder(DonutType type)
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

// オーダーにあるドーナツの個数を返す処理(引数：ドーナツの種類　戻り値：ドーナツの個数)
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
