#include "SceneBase.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/FontManager.h"
#include "DxLib.h"

SceneBase::SceneBase() : frame_count(0),button_se_handle(0),button_string_color(0x5C4630),button_string_yspacing(0)
{
	ButtonState button = {
		0,    // lx
		100,  // rx
		0,    // ly
		50,   // ry
		false,                 // collision
		eSceneType::eTitle,     // targetScene
		NULL,   // style
		NULL   // label
	};

	ResourceManager* rm = ResourceManager::GetInstance();
	button_se_handle = rm->GetSounds("Resource/Sounds/button_se.mp3");
	
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/button.png");
	button_img = tmp[0];
}

SceneBase::~SceneBase()
{
	this->Finalize();
}

void SceneBase::Initialize()
{

}

eSceneType SceneBase::Update()
{
	return GetNowSceneType();
}

void SceneBase::Draw() const
{
}

void SceneBase::Finalize()
{
}

// プレイヤーカーソルとボタンの当たり判定(引数：当たり判定を取りたいボタンの情報　戻り値：0→当たってない 1→当たっている)
int SceneBase::CheckPlayerButtonCollision(int left, int right, int top, int bottom)
{
	InputManager* input = InputManager::GetInstance();

	int player_width = 5;  // プレイヤーの幅
	int player_hight = 10; // プレイヤーの高さ

	// プレイヤー情報
	int player_left = (int)input->GetMouseLocation().x;
	int player_right = (int)input->GetMouseLocation().x + player_width;
	int player_top = (int)input->GetMouseLocation().y;
	int player_bottom = (int)input->GetMouseLocation().y + player_hight;

	// 当たり判定(四角同士)
	if ((player_right > left) && (player_left < right))
	{
		if ((player_bottom > top) && (player_top < bottom))
		{
			return 1;
		}
	}

	return 0;
}

// ボタン描画処理(引数：ボタンの数,ボタンの詳細情報)
void SceneBase::DrawButton(int button_num, const ButtonState* button) const
{
	int button_color = 0xD8C3A5; // ボタン背景のカラーコード
	int button_line_color = 0xA67C52; // ボタン枠のカラーコード

	int shadow_pos = 9;

	// ボタン枠の太さ
	int button_line_width = 3;

	for (int i = 0; i < button_num; i++)
	{

		if (button[i].collision)
		{
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(128, 128, 128);

			int offset_y = 4;

			// ボタン背景描画
			//DrawBox(button[i].lx, button[i].ly + offset_y, button[i].rx, button[i].ry + offset_y, button_color, TRUE);

			//// ボタン枠描画(枠を太くするために複数描画)
			//for (int j = 0; j < button_line_width; j++)
			//{
			//	DrawBox(button[i].lx - j, button[i].ly - j + offset_y, button[i].rx + j, button[i].ry + j + offset_y, button_line_color, FALSE);
			//}

			DrawGraph(button[i].lx, button[i].ly + offset_y, button_img, TRUE);

			FontManager::Draw(button[i].lx + button[i].style.xspacing, button[i].ly + button[i].style.yspacing + offset_y, button[i].style.xscale, button[i].style.yscale, button[i].style.string_color, button[i].label);

			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
		}
		else
		{
			// ボタン影描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
			DrawBox(button[i].lx + shadow_pos, button[i].ly + shadow_pos, button[i].rx + shadow_pos, button[i].ry + shadow_pos, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// ボタン背景描画
			//DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);

			//// ボタン枠描画(枠を太くするために複数描画)
			//for (int j = 0; j < button_line_width; j++)
			//{
			//	DrawBox(button[i].lx - j, button[i].ly - j, button[i].rx + j, button[i].ry + j, button_line_color, FALSE);
			//}

			DrawGraph(button[i].lx, button[i].ly, button_img, TRUE);

			FontManager::Draw(button[i].lx + button[i].style.xspacing, button[i].ly + button[i].style.yspacing, button[i].style.xscale, button[i].style.yscale, button[i].style.string_color, button[i].label);
		}
	}
}

// ボタンの効果音を鳴らす処理
void SceneBase::PlayButtonSound()
{
	PlaySoundMem(button_se_handle, DX_PLAYTYPE_BACK, TRUE);
}