#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Order/Order.h"
#include "DxLib.h"


GameMainScene::GameMainScene()
{
	gameobjects = new GameObjectManager();
	player = nullptr;
	order  = nullptr;
	is_gameover = false;
	score = 0;
	pause = false;
	pause_collision = false;
	pause_b1_collision = false;
	pause_b2_collision = false;
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete gameobjects;
	delete order;
	donut_collision.clear();
}

void GameMainScene::Initialize()
{
	player = gameobjects->CreateGameObject<Player>(Vector2D(600.0f, 60.0f));
	order  = gameobjects->CreateGameObject<Order>(Vector2D(0.0f, 0.0f));
}

eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	if (!pause)
	{// ポーズ状態じゃないとき
		
		if (CheckPlayerButtonCollision(PAUSE_LX, PAUSE_RX, PAUSE_LY, PAUSE_RY) == 1)
		{
			pause_collision = true;
		}
		else
		{
			pause_collision = false;
		}

		// プレイヤーが左クリックしたとき
		if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
		{
			// ポーズボタンの上で左クリックしたら、ポーズ状態にする
			if (pause_collision == true)
			{
				player->SetClickFlg(true);
				pause = true;
			}
			else if (player->GetDonutCollision() == true && player->GetClickFlg() == false)
			{// プレイヤーとドーナツが当たっていたら
				
				player->SetClickFlg(true);
				
				//std::vector<Donuts*> donutList;
				//for (GameObject* obj : gameobjects->GetObjectList())
				//{
				//	Donuts* donut = dynamic_cast<Donuts*>(obj);

				//	if (donut)
				//	{
				//		donutList.push_back(donut);
				//		donut->SetMerged(false);
				//	}
				//}

				//// プレイヤーと当たっているドーナツを削除/オーダーの個数を減らす
				//for (Donuts* donut : donutList)
				//{
				//	if (donut->GetPlayerCollisionFlg() == true && donut == donut_collision)
				//	{
				//		order->DecrementDonutNum(donut->GetDonutType());
				//		donut->SetDead(true);
				//		player->SetDonutCollision(false);
				//		donut_collision.erase(donut);
				//	}
				//}

				// 当たっているドーナツをすべて処理
				for (Donuts* donut : donut_collision)
				{
					if (donut->GetPlayerCollisionFlg() == true)
					{
						order->DecrementDonutNum(donut->GetDonutType());
						donut->SetDead(true);
					}
				}
				player->SetDonutCollision(false);
				donut_collision.clear(); // 処理が終わったのでクリア
			}
			else if (pause_b1_collision == false && player->GetClickFlg() == false)
			{// 左クリックされたらドーナツを落とす

				player->SetClickFlg(true);

				// 落とすドーナツの種類を取得
				DonutType type = player->GetDonutType();

				// ドーナツを追加(落とす)
				Donuts* donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f), type);

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

		std::vector<Donuts*> donutList;
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			Donuts* donut = dynamic_cast<Donuts*>(obj);

			if (donut)
			{
				donutList.push_back(donut);
				donut->SetMerged(false);
			}
		}

		// ドーナツ落下処理
		for (Donuts* donut : donutList)
		{
			donut->FallDonut(donutList);  // 他ドーナツ情報を渡す

			float upper_line = 100.0f;    // 上枠の位置
			float d_locy = donut->GetLocation().y - donut->GetRadiusSize(); // ドーナツの上側のY座標

			// ドーナツが上枠からはみ出していないか確認
			if (d_locy < upper_line && donut->GetLanded() == true)
			{
				is_gameover = true;
				WaitTimer(2000);
				return eSceneType::eResult;
			}
		}

		// 他のUpdate処理
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Update();
		}

		// ドーナツ同士の当たり判定
		CollisionDonuts();

		// プレイヤーとドーナツの当たり判定
		// まず、前フレームの当たり判定情報をクリア
		donut_collision.clear();
		player->SetDonutCollision(false);

		// プレイヤーとドーナツの当たり判定
		for (Donuts* donut : donutList)
		{
			//// オーダーにあるドーナツか？/オーダーのドーナツの個数が0個より大きいか？
			//if (order->GetDonutOrder(donut->GetDonutType()) == 1 && order->GetDonutOrderNum(donut->GetDonutType()) > 0)
			//{
			//	CheckDonutPlayerCollision(donut);
			//}
			//else
			//{
			//	donut->SetPlayerCollisionFlg(false);
			//}

			if (order->GetDonutOrder(donut->GetDonutType()) == 1 && order->GetDonutOrderNum(donut->GetDonutType()) > 0)
			{
				if (CheckDonutPlayerCollision(donut) == 1)
				{
					donut->SetPlayerCollisionFlg(true);
					player->SetDonutCollision(true); // 当たっているドーナツが一つでもあればtrue
					donut_collision.push_back(donut); // 当たったドーナツをリストに追加
				}
				else
				{
					donut->SetPlayerCollisionFlg(false);
				}
			}
		}

		// オブジェクトの削除
		gameobjects->RemoveDeadObjects();
	}
	else
	{// ポーズ状態のとき
		
		// 「続ける」ボタンとプレイヤーカーソルの当たり判定
		if (CheckPlayerButtonCollision(PAUSE_B1B2_LX, PAUSE_B1B2_RX, PAUSE_B1_LY, PAUSE_B1_RY) == 1)
		{
			// 当たっていたらフラグをtrueに
			pause_b1_collision = true;
		}
		else
		{
			pause_b1_collision = false;
		}

		// 「タイトルに戻る」ボタンとプレイヤーカーソルの当たり判定
		if (CheckPlayerButtonCollision(PAUSE_B1B2_LX, PAUSE_B1B2_RX, PAUSE_B2_LY, PAUSE_B2_RY) == 1)
		{
			// 当たっていたらフラグをtrueに
			pause_b2_collision = true;
		}
		else
		{
			pause_b2_collision = false;
		}

		// ボタンとカーソルが当たっているときに、プレイヤーが左クリックしたときの処理
		if (pause_b1_collision == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
		{
			player->SetClickFlg(true);
			// 「続ける」ボタンがクリックされたとき、ポーズ状態を解除
			pause = false;
			pause_b1_collision = false;
		}
		else if (pause_b2_collision == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
		{
			player->SetClickFlg(true);
			// 「タイトルに戻る」ボタンがクリックされたとき、タイトルに画面に遷移
			return eSceneType::eTitle;
		}
	}

	return GetNowSceneType();
}

void GameMainScene::Draw() const
{
	// ゲームメイン背景表示
	DrawBox(0, 0, 1280, 720, 0xD8C3A5, TRUE);

	SetFontSize(20);
	DrawString(0, 0, "GameMain", 0x1A2E40);
	//DrawFormatString(0, 50, 0x000000, "%d", pause_b1_collision);

	// オブジェクトの描画
	for (GameObject* obj : gameobjects->GetObjectList())
	{
		obj->Draw();
	}

	// ドーナツを落とす枠の描画
	DrawBox(400, 100, 880, 680, 0x1A2E40, FALSE);

	// スコア表示
	SetFontSize(20);
	DrawString(170, 80, "スコア", 0x1A2E40);
	SetFontSize(40);
	DrawFormatString(118, 125, 0x1A2E40, "%08d", score);
	DrawCircle(200, 135,100, 0x1A2E40, FALSE);

	// 進化の輪表示
	SetFontSize(30);
	DrawString(1015, 300, "進化の輪", 0x1A2E40);
	DrawCircle(1080, 510, 170, 0x1A2E40, FALSE);

	// ポーズボタン表示
	if (pause_collision == true || pause == true)
	{
		SetDrawBright(128, 128, 128);
		DrawBox(PAUSE_LX, PAUSE_LY, PAUSE_RX, PAUSE_RY, 0xffffff, TRUE);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(PAUSE_LX, PAUSE_LY, PAUSE_RX, PAUSE_RY, 0xffffff, TRUE);
	}

	SetFontSize(17);
	DrawString(PAUSE_LX + 12, PAUSE_LY + 8, "中断する", 0x000000);

	// ポーズ画面表示
	if (pause)
	{
		DrawBox(200, 70, 1080, 650, 0xfff8f0, TRUE);
		DrawBox(200, 70, 1080, 650, 0x000000, FALSE);

		SetFontSize(30);
		DrawString(580, 120, "ポーズ画面", 0x000000);

		// ポーズ画面のボタン(続ける)表示
		if (pause_b1_collision == true)
		{
			SetDrawBright(128, 128, 128);
			DrawBox(PAUSE_B1B2_LX, PAUSE_B1_LY, PAUSE_B1B2_RX, PAUSE_B1_RY, 0xffffff, TRUE);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			DrawBox(PAUSE_B1B2_LX, PAUSE_B1_LY, PAUSE_B1B2_RX, PAUSE_B1_RY, 0xffffff, TRUE);
		}

		SetFontSize(30);
		DrawString(PAUSE_B1B2_LX + 105, PAUSE_B1_LY + 35, "続ける", 0x000000);

		// ポーズ画面のボタン(タイトルに戻る)表示
		if (pause_b2_collision == true)
		{
			SetDrawBright(128, 128, 128);
			DrawBox(PAUSE_B1B2_LX, PAUSE_B2_LY, PAUSE_B1B2_RX, PAUSE_B2_RY, 0xffffff, TRUE);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			DrawBox(PAUSE_B1B2_LX, PAUSE_B2_LY, PAUSE_B1B2_RX, PAUSE_B2_RY, 0xffffff, TRUE);
		}

		SetFontSize(30);
		DrawString(PAUSE_B1B2_LX + 40, PAUSE_B2_LY + 35, "タイトルに戻る", 0x000000);
	}
}

void GameMainScene::Finalize()
{
}

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

		if (nextTypeIndex < MAX_DONUT_NUM)
		{
			// aを進化させる
			a->SetDonutType(static_cast<DonutType>(nextTypeIndex));
			a->SetRadius(g_DonutInfoTable[nextTypeIndex].size);
			a->SetMerged(true);

			// bを削除対象に
			b->SetDead(true);

			score += a->GetDonutScore(a->GetDonutType());

			return;
		}
		else if (nextTypeIndex == MAX_DONUT_NUM)
		{
			// 最大まで進化したもの同士が合体すると、両方消える
			score += a->GetDonutScore(a->GetDonutType());

			// aを削除対象に
			a->SetDead(true);

			// bを削除対象に
			b->SetDead(true);

			return;
		}
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
}
//void GameMainScene::ResolveDonutCollision(Donuts* a, Donuts* b)
//{
//	if (a->IsDead() || b->IsDead()) return;
//
//	// 同じタイプ & まだ進化していない
//	if (a->GetDonutType() == b->GetDonutType() && !a->IsMerged() && !b->IsMerged())
//	{
//		int nextTypeIndex = static_cast<int>(a->GetDonutType()) + 1;
//
//		if (nextTypeIndex < MAX_DONUT_NUM)
//		{
//			// aを進化させる
//			a->SetDonutType(static_cast<DonutType>(nextTypeIndex));
//			a->SetRadius(g_DonutInfoTable[nextTypeIndex].size);
//			a->SetMerged(true);
//
//			// bを削除対象に
//			b->SetDead(true);
//
//			score += a->GetDonutScore(a->GetDonutType());
//
//			return; // 衝突解決は不要（1つになるため）
//		}
//		else if (nextTypeIndex == MAX_DONUT_NUM)
//		{// 最大まで進化したもの同士が合体すると、両方消える
//
//			score += a->GetDonutScore(a->GetDonutType());
//
//			// aを削除対象に
//			a->SetDead(true);
//
//			// bを削除対象に
//			b->SetDead(true);
//
//			return; // 衝突解決は不要（両方消えるため）
//		}
//	}
//
//	// 通常の衝突処理（反発）
//	Vector2D delta = a->GetLocation() - b->GetLocation();
//	float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
//	float rSum = a->GetRadiusSize() + b->GetRadiusSize();
//
//	if (dist == 0.0f) return;
//
//	float overlap = rSum - dist;
//	Vector2D normal = delta / dist;
//
//	a->SetLocation(a->GetLocation() + normal * (overlap / 2.0f));
//	b->SetLocation(b->GetLocation() - normal * (overlap / 2.0f));
//
//	a->SetVelocity(a->GetVelocity() + normal * 0.3f);
//	b->SetVelocity(b->GetVelocity() - normal * 0.3f);
//}

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
		/*donut->SetPlayerCollisionFlg(true);
		player->SetDonutCollision(true);*/
		return 1;
	}
	else
	{
		/*donut->SetPlayerCollisionFlg(false);
		player->SetDonutCollision(false);*/
		return 0;
	}
	
}

// プレイヤーカーソルとボタンの当たり判定(引数：当たり判定を取りたいボタンの情報　戻り値：0→当たってない 1→当たっている)
int GameMainScene::CheckPlayerButtonCollision(int left, int right, int top, int bottom)
{
	InputManager* input = InputManager::GetInstance();

	// プレイヤー情報
	int player_l = (int)input->GetMouseLocation().x - 5;
	int player_r = (int)input->GetMouseLocation().x + 10;
	int player_t = (int)input->GetMouseLocation().y;
	int player_b = (int)input->GetMouseLocation().y + 10;

	if ((player_r > left) && (player_l < right))
	{
		if ((player_b > top) && (player_t < bottom))
		{
			return 1;
		}
	}

	return 0;
}

