#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/FontManager.h"
#include "DxLib.h"

// コンストラクタ
HelpScene::HelpScene()
{
	frame_count = 0;
	can_click = false;

	int button_color = 0xD6A15D;        // ボタンのカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 20;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int start_button_xspacing = 115;   // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int title_button_xspacing = 50;    // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

	// リスタートボタン初期化
	button[0] = { HELP_START_BUTTON_LX,HELP_START_BUTTON_RX,HELP_BUTTON_LY,HELP_BUTTON_RY,false,eSceneType::eGameMain,{100,17,0x5C4630,0.35,0.35},"START" };

	// タイトルボタン初期化
	button[1] = { HELP_TITLE_BUTTON_LX,HELP_TITLE_BUTTON_RX,HELP_BUTTON_LY,HELP_BUTTON_RY,false,eSceneType::eTitle,{32,17,0x5C4630,0.35,0.35},"BACK TO TITLE" };
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
	for (int i = 0; i < HELP_BUTTON_NUM; i++)
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
		for (int i = 0; i < HELP_BUTTON_NUM; i++)
		{
			PlayButtonSound();

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
	FontManager::Draw(350, 30, 1, 1, 0xffffff, "HOW TO PLAY");

	// メニューボタン
	DrawButton(HELP_BUTTON_NUM, button);
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
