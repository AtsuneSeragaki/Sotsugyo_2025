#include "DxLib.h"
#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"

// 初期化処理
void TitleScene::Initialize()
{
	button[0] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX, TITLE_START_BUTTON_LY, TITLE_START_BUTTON_RY, false, eSceneType::eGameMain,{100,15,0x5C4630,0.4,0.4},"START" };
	button[1] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,TITLE_HELP_BUTTON_LY,TITLE_HELP_BUTTON_RY,false,eSceneType::eHelp,{20,15,0x5C4630,0.4,0.4},"HOW TO PLAY" };
	button[2] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,TITLE_RANKING_BUTTON_LY,TITLE_RANKING_BUTTON_RY,false,eSceneType::eRanking,{70,15,0x5C4630,0.4,0.4},"RANKING" };
	button[3] = { TITLE_BUTTON_LX,TITLE_BUTTON_RX,TITLE_END_BUTTON_LY,TITLE_END_BUTTON_RY,false,eSceneType::eEnd,{115,15,0x5C4630,0.4,0.4},"EXIT" };

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/title2.png");
	background_img = tmp[0];

	for (int i = 0; i < MAX_DONUT_NUM; i++)
	{
		tmp = rm->GetImages(g_DonutInfoTable[i].image_path);
		donut_img[i] = tmp[0];
	}

	tmp = rm->GetImages("Resource/Images/donut2/donut_shadow1.png");
	donut_shadow_img[0] = tmp[0];

	tmp = rm->GetImages("Resource/Images/donut2/donut_shadow2.png");
	donut_shadow_img[1] = tmp[0];

	tmp = rm->GetImages("Resource/Images/donut2/donut_shadow3.png");
	donut_shadow_img[2] = tmp[0];

	donut1_x = 150.0f;
	donut1_y = -50.0f;

	donut2_x = 1150.0f;
	donut2_y = -300.0f;

	rotation1 = 0.0;
	rotation2 = 10.0;

	donut_number[0] = GetRand(MAX_DONUT_NUM - 1);
	donut_number[1] = GetRand(MAX_DONUT_NUM - 1);

}

// 更新処理
eSceneType TitleScene::Update()
{
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
	if (input->IsMouseTriggered())
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

	MoveDonut();

	return GetNowSceneType();
}

// 描画処理
void TitleScene::Draw() const
{
	// 背景
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xE0D9CE, TRUE);
	DrawGraph(0, 0, background_img, TRUE);

	// タイトル
	//FontManager::Draw(355, 100, 1, 1, 0x5C4630, "DONUT POP");

	DrawDonut();

	// メニューボタン
	DrawButton(TITLE_BUTTON_NUM, button);
}

// 終了時処理
void TitleScene::Finalize()
{
}

void TitleScene::DrawDonut() const
{
	float base_radius = 296.5; // 元画像(288x288)の半径
	double scale = (double)g_DonutInfoTable[6].size / (double)base_radius; // 画像の拡大率

	float shadow = 5;

	// 左側ドーナツ描画
	// 影
	if (donut_number[0] < 5 || donut_number[0] == 10)
	{
		DrawRotaGraph2F(donut1_x + shadow, donut1_y + shadow, base_radius, base_radius, scale, rotation1, donut_shadow_img[0], TRUE);
	}
	else if (donut_number[0] < 7)
	{
		DrawRotaGraph2F(donut1_x + shadow, donut1_y + shadow, base_radius, base_radius, scale, rotation1, donut_shadow_img[1], TRUE);
	}
	else
	{
		DrawRotaGraph2F(donut1_x + shadow, donut1_y + shadow, base_radius, base_radius, scale, rotation1, donut_shadow_img[2], TRUE);
	}

	// ドーナツ本体
	DrawRotaGraph2F(donut1_x, donut1_y, base_radius, base_radius, scale, rotation1, donut_img[donut_number[0]], TRUE);
	

	// 右側ドーナツ描画
	// 影
	if (donut_number[1] < 5 || donut_number[1] == 10)
	{
		DrawRotaGraph2F(donut2_x + shadow, donut2_y + shadow, base_radius, base_radius, scale, rotation2, donut_shadow_img[0], TRUE);
	}
	else if (donut_number[1] < 7)
	{
		DrawRotaGraph2F(donut2_x + shadow, donut2_y + shadow, base_radius, base_radius, scale, rotation2, donut_shadow_img[1], TRUE);
	}
	else
	{
		DrawRotaGraph2F(donut2_x + shadow, donut2_y + shadow, base_radius, base_radius, scale, rotation2, donut_shadow_img[2], TRUE);
	}

	// ドーナツ本体
	DrawRotaGraph2F(donut2_x, donut2_y, base_radius, base_radius, scale, rotation2, donut_img[donut_number[1]], TRUE);

}

// ドーナツの落下処理
void TitleScene::MoveDonut()
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

// 現在のシーン情報を返す
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}