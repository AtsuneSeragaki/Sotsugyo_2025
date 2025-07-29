#include "Donuts.h"
#include "DxLib.h"

Donuts::Donuts(DonutType type)
{
    vy = 0.0f;
    r = 20.0f;
    landed = false;
    this->type = type;
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
    /*if (location.y < 680.0f - r)
    {
        location.y += 3.0f;
    }
    else
    {
        landed = true;
        location.y = 680.0f - r;
    }*/

    if (!landed) {
        vy += 0.08f;   // d—Í‰Á‘¬“x
        location.y += vy;

        if (location.y + r >= 680.0f) {
            location.y = 680.0f - r;
            landed = true;
        }
    }
}
