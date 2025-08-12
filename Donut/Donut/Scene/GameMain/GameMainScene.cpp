#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Order/Order.h"
#include "DxLib.h"


GameMainScene::GameMainScene()
{
	gameobjects = new GameObjectManager();
	player = nullptr;
	is_gameover = false;
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete gameobjects;
}

void GameMainScene::Initialize()
{
	player = gameobjects->CreateGameObject<Player>(Vector2D(600.0f, 60.0f));
	gameobjects->CreateGameObject<Order>(Vector2D(0.0f, 0.0f));
}

eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	// 左クリックされたらドーナツを落とす
	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress && player->GetClickFlg() == false)
	{
		player->SetClickFlg(true);

		// 落とすドーナツの種類を取得
		DonutType type = player->GetDonutType();

		// ドーナツを追加(落とす)
		Donuts* donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f),type);

		// 次に落とすドーナツの種類を決める
		player->ChooseRandomDonut();

		// 落とすドーナツの情報を変更する
		player->SetDonutRadius(donut->GetDonutRadius(player->GetDonutType()));
		player->SetDonutNumber(donut->GetDonutNumber(player->GetDonutType()));

		// 次に落とすドーナツの情報を変更する
		player->SetNextDonutRadius(donut->GetDonutRadius(player->GetNextDonutType()));
		player->SetNextDonutNumber(donut->GetDonutNumber(player->GetNextDonutType()));
	}
	else if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::eNone)
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

		float upper_line = 100.0f; // 上枠の位置
		float d_locy = donut->GetLocation().y - donut->GetRadiusSize(); // ドーナツの上側のY座標

		// ドーナツが上枠からはみ出していないか確認
		if (d_locy < upper_line && donut->GetLanded() == true)
		{
			is_gameover = true;
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
	
	// オブジェクトの削除
	gameobjects->RemoveDeadObjects();

	return GetNowSceneType();
}

void GameMainScene::Draw() const
{
	SetFontSize(20);
	DrawString(0, 0, "GameMain", 0xffffff);
	DrawFormatString(0, 50, 0xffffff, "%d", is_gameover);

	for (GameObject* obj : gameobjects->GetObjectList())
	{
		obj->Draw();
	}

	// ドーナツを落とす枠の描画
	DrawBox(400, 100, 880, 680, 0xffffff, FALSE);
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

// 当たった時の処理
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

			return; // 衝突解決は不要（1つになるため）
		}
		else if (nextTypeIndex == MAX_DONUT_NUM)
		{// 最大まで進化したもの同士が合体すると、両方消える

			// aを削除対象に
			a->SetDead(true);

			// bを削除対象に
			b->SetDead(true);

			return; // 衝突解決は不要（両方消えるため）
		}
	}

	// 通常の衝突処理（反発）
	Vector2D delta = a->GetLocation() - b->GetLocation();
	float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
	float rSum = a->GetRadiusSize() + b->GetRadiusSize();

	if (dist == 0.0f) return;

	float overlap = rSum - dist;
	Vector2D normal = delta / dist;

	a->SetLocation(a->GetLocation() + normal * (overlap / 2.0f));
	b->SetLocation(b->GetLocation() - normal * (overlap / 2.0f));

	a->SetVelocity(a->GetVelocity() + normal * 0.3f);
	b->SetVelocity(b->GetVelocity() - normal * 0.3f);
}

