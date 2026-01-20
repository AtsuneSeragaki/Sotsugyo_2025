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
	tmp = rm->GetImages("Resource/Images/effect1.png");
	effect_img[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/effect2.png");
	effect_img[1] = tmp[0];

	for (int i = 0; i < 3; i++)
	{
		effect_alpha[i] = 0;
		effect_reverse[i] = 0;
	}

	effect_num[0] = 0;
	effect_num[1] = 1;
	effect_num[2] = 0;
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

	for (int i = 0; i < 3; i++)
	{
		if (effect_alpha[i] < 60)
		{
			effect_alpha[i]++;
		}
		else
		{
			effect_alpha[i] = 0;
			if (effect_num[i] == 0)
			{
				effect_num[i] = 1;
			}
			else
			{
				effect_num[i] = 0;
			}
		}
		
	}

	return GetNowSceneType();
}

// 描画処理
void RankingScene::Draw() const
{
	// 背景
	DrawGraph(0, 0, background_img, FALSE);

	int effect1_x = 180;
	int effect1_y = 230;

	int t = GetNowCount();
	
	float swayX = sinf(t * 0.004f) * 10.0f;   // 横揺れ
	float swayY = cosf(t * 0.003f) * 6.0f;    // 縦揺れ

	// エフェクト
	if (effect_num[0] == 0)
	{
		DrawRotaGraph(effect1_x + swayX,effect1_y + swayY,1.0, 0.0, effect_img[0], TRUE);

		DrawRotaGraph(effect1_x + 100 - swayX * 0.6f,effect1_y - 30 + swayY * 0.6f,1.0, 0.0, effect_img[1], TRUE);
	}
	else
	{
		DrawRotaGraph(effect1_x - 10 - swayX,effect1_y - 30 + swayY,1.0, 0.0, effect_img[1], TRUE);

		DrawRotaGraph(effect1_x + 110 + swayX * 0.6f,effect1_y + swayY * 0.6f,1.0, 0.0, effect_img[0], TRUE);
	}

	int effect2_x = 595;
	int effect2_y = 230;

	// エフェクト
	if (effect_num[1] == 0)
	{
		DrawRotaGraph(effect2_x, effect2_y, 1.0, 0.0, effect_img[0], TRUE);
		DrawRotaGraph(effect2_x + 100, effect2_y - 30, 1.0, 0.0, effect_img[1], TRUE);
	}
	else
	{
		DrawRotaGraph(effect2_x - 10, effect2_y - 30, 1.0, 0.0, effect_img[1], TRUE);
		DrawRotaGraph(effect2_x + 110, effect2_y, 1.0, 0.0, effect_img[0], TRUE);
	}

	int effect3_x = 1005;
	int effect3_y = 230;

	// エフェクト
	if (effect_num[2] == 0)
	{
		DrawRotaGraph(effect3_x, effect3_y, 1.0, 0.0, effect_img[0], TRUE);
		DrawRotaGraph(effect3_x + 100, effect3_y - 30, 1.0, 0.0, effect_img[1], TRUE);
	}
	else
	{
		DrawRotaGraph(effect3_x - 10, effect3_y - 30, 1.0, 0.0, effect_img[0], TRUE);
		DrawRotaGraph(effect3_x + 100, effect3_y, 1.0, 0.0, effect_img[1], TRUE);
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

		FontManager::DrawNum(default_x + i * string_space, default_y, ranking_fontsize, ranking_fontsize, 0x5C4630, ranking_buf);
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
