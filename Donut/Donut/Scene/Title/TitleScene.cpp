#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"

void TitleScene::Initialize()
{
	start_btn_collision = false;
	help_btn_collision = false;
	end_btn_collision = false;
	canClick = false;
	frame_count = 0;
}

eSceneType TitleScene::Update()
{
	// フレームカウントが5以上になったらクリックできるようにする
	if (frame_count >= 10)
	{
		canClick = true;
	}
	else
	{
		frame_count++;
	}
	
	InputManager* input = InputManager::GetInstance();

    // スタートボタンとプレイヤーカーソルの当たり判定
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, START_BUTTON_LY, START_BUTTON_RY) == 1)
	{
		start_btn_collision = true;
	}
	else
	{
		start_btn_collision = false;
	}

	// ヘルプボタンとプレイヤーカーソルの当たり判定
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, HELP_BUTTON_LY, HELP_BUTTON_RY) == 1)
	{
		help_btn_collision = true;
	}
	else
	{
		help_btn_collision = false;
	}

	// エンドボタンとプレイヤーカーソルの当たり判定
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, END_BUTTON_LY, END_BUTTON_RY) == 1)
	{
		end_btn_collision = true;
	}
	else
	{
		end_btn_collision = false;
	}

	if (canClick == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		if (start_btn_collision == true)
		{
			return eSceneType::eGameMain;
		}
		else if (help_btn_collision == true)
		{
			return eSceneType::eHelp;
		}
		else if (end_btn_collision == true)
		{
			return eSceneType::eEnd;
		}
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0xFFC0CB, TRUE);

	// タイトル表示
	SetFontSize(90);
	DrawString(540, 80, "Title", 0xffffff);

	// メニューボタン表示
	// スタートボタン
	if (start_btn_collision == true)
	{
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, START_BUTTON_LY, BUTTON_RX, START_BUTTON_RY, 0xD6A15D, TRUE);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, START_BUTTON_LY, BUTTON_RX, START_BUTTON_RY, 0xD6A15D, TRUE);
	}

	SetFontSize(30);
	DrawString(BUTTON_LX + 90, START_BUTTON_LY + 20, "はじめる", 0xffffff);

	// ヘルプボタン
	if (help_btn_collision == true)
	{
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, HELP_BUTTON_LY, BUTTON_RX, HELP_BUTTON_RY, 0xD6A15D, TRUE);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, HELP_BUTTON_LY, BUTTON_RX, HELP_BUTTON_RY, 0xD6A15D, TRUE);
	}

	SetFontSize(30);
	DrawString(BUTTON_LX + 75, HELP_BUTTON_LY + 20, "あそびかた", 0xffffff);

	// エンドボタン
	if (end_btn_collision == true)
	{
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, END_BUTTON_LY, BUTTON_RX, END_BUTTON_RY, 0xD6A15D, TRUE);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, END_BUTTON_LY, BUTTON_RX, END_BUTTON_RY, 0xD6A15D, TRUE);
	}

	SetFontSize(30);
	DrawString(BUTTON_LX + 105, END_BUTTON_LY + 20, "おわる", 0xffffff);
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

int TitleScene::CheckPlayerButtonCollision(int left, int right, int top, int bottom)
{
	InputManager* input = InputManager::GetInstance();

	// プレイヤー情報
	int player_l = (int)input->GetMouseLocation().x - 5;
	int player_r = (int)input->GetMouseLocation().x + 10;
	int player_t = (int)input->GetMouseLocation().y;
	int player_b = (int)input->GetMouseLocation().y + 10;

	if ((player_r > left) && (player_l < right))
	{
		if ((player_b > top) && (player_t < bottom))
		{
			return 1;
		}
	}

	return 0;
}