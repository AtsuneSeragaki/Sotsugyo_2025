#include "RankingScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "DxLib.h"
#include "../../Utility/InputManager.h"

// コンストラクタ
RankingScene::RankingScene()
{
	// タイトルボタン初期化
	button[0] = { RANKING_TITLE_BUTTON_LX,RANKING_TITLE_BUTTON_RX,RANKING_BUTTON_LY,RANKING_BUTTON_RY,false,eSceneType::eTitle };
}

// デストラクタ
RankingScene::~RankingScene()
{
}

// 初期化処理
void RankingScene::Initialize()
{
}

// 更新処理
eSceneType RankingScene::Update()
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
	for (int i = 0; i < RANKING_BUTTON_NUM; i++)
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

		for (int i = 0; i < RANKING_BUTTON_NUM; i++)
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
void RankingScene::Draw() const
{
	// 背景
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(90);
	DrawString(500, 35, "RANKING", 0xffffff);

	RankingData* ranking = new RankingData();
	ranking->Initialize();

	SetFontSize(65);
	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		DrawFormatString(425, 155 + i * 90, 0x000000, "No.%d:%08d", i + 1, ranking->GetScore(i));
	}

	int button_color = 0xD6A15D;         // ボタンのカラーコード
	int button_string_color = 0xffffff;  // ボタンの文字のカラーコード
	int button_string_yspacing = 20;     // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int title_button_xspacing = 50;

	// メニューボタン
	DrawButton(RANKING_BUTTON_NUM, button);

	// ボタン文字描画(画像が出来たら消す)
	for (int i = 0; i < RANKING_BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if(i == 0)
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
				DrawString(button[i].lx + title_button_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
			}
		}
	}
}

// 終了時処理
void RankingScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}
