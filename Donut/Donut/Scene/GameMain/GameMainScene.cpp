#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Player/Player.h"
#include "DxLib.h"


GameMainScene::GameMainScene()
{
	gameobjects = new GameObjectManager();
	player = nullptr;
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete gameobjects;
}

void GameMainScene::Initialize()
{
	player = gameobjects->CreateGameObject<Player>(Vector2D(600.0f, 60.0f));
}

eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	// ���N���b�N���ꂽ��h�[�i�c�𗎂Ƃ�
	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress && player->GetClickFlg() == false)
	{
		player->SetClickFlg(true);

		// ���Ƃ��h�[�i�c�̎�ނ��擾
		DonutType type = player->GetNextDonutType();

		// �h�[�i�c��ǉ�(���Ƃ�)
		Donuts* donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f),type);

		// ���ɗ��Ƃ��h�[�i�c�̎�ނ����߂�
		player->ChooseRandomDonut();

		player->SetDonutRadius(donut->GetDonutRadius(player->GetNextDonutType()));

		player->SetNextDonutRadius(donut->GetDonutRadius(player->GetNextNextDonutType()));
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

	// �h�[�i�c�𗎂Ƃ��g�̕`��
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
