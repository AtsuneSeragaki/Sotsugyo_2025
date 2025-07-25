#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Donuts/Donuts.h"
#include "DxLib.h"


GameMainScene::GameMainScene()
{
	gameobjects = new GameObjectManager();
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{
	player = gameobjects->CreateGameObject<Player>(Vector2D(600.0f, 60.0f));
}

eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	// 左クリックされたらドーナツを落とす
	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress && player->GetClickFlg() == false)
	{
		player->SetClickFlg(true);

		// ドーナツを新しく追加
		gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f));
	}
	else if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::eNone)
	{
		player->SetClickFlg(false);
	}

	for (GameObject* obj : gameobjects->GetObjectList())
	{
		obj->Update();
	}

	return GetNowSceneType();
}

void GameMainScene::Draw() const
{
	SetFontSize(20);
	DrawString(0, 0, "GameMain", 0xffffff);

	for (GameObject* obj : gameobjects->GetObjectList())
	{
		obj->Draw();
	}

	// ドーナツを落とす枠の描画
	DrawBox(400, 100, 880, 680, 0xffffff, FALSE);

	DrawFormatString(0, 30, 0xffffff, "%d", player->GetClickFlg());
}

void GameMainScene::Finalize()
{
}

eSceneType GameMainScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}
