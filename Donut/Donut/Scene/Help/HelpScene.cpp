#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/FontManager.h"
#include "DxLib.h"
#include <vector>

// コンストラクタ
HelpScene::HelpScene()
{
	int button_color = 0xD6A15D;        // ボタンのカラーコード
	int button_string_color = 0xffffff; // ボタンの文字のカラーコード
	int button_string_yspacing = 20;    // ボタンの文字の表示する高さ(ボタン左上Y座標からの距離)

	int start_button_xspacing = 115;   // ボタンの文字の表示する位置(ボタン左上X座標からの距離)
	int title_button_xspacing = 50;    // ボタンの文字の表示する位置(ボタン左上X座標からの距離)

	// リスタートボタン初期化
	button[0] = { HELP_START_BUTTON_LX,HELP_START_BUTTON_RX,HELP_BUTTON_LY,HELP_BUTTON_RY,false,eSceneType::eGameMain,{100,17,0x5C4630,0.35,0.35},"START" };

	// タイトルボタン初期化
	button[1] = { HELP_TITLE_BUTTON_LX,HELP_TITLE_BUTTON_RX,HELP_BUTTON_LY,HELP_BUTTON_RY,false,eSceneType::eTitle,{32,17,0x5C4630,0.35,0.35},"BACK TO TITLE" };

	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/help.png");
	background_img[0] = tmp[0];
	tmp = rm->GetImages("Resource/Images/help2.png");
	background_img[1] = tmp[0];
	tmp = rm->GetImages("Resource/Images/triangle2.png");
	triangle_img = tmp[0];
	for (int i = 0; i < MAX_DONUT_NUM; i++)
	{
		tmp = rm->GetImages(g_DonutInfoTable[i].image_path);
		donut_img[i] = tmp[0];
	}

	page_num = 0;
	triangle_collision = false;
}

// デストラクタ
HelpScene::~HelpScene()
{
}

// 初期化処理
void HelpScene::Initialize()
{
	
}

