#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"

// 初期化処理
void TitleScene::Initialize()
{
	start_btn_collision = false;
	help_btn_collision = false;
	end_btn_collision = false;
	canClick = false;
	frame_count = 0;
}

// 更新処理
eSceneType TitleScene::Update()
{
	// フレームカウントが10以上になったらクリックできるようにする
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
		// 当たっていたら、フラグをtrueにする
		start_btn_collision = true;
	}
	else
	{
		start_btn_collision = false;
	}

	// ヘルプボタンとプレイヤーカーソルの当たり判定
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, HELP_BUTTON_LY, HELP_BUTTON_RY) == 1)
	{
		// 当たっていたら、フラグをtrueにする
		help_btn_collision = true;
	}
	else
	{
		help_btn_collision = false;
	}

	// エンドボタンとプレイヤーカーソルの当たり判定
	if (CheckPlayerButtonCollision(BUTTON_LX, BUTTON_RX, END_BUTTON_LY, END_BUTTON_RY) == 1)
	{
		// 当たっていたら、フラグをtrueにする
		end_btn_collision = true;
	}
	else
	{
		end_btn_collision = false;
	}

	// ボタンの上でクリックしたら、それぞれの画面に遷移する
	if (canClick == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		if (start_btn_collision == true)
		{
			// スタートボタン→ゲームメイン画面に遷移
			return eSceneType::eGameMain;
		}
		else if (help_btn_collision == true)
		{
			// ヘルプボタン→ヘルプ画面に遷移
			return eSceneType::eHelp;
		}
		else if (end_btn_collision == true)
		{
			// エンドボタン→エンド画面に遷移
			return eSceneType::eEnd;
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
	int button_string_spacing = 20;      // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	// メニューボタン
	// スタートボタン
	if (start_btn_collision == true)
	{
		// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, START_BUTTON_LY, BUTTON_RX, START_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 90, START_BUTTON_LY + button_string_spacing, "はじめる", button_string_color);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, START_BUTTON_LY, BUTTON_RX, START_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 90, START_BUTTON_LY + button_string_spacing, "はじめる", button_string_color);
	}

	// ヘルプボタン
	if (help_btn_collision == true)
	{
		// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, HELP_BUTTON_LY, BUTTON_RX, HELP_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 75, HELP_BUTTON_LY + button_string_spacing, "あそびかた", button_string_color);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, HELP_BUTTON_LY, BUTTON_RX, HELP_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 75, HELP_BUTTON_LY + button_string_spacing, "あそびかた", button_string_color);
	}

	// エンドボタン
	if (end_btn_collision == true)
	{
		// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
		SetDrawBright(128, 128, 128);
		DrawBox(BUTTON_LX, END_BUTTON_LY, BUTTON_RX, END_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 105, END_BUTTON_LY + button_string_spacing, "おわる", button_string_color);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(BUTTON_LX, END_BUTTON_LY, BUTTON_RX, END_BUTTON_RY, button_color, TRUE);
		SetFontSize(30);
		DrawString(BUTTON_LX + 105, END_BUTTON_LY + button_string_spacing, "おわる", button_string_color);

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