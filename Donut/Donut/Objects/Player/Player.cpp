#include "Player.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

Player::Player() : is_click(false)
{
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

	// ドーナツ移動制限
	LocXControl();

	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		if (is_click == false)
		{
			is_click = true;
		}
	}

	// ドーナツ落下処理
	if (is_click == true)
	{
		FallDonut();
	}
}

void Player::Draw() const
{
	//DrawCircleAA(location.x, location.y, r, 32, 0xffff00, TRUE);
}

void Player::Finalize()
{
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

void Player::FallDonut()
{
	if (location.y < 680.0f - r)
	{
		location.y += 4.0f;
	}
	else
	{
		is_click = false;
		location.y = 680.0f - r;
	}
}
