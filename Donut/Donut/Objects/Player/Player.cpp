#include "Player.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

// コンストラクタ
Player::Player() : is_click(false)
{
	// 最初は1のドーナツを設定
	donut_type = DonutType::DONUT_MINI_BASIC;
	r = 10.0f;
	donut_number = 1;

	// 次のドーナツは3のドーナツを設定
	next_donut_type = DonutType::DONUT_FRENCH_CRULLER;
	next_r = 30.0f;
	next_donut_number = 3;

	donut_collision = false;
}

// デストラクタ
Player::~Player()
{
}

// 初期化処理
void Player::Initialize()
{
	
}

// 更新処理
void Player::Update()
{
	InputManager* input = InputManager::GetInstance();

	// マウスのX座標を取得
	location.x = input->GetMouseLocation().x;

	// カーソル移動制限
	LocXControl();
}

// 描画処理
void Player::Draw() const
{
	// ドーナツ仮表示
	DrawCircleAA(location.x, location.y, r, 32, 0xD6A15D, TRUE);
	// ドーナツ番号を表示
	DrawFormatString((int)location.x, (int)location.y - 3, 0x000000, "%d", donut_number);

	SetFontSize(20);
	DrawString(1030, 90, "ネクスト", 0x1A2E40);
	// 次に落とすドーナツを表示(右上)
	DrawCircleAA(1070.0f, 175.0f, next_r, 32, 0xD6A15D, TRUE);
	// 次に落とすドーナツ番号を表示
	DrawFormatString((int)1067.0f, (int)170.0f - 3, 0x1A2E40, "%d", next_donut_number);
	DrawCircle(1070, 150, 105, 0x1A2E40, FALSE);

	InputManager* input = InputManager::GetInstance();
	//DrawCircleAA(location.x, input->GetMouseLocation().y, 10, 32, 0xffffff, TRUE);

	//DrawBox(input->GetMouseLocation().x - 5, input->GetMouseLocation().y, input->GetMouseLocation().x + 10, input->GetMouseLocation().y + 10, 0xffffff, TRUE);

	//DrawFormatString(0, 100, 0xffffff, "%d", donut_collision);
}

// 終了時処理
void Player::Finalize()
{
}

// ドーナツをランダムに選ぶ
void Player::ChooseRandomDonut()
{
	// 次に落とすドーナツを今落とすドーナツに上書き
	donut_type = next_donut_type;

	// 次に落とすドーナツを決めなおす
	next_donut_type = static_cast<DonutType>(rand() % (static_cast<int>(DonutType::DONUT_OLD_FASHIONED) + 1));
}

// ドーナツを落とす枠の範囲しか移動出来ないようにする処理
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