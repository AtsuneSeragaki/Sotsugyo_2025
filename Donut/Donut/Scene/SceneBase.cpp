#include "SceneBase.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"

SceneBase::SceneBase() : background_image(NULL),frame_count(0),can_click(false)
{

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
	//DrawGraph(0, 0, background_image, TRUE);
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

void SceneBase::DrawButton(int button_num, const ButtonState* button,int button_color) const
{
	for (int i = 0; i < button_num; i++)
	{
		if (button[i].collision == true)
		{
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(128, 128, 128);
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);
		}
	}
}
