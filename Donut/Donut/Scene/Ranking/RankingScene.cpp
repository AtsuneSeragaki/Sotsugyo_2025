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
	tmp = rm->GetImages("Resource/Images/donut2/donut2.png");
	donut_img[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/donut2/donut_shadow1.png");
	donut_img[1] = tmp[0];
	tmp = rm->GetImages("Resource/Images/rank1.png");
	rank_img[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/rank2.png");
	rank_img[1] = tmp[0];
	tmp = rm->GetImages("Resource/Images/rank3.png");
	rank_img[2] = tmp[0];

	drop_se = rm->GetSounds("Resource/Sounds/GameMain/marge_se.mp3");
	ChangeVolumeSoundMem(170, drop_se);

	for (int i = 0; i < RANK_MAX_NUM; i++)
	{
		donut_num[i] = -200;
	}

	donut_y = 387.0f;
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

	// 0番目
	if(donut_num[0] < donut_y)
	{
		donut_num[0] += 20;

		if (donut_num[0] >= donut_y)
		{
			donut_num[0] = donut_y;
			PlaySoundMem(drop_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	// 1番目
	if (donut_num[0] == donut_y && donut_num[1] < donut_y)
	{
		donut_num[1] += 20;

		if (donut_num[1] >= donut_y)
		{
			donut_num[1] = donut_y;
			PlaySoundMem(drop_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	// 2番目
	if (donut_num[1] == donut_y && donut_num[2] < donut_y)
	{
		donut_num[2] += 20;

		if (donut_num[2] >= donut_y)
		{
			donut_num[2] = donut_y;
			PlaySoundMem(drop_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	return GetNowSceneType();
}

// 描画処理
void RankingScene::Draw() const
{
	// 背景
	DrawGraph(0, 0, background_img, FALSE);

	float base_radius = 296.5; // 元画像(288x288)の半径
	double scale = 0.57; // 画像の拡大率

	float donut_x = 235.0f;

	float donut_width = 410.0f;

	float shadow_x = 5;
	float shadow_y = 9;

	for (int i = 0; i < RANK_MAX_NUM; i++)
	{
		DrawRotaGraph2F(donut_x + i * donut_width + shadow_x, donut_num[i] + shadow_y, base_radius, base_radius, scale, 0, donut_img[1], TRUE);

		DrawRotaGraph2F(donut_x + i * donut_width, donut_num[i], base_radius, base_radius, scale, 0, donut_img[0], TRUE);

		DrawRotaGraph2F(donut_x + 40 + i * donut_width, donut_num[i] - 140, base_radius, base_radius, 0.32, 0, rank_img[i], TRUE);
	}

	RankingData* ranking = new RankingData();
	ranking->Initialize();

	double ranking_fontsize = 0.6; // 文字サイズ
	int default_x = 83; // 固定X座標
	int default_y = 333; // 固定Y座標
	int string_space = 412; // ランキング文字の表示間隔

	char ranking_buf[50];

	for (int i = 0; i < RANKING_DATA_MAX; i++)
	{
		// ランキングを文字列に変換
		sprintf_s(ranking_buf, sizeof(ranking_buf), "%08d", ranking->GetScore(i));

		FontManager::DrawNum(default_x + i * string_space, donut_num[i] - 54, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
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
