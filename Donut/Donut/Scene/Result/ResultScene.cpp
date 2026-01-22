#include "ResultScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include <cstdio>
#include <time.h>
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
	receipt_se = rm->GetSounds("Resource/Sounds/result_se.mp3");
	ChangeVolumeSoundMem(200, receipt_se);

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

	//receipt_y = 150.0f;

	for (int i = 0; i < 6; i++)
	{
		
		this->donut_count[i] = delete_donut_count[i];
	}

	receipt_se_flg = false;

	GetNowTime();
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

	if (receipt_se_flg == false)
	{
		PlaySoundMem(receipt_se, DX_PLAYTYPE_BACK, TRUE);
		receipt_se_flg = true;
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

	FontManager::DrawNum(600, receipt_y + 55, 0.15, 0.15, 0x5C4630, time_buf);

	DrawBox(0, 560, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);

	DrawGraph(305, 550, line_img, TRUE);

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

	for (int i = 0; i < 6; i++)
	{
		// スコアを文字列に変換
		char buf[16];
		sprintf_s(buf, sizeof(buf), "%d", donut_count[i]);

		if (i < 3)
		{
			// ドーナツの個数を表示
			FontManager::DrawNum(525 + 185 * i, receipt_y + 98, 0.45, 0.45, 0x5C4630, buf);
		}
		else
		{
			// ドーナツの個数を表示
			FontManager::DrawNum(525 + 185 * (i - 3), receipt_y + 198, 0.45, 0.45, 0x5C4630, buf);
		}
	}

	// スコアを文字列に変換
	char score_buf[16];
	sprintf_s(score_buf, sizeof(score_buf), "%08d", score);

	FontManager::DrawNum(445 + plus, receipt_y + 318, 0.85, 0.85, 0x5C4630, score_buf);
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

void ResultScene::GetNowTime()
{
	time_t timer = time(NULL);

	struct tm now;              // ポインタではなく実体
	localtime_s(&now, &timer);  // 安全版

	sprintf_s(
		time_buf,
		sizeof(time_buf),
		"%02d/%02d/%02d %02d:%02d",
		now.tm_year % 100,
		now.tm_mon + 1,
		now.tm_mday,
		now.tm_hour,
		now.tm_min
	);
}

