#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"

// 初期化処理
void TitleScene::Initialize()
{
	can_click = false;
	frame_count = 0;

	button[0] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX, TITLE_START_BUTTON_LY, TITLE_START_BUTTON_RY, false, eSceneType::eGameMain };
	button[1] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,TITLE_HELP_BUTTON_LY,TITLE_HELP_BUTTON_RY,false,eSceneType::eHelp };
	button[2] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,TITLE_RANKING_BUTTON_LY,TITLE_RANKING_BUTTON_RY,false,eSceneType::eRanking };
	button[3] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,TITLE_END_BUTTON_LY,TITLE_END_BUTTON_RY,false,eSceneType::eEnd };

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/back.png");
	background_image = tmp[0];
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
	for (int i = 0; i < TITLE_BUTTON_NUM; i++)
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
		PlayButtonSound();

		for (int i = 0; i < TITLE_BUTTON_NUM; i++)
		{
			if (button[i].collision)
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
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);
	DrawGraph(0, 0, background_image, TRUE);

	// タイトル
	SetFontSize(100);
	//DrawString(525, 100, "TITLE", 0xffffff);

	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawExtendStringToHandle(355, 100, 1, 1, "DONUT POP", 0xffffff, FontManager::GetFontHandle());
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);

	int button_color = 0xf4b183;        // ボタンのカラーコード
	int button_line_color = 0x843c0c;   // ボタン枠のカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 15;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	// ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int start_button_xspacing = 100;
	int help_button_xspacing = 20; 
	int ranking_button_xspacing = 70;
	int end_button_xspacing = 115;

	// メニューボタン
	DrawButton(TITLE_BUTTON_NUM, button);

	// ボタン文字描画(画像が出来たら消す)
	for (int i = 0; i < TITLE_BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				//DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
				DrawExtendStringToHandle(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "START", 0xffffff, FontManager::GetFontHandle());
				SetDrawBright(255, 255, 255);
			}
			else if(i == 1)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				//DrawString(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, "HOW TO PLAY", button_string_color);
				DrawExtendStringToHandle(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "HOW TO PLAY", 0xffffff, FontManager::GetFontHandle());
				SetDrawBright(255, 255, 255);
			}
			else if (i == 2)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				//DrawString(button[i].lx + ranking_button_xspacing, button[i].ly + button_string_yspacing, "RANKING", button_string_color);
				DrawExtendStringToHandle(button[i].lx + ranking_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "RANKING", 0xffffff, FontManager::GetFontHandle());
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				//DrawString(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, "EXIT", button_string_color);
				DrawExtendStringToHandle(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "EXIT", 0xffffff, FontManager::GetFontHandle());
				SetDrawBright(255, 255, 255);
			}

		}
		else
		{
			//バイリニア法で描画する
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			if (i == 0)
			{
				SetFontSize(30);
				//DrawString(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, "START", button_string_color);
				DrawExtendStringToHandle(button[i].lx + start_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "START", 0xffffff, FontManager::GetFontHandle());
			}
			else if(i == 1)
			{
				SetFontSize(30);
				//DrawString(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, "HOW TO PLAY", button_string_color);
				DrawExtendStringToHandle(button[i].lx + help_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "HOW TO PLAY", 0xffffff, FontManager::GetFontHandle());
			}
			else if (i == 2)
			{
				SetFontSize(30);
				//DrawString(button[i].lx + ranking_button_xspacing, button[i].ly + button_string_yspacing, "RANKING", button_string_color);
				DrawExtendStringToHandle(button[i].lx + ranking_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "RANKING", 0xffffff, FontManager::GetFontHandle());
			}
			else
			{
				SetFontSize(30);
				//DrawString(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, "EXIT", button_string_color);
				DrawExtendStringToHandle(button[i].lx + end_button_xspacing, button[i].ly + button_string_yspacing, 0.4, 0.4, "EXIT", 0xffffff, FontManager::GetFontHandle());
			}
			// ネアレストネイバー法で描画する(標準)
			SetDrawMode(DX_DRAWMODE_NEAREST);
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