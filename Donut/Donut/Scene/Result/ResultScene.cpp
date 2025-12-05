#include "ResultScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include <cstdio>
#include "DxLib.h"

// コンストラクタ
ResultScene::ResultScene(int score)
{
	this->score = score;

	// リスタートボタン初期化
	button[0] = { RESULT_RESTART_BUTTON_LX,RESULT_RESTART_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eGameMain,{55,17,0x5C4630,0.35,0.35},"PLAY AGAIN" };

	// タイトルボタン初期化
	button[1] = { RESULT_TITLE_BUTTON_LX,RESULT_TITLE_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eTitle,{32,17,0x5C4630,0.35,0.35},"BACK TO TITLE" };

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/result.png");
	background_img = tmp[0];
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
	if (input->IsMouseTriggered())
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
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);
	DrawGraph(0, 0, background_img, FALSE);

	// タイトル
	//FontManager::Draw(475, 30, 1.0, 1.0, 0x5C4630, "RESULT");

	// リザルト表示背景
	//DrawBox(340, 150, 940, 560, 0xD8C3A5, TRUE);

	//// リザルト表示背景枠の太さ
	//int box_line_width = 3;

	//// リザルト表示背景枠描画(枠を太くするために複数描画)
	//for (int j = 0; j < box_line_width; j++)
	//{
	//	DrawBox(340 - j, 150 - j, 940 + j, 560 + j, 0xA67C52, FALSE);
	//}

	// スコア
	DrawScore();

	// ランキング
	DrawRanking();
	
	// メニューボタン
	DrawButton(RESULT_BUTTON_NUM, button);
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
	FontManager::Draw(520, 170, 0.4, 0.4, 0x5C4630, "YOUR SCORE");

	// スコアを文字列に変換
	char score_buf[16];
	sprintf_s(score_buf, sizeof(score_buf), "%08d", score);

	FontManager::Draw(447, 230, 0.7, 0.7, 0x5C4630, score_buf);
}

// ランキング描画処理
void ResultScene::DrawRanking() const
{
	RankingData* ranking = new RankingData();
	ranking->Initialize();

	// 文字サイズ
	double ranking_fontsize = 0.4;

	FontManager::Draw(565, 320, ranking_fontsize, ranking_fontsize, 0x5C4630, "RANKING");

	char ranking_buf[50];

	for (int i = 0; i < RANKING_DATA_MAX - 2; i++)
	{
		if (i == 0)
		{// 描画位置を合わせるためにNo.1だけ空白を加えて描画する

			// ランキングを文字列に変換
			sprintf_s(ranking_buf, sizeof(ranking_buf), "No.%d   : %08d", i + 1, ranking->GetScore(i));

			FontManager::Draw(480, 380 + i * 60, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
		}
		else 
		{
			// ランキングを文字列に変換
			sprintf_s(ranking_buf, sizeof(ranking_buf), "No.%d  : %08d", i + 1, ranking->GetScore(i));

			FontManager::Draw(480, 380 + i * 60, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
		}
	}
}
