#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"

// 初期化処理
void TitleScene::Initialize()
{
	can_click = false;
	frame_count = 0;

	// スタートボタン初期化
	button[0] = { BUTTON_LX,BUTTON_RX,START_BUTTON_LY,START_BUTTON_RY,false,eSceneType::eGameMain };

	// ヘルプボタン初期化
	button[1] = { BUTTON_LX,BUTTON_RX,HELP_BUTTON_LY,HELP_BUTTON_RY,false,eSceneType::eHelp };

	// エンドボタン初期化
	button[2] = { BUTTON_LX,BUTTON_RX,END_BUTTON_LY,END_BUTTON_RY,false,eSceneType::eEnd };

}

// 更新処理
eSceneType TitleScene::Update()
{
	// フレームカウントが10以上になったらクリックできるようにする
	if (frame_count >= 10)
	{
		can_click = true;
	}
	else
	{
		frame_count++;
	}
	
	InputManager* input = InputManager::GetInstance();

	// ボタンとプレイヤーカーソルの当たり判定
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (CheckPlayerButtonCollision(button[i].lx, button[i].rx, button[i].ly, button[i].ry) == 1)
		{
			button[i].collision = true;
		}
		else
		{
			button[i].collision = false;
		}
	}

	// ボタンの上でクリックしたら、それぞれの画面に遷移する
	if (can_click == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		for (int i = 0; i < BUTTON_NUM; i++)
		{
			if (button[i].collision == true)
			{
				// それぞれの画面に遷移
				return button[i].targetScene;
			}
		}
	}

	return GetNowSceneType();
}

// 描画処理
void TitleScene::Draw() const
{
	// 背景
	DrawBox(0, 0, 1280, 720, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(90);
	DrawString(540, 80, "Title", 0xffffff);

	int button_color = 0xD6A15D;         // ボタンのカラーコード
	int button_string_color = 0xffffff;  // ボタンの文字のカラーコード
	int button_string_yspacing = 20;     // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int start_button_xspacing = 90; // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int help_button_xspacing = 75;  // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int end_button_xspacing = 105;  // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

	// メニューボタン
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (button[i].collision == true)
		{
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(128, 128, 128);
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);
			SetDrawBright(255, 255, 255);

			// 仮表示用文字(画像が出来たら消す)
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "はじめる", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else if(i == 1)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, "あそびかた", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, "おわる", button_string_color);
				SetDrawBright(255, 255, 255);
			}

		}
		else
		{
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);

			// 仮表示用文字(画像が出来たら消す)
			if (i == 0)
			{
				SetFontSize(30);
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "はじめる", button_string_color);
			}
			else if(i == 1)
			{
				SetFontSize(30);
				DrawString(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, "あそびかた", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, "おわる", button_string_color);
			}
		}
	}
}

// 終了時処理
void TitleScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}