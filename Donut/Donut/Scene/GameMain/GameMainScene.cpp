#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Order/Order.h"
#include "../../Objects/Ranking/RankingData.h"
#include "../../Utility/FontManager.h"
#include <cstdio>
#include "DxLib.h"

int GameMainScene::score = 0;

// コンストラクタ
GameMainScene::GameMainScene():gameobjects(nullptr),player(nullptr),order(nullptr),is_gameover(false),pause(false),gameover_timer(0),button{},marge_se(0),drop_se(0),delete_se(0),donut_creat_count(0),donut_creat_flg(true),ranking_data(nullptr),can_check_gameover(false),donut_image{},is_donutgraphloaded(false),circle_image(0)
{
}

// デストラクタ
GameMainScene::~GameMainScene()
{
	
}

// 初期化処理
void GameMainScene::Initialize()
{
	gameobjects = new GameObjectManager();
	score = 0;
	pause = false;
	is_gameover = false;
	gameover_timer = 0;
	player = gameobjects->CreateGameObject<Player>(Vector2D(600.0f, 60.0f));
	order  = gameobjects->CreateGameObject<Order>(Vector2D(0.0f, 0.0f));
	ranking_data = new RankingData();

	// ポーズボタン初期化
	button[0] = { PAUSE_LX,PAUSE_RX,PAUSE_LY,PAUSE_RY,false,eSceneType::eGameMain,{20,7,0x5C4630,0.2,0.2},"PAUSE" };

	// 「続ける」ボタン初期化
	button[1] = { PAUSE_B1_LX,PAUSE_B1_RX,PAUSE_B1B2_LY,PAUSE_B1B2_RY,false,eSceneType::eGameMain,{80,28,0x5C4630,0.38,0.38},"RESUME" };

	// 「タイトルに戻る」ボタン初期化
	button[2] = { PAUSE_B2_LX,PAUSE_B2_RX,PAUSE_B1B2_LY,PAUSE_B1B2_RY,false,eSceneType::eTitle,{19,28,0x5C4630,0.38,0.38},"BACK TO TITLE" };

	ResourceManager* rm = ResourceManager::GetInstance();
	marge_se = rm->GetSounds("Resource/Sounds/GameMain/marge_se.mp3");
	ChangeVolumeSoundMem(200, marge_se);

	drop_se = rm->GetSounds("Resource/Sounds/GameMain/drop_se.mp3");
	ChangeVolumeSoundMem(170, drop_se);

	delete_se = rm->GetSounds("Resource/Sounds/GameMain/delete_se.mp3");
	ChangeVolumeSoundMem(200, delete_se);

	std::vector<int> tmp;
	for (int i = 0; i < MAX_DONUT_NUM; i++)
	{
		tmp = rm->GetImages(g_DonutInfoTable[i].image_path);
		donut_image[i] = tmp[0];
	}

	tmp = rm->GetImages("Resource/Images/circle.png");
	circle_image = tmp[0];

	donut_creat_flg = true;
	donut_creat_count = 0;
}

// 更新処理
eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	// Update() 冒頭などに追加
	if (!can_check_gameover)
	{
		if (gameover_timer++ > 30) // 30フレーム後に再び有効化
		{
			can_check_gameover = true;
			gameover_timer = 0;
		}
	}

	if (is_gameover)
	{
		gameover_timer++;

		if (gameover_timer > 110)
		{
			return eSceneType::eResult;
		}

		return eSceneType::eGameMain;
	}

	if (!pause)
	{// ポーズ状態じゃないとき

		if (!donut_creat_flg)
		{
			CountDonutCreateTime();
		}

		// ポーズボタンの当たり判定処理
		PauseButtonCollision();

		// プレイヤーが左クリックした時の処理
		OnPlayerClick();

		// ドーナツリストを作成
		MakeDonutList();

		// ドーナツの落下処理(戻り値：シーン名)
		FallDonut();

		for (Donuts* donut : donut_list)
		{
			// 他ドーナツ情報を渡す
			donut->CheckDonutLanded(donut_list);
		}

		// 他のUpdate処理
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Update();
		}

		// ドーナツ同士の当たり判定
		CollisionDonuts();

		// ドーナツとプレイヤーの当たり判定処理
		HitDonutPlayerCollision();

		for (Donuts* donut : donut_list)
		{
			// 枠からはみ出していないか確認
			CheckDonutOutOfFrame(donut);
		}

		// オブジェクトの削除
		gameobjects->RemoveDeadObjects();
	}
	else
	{// ポーズ状態のとき
		
		// 更新処理(戻り値：シーン名)
		eSceneType next_scene = PauseUpdate();

		// 更新処理からの戻り値が現在のシーン名と違う場合、次のシーンに遷移
		if (GetNowSceneType() != next_scene)
		{
			return next_scene;
		}
	}

	return GetNowSceneType();
}

