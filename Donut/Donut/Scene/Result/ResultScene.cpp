#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

ResultScene::ResultScene(int score)
{
	this->score = score;
	frame_count = 0;
	can_click = false;

	// リスタートボタン初期化
	button[0] = { RESTART_BUTTON_LX,RESTART_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eGameMain };

	// タイトルボタン初期化
	button[1] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eTitle };
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update()
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

void ResultScene::Draw() const
{
	// 背景
	DrawBox(0, 0, 1280, 720, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(90);
	DrawString(500, 35, "Result", 0xffffff);

	DrawBox(340, 150, 940, 560, 0xffffff, TRUE);

	// スコア
	SetFontSize(40);
	DrawFormatString(540, 170, 0x000000, "Your score");
	SetFontSize(70);
	DrawFormatString(502, 230, 0x000000, "%08d", score);

	// ランキング表示
	SetFontSize(40);
	DrawFormatString(580, 320, 0x000000, "Ranking");
	SetFontSize(40);
	DrawFormatString(520, 380, 0x000000, "No.1:%08d", score);
	DrawFormatString(520, 440, 0x000000, "No.2:%08d", score);
	DrawFormatString(520, 500, 0x000000, "No.3:%08d", score);


	int button_color = 0xD6A15D;        // ボタンのカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 20;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int restart_button_xspacing = 55;   // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int title_button_xspacing = 45;     // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

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
				DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "もう一度遊ぶ", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "タイトルに戻る", button_string_color);
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
				DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "もう一度遊ぶ", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "タイトルに戻る", button_string_color);
			}
		}
	}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
