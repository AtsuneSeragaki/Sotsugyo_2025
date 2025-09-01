#include "Donuts.h"
#include "DxLib.h"
#include <math.h>

// 全ドーナツの情報設定(変更不可)
//DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
//        { DonutType::DONUT_MINI_BASIC,        10.0f, 0, "images/donut_mini_basic.png" ,1},
//        { DonutType::DONUT_MINI_VARIANT,      20.0f, 20, "images/donut_mini_variant.png",2 },
//        { DonutType::DONUT_FRENCH_CRULLER,    30.0f, 50, "images/french_cruller.png" ,3},
//        { DonutType::DONUT_FRENCH_CRULLER_VAR,40.0f, 70, "images/french_cruller_var.png",4 },
//        { DonutType::DONUT_OLD_FASHIONED,     50.0f, 100, "images/old_fashioned.png" ,5},
//        { DonutType::DONUT_OLD_FASHIONED_VAR, 60.0f, 150, "images/old_fashioned_var.png",6 },
//        { DonutType::DONUT_GOLDEN_CHOCOLATE,  70.0f, 200, "images/golden_chocolate.png" ,7},
//        { DonutType::DONUT_COCONUT_CHOCOLATE, 80.0f, 250, "images/coconut_chocolate.png" ,8},
//        { DonutType::DONUT_HALF_CHOCOLATE,    90.0f, 300, "images/half_chocolate.png" ,9},
//        { DonutType::DONUT_HALF_STRAWBERRY,   100.0f, 350, "images/half_strawberry.png" ,10},
//        { DonutType::DONUT_PON_DE_RING,       110.0f, 400, "images/pon_de_ring.png",11 }
//};

// テスト用ドーナツ情報(変更可)
DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
        { DonutType::DONUT_MINI_BASIC,        10.0f, 100, "images/donut_mini_basic.png" ,1},
        { DonutType::DONUT_MINI_VARIANT,      20.0f, 120, "images/donut_mini_variant.png",2 },
        { DonutType::DONUT_FRENCH_CRULLER,    30.0f, 150, "images/french_cruller.png" ,3},
        { DonutType::DONUT_FRENCH_CRULLER_VAR,40.0f, 160, "images/french_cruller_var.png",4 },
        { DonutType::DONUT_OLD_FASHIONED,     50.0f, 130, "images/old_fashioned.png" ,5},
        { DonutType::DONUT_OLD_FASHIONED_VAR, 60.0f, 140, "images/old_fashioned_var.png",6 },
        { DonutType::DONUT_GOLDEN_CHOCOLATE,  80.0f, 200, "images/golden_chocolate.png" ,7},
        { DonutType::DONUT_COCONUT_CHOCOLATE, 100.0f, 200, "images/coconut_chocolate.png" ,8},
        { DonutType::DONUT_HALF_CHOCOLATE,    120.0f, 170, "images/half_chocolate.png" ,9},
        { DonutType::DONUT_HALF_STRAWBERRY,   140.0f, 170, "images/half_strawberry.png" ,10},
        { DonutType::DONUT_PON_DE_RING,       160.0f, 180, "images/pon_de_ring.png",11 }
};

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
    player_collision = false;
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
    ClampToFrame((float)FRAME_LX, (float)FRAME_RX, (float)FRAME_LY, (float)FRAME_RY);
}

// 描画処理
void Donuts::Draw() const 
{
    // ドーナツ仮表示
    if (player_collision)
    {
        // ドーナツを暗くする
        // 描画輝度のセット
        SetDrawBright(128, 128, 128);
        DrawCircleAA(location.x, location.y, r, 32, 0xD6A15D, TRUE);
        // 描画輝度を元に戻す
        SetDrawBright(255, 255, 255);
    }
    else
    {
       DrawCircleAA(location.x, location.y, r, 32, 0xD6A15D, TRUE);
    }
   
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

// ドーナツのスコアを返す処理(引数：ドーナツの種類　戻り値：スコア)
int Donuts::GetDonutScore(DonutType dtype)
{
    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(dtype)];
    return info.score;
}

