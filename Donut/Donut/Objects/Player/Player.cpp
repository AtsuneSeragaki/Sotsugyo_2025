#include "Player.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

Player::Player() : is_click(false)
{
	next_donut_type = DonutType::DONUT_MINI_BASIC;
}

Player::~Player()
{
}

void Player::Initialize()
{
	r = 20.0f;
}

void Player::Update()
{
	InputManager* input = InputManager::GetInstance();

	// マウスのX座標を取得
	location.x = input->GetMouseLocation().x;

	// カーソル移動制限
	LocXControl();
}

void Player::Draw() const
{
	DrawCircleAA(location.x, location.y, r, 32, 0xffff00, TRUE);
}

void Player::Finalize()
{
}

void Player::ChooseRandomDonut()
{
	next_donut_type = static_cast<DonutType>(rand() % (static_cast<int>(DonutType::DONUT_OLD_FASHIONED) + 1));
}

void Player::LocXControl()
{
	if (location.x > 880.0f - r)
	{// 右側
		location.x = 880.0f - r;
	}
	else if (location.x < 400.0f + r)
	{// 左側
		location.x = 400.0f + r;
	}
}

bool Player::SetClickFlg(bool flg)
{
	return is_click = flg;
}

bool Player::GetClickFlg()
{
	return is_click;
}