// 描画処理
void GameMainScene::Draw() const
{   
	// 枠の太さ
	int line_width = 3;

	const int numDonuts = 11;
	const float centerX = 1080.0f;
	const float centerY = 510.0f;
	const float radius = 170.0f;

	float angleOffset = -3.14159265f / 2.5f; // 上方向スタートに調整

	if (pause)
	{// ポーズ画面描画

		// ポーズ画面以外は暗くする
		// 描画輝度セット
		SetDrawBright(120, 120, 120);

		// ゲームメイン背景描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xE0D9CE, TRUE);

		// ドーナツを落とす枠描画
		DrawBox(FRAME_LX, FRAME_LY, FRAME_RX, FRAME_RY, 0xD8C3A5, TRUE);

		// オブジェクト描画
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Draw();
		}

		// ドーナツを落とす枠描画(枠を太くするために複数描画)
		for (int i = 0; i < line_width; i++)
		{
			DrawBox(FRAME_LX - i, FRAME_LY - i, FRAME_RX + i, FRAME_RY + i, 0xA67C52, FALSE);
		}

		// スコア描画
		DrawScore();

		// 進化の輪描画
		FontManager::Draw(960, 300, 0.2, 0.2, 0x5C4630, "DONUT EVOLUTION CHART");
		DrawCircle(1080, 510, 170, 0xD8C3A5, TRUE);

		for (int i = 0; i < numDonuts; i++) {
			float angle = 2.0f * 3.14159265f * i / numDonuts + angleOffset;

			int w, h;
			GetGraphSize(donut_image[i], &w, &h);  // 画像サイズ取得

			float centerX = 1080.0f;
			float centerY = 510.0f;
			float radius = 125.0f;

			float base_radius = 296.5f; // 元画像(288x288)の半径
			double scale = 28.0 / (double)base_radius; // 表示サイズ調整

			// 円周上の位置
			float x = centerX + radius * cosf(angle);
			float y = centerY + radius * sinf(angle);

			// DrawRotaGraph2F の中心を画像中心に設定
			DrawRotaGraph2F(
				x, y,              // 描画位置
				base_radius,        // 画像内で回転の基準X（中心）
				base_radius,        // 回転の基準Y（中心）
				scale,              // 拡大率
				0.0,              // 回転角度（円周に沿って向けたい場合）
				donut_image[i],
				TRUE
			);
		}

		DrawGraph(997, 425, circle_image, TRUE);

		// 進化の輪枠描画(枠を太くするために複数描画)
		for (int j = 0; j < line_width; j++)
		{
			DrawCircleAA(1080.0f, 510.0f, 170.0f + j, 64,0xA67C52, FALSE);
		}

		// ポーズボタン描画
		DrawButton(1, button);

		// 描画輝度を元に戻す
		SetDrawBright(255, 255, 255);

		PauseDraw();
	}
	else
	{
		// ゲームメイン背景描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xE0D9CE, TRUE);

		// ドーナツを落とす枠描画
		DrawBox(FRAME_LX, FRAME_LY, FRAME_RX, FRAME_RY, 0xD8C3A5, TRUE);
		
		// オブジェクト描画
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Draw();
		}

		// ドーナツを落とす枠描画(枠を太くするために複数描画)
		for (int i = 0; i < line_width; i++)
		{
			DrawBox(FRAME_LX - i, FRAME_LY - i, FRAME_RX + i, FRAME_RY + i, 0xA67C52, FALSE);
		}

		// スコア描画
		DrawScore();

		// 進化の輪描画
		FontManager::Draw(925, 290, 0.25, 0.25, 0x5C4630, "DONUT EVOLUTION CHART");
		DrawCircle(1080, 510, 170, 0xD8C3A5, TRUE);

		for (int i = 0; i < numDonuts; i++) {
			float angle = 2.0f * 3.14159265f * i / numDonuts + angleOffset;

			int w, h;
			GetGraphSize(donut_image[i], &w, &h);  // 画像サイズ取得

			float centerX = 1080.0f;
			float centerY = 510.0f;
			float radius = 125.0f;

			float base_radius = 296.5f; // 元画像(288x288)の半径
			double scale = 28.0 / (double)base_radius; // 表示サイズ調整

			// 円周上の位置
			float x = centerX + radius * cosf(angle);
			float y = centerY + radius * sinf(angle);

			// DrawRotaGraph2F の中心を画像中心に設定
			DrawRotaGraph2F(
				x, y,              // 描画位置
				base_radius,        // 画像内で回転の基準X（中心）
				base_radius,        // 回転の基準Y（中心）
				scale,              // 拡大率
				0.0,              // 回転角度（円周に沿って向けたい場合）
				donut_image[i],
				TRUE
			);
		}

		DrawGraph(997, 425, circle_image, TRUE);

		// 進化の輪枠描画(枠を太くするために複数描画)
		for (int j = 0; j < line_width; j++)
		{
			DrawCircleAA(1080.0f, 510.0f, 170.0f + j, 64, 0xA67C52, FALSE);
		}

		// ポーズボタン描画
		DrawButton(1, button);

		if (is_gameover)
		{
			FontManager::Draw(420, 350, 0.75, 0.75, 0x1A2E40, "GAME OVER!");
		}
	}
}

