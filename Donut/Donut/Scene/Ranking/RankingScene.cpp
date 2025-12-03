#include "RankingScene.h"
#include "../../Objects/Ranking/RankingData.h"
#include "DxLib.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"

// コンストラクタ
RankingScene::RankingScene()
{
	// タイトルボタン初期化
	button[0] = { RANKING_TITLE_BUTTON_LX,RANKING_TITLE_BUTTON_RX,RANKING_BUTTON_LY,RANKING_BUTTON_RY,false,eSceneType::eTitle,{32,17,0x5C4630,0.35,0.35},"BACK TO TITLE" };
	
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/ranking.png");
	background_img = tmp[0];
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
	if (input->IsMouseTriggered())
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
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);
	DrawGraph(0, 0, background_img, FALSE);

	// タイトル
	//FontManager::Draw(430, 30, 1.0, 1.0, 0x5C4630, "RANKING");

	// ランキング表示背景
	//DrawBox(340, 150, 940, 560, 0xD8C3A5, TRUE);

	//// ランキング表示背景枠の太さ
	//int box_line_width = 3;

	//// ランキング表示背景枠描画(枠を太くするために複数描画)
	//for (int j = 0; j < box_line_width; j++)
	//{
	//	DrawBox(340 - j, 150 - j, 940 + j, 560 + j, 0xA67C52, FALSE);
	//}

	RankingData* ranking = new RankingData();
	ranking->Initialize();

	double ranking_fontsize = 0.55; // 文字サイズ
	int default_x = 410; // 固定X座標
	int default_y = 168; // 固定Y座標
	int string_space = 80; // ランキング文字の表示間隔

	char ranking_buf[50];

	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		if (i == 0)
		{// 描画位置を合わせるためにNo.1だけ空白を加えて描画する

			// ランキングを文字列に変換
			sprintf_s(ranking_buf, sizeof(ranking_buf), "No.%d   : %08d", i + 1, ranking->GetScore(i));

			FontManager::Draw(default_x, default_y + i * string_space, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
		}
		else
		{
			// ランキングを文字列に変換
			sprintf_s(ranking_buf, sizeof(ranking_buf), "No.%d  : %08d", i + 1, ranking->GetScore(i));

			FontManager::Draw(default_x, default_y + i * string_space, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
		}
	}

	// メニューボタン
	DrawButton(RANKING_BUTTON_NUM, button);
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
