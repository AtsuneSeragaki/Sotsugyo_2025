#include "ResultScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include <cstdio>
#include "DxLib.h"

// コンストラクタ
ResultScene::ResultScene(int score,int* delete_donut_count)
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
	tmp = rm->GetImages("Resource/Images/line.png");
	line_img = tmp[0];
	tmp = rm->GetImages("Resource/Images/receipt.png");
	receipt_img = tmp[0];

	for (int i = 0; i < MAX_DONUT_NUM; i++)
	{
		tmp = rm->GetImages(g_DonutInfoTable[i].image_path);
		donut_img[i] = tmp[0];
	}

	donut1_x = 150.0f;
	donut1_y = -50.0f;

	donut2_x = 1150.0f;
	donut2_y = -300.0f;

	rotation1 = 0.0;
	rotation2 = 10.0;

	donut_number[0] = GetRand(MAX_DONUT_NUM - 1);
	donut_number[1] = GetRand(MAX_DONUT_NUM - 1);

	receipt_y = 650.0f;

	for (int i = 0; i < 6; i++)
	{
		
		this->donut_count[i] = delete_donut_count[i];
	}
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

	if (receipt_y > 150.0f)
	{
		receipt_y -= 2.5f;
	}

	MoveDonut();

	return GetNowSceneType();
}

// 描画処理
void ResultScene::Draw() const
{
	// 背景
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);
	DrawGraph(0, 0, background_img, FALSE);

	DrawGraph(350, receipt_y, receipt_img, TRUE);
	// スコア
	DrawScore();

	DrawBox(0, 560, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);

	DrawGraph(305, 550, line_img, TRUE);

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

	//DrawDonut();

	for (int i = 0; i < 6; i++)
	{
		DrawFormatString(0, 0 + i * 40, 0x000000, "Donut%d:%d", i, donut_count[i]);
	}

	//// ランキング
	//DrawRanking();
	
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
	int plus = 10;

	//FontManager::DrawStr(535, 170, 0.4, 0.4, 0x5C4630, "YOUR SCORE");

	// スコアを文字列に変換
	char score_buf[16];
	sprintf_s(score_buf, sizeof(score_buf), "%08d", score);

	FontManager::DrawNum(447 + plus, receipt_y + 310, 0.85, 0.85, 0x5C4630, score_buf);
	//FontManager::Draw(447 + plus, 230, 0.7, 0.7, 0x5C4630, "");

}

// ランキング描画処理
void ResultScene::DrawRanking() const
{
	RankingData* ranking = new RankingData();
	ranking->Initialize();

	int plus = 90;

	// 文字サイズ
	double ranking_fontsize = 0.4;

	FontManager::DrawStr(580, 320, ranking_fontsize, ranking_fontsize, 0x5C4630, "RANKING");

	char ranking_buf[50];

	ranking_fontsize = 0.5;

	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		// ランキングを文字列に変換
		sprintf_s(ranking_buf, sizeof(ranking_buf),"%08d",ranking->GetScore(i));

		FontManager::DrawNum(480 + plus, 375 + i * 60, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
		//FontManager::DrawNum(480 + plus, 375 + i * 60, ranking_fontsize, ranking_fontsize, 0x766351, ranking_buf);
	}
}

void ResultScene::DrawDonut() const
{
	float base_radius = 296.5; // 元画像(288x288)の半径
	double scale = (double)g_DonutInfoTable[6].size / (double)base_radius; // 画像の拡大率

	// 左側ドーナツ描画
	DrawRotaGraph2F(donut1_x, donut1_y, base_radius, base_radius, scale, rotation1, donut_img[donut_number[0]], TRUE);
	// 右側ドーナツ描画
	DrawRotaGraph2F(donut2_x, donut2_y, base_radius, base_radius, scale, rotation2, donut_img[donut_number[1]], TRUE);
}

// ドーナツの落下処理
void ResultScene::MoveDonut()
{
	float speed = 3.4f;

	// 左側ドーナツの落下処理
	if (donut1_y <= 900.0f)
	{
		donut1_y += speed;
	}
	else
	{// 画面外に出たときの処理

		// ランダムに、次の描画開始地点を決める
		int ran1 = GetRand(2);

		if (ran1 == 0)
		{
			donut1_y = -250.0f;
		}
		else if (ran1 == 1)
		{
			donut1_y = -350.0f;
		}
		else
		{
			donut1_y = -450.0f;
		}

		// 次のドーナツの種類を決める
		int d_num1 = donut_number[0];

		do {
			donut_number[0] = GetRand(MAX_DONUT_NUM - 1);
		} while (d_num1 == donut_number[0]);
	}

	// 左側ドーナツの角度を更新
	rotation1 += 0.85 / (double)g_DonutInfoTable[0].size;

	if (rotation1 > DX_TWO_PI)
	{
		rotation1 -= DX_TWO_PI;
	}

	// 右側ドーナツの落下処理
	if (donut2_y <= 900.0f)
	{
		donut2_y += speed;
	}
	else
	{// 画面外に出たときの処理

		// 次の描画開始地点を決める
		int ran2 = GetRand(2);

		if (ran2 == 0)
		{
			donut2_y = -150.0f;
		}
		else if (ran2 == 1)
		{
			donut2_y = -250.0f;
		}
		else
		{
			donut2_y = -350.0f;
		}

		// 次のドーナツの種類を決める
		int d_num2 = donut_number[1];

		do {
			donut_number[1] = GetRand(MAX_DONUT_NUM - 1);
		} while (d_num2 == donut_number[1]);
	}

	// 右側ドーナツの角度を更新
	rotation2 += 0.85 / (double)g_DonutInfoTable[0].size;

	if (rotation2 > DX_TWO_PI)
	{
		rotation2 -= DX_TWO_PI;
	}
}