// 終了時処理
void GameMainScene::Finalize()
{
	ranking_data->Initialize();
	ranking_data->SetRankingData(score);
	delete player;
	delete gameobjects;
	delete order;
	donut_list.clear();
	donut_collision.clear();
}

// 現在のシーン情報を返す
eSceneType GameMainScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

// ドーナツ同士の当たり判定
void GameMainScene::CollisionDonuts()
{
	std::vector<Donuts*> donutList;
	for (GameObject* obj : gameobjects->GetObjectList()) 
	{
		Donuts* donut = dynamic_cast<Donuts*>(obj);

		if (donut) 
		{
			donutList.push_back(donut);
		}
	}

	for (size_t i = 0; i < donutList.size(); ++i) 
	{
		for (size_t j = i + 1; j < donutList.size(); ++j)
		{
			Donuts* a = donutList[i];
			Donuts* b = donutList[j];

			Vector2D delta = a->GetLocation() - b->GetLocation();
			float distSq = delta.x * delta.x + delta.y * delta.y;
			float rSum = a->GetRadiusSize() + b->GetRadiusSize();

			if (distSq < rSum * rSum)
			{
				// 当たってるので反発 or 位置修正などを行う
				ResolveDonutCollision(a, b);
			}
			else
			{
				// 枠からはみ出していないか確認
				CheckDonutOutOfFrame(a);
				CheckDonutOutOfFrame(b);
			}
		}
	}
}

