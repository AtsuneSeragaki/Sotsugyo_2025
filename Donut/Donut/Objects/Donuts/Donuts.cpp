#include "Donuts.h"
#include "DxLib.h"
#include <math.h>

DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
        { DonutType::DONUT_MINI_BASIC,        20.0f, 100, "images/donut_mini_basic.png" },
        { DonutType::DONUT_MINI_VARIANT,      21.0f, 120, "images/donut_mini_variant.png" },
        { DonutType::DONUT_FRENCH_CRULLER,    22.0f, 150, "images/french_cruller.png" },
        { DonutType::DONUT_FRENCH_CRULLER_VAR,23.0f, 160, "images/french_cruller_var.png" },
        { DonutType::DONUT_OLD_FASHIONED,     24.0f, 130, "images/old_fashioned.png" },
        { DonutType::DONUT_OLD_FASHIONED_VAR, 22.0f, 140, "images/old_fashioned_var.png" },
        { DonutType::DONUT_GOLDEN_CHOCOLATE,  28.0f, 200, "images/golden_chocolate.png" },
        { DonutType::DONUT_COCONUT_CHOCOLATE, 28.0f, 200, "images/coconut_chocolate.png" },
        { DonutType::DONUT_HALF_CHOCOLATE,    24.0f, 170, "images/half_chocolate.png" },
        { DonutType::DONUT_HALF_STRAWBERRY,   24.0f, 170, "images/half_strawberry.png" },
        { DonutType::DONUT_PON_DE_RING,       26.0f, 180, "images/pon_de_ring.png" }
};

Donuts::Donuts(DonutType type)
{
    this->type = type;
    vx = 0.0f;
    vy = 0.0f;

    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(type)];
    r = info.size;
    landed = false;
    name = GetDonutTypeName(this->type);
}

Donuts::~Donuts()
{
}

void Donuts::Initialize()
{
}

void Donuts::Update()
{
    if (landed == false)
    {
        FallDonut();
    }

    // --- 横方向の移動 ---
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

    ClampToFrame(440.0f, 880.0f, 100.0f, 680.0f);
}

void Donuts::Draw() const 
{
    DrawCircleAA(location.x, location.y, r, 32, GetColor(255, 255, 0), TRUE);
    SetFontSize(20);
    DrawFormatString((int)location.x, (int)location.y - 3, 0x000000, "%s", name);
}

void Donuts::Finalize()
{
}

float Donuts::GetDonutRadius(DonutType dtype)
{
    const DonutInfo& info = g_DonutInfoTable[static_cast<int>(dtype)];
    return info.size;
}

void Donuts::FallDonut()
{
    if (!landed) {
        vy += 0.5f;             // 重力加速度
        location.y += vy;

        if (location.y + r >= 680.0f) {
            location.y = 680.0f - r;
            vy *= -0.15f;        // 跳ね返り（減衰付き）

            if (fabs(vy) < 1.0f) {
                vy = 0.0f;
                landed = true;
            }
        }
    }
}

const char* Donuts::GetDonutTypeName(DonutType type)
{
    switch (type)
    {
    case DonutType::DONUT_MINI_BASIC:           return "1";
    case DonutType::DONUT_MINI_VARIANT:         return "2";
    case DonutType::DONUT_FRENCH_CRULLER:       return "3";
    case DonutType::DONUT_FRENCH_CRULLER_VAR:   return "4";
    case DonutType::DONUT_OLD_FASHIONED:        return "5";
    case DonutType::DONUT_OLD_FASHIONED_VAR:    return "6";
    case DonutType::DONUT_GOLDEN_CHOCOLATE:     return "7";
    case DonutType::DONUT_COCONUT_CHOCOLATE:    return "8";
    case DonutType::DONUT_HALF_CHOCOLATE:       return "9";
    case DonutType::DONUT_HALF_STRAWBERRY:      return "10";
    case DonutType::DONUT_PON_DE_RING:          return "11";
    default:                                    return "UNKNOWN_DONUT";
    }
}

void Donuts::ClampToFrame(float left, float right, float top, float bottom)
{
    if (location.x - r < left) {
        location.x = left + r;
        vx *= -0.5f;
    }
    if (location.x + r > right) {
        location.x = right - r;
        vx *= -0.5f;
    }

    if (location.y - r < top) {
        location.y = top + r;
        vy *= -0.5f;
    }
    if (location.y + r > bottom) {
        location.y = bottom - r;
        vy *= -0.6f;
    }
}