// 更新処理
eSceneType HelpScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	// ボタンとプレイヤーカーソルの当たり判定
	for (int i = 0; i < HELP_BUTTON_NUM; i++)
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

	TrianglePlayerCollision();

	// プレイヤーが左クリックした時の処理
	if (input->IsMouseTriggered())
	{
		PlayButtonSound();

		// 三角形ボタンに当たっていたら
		if (triangle_collision)
		{
			triangle_collision = false;

			if (page_num == 0)
			{
				page_num = 1;
			}
			else
			{
				page_num = 0;
			}
		}

		// スタートorタイトルボタンに当たっていたら
		for (int i = 0; i < HELP_BUTTON_NUM; i++)
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
void HelpScene::Draw() const
{
	// 三角形ボタン
	int y = 300; // Y座標
	double triangle_font_scale = 0.28; // フォントサイズ
	int triangle_font_y = y - 38; // フォントY座標 
	int shadow_pos = 5;
	int offset_y = 2;

	if (page_num == 0)
	{
		// 背景
		DrawGraph(0, 0, background_img[0], FALSE);

		float donut_y = 430.0f; // 描画Y座標（縦位置）
		float spacing = 15.0f;     // ドーナツ同士の空白幅（px）
		float current_x = 120.0f;   // 最初のドーナツ左端のX座標
		float base_radius = 296.5f; // 元画像(593x593)の半径

		for (int i = 0; i < MAX_DONUT_NUM; i++) 
		{
			double scale = ((double)g_DonutInfoTable[i].size - 7.0) / (double)base_radius; // 画像の拡大率

			float draw_w = base_radius * 2 * (float)scale;  // 拡大後の幅
			float draw_h = base_radius * 2 * (float)scale;  // 拡大後の高さ

			// DrawRotaGraph2F の左上座標 = current_x + 画像中心からのオフセット
			float draw_x = current_x;
			float draw_y = donut_y - draw_h / 2;     // Yは中心に揃える

			DrawRotaGraph2F(draw_x, draw_y, base_radius, base_radius, scale, 0.0, donut_img[i], TRUE);

			// 次のドーナツの左端X = 現在ドーナツの右端 + 空白
			current_x += draw_w + spacing;
		}

		// どのページにいるかの表示
		/*DrawCircleAA(630, 570, 7, 64, 0xA67C52, TRUE);
		DrawCircleAA(680, 570, 7, 64, 0x5C4630, TRUE);*/

		//FontManager::Draw(1150 + 3, triangle_font_y, triangle_font_scale, triangle_font_scale, 0x5C4630, "NEXT");

		if (triangle_collision)
		{
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(115, 128, 128);

			// 三角形ボタン
			DrawGraph(1150, y + offset_y, triangle_img, TRUE);

			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
		}
		else
		{

			// ボタン影描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(0, 0, 0);
			DrawGraph(1150 + shadow_pos, y + shadow_pos, triangle_img, TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// 三角形ボタン
			DrawGraph(1150, y, triangle_img, TRUE);
		}
	}
	else
	{
		// 背景
		DrawGraph(0, 0, background_img[1], FALSE);

		// どのページにいるかの表示
		/*DrawCircleAA(630, 570, 7, 64, 0x5C4630, TRUE);
		DrawCircleAA(680, 570, 7, 64, 0xA67C52, TRUE);

		FontManager::Draw(80 + 5, triangle_font_y, triangle_font_scale, triangle_font_scale, 0x5C4630, "BACK");*/

		if (triangle_collision)
		{
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(128, 128, 128);

			// 三角形ボタン
			DrawTurnGraph(80, y + offset_y, triangle_img, TRUE);

			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
		}
		else
		{
			// ボタン影描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
			// プレイヤーカーソルが当たっている時は、ボタンの色を暗くする
			SetDrawBright(0, 0, 0);
			DrawTurnGraph(80 + shadow_pos, y + shadow_pos, triangle_img, TRUE);
			// 描画輝度を元に戻す
			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// 三角形ボタン
			DrawTurnGraph(80, y, triangle_img, TRUE);
		}
	}

	// タイトル
	//FontManager::Draw(330, 30, 1, 1, 0x5C4630, "HOW TO PLAY");

	// メニューボタン
	DrawButton(HELP_BUTTON_NUM, button);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 終了時処理
void HelpScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}

// 内積を求める処理
float HelpScene::Dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

// 正規化処理
Vec2 HelpScene::Normalize(const Vec2& v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y);
	return { v.x / len, v.y / len };
}

// 辺から法線を作る(左法線)処理
Vec2 HelpScene::GetNormal(const Vec2& a, const Vec2& b)
{
	Vec2 edge = { b.x - a.x, b.y - a.y };
	return Normalize({ -edge.y, edge.x });
}

// 多角形を軸に投影する処理
void HelpScene::Project(const std::vector<Vec2>& poly, const Vec2& axis, float& minOut, float& maxOut)
{
	minOut = maxOut = Dot(poly[0], axis);
	for (size_t i = 1; i < poly.size(); i++) {
		float proj = Dot(poly[i], axis);
		if (proj < minOut) minOut = proj;
		if (proj > maxOut) maxOut = proj;
	}
}

// SAT判定処理
bool HelpScene::CheckSAT(const std::vector<Vec2>& polyA, const std::vector<Vec2>& polyB)
{
	std::vector<Vec2> axes;

	// Aの法線
	for (size_t i = 0; i < polyA.size(); i++) {
		Vec2 p1 = polyA[i];
		Vec2 p2 = polyA[(i + 1) % polyA.size()];
		axes.push_back(GetNormal(p1, p2));
	}
	// Bの法線
	for (size_t i = 0; i < polyB.size(); i++) {
		Vec2 p1 = polyB[i];
		Vec2 p2 = polyB[(i + 1) % polyB.size()];
		axes.push_back(GetNormal(p1, p2));
	}

	// すべての軸で重なりチェック
	for (auto& axis : axes) {
		float minA, maxA, minB, maxB;
		Project(polyA, axis, minA, maxA);
		Project(polyB, axis, minB, maxB);

		// 投影が重ならない → 分離軸あり → 当たっていない
		if (maxA < minB || maxB < minA)
		{
			triangle_collision = false;
			return false;
		}	
	}

	// 全軸で区間が重なった → 当たり
	triangle_collision = true;
	return true;
}

// プレイヤーと三角の当たり判定処理
bool HelpScene::TrianglePlayerCollision()
{
	InputManager* input = InputManager::GetInstance();

	std::vector<Vec2> triangle;

	float player_width = 5.0f;  // プレイヤーの幅
	float player_hight = 10.0f; // プレイヤーの高さ

	// プレイヤー情報
	float player_left = input->GetMouseLocation().x;
	float player_right = input->GetMouseLocation().x + player_width;
	float player_top = input->GetMouseLocation().y;
	float player_bottom = input->GetMouseLocation().y + player_hight;

	std::vector<Vec2> player = {
		{player_left, player_top},
		{player_right, player_top},
		{player_left, player_bottom},
		{player_right, player_bottom}
	};

	if (page_num == 0)
	{
		triangle = {
			{1135, 300},
			{1135, 380},
			{1205, 340}
		};
	}
	else
	{
		triangle = {
			{175, 300},
			{175, 380},
			{105, 340}
		};
	}

	return CheckSAT(triangle, player);
}