// ドーナツ同士が当たった時の処理(引数：ドーナツ1(仮)の情報、ドーナツ2(仮)の情報)
void GameMainScene::ResolveDonutCollision(Donuts* a, Donuts* b)
{
	if (a->IsDead() || b->IsDead()) return;

	// 同じタイプ & まだ進化していない
	if (a->GetDonutType() == b->GetDonutType() && !a->IsMerged() && !b->IsMerged())
	{
		int nextTypeIndex = static_cast<int>(a->GetDonutType()) + 1;

		PlaySoundMem(marge_se, DX_PLAYTYPE_BACK, TRUE);

		// 合体後しばらくゲームオーバー判定を無効にする
		can_check_gameover = false;
		gameover_timer = 0;

		if (nextTypeIndex < MAX_DONUT_NUM)
		{
			// aを進化させる
			a->SetDonutType(static_cast<DonutType>(nextTypeIndex));
			a->SetRadius(g_DonutInfoTable[nextTypeIndex].size);
			a->SetImage(g_DonutInfoTable[nextTypeIndex].image_path);
			a->SetMerged(true);

			// bを削除対象に
			b->SetDead(true);

			AddScore(a);

			return;
		}
		else if (nextTypeIndex == MAX_DONUT_NUM)
		{
			// 最大まで進化したもの同士が合体すると、両方消える
			AddScore(a);

			// aを削除対象に
			a->SetDead(true);

			// bを削除対象に
			b->SetDead(true);

			return;
		}

		//// ←ここで速度をリセット or 抑制して跳ね防止
		//a->SetVelocity({ 0.0f, 0.0f });
		//b->SetVelocity({ 0.0f, 0.0f });

		//return; // ※以降の反発処理をスキップ！
	}

	// ドーナツの質量を半径に比例させる
	float massA = a->GetRadiusSize();
	float massB = b->GetRadiusSize();

	// 現在の速度
	Vector2D vA = a->GetVelocity();
	Vector2D vB = b->GetVelocity();

	// 衝突後の速度計算
	Vector2D delta = a->GetLocation() - b->GetLocation();
	float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
	float rSum = a->GetRadiusSize() + b->GetRadiusSize();

	if (dist == 0.0f) return;

	// めり込み防止のための位置補正
	float overlap = rSum - dist;
	Vector2D normal = delta / dist;

	// 質量に応じた位置補正
	a->SetLocation(a->GetLocation() + normal * (overlap * (massB / (massA + massB))));
	b->SetLocation(b->GetLocation() - normal * (overlap * (massA / (massA + massB))));

	// 運動量保存の法則に基づく弾性衝突の計算
	float a_dot_n = vA.x * normal.x + vA.y * normal.y;
	float b_dot_n = vB.x * normal.x + vB.y * normal.y;

	float new_a_dot_n = (a_dot_n * (massA - massB) + 2 * massB * b_dot_n) / (massA + massB);
	float new_b_dot_n = (b_dot_n * (massB - massA) + 2 * massA * a_dot_n) / (massA + massB);

	// 新しい速度ベクトルを計算
	Vector2D v_a_new = vA + normal * (new_a_dot_n - a_dot_n);
	Vector2D v_b_new = vB + normal * (new_b_dot_n - b_dot_n);

	// 新しい速度をセット（反発係数0.85を適用）
	a->SetVelocity(v_a_new * 0.85f);
	b->SetVelocity(v_b_new * 0.85f);
	/*a->SetVelocity(v_a_new * 0.8f);
	b->SetVelocity(v_b_new * 0.8f); */

	// 枠からはみ出していないか確認
	CheckDonutOutOfFrame(a);
	CheckDonutOutOfFrame(b);
}

// ドーナツとプレイヤーが当たった時の処理
void GameMainScene::HitDonutPlayerCollision()
{
	// プレイヤーとドーナツの当たり判定
	// まず、前フレームの当たり判定情報をクリア
	donut_collision.clear();
	player->SetDonutCollision(false);

	// プレイヤーとドーナツの当たり判定
	for (Donuts* donut : donut_list)
	{
		if (order->CheckDonutOrder(donut->GetDonutType()) == 1 && order->GetDonutOrderNum(donut->GetDonutType()) > 0)
		{
			if (CheckDonutPlayerCollision(donut) == 1)
			{
				donut->SetPlayerCollisionFlg(true);

				// 当たっているドーナツが一つでもあればtrue
				player->SetDonutCollision(true);

				// 当たったドーナツをリストに追加
				donut_collision.push_back(donut);
			}
			else
			{
				donut->SetPlayerCollisionFlg(false);
			}
		}
	}
}

