#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

// コンストラクタ
HelpScene::HelpScene()
{
	frame_count = 0;
	can_click = false;

	// リスタートボタン初期化
	button[0] = { START_BUTTON_LX,START_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eGameMain };

	// タイトルボタン初期化
	button[1] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,BUTTON_LY,BUTTON_RY,false,eSceneType::eTitle };
}

// デストラクタ
HelpScene::~HelpScene()
{
}

// 初期化処理
void HelpScene::Initialize()
{
	
}

// 更新処理
eSceneType HelpScene::Update()
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
	if (can_click && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
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
void HelpScene::Draw() const
{
	// 背景
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(80);
	DrawString(450, 35, "HOW TO PLAY", 0xffffff);

	int button_color = 0xD6A15D;        // ボタンのカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 20;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int start_button_xspacing = 115;   // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int title_button_xspacing = 50;     // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

	// メニューボタン
	DrawButton(BUTTON_NUM, button, button_color);

	// ボタン文字描画(画像が出来たら消す)
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
				SetDrawBright(255, 255, 255);
			}

		}
		else
		{
			if (i == 0)
			{
				SetFontSize(30);
				DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
			}
		}
	}
}

// 終了時処理
void HelpScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
