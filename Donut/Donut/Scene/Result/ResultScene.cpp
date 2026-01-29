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
	GetNowTime();

	this->score = score;
	
	// デバック用
	//this->score = 100;

	// リスタートボタン初期化
	button[0] = { RESULT_RESTART_BUTTON_LX,RESULT_RESTART_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eGameMain,{55,17,0x5C4630,0.35,0.35},"PLAY AGAIN" };

	// タイトルボタン初期化
	button[1] = { RESULT_TITLE_BUTTON_LX,RESULT_TITLE_BUTTON_RX,RESULT_BUTTON_LY,RESULT_BUTTON_RY,false,eSceneType::eTitle,{32,17,0x5C4630,0.35,0.35},"BACK TO TITLE" };

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/result/result.png");
	background_img = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/line.png");
	line_img = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/receipt.png");
	receipt_img = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/c.png");
	rank_img[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/b.png");
	rank_img[1] = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/a.png");
	rank_img[2] = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/s.png");
	rank_img[3] = tmp[0];
	tmp = rm->GetImages("Resource/Images/result/highscore.png");
	high_score_img = tmp[0];

	receipt_se = rm->GetSounds("Resource/Sounds/result/receipt_se.mp3");
	ChangeVolumeSoundMem(200, receipt_se);
	rank_se = rm->GetSounds("Resource/Sounds/result/rank_se.mp3");
	ChangeVolumeSoundMem(200, rank_se);

	for (int i = 0; i < MAX_DONUT_NUM; i++)
	{
		tmp = rm->GetImages(g_DonutInfoTable[i].image_path);
		donut_img[i] = tmp[0];
	}

	receipt_y = 650.0f;

	// デバック用
	//receipt_y = 150.0f;

	for (int i = 0; i < 6; i++)
	{
		this->donut_count[i] = delete_donut_count[i];
	}

	rank_scale = 1.45;
	high_score_scale = 1.5;

	receipt_se_flg = false;
	receipt_moved_flg = false;
	rank_moved_flg = false;
	high_score_moved_flg = false;

	RankingData* ranking = new RankingData();
	ranking->Initialize();

	// ハイスコアかどうか確かめる
	if (ranking->GetRank(RANKING_DATA_MAX - 1) < this->score)
	{
		high_score_flg = true;
	}
	else
	{
		high_score_flg = false;
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

	// レシート効果音流れていなかったら再生
	if (receipt_se_flg == false)
	{
		PlaySoundMem(receipt_se, DX_PLAYTYPE_BACK, TRUE);
		receipt_se_flg = true;
	}

	if (!receipt_moved_flg)
	{// レシートアニメーション再生

		ReceiptAnim();
	}
	else
	{
		if (!rank_moved_flg)
		{// ランクアニメーション再生

			RankAnim();
		}
		else
		{
			// ハイスコアだったら、ハイスコアアニメーション再生
			if (high_score_flg)
			{
				if (!high_score_moved_flg)
				{
					HighScoreAnim();
				}
			}
		}
	}

	return GetNowSceneType();
}

// 描画処理
void ResultScene::Draw() const
{
	// 背景
	DrawGraph(0, 0, background_img, FALSE);

	DrawGraph(350, (int)receipt_y, receipt_img, TRUE);
	
	// スコア
	DrawScore();

	float rank_x = 1130.0f;
	float rank_y = 320.0f;
	float rank_cx = 97.5f;
	float rank_cy = 94.0f;

	// レシートが最後まで出たら、ランク表示
	if (receipt_y <= 150.0f)
	{
		if (score < 1800)
		{
			DrawRotaGraph2F(rank_x, rank_y, rank_cx, rank_cy, rank_scale, 0.0, rank_img[0], TRUE);
		}
		else if (score < 4000)
		{
			DrawRotaGraph2F(rank_x, rank_y, rank_cx, rank_cy, rank_scale, 0.0, rank_img[1], TRUE);
		}
		else if (score < 10000)
		{
			DrawRotaGraph2F(rank_x, rank_y, rank_cx, rank_cy, rank_scale, 0.0, rank_img[2], TRUE);
		}
		else
		{
			DrawRotaGraph2F(rank_x, rank_y, rank_cx, rank_cy, rank_scale, 0.0, rank_img[3], TRUE);
		}
	}

	if (high_score_flg && rank_scale <= 1.0)
	{
		DrawRotaGraph2F(rank_x /*- 265*/, rank_y + 125, 95, 16, high_score_scale, 0.0, high_score_img, TRUE);
	}
	
	// リザルト画面に遷移した日時
	FontManager::DrawNum(600, (int)receipt_y + 55, 0.15, 0.15, 0x5C4630, time_buf);

	DrawBox(0, 560, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);

	DrawGraph(305, 550, line_img, TRUE);
	
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

	std::string num = std::to_string(score);
	int len = (int)num.length();
	std::string res = "";
	int count = 0;

	for (int i = len - 1; i >= 0; --i) {
		res = num[i] + res;
		count++;
		if (count % 3 == 0 && i != 0) {
			res = "," + res;
		}
	}

	int charWidth = (int)(100 * 0.34f); // 35pxくらい
	int rightX = 750;

	int drawX = rightX - (int)(res.length() * charWidth);

	FontManager::DrawNum(drawX, (int)receipt_y + 318, 0.75, 0.75, 0x5C4630, res.c_str());

	for (int i = 0; i < 6; i++)
	{
		// スコアを文字列に変換
		char buf[16];
		sprintf_s(buf, sizeof(buf), "%d", donut_count[i]);

		if (i < 3)
		{
			// ドーナツの個数を表示
			FontManager::DrawNum(525 + 185 * i, (int)receipt_y + 98, 0.45, 0.45, 0x5C4630, buf);
		}
		else
		{
			// ドーナツの個数を表示
			FontManager::DrawNum(525 + 185 * (i - 3), (int)receipt_y + 198, 0.45, 0.45, 0x5C4630, buf);
		}
	}

	//// スコアを文字列に変換
	//char score_buf[16];
	//sprintf_s(score_buf, sizeof(score_buf), "%08d", score);

	//FontManager::DrawNum(445 + plus, (int)receipt_y + 318, 0.85, 0.85, 0x5C4630, score_buf);
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

// 現在の日時を取得する処理
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

// レシートアニメーション処理
void ResultScene::ReceiptAnim()
{
	receipt_y -= 2.5f;

	if (receipt_y <= 150.0f)
	{
		receipt_y = 150.0f;
		receipt_moved_flg = true;
	}
}

// ランクアニメーション処理
void ResultScene::RankAnim()
{
	rank_scale -= 0.03;

	if (rank_scale <= 1.0)
	{
		rank_scale = 1.0;
		rank_moved_flg = true;
		PlaySoundMem(rank_se, DX_PLAYTYPE_BACK, TRUE);
	}
}

// ハイスコアアニメーション処理
void ResultScene::HighScoreAnim()
{
	high_score_scale -= 0.03;

	if (high_score_scale <= 1.0)
	{
		high_score_scale = 1.0;
		high_score_moved_flg = true;
		PlaySoundMem(rank_se, DX_PLAYTYPE_BACK, TRUE);
	}
}

