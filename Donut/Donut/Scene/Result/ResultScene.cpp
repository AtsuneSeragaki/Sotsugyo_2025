#include "ResultScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/FontManager.h"
#include "DxLib.h"

// コンストラクタ
ResultScene::ResultScene(int score)
{
	this->score = score;
	frame_count = 0;
	can_click = false;

	// リスタートボタン初期化
	button[0] = { RESULT_RESTART_BUTTON_LX,RESULT_RESTART_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eGameMain };

	// タイトルボタン初期化
	button[1] = { RESULT_TITLE_BUTTON_LX,RESULT_TITLE_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eTitle };
}

// デストラクタ
ResultScene::~ResultScene()
{
}

// 初期化処理
void ResultScene::Initialize()
{
}

// 更新処理
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
	for (int i = 0; i < RESULT_BUTTON_NUM; i++)
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

		for (int i = 0; i < RESULT_BUTTON_NUM; i++)
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
void ResultScene::Draw() const
{
	// 背景
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(90);
	//DrawString(510, 35, "RESULT", 0x000000);

	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawExtendStringToHandle(475, 30, 1, 1, "RESULT", 0xffffff, FontManager::GetFontHandle());
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);

	DrawBox(340, 150, 940, 560, 0xffffff, TRUE);

	// スコア
	DrawScore();

	// ランキング表示
	DrawRanking();

	int button_color = 0xD6A15D;        // ボタンのカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 17;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int restart_button_xspacing = 55;   // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int title_button_xspacing = 32;     // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

	// メニューボタン
	DrawButton(RESULT_BUTTON_NUM, button);

	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// ボタン文字描画(画像が出来たら消す)
	for (int i = 0; i < RESULT_BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if (i == 0)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				//DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "PLAY AGAIN", button_string_color);
				DrawExtendStringToHandle(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, 0.35, 0.35, "PLAY AGAIN", 0xffffff, FontManager::GetFontHandle());
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				//DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
				DrawExtendStringToHandle(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, 0.35, 0.35, "BACK TO TITLE", 0xffffff, FontManager::GetFontHandle());
				SetDrawBright(255, 255, 255);
			}
			
		}
		else
		{
			if (i == 0)
			{
				SetFontSize(30);
				//DrawString(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, "PLAY AGAIN", button_string_color);
				DrawExtendStringToHandle(button[i].lx + restart_button_xspacing, button[i].ly + button_string_yspacing, 0.35, 0.35, "PLAY AGAIN", 0xffffff, FontManager::GetFontHandle());
			}
			else
			{
				SetFontSize(30);
				//DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
				DrawExtendStringToHandle(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, 0.35, 0.35, "BACK TO TITLE", 0xffffff, FontManager::GetFontHandle());
			}
		}
	}
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// 終了時処理
void ResultScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

// スコア描画処理
void ResultScene::DrawScore() const
{
	SetFontSize(40);
	//DrawFormatString(540, 170, 0x000000, "Your score");
	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawExtendStringToHandle(540 - 20, 170, 0.4, 0.4, "YOUR SCORE", 0x000000, FontManager::GetFontHandle());
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);
	//SetFontSize(70);
	//DrawFormatString(502, 230, 0x000000, "%08d", score);
	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawExtendFormatStringToHandle(502 -55, 230, 0.7, 0.7, 0x000000, FontManager::GetFontHandle(), "%08d", score);
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// ランキング描画処理
void ResultScene::DrawRanking() const
{
	RankingData* ranking = new RankingData();
	ranking->Initialize();

	SetFontSize(40);
	//DrawFormatString(580, 320, 0x000000, "Ranking");

	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawExtendStringToHandle(580 -20, 320, 0.4, 0.4, "RANKING", 0x000000, FontManager::GetFontHandle());
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);

	SetFontSize(40);
	for (int i = 0; i < RANKING_DATA_MAX - 2; i++)
	{
		//DrawFormatString(515, 380 + i * 60, 0x000000, "No.%d:%08d",i + 1,ranking->GetScore(i));
	
		if (i == 0)
		{
			//バイリニア法で描画する
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawExtendFormatStringToHandle(515 -35, 380 + i * 60, 0.4, 0.4, 0x000000, FontManager::GetFontHandle(), "No.%d  : %08d", i + 1, ranking->GetScore(i));
			// ネアレストネイバー法で描画する(標準)
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		else 
		{
			//バイリニア法で描画する
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawExtendFormatStringToHandle(515 -35, 380 + i * 60, 0.4, 0.4, 0x000000, FontManager::GetFontHandle(), "No.%d : %08d", i + 1, ranking->GetScore(i));
			// ネアレストネイバー法で描画する(標準)
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		
	}
}
