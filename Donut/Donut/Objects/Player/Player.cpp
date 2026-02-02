#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include "DxLib.h"

// コンストラクタ
Player::Player()
{
	// 最初は1のドーナツを設定
	donut_type = DonutType::DONUT_BASIC;
	const DonutInfo& info = g_DonutInfoTable[static_cast<int>(donut_type)];
	r = info.size;
	donut_number = 1;

	// 次のドーナツは3のドーナツを設定
	next_donut_type = DonutType::DONUT_HALF_CHOCOLATE;
	const DonutInfo& info2 = g_DonutInfoTable[static_cast<int>(next_donut_type)];
	next_r = info2.size;
	next_donut_number = 3;

	// 画像読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages(info.image_path);
	donut_img[0] = tmp[0];
	tmp = rm->GetImages(info2.image_path);
	donut_img[1] = tmp[0];

	click_timer = 0;
	click_timer_flg = true;
	donut_collision = false;
	is_click = true;
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

	/*if (click_timer_flg)
	{
		click_timer++;
	}*/
}

// 描画処理
void Player::Draw() const
{
	// 枠の太さ
	int line_width = 3;

	float base_radius = 296.5; // 元画像(593x593)の半径
	double scale = (double)r / (double)base_radius; // 落とすドーナツ画像の拡大率
	double next_scale = (double)next_r / (double)base_radius; // 次に落とすドーナツ画像の拡大率

	// ドーナツの落下位置(白い線)
	for (int i = 0; i < line_width; i++)
	{
		DrawLineAA(location.x + i, location.y + r, location.x + i, FRAME_RY, 0xffffff);
	}

	// 落とすドーナツ
	DrawRotaGraph2F(location.x, location.y, base_radius, base_radius, scale, 0.0, donut_img[0], TRUE);

	// 次に落とすドーナツの描画(右上)
	DrawRotaGraph2F(1078.0f, 150.0f, base_radius, base_radius, next_scale, 0.0, donut_img[1], TRUE);
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
	next_donut_type = static_cast<DonutType>(rand() % (static_cast<int>(DonutType::DONUT_CHOCOLATE) + 1));

	const DonutInfo& info = g_DonutInfoTable[static_cast<int>(donut_type)];
	const DonutInfo& info2 = g_DonutInfoTable[static_cast<int>(next_donut_type)];

	// 画像読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages(info.image_path);
	donut_img[0] = tmp[0];
	tmp = rm->GetImages(info2.image_path);
	donut_img[1] = tmp[0];

	// 大きさ設定
	r = info.size;
	next_r = info2.size;

	// 番号設定
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