// 枠内にあるドーナツとプレイヤーの当たり判定処理(戻り値：0→当たってない 1→当たっている)
int GameMainScene::CheckDonutPlayerCollision(Donuts* donut)
{
	InputManager* input = InputManager::GetInstance();

	// プレイヤーの情報
	float player_pos_x  = player->GetLocation().x;
	float player_pos_y  = input->GetMouseLocation().y;
	float player_radius = 10.0f;

	// ドーナツの情報
	float donut_pos_x  = donut->GetLocation().x;
	float donut_pos_y  = donut->GetLocation().y;
	float donut_radius = donut->GetRadiusSize();

	float dx = player_pos_x - donut_pos_x;
	float dy = player_pos_y - donut_pos_y;
	float dr = dx * dx + dy * dy;

	float ar = player_radius + donut_radius;
	float dl = ar * ar;
	
	if (dr < dl)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

// ポーズ状態の時の更新処理
eSceneType GameMainScene::PauseUpdate()
{
	InputManager* input = InputManager::GetInstance();

	// ボタンとプレイヤーカーソルの当たり判定
	for (int i = 1; i < GAMEMAIN_BUTTON_NUM; i++)
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
		for (int i = 1; i < GAMEMAIN_BUTTON_NUM; i++)
		{
			if (button[i].collision)
			{
				if (i == 1)
				{
					PlayButtonSound();
					player->SetClickFlg(true);
					// 「続ける」ボタンがクリックされたとき、ポーズ状態を解除
					pause = false;
					button[i].collision = false;
				}
				else
				{
					PlayButtonSound();
					player->SetClickFlg(true);
					// それぞれの画面に遷移
					return button[i].targetScene;
				}
			}
		}
	}

	return eSceneType::eGameMain;
}

// ポーズ状態の時の描画処理
void GameMainScene::PauseDraw() const
{
	// 背景
	DrawBox(200 + 60, 70 + 80, 1080 - 60, 650 - 120, 0xE0D9CE, TRUE);

	// 画面名
	FontManager::Draw(520, 200, 0.85, 0.85, 0x5C4630, "PAUSE");

	// ポーズ画面ボタンだけの新しい変数を作成
	ButtonState pause_button[2];
	pause_button[0] = button[1];
	pause_button[1] = button[2];

	// ボタン描画
	DrawButton(2, pause_button);
}

// スコア加算(引数：スコア加算するドーナツ情報)
void GameMainScene::AddScore(Donuts* donut)
{
	int add_score = score + donut->GetDonutScore(donut->GetDonutType());

	if (add_score < 99999999)
	{
		score = add_score;
	}
	else
	{
		score = 99999999;
	}
}

// ドーナツ落下処理
void GameMainScene::FallDonut()
{
	// ドーナツ落下処理
	for (Donuts* donut : donut_list)
	{
		// 他ドーナツ情報を渡す
		donut->FallDonut(donut_list);
	}
}

// ポーズボタンの当たり判定処理
void GameMainScene::PauseButtonCollision()
{
	if (CheckPlayerButtonCollision(button[0].lx, button[0].rx, button[0].ly, button[0].ry) == 1)
	{
		button[0].collision = true;
	}
	else
	{
		button[0].collision = false;
	}
}

