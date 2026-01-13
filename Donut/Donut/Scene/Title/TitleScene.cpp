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

	if (donut1_y <= 900.0f)
	{
		donut1_y += 3.4f;
	}
	else
	{
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

		int d_num1 = donut_number[0];

		do {
			donut_number[0] = GetRand(MAX_DONUT_NUM - 1);
		} while (d_num1 == donut_number[0]);
	}

	if (donut2_y <= 900.0f)
	{
		donut2_y += 3.4f;
	}
	else
	{
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

		int d_num2 = donut_number[1];

		do {
			donut_number[1] = GetRand(MAX_DONUT_NUM - 1);
		} while (d_num2 == donut_number[1]);
	}

	// 転がり中に回転を更新
	rotation1 += 0.85 / (double)g_DonutInfoTable[0].size;  // vxに応じて角度を加算（rが大きいとゆっくり回転）

	if (rotation1 > DX_TWO_PI)
	{
		rotation1 -= DX_TWO_PI;
	}

	rotation2 += 0.85 / (double)g_DonutInfoTable[0].size;  // vxに応じて角度を加算（rが大きいとゆっくり回転）

	if (rotation2 > DX_TWO_PI)
	{
		rotation2 -= DX_TWO_PI;
	}

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

	DonutDraw();

	// メニューボタン
	DrawButton(TITLE_BUTTON_NUM, button);
}

// 終了時処理
void TitleScene::Finalize()
{
}

void TitleScene::DonutDraw() const
{
	float base_radius = 296.5; // 元画像(288x288)の半径
	double scale = (double)g_DonutInfoTable[6].size / (double)base_radius; // 画像の拡大率

	DrawRotaGraph2F(donut1_x, donut1_y, base_radius, base_radius, scale, rotation1, donut_img[donut_number[0]], TRUE);
	DrawRotaGraph2F(donut2_x, donut2_y, base_radius, base_radius, scale, rotation2, donut_img[donut_number[1]], TRUE);

	/*SetFontSize(20);
	DrawFormatString(0, 10, 0x000000, "donut1_y:%f", donut1_y);
	DrawFormatString(0, 40, 0x000000, "donut2_y:%f", donut2_y);

	DrawFormatString(0, 70, 0x000000, "donut_number[0]:%d", donut_number[0]);
	DrawFormatString(0, 100, 0x000000, "donut_number[1]:%d", donut_number[1]);*/
}

// 現在のシーン情報を返す
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}