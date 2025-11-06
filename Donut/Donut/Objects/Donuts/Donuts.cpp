#include "Donuts.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include <math.h>

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

    player_collision = false;

    landedOnSomething = false;

    ResourceManager* rm = ResourceManager::GetInstance();
    std::vector<int> tmp;
    tmp = rm->GetImages(g_DonutInfoTable[0].image_path);
    donut_img[0] = tmp[0];

    rotation = 0.0;
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

    if (!landed)
    {
        // 転がり中に回転を更新
        rotation += vx / r;  // vxに応じて角度を加算（rが大きいとゆっくり回転）

        if (rotation > DX_TWO_PI)
        {
            rotation -= DX_TWO_PI;
        }
    }
    else
    { // 着地中なら摩擦で減速
        
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
    float base_radius = 46.5; // 元画像(93x93)の半径
    double scale = (double)r / (double)base_radius; // 画像の拡大率

    // ドーナツ仮表示
    if (player_collision)
    {
        // ドーナツを暗くする
        // 描画輝度のセット
        SetDrawBright(128, 128, 128);
        DrawRotaGraph2F(location.x, location.y, base_radius, base_radius, scale,rotation, donut_img[0], TRUE);
        // 描画輝度を元に戻す
        SetDrawBright(255, 255, 255);
    }
    else
    {
       DrawRotaGraph2F(location.x, location.y, base_radius, base_radius, scale, rotation, donut_img[0], TRUE);
    }
   
    SetFontSize(20);
    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(type)];
   
    // ドーナツ番号表示
    DrawFormatStringF(location.x, location.y - 3.0f, 0x5C4630, "%d", info.number);
    // ドーナツ着地フラグ表示
    //DrawFormatStringF(location.x, location.y - 40.0f, 0x5C4630, "%d", landed);
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

// ドーナツ落下処理(引数:全てのドーナツオブジェクト)
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
            if (this->GetDonutType() != other->GetDonutType())
            {
                // 物理的な反発処理
                HandleCollision(other);
            }
        }
    }

   landedOnSomething = false;

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
        if(distX < (r + other->r) * 0.9f &&distY > 0 && distY < 5.0f)
        {
            // ドーナツの上に着地とみなす
            location.y = other->location.y - r - other->r;
            vy = 0.0f;
            landedOnSomething = true;
            break;
        }
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

// 衝突処理 (引数:全てのドーナツオブジェクト)
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
    //vx *= 0.85f; // 反発後の減速
    //vy *= 0.85f;
    //other->vx *= 0.85f;
    //other->vy *= 0.85f;
    vx *= 0.75f; // 反発後の減速
    vy *= 0.75f;
    other->vx *= 0.75f;
    other->vy *= 0.75f;
}

// ドーナツが着地したか確認する処理(引数:全てのドーナツオブジェクト)
void Donuts::CheckDonutLanded(const std::vector<Donuts*>& others)
{
    if (landedOnSomething || IsSupported(others))
    {
        landed = true;
    }
}

// ドーナツの枠はみ出し防止処理(引数：ドーナツを落とす枠の座標)
void Donuts::ClampToFrame(float left, float right, float top, float bottom)
{
    if (location.x - r < left) 
    {// 左
        location.x = left + r;
        vx *= -0.5f;
    }
    if (location.x + r > right) 
    {// 右
        location.x = right - r;
        vx *= -0.5f;
    }

    if (location.y - r < top)
    {
        // 上の壁にはぶつからないようにする（ゲームのルール上）
    }
    if (location.y + r > bottom) 
    {// 下
        location.y = bottom - r;
        vy *= -0.5f;
    }
}

// どこかしらに支えられているか判定する処理(引数:全てのドーナツオブジェクト)
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
