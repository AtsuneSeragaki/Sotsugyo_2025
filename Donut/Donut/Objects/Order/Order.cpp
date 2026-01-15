#include "Order.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include <random>
#include <cstdio>
#include "DxLib.h"

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

    SetDonutImage();
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
    //DrawBox(ORDER_LX, ORDER_LY, ORDER_RX, ORDER_RY, 0xffffff, TRUE);

    //// 枠の太さ
    //int line_width = 3;
    //// 枠描画(枠を太くするために複数描画)
    //for (int j = 0; j < line_width; j++)
    //{
    //    DrawBox(ORDER_LX - j, ORDER_LY - j, ORDER_RX + j, ORDER_RY + j, 0xA67C52, FALSE);
    //}

    //FontManager::Draw(ORDER_LX + 105, ORDER_LY + 13, 0.3, 0.3, 0x5C4630, "ORDER");

    if (complete_order && clear_timer <= 80)
    {// オーダーをクリアした時

        FontManager::DrawStr(ORDER_LX + 15, ORDER_LY + 165, 1.0, 1.0, 0xff5555, "Clear!");
    }
    else
    {// それ以外

        //float base_radius = 46.5; // 元画像(93x93)の半径
        float base_radius = 296.5; // 元画像(288x288)の半径
        double scale = 40.0 / (double)base_radius; // 画像の拡大率

        // オーダーのドーナツを表示
        for (int i = 0; i < ORDER_MAX; i++)
        {
            // ドーナツ表示
            DrawRotaGraph2F((float)ORDER_LX + 95.0f, (float)ORDER_LY + 95.0f + 90.0f * i, base_radius, base_radius, scale, 0.0, donut_img[i], TRUE);
            
            // ドーナツの種類表示
            /*Donuts* donut = new Donuts(order_list[i]);
            SetFontSize(20);
            DrawFormatString(ORDER_LX + 107, ORDER_LY + 80 + 90 * i + 10, 0x5C4630, "%d", donut->GetDonutNumber(order_list[i]));*/

            // スコアを文字列に変換
            char buf[16];
            sprintf_s(buf, sizeof(buf), "x %d", order_num[i]);

            // ドーナツの個数を表示
            FontManager::DrawNum(ORDER_LX + 157, ORDER_LY + 75 + 90 * i, 0.45, 0.45, 0x5C4630, buf);
        }
    }
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
        DonutType::DONUT_FRENCH_CRULLER,
        DonutType::DONUT_FRENCH_CRULLER_VAR,
        DonutType::DONUT_PON_DE_RING,
        DonutType::DONUT_PON_DE_RING_MATCHA,
        DonutType::DONUT_PON_DE_RING_CHOCOLATE,
        DonutType::DONUT_GOLDEN_CHOCOLATE,
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
    else if (difficulty == 2) { min_index = 1; max_index = 4; min_count = 1; max_count = 2; }
    else if (difficulty == 3) { min_index = 2; max_index = 5; min_count = 1; max_count = 1; }
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
            case DonutType::DONUT_FRENCH_CRULLER: return 0;
            case DonutType::DONUT_FRENCH_CRULLER_VAR:  return 1;
            case DonutType::DONUT_PON_DE_RING: return 2;
            case DonutType::DONUT_PON_DE_RING_MATCHA:    return 3;
            case DonutType::DONUT_PON_DE_RING_CHOCOLATE:   return 4;
            case DonutType::DONUT_GOLDEN_CHOCOLATE:       return 5;
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

    SetDonutImage();
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

void Order::SetDonutImage()
{
    ResourceManager* rm = ResourceManager::GetInstance();

    std::vector<int> tmp;

    // 画像読み込み
    for (int i = 0; i < ORDER_MAX; i++)
    {
        const DonutInfo& info = g_DonutInfoTable[(int)order_list[i]];
        tmp = rm->GetImages(info.image_path);
        donut_img[i] = tmp[0];
    }
}
