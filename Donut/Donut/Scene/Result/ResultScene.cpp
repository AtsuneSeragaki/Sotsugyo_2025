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

	// リスタートボタンとプレイヤーカーソルの当たり判定

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
	DrawString(540, 80, "Result", 0xffffff);

	// スコア
	SetFontSize(30);
	DrawFormatString(540, 150, 0xffffff, "スコア：%d", score);

	int button_color = 0xD6A15D;        // ボタンのカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 20;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int restart_button_xspacing = 55;   // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int title_button_xspacing = 45;     // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

	// メニューボタン
	// リスタートボタン

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (button[i].collision == true)
		{
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(128, 128, 128);
			DrawBox(button[i].lx, button[i].ly, button[i].rx, button[i].ry, button_color, TRUE);
			SetFontSize(30);
			DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "もう一度遊ぶ", button_string_color);
			SetDrawBright(255, 255, 255);
		}
		else
		{

		}
	}

	//if (restart_btn_collision == true)
	//{
	//	// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
	//	SetDrawBright(128, 128, 128);
	//	DrawBox(RESTART_BUTTON_LX, BUTTON_LY, RESTART_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(RESTART_BUTTON_LX + restart_button_xspacing, BUTTON_LY + button_string_yspacing, "もう一度遊ぶ", button_string_color);
	//	SetDrawBright(255, 255, 255);
	//}
	//else
	//{
	//	DrawBox(RESTART_BUTTON_LX, BUTTON_LY, RESTART_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(RESTART_BUTTON_LX + restart_button_xspacing,BUTTON_LY + button_string_yspacing, "もう一度遊ぶ", button_string_color);
	//}

	//// タイトルボタン
	//if (title_btn_collision == true)
	//{
	//	// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
	//	SetDrawBright(128, 128, 128);
	//	DrawBox(TITLE_BUTTON_LX, BUTTON_LY, TITLE_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(TITLE_BUTTON_LX + title_button_xspacing, BUTTON_LY + button_string_yspacing, "タイトルに戻る", button_string_color);
	//	SetDrawBright(255, 255, 255);
	//}
	//else
	//{
	//	DrawBox(TITLE_BUTTON_LX, BUTTON_LY, TITLE_BUTTON_RX, BUTTON_RY, button_color, TRUE);
	//	SetFontSize(30);
	//	DrawString(TITLE_BUTTON_LX + title_button_xspacing, BUTTON_LY + button_string_yspacing, "タイトルに戻る", button_string_color);
	//}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
