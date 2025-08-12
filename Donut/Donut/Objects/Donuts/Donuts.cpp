#include "Donuts.h"
#include "DxLib.h"
#include <math.h>

// 全ドーナツの情報設定(変更不可)
DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
        { DonutType::DONUT_MINI_BASIC,        10.0f, 100, "images/donut_mini_basic.png" ,1},
        { DonutType::DONUT_MINI_VARIANT,      20.0f, 120, "images/donut_mini_variant.png",2 },
        { DonutType::DONUT_FRENCH_CRULLER,    30.0f, 150, "images/french_cruller.png" ,3},
        { DonutType::DONUT_FRENCH_CRULLER_VAR,40.0f, 160, "images/french_cruller_var.png",4 },
        { DonutType::DONUT_OLD_FASHIONED,     50.0f, 130, "images/old_fashioned.png" ,5},
        { DonutType::DONUT_OLD_FASHIONED_VAR, 60.0f, 140, "images/old_fashioned_var.png",6 },
        { DonutType::DONUT_GOLDEN_CHOCOLATE,  70.0f, 200, "images/golden_chocolate.png" ,7},
        { DonutType::DONUT_COCONUT_CHOCOLATE, 80.0f, 200, "images/coconut_chocolate.png" ,8},
        { DonutType::DONUT_HALF_CHOCOLATE,    90.0f, 170, "images/half_chocolate.png" ,9},
        { DonutType::DONUT_HALF_STRAWBERRY,   100.0f, 170, "images/half_strawberry.png" ,10},
        { DonutType::DONUT_PON_DE_RING,       110.0f, 180, "images/pon_de_ring.png",11 }
};

// テスト用ドーナツ情報(変更可)
//DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
//        { DonutType::DONUT_MINI_BASIC,        80.0f, 100, "images/donut_mini_basic.png" ,1},
//        { DonutType::DONUT_MINI_VARIANT,      90.0f, 120, "images/donut_mini_variant.png",2 },
//        { DonutType::DONUT_FRENCH_CRULLER,    100.0f, 150, "images/french_cruller.png" ,3},
//        { DonutType::DONUT_FRENCH_CRULLER_VAR,120.0f, 160, "images/french_cruller_var.png",4 },
//        { DonutType::DONUT_OLD_FASHIONED,     130.0f, 130, "images/old_fashioned.png" ,5},
//        { DonutType::DONUT_OLD_FASHIONED_VAR, 140.0f, 140, "images/old_fashioned_var.png",6 },
//        { DonutType::DONUT_GOLDEN_CHOCOLATE,  150.0f, 200, "images/golden_chocolate.png" ,7},
//        { DonutType::DONUT_COCONUT_CHOCOLATE, 160.0f, 200, "images/coconut_chocolate.png" ,8},
//        { DonutType::DONUT_HALF_CHOCOLATE,    170.0f, 170, "images/half_chocolate.png" ,9},
//        { DonutType::DONUT_HALF_STRAWBERRY,   180.0f, 170, "images/half_strawberry.png" ,10},
//        { DonutType::DONUT_PON_DE_RING,       190.0f, 180, "images/pon_de_ring.png",11 }
//};

// コンストラクタ
Donuts::Donuts(DonutType type)
{
    this->type = type;
    vx = 0.0f;
    vy = 0.0f;

    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(type)];
    r = info.size;
    landed = false;

    isMerged = false;
    isDead = false;

    donutList = nullptr;
}

// デストラクタ
Donuts::~Donuts()
{
}

// 初期化処理
void Donuts::Initialize()
{
}

// 更新処理
void Donuts::Update()
{
    isMerged = false;

    // 横方向の移動
    location.x += vx;

    // 壁で跳ね返り（画面サイズ: 640x480 を前提）
    if (location.x < 400.0f + r)
    {
        location.x = r;
        vx *= -0.3f;
    }
    if (location.x > 880.0f - r)
    {
        location.x = 880.0f - r;
        vx *= -0.3f;
    }

    // 着地中なら摩擦で減速
    if (landed)
    {
        vx *= 0.85f; // 摩擦減衰
        if (fabs(vx) < 0.1f)
        {
            vx = 0.0f;
        }
    }

    // ドーナツの枠はみ出し防止処理
    ClampToFrame(400.0f, 880.0f, 100.0f, 680.0f);
}

// 描画処理
void Donuts::Draw() const 
{
    // ドーナツ仮表示
    DrawCircleAA(location.x, location.y, r, 32, GetColor(255, 255, 0), TRUE);

    SetFontSize(20);
    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(type)];
   
    // ドーナツ番号表示
    DrawFormatString((int)location.x, (int)location.y - 3, 0x000000, "%d", info.number);
    // ドーナツ着地フラグ表示
    DrawFormatString((int)location.x, (int)location.y - 40, 0xffffff, "%d", landed);
}

