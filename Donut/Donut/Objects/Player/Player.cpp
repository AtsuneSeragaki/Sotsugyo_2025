#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include "DxLib.h"

// コンストラクタ
Player::Player() : is_click(true)
{
	// 最初は1のドーナツを設定
	donut_type = DonutType::DONUT_MINI_BASIC;
	const DonutInfo& info = g_DonutInfoTable[static_cast<int>(donut_type)];
	r = info.size;
	donut_number = 1;

	// 次のドーナツは3のドーナツを設定
	next_donut_type = DonutType::DONUT_FRENCH_CRULLER;
	const DonutInfo& info2 = g_DonutInfoTable[static_cast<int>(next_donut_type)];
	next_r = info2.size;
	next_donut_number = 3;

	donut_collision = false;

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages(info.image_path);
	donut_img[0] = tmp[0];
	tmp = rm->GetImages(info2.image_path);
	donut_img[1] = tmp[0];
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
	// ネクスト枠の描画(右上)
	//DrawCircle(1070, 135, 105, 0xD8C3A5, TRUE);

	//// 枠の太さ
	//int line_width = 3;

	//// ドーナツを落とす枠描画(枠を太くするために複数描画)
	//for (int i = 0; i < line_width; i++)
	//{
	//	DrawCircleAA(1070.0f, 135.0f, 105.0f + i, 64,0xA67C52, FALSE);
	//}

	//FontManager::Draw(1035, 65, 0.3, 0.3, 0x5C4630, "NEXT");

	//float base_radius = 46.5; // 元画像(93x93)の半径
	float base_radius = 296.5; // 元画像(288x288)の半径
	double scale = (double)r / (double)base_radius; // 落とすドーナツ画像の拡大率
	double next_scale = (double)next_r / (double)base_radius; // 次に落とすドーナツ画像の拡大率

	// 落とすドーナツ仮描画
	DrawRotaGraph2F(location.x, location.y, base_radius, base_radius, scale, 0.0, donut_img[0], TRUE);

	// 落とすドーナツ番号の描画
	//DrawFormatString((int)location.x, (int)location.y - 3, 0x5C4630, "%d", donut_number);

	scale = (double)next_r / base_radius; // 次に落とすドーナツ画像の拡大率

	// 次に落とすドーナツの描画(右上)
	DrawRotaGraph2F(1074.0f, 155.0f, base_radius, base_radius, next_scale, 0.0, donut_img[1], TRUE);

	// 次に落とすドーナツ番号の描画(右上)
	//DrawFormatString(1072, 157, 0x5C4630, "%d", next_donut_number);
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

	const DonutInfo& info = g_DonutInfoTable[static_cast<int>(donut_type)];
	const DonutInfo& info2 = g_DonutInfoTable[static_cast<int>(next_donut_type)];

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages(info.image_path);
	donut_img[0] = tmp[0];
	tmp = rm->GetImages(info2.image_path);
	donut_img[1] = tmp[0];

	r = info.size;
	next_r = info2.size;

	donut_number = info.number;
	next_donut_number = info2.number;
}

// ドーナツを落とす枠の範囲しか横移動出来ないようにする処理
void Player::LocXControl()
{
	if (location.x > (float)FRAME_RX - r)
	{// 右側
		location.x = (float)FRAME_RX - r;
	}
	else if (location.x < (float)FRAME_LX + r)
	{// 左側
		location.x = (float)FRAME_LX + r;
	}
}