// ドーナツ落下処理
void Donuts::FallDonut(const std::vector<Donuts*>& others)
{
    // 重力適用
    vy += 0.5f;
    location.y += vy;
    location.x += vx;

    landed = false;
    for (Donuts* other : others)
    {
        if (other == this) continue;

        float combinedRadius = r + other->r;
        float distSq = (location.x - other->location.x) * (location.x - other->location.x) + (location.y - other->location.y) * (location.y - other->location.y);

        // 衝突判定
        if (distSq < combinedRadius * combinedRadius)
        {
            // 物理的な反発処理
            HandleCollision(other);
        }
    }

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
    }

    if (landedOnSomething || IsSupported(others)) 
    {
        landed = true;
    }

    // 地面への着地判定と反発
    if (location.y + r >= 680.0f)
    {
        location.y = 680.0f - r;
        vy *= -0.3f; // 地面への反発
        vx *= 0.85f; // 地面摩擦
        if (fabs(vy) < 1.0f)
        {
            vy = 0.0f;
            landed = true;
        }
    }
}

// 衝突処理 (弾性衝突)
void Donuts::HandleCollision(Donuts* other)
{
    float combinedRadius = r + other->r;
    float dx = location.x - other->location.x;
    float dy = location.y - other->location.y;
    float distance = sqrtf(dx * dx + dy * dy);

    // めり込み防止
    if (distance < combinedRadius)
    {
        float overlap = combinedRadius - distance;
        float totalMass = r + other->r;
        float massRatioA = other->r / totalMass;
        float massRatioB = r / totalMass;

        // めり込みを解消するために位置をずらす
        location.x += overlap * (dx / distance) * massRatioA;
        location.y += overlap * (dy / distance) * massRatioA;
        other->location.x -= overlap * (dx / distance) * massRatioB;
        other->location.y -= overlap * (dy / distance) * massRatioB;
    }

    // 速度を分解して反発を計算
    float nx = dx / distance;
    float ny = dy / distance;
    float tangentx = -ny;
    float tangenty = nx;

    float v1n = vx * nx + vy * ny;
    float v1t = vx * tangentx + vy * tangenty;
    float v2n = other->vx * nx + other->vy * ny;
    float v2t = other->vx * tangentx + other->vy * tangenty;

    // 質量を考慮した速度の交換
    float new_v1n = (v1n * (r - other->r) + 2 * other->r * v2n) / (r + other->r);
    float new_v2n = (v2n * (other->r - r) + 2 * r * v1n) / (r + other->r);

    // 新しい速度を元のベクトルに戻す
    vx = new_v1n * nx + v1t * tangentx;
    vy = new_v1n * ny + v1t * tangenty;
    other->vx = new_v2n * nx + v2t * tangentx;
    other->vy = new_v2n * ny + v2t * tangenty;

    // 弾性反発係数と摩擦を適用
    vx *= 0.85f; // 反発後の減速
    vy *= 0.85f;
    other->vx *= 0.85f;
    other->vy *= 0.85f;
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
        // 上の壁にはぶつからないようにする（ゲームのルール上）
    }
    if (location.y + r > bottom) 
    {
        location.y = bottom - r;
        vy *= -0.5f;
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

    // 他のドーナツに支えられているか
    for (Donuts* other : others)
    {
        if (other == this) continue;

        float combinedRadius = r + other->r;
        float distSq = (location.x - other->location.x) * (location.x - other->location.x) + (location.y - other->location.y) * (location.y - other->location.y);

        // 衝突しているか、または非常に近いかをチェック
        if (distSq < combinedRadius * combinedRadius * 1.1) // 少し余裕を持たせる
        {
            // 真下にいるかをチェック
            if (location.y < other->location.y)
            {
                // this ドーナツの底が other ドーナツの上にあるか
                if (location.y + r > other->location.y - other->r && fabs(location.x - other->location.x) < combinedRadius * 0.9)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
