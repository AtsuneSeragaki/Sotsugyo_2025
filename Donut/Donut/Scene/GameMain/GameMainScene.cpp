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
	
	CollisionDonuts();

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

void GameMainScene::CollisionDonuts()
{
	std::vector<Donuts*> donutList;
	for (GameObject* obj : gameobjects->GetObjectList()) {
		Donuts* donut = dynamic_cast<Donuts*>(obj);
		if (donut) {
			donutList.push_back(donut);
		}
	}

	for (size_t i = 0; i < donutList.size(); ++i) {
		for (size_t j = i + 1; j < donutList.size(); ++j) {
			Donuts* a = donutList[i];
			Donuts* b = donutList[j];

			Vector2D delta = a->GetLocation() - b->GetLocation();
			float distSq = delta.x * delta.x + delta.y * delta.y;
			float rSum = a->GetRadiusSize() + b->GetRadiusSize();

			if (distSq < rSum * rSum) {
				// �������Ă�̂Ŕ��� or �ʒu�C���Ȃǂ��s��
				ResolveDonutCollision(a, b);
			}
		}
	}



}

void GameMainScene::ResolveDonutCollision(Donuts* a, Donuts* b)
{
	Vector2D delta = a->GetLocation() - b->GetLocation();
	float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
	float rSum = a->GetRadiusSize() + b->GetRadiusSize();

	if (dist == 0.0f) return; // ������

	float overlap = rSum - dist;
	Vector2D normal = delta / dist;

	// �d�Ȃ�����i�����������߂��j
	a->SetLocation(a->GetLocation() + normal * (overlap / 2.0f));
	b->SetLocation(b->GetLocation() - normal * (overlap / 2.0f));

	// �ȒP�Ȕ����i���˕Ԃ�j
	a->SetVelocity(a->GetVelocity() + normal * 0.3f);
	b->SetVelocity(b->GetVelocity() - normal * 0.3f);
}
