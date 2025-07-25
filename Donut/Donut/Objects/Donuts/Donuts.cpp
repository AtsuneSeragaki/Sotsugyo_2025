#include "Donuts.h"
#include "DxLib.h"

Donuts::Donuts()
{
    r = 20.0f;
    landed = false;
}

Donuts::~Donuts()
{
}

void Donuts::Initialize()
{
}

void Donuts::Update()
{
    //if (!landed) {
    //    vy += 0.3f;   // d—Í‰Á‘¬“x
    //    y += vy;

    //    if (y + r >= 680.0f) {
    //        y = 680.0f - r;
    //        landed = true;
    //    }
    //}

    if (landed == false)
    {
        FallDonut();
    }
}

void Donuts::Draw() const 
{
    DrawCircleAA(location.x, location.y, r, 32, GetColor(255, 255, 0), TRUE);
}

void Donuts::Finalize()
{
}

void Donuts::FallDonut()
{
    if (location.y < 680.0f - r)
    {
        location.y += 7.0f;
    }
    else
    {
        landed = true;
        location.y = 680.0f - r;
    }
}