// プレイヤーがクリックした時の処理(ポーズ状態じゃないとき)
void GameMainScene::OnPlayerClick()
{
	InputManager* input = InputManager::GetInstance();
	Donuts* donut = nullptr;

	// プレイヤーが左クリックしたとき
	if (input->IsMouseTriggered())
	{
		// ポーズボタンの上で左クリックしたら、ポーズ状態にする
		if (button[0].collision)
		{
			PlayButtonSound();
			player->SetClickFlg(true);
			pause = true;
			button[0].collision = false;
			player->SetClickFlg(false);
		}
		else if (player->GetDonutCollision() && !player->GetClickFlg())
		{// プレイヤーとドーナツが当たっていたら

			player->SetClickFlg(true);

			// 当たっているドーナツをすべて処理
			for (Donuts* donut : donut_collision)
			{
				if (donut->GetPlayerCollisionFlg() == true)
				{
					order->DecrementDonutNum(donut->GetDonutType());
					donut->SetDead(true);
				}
			}

			PlaySoundMem(delete_se, DX_PLAYTYPE_BACK, TRUE);

			player->SetDonutCollision(false);

			// 処理が終わったのでクリア
			donut_collision.clear();
		}
		else if (!button[1].collision && !player->GetClickFlg() && donut_creat_flg == true)
		{// 左クリックされたらドーナツを落とす

			player->SetClickFlg(true);

			donut_creat_flg = false;

			// 落とすドーナツの種類を取得
			DonutType type = player->GetDonutType();

			// ドーナツを追加(落とす)
			donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f), type);

			PlaySoundMem(drop_se, DX_PLAYTYPE_BACK, TRUE);

			// 次に落とすドーナツの種類を決める
			player->ChooseRandomDonut();

			// 落とすドーナツの情報を変更する
			player->SetDonutRadius(donut->GetDonutRadius(player->GetDonutType()));
			player->SetDonutNumber(donut->GetDonutNumber(player->GetDonutType()));

			// 次に落とすドーナツの情報を変更する
			player->SetNextDonutRadius(donut->GetDonutRadius(player->GetNextDonutType()));
			player->SetNextDonutNumber(donut->GetDonutNumber(player->GetNextDonutType()));
		}
	}
	else
	{
		player->SetClickFlg(false);
	}
}

// ドーナツリストを作成する処理
void GameMainScene::MakeDonutList()
{
	donut_list.clear();

	for (GameObject* obj : gameobjects->GetObjectList())
	{
		Donuts* donut = dynamic_cast<Donuts*>(obj);

		if (donut)
		{
			donut_list.push_back(donut);
			donut->SetMerged(false);
		}
	}
}

// スコア描画処理
void GameMainScene::DrawScore() const
{
	// スコア描画背景
	DrawCircle(200, 135, 105, 0xD8C3A5, TRUE);

	// 枠の太さ
	int line_width = 3;

	// 枠描画(枠を太くするために複数描画)
	for (int j = 0; j < line_width; j++)
	{
		DrawCircleAA(200.0f, 135.0f, 105.0f + j, 64, 0xA67C52, FALSE);
	}
	
	FontManager::Draw(155, 65, 0.3, 0.3, 0x5C4630, "SCORE");

	// スコアを文字列に変換
	char score_buf[16];
	sprintf_s(score_buf, sizeof(score_buf), "%08d", score);

	FontManager::Draw(115, 128, 0.3, 0.3, 0x5C4630, score_buf);
}

// ドーナツが枠からはみ出していないか確認する処理
void GameMainScene::CheckDonutOutOfFrame(Donuts* donut)
{
	//float upper_line = FRAME_LY;    // 上枠の位置
	//float d_locy = donut->GetLocation().y - donut->GetRadiusSize(); // ドーナツの上側のY座標

	//// ドーナツが上枠からはみ出していないか確認
	//if (d_locy < upper_line && donut->GetLanded())
	//{
	//	is_gameover = true;
	//}

	// 合体直後の不安定時間はスキップ
	if (!can_check_gameover)
		return;

	float upper_line = FRAME_LY;
	float d_locy = donut->GetLocation().y - donut->GetRadiusSize();

	// ドーナツが上枠を超えていて、ほぼ静止しているならゲームオーバー
	if (d_locy < upper_line && donut->GetLanded() && fabs(donut->GetVelocity().y) < 0.5f)
	{
		is_gameover = true;
	}
}

// 次のドーナツを生成できる時間をカウントする処理
void GameMainScene::CountDonutCreateTime()
{
	if (donut_creat_count < 20)
	{
		donut_creat_count++;
	}
	else
	{
		for (Donuts* donut : donut_list)
		{
			// 枠からはみ出していないか確認
			CheckDonutOutOfFrame(donut);
		}
		donut_creat_flg = true;
		donut_creat_count = 0;
	}
}