// 終了時処理
void Donuts::Finalize()
{
}

// ドーナツの半径を返す処理(引数：ドーナツの種類　戻り値：半径)
float Donuts::GetDonutRadius(DonutType dtype)
{
    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(dtype)];
    return info.size;
}

// ドーナツの番号を返す処理(引数：ドーナツの種類　戻り値：番号)
int Donuts::GetDonutNumber(DonutType dtype)
{
    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(dtype)];
    return info.number;
}

// ドーナツ落下処理
void Donuts::FallDonut(const std::vector<Donuts*>& others)
{
    // もし既に着地していても、下に支えがないなら落下再開
    if (landed && !IsSupported(others)) 
    {
        landed = false;
    }

    if (landed) return;

    vy += 0.5f; // 重力
    location.y += vy;

    bool landedOnSomething = false;

    // 地面に着地したかチェック
    if (location.y + r >= 680.0f)
    {
        location.y = 680.0f - r;
        vy *= -0.15f;
        if (fabs(vy) < 1.0f) 
        {
            vy = 0.0f;
            landedOnSomething = true;
        }
    }

    // 他のドーナツの上に着地したかチェック
    for (Donuts* other : others) 
    {
        if (other == this) continue;

        float distX = (float)fabs(location.x - other->location.x);
        float distY = location.y - other->location.y;

        // 横方向は近く、縦方向は下にちょっと接触しているか？
        if(distX < (r + other->r) * 0.8f &&distY > 0 && distY < 5.0f)
        {
            // ドーナツの上に着地とみなす
            location.y = other->location.y - r - other->r;
            vy = 0.0f;
            landedOnSomething = true;
            break;
        }

        //float distCenter = sqrtf(distX * distX + distY * distY);
        //float threshold = r + other->r - 0.8f; // 少し余裕を持たせる

        //if (distCenter < threshold && location.y < other->location.y)
        //{
        //    // 接地処理
        //    location.y = other->location.y - r - other->r;
        //    vy = 0.0f;
        //    landedOnSomething = true;
        //    break;
        //}
    }

    if (landedOnSomething || IsSupported(others)) 
    {
        landed = true;
    }
}

// ドーナツの枠はみ出し防止処理
void Donuts::ClampToFrame(float left, float right, float top, float bottom)
{
    if (location.x - r < left) 
    {
        location.x = left + r;
        vx *= -0.5f;
    }
    if (location.x + r > right) 
    {
        location.x = right - r;
        vx *= -0.5f;
    }

    if (location.y - r < top)
    {
        location.y = top + r;
        vy *= -0.5f;
    }
    if (location.y + r > bottom) 
    {
        location.y = bottom - r;
        vy *= -0.6f;
    }
}

// どこかしらに支えられているか判定する処理
bool Donuts::IsSupported(const std::vector<Donuts*>& others)
{
    // 地面に接地している
    if (location.y + r >= 680.0f)
    {
        return true;
    }

    bool supportBelow = false;
    bool supportLeft = false;
    bool supportRight = false;
    bool supportLeftBelow = false;
    bool supportRightBelow = false;

    for (Donuts* other : others) 
    {
        if (other == this)
        {
            continue;
        }

        float dx = location.x - other->location.x;
        float dy = other->location.y - location.y;

        float distX = (float)fabs(dx);
        float distY = (float)fabs(location.y - other->location.y);
        float combinedRadius = r + other->r;

        // 真下に支えがあるかチェック
        if (distX < combinedRadius * 0.8f) 
        {
            float verticalGap = other->location.y - location.y;

            if (verticalGap > 0 && verticalGap < 5.0f) 
            {
                supportBelow = true;
            }
        }

        // 左右に支えがあるかチェック
        if (distY < combinedRadius * 0.8f) 
        {
            if (dx > 0 && dx < combinedRadius * 0.9f) 
            {
                supportLeft = true;
            }
            else if (dx < 0 && dx > -combinedRadius * 0.9f) 
            {
                supportRight = true;
            }
        }

        // 左下にドーナツがあるかチェック
        if (dx > combinedRadius * 0.3f && dx < combinedRadius * 1.1f && dy > 0 && dy < combinedRadius * 1.1f) 
        {
            supportLeftBelow = true;
        }

        // 右下にドーナツがあるかチェック
        if (dx < -combinedRadius * 0.3f && dx > -combinedRadius * 1.1f && dy > 0 && dy < combinedRadius * 1.1f) 
        {
            supportRightBelow = true;
        }
    }

    // 最終的な支え判定
    return supportBelow || (supportLeft && supportRight) || (supportLeftBelow && supportRightBelow);  // 両側にある時のみOK
}
