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

	// ���N���b�N���ꂽ��h�[�i�c�𗎂Ƃ�
	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress && player->GetClickFlg() == false)
	{
		player->SetClickFlg(true);

		// ���Ƃ��h�[�i�c�̎�ނ��擾
		DonutType type = player->GetDonutType();

		// �h�[�i�c��ǉ�(���Ƃ�)
		Donuts* donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f),type);

		// ���ɗ��Ƃ��h�[�i�c�̎�ނ����߂�
		player->ChooseRandomDonut();

		// ���Ƃ��h�[�i�c�̏���ύX����
		player->SetDonutRadius(donut->GetDonutRadius(player->GetDonutType()));
		player->SetDonutNumber(donut->GetDonutNumber(player->GetDonutType()));

		// ���ɗ��Ƃ��h�[�i�c�̏���ύX����
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

	// �h�[�i�c��������
	for (Donuts* donut : donutList) 
	{
		donut->FallDonut(donutList);  // ���h�[�i�c����n��

		float upper_line = 100.0f; // ��g�̈ʒu
		float d_locy = donut->GetLocation().y - donut->GetRadiusSize(); // �h�[�i�c�̏㑤��Y���W

		// �h�[�i�c����g����͂ݏo���Ă��Ȃ����m�F
		if (d_locy < upper_line && donut->GetLanded() == true)
		{
			is_gameover = true;
			return eSceneType::eResult;
		}
	}

	// ����Update����
	for (GameObject* obj : gameobjects->GetObjectList())
	{
		obj->Update();
	}

	// �h�[�i�c���m�̓����蔻��
	CollisionDonuts();
	
	// �I�u�W�F�N�g�̍폜
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

	// �h�[�i�c�𗎂Ƃ��g�̕`��
	DrawBox(400, 100, 880, 680, 0xffffff, FALSE);
}

void GameMainScene::Finalize()
{
}

eSceneType GameMainScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

// �h�[�i�c���m�̓����蔻��
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
				// �������Ă�̂Ŕ��� or �ʒu�C���Ȃǂ��s��
				ResolveDonutCollision(a, b);
			}
		}
	}
}

// �����������̏���
void GameMainScene::ResolveDonutCollision(Donuts* a, Donuts* b)
{
	if (a->IsDead() || b->IsDead()) return;

	// �����^�C�v & �܂��i�����Ă��Ȃ�
	if (a->GetDonutType() == b->GetDonutType() && !a->IsMerged() && !b->IsMerged())
	{
		int nextTypeIndex = static_cast<int>(a->GetDonutType()) + 1;

		if (nextTypeIndex < MAX_DONUT_NUM)
		{
			// a��i��������
			a->SetDonutType(static_cast<DonutType>(nextTypeIndex));
			a->SetRadius(g_DonutInfoTable[nextTypeIndex].size);
			a->SetMerged(true);

			// b���폜�Ώۂ�
			b->SetDead(true);

			return; // �Փˉ����͕s�v�i1�ɂȂ邽�߁j
		}
		else if (nextTypeIndex == MAX_DONUT_NUM)
		{// �ő�܂Ői���������̓��m�����̂���ƁA����������

			// a���폜�Ώۂ�
			a->SetDead(true);

			// b���폜�Ώۂ�
			b->SetDead(true);

			return; // �Փˉ����͕s�v�i���������邽�߁j
		}
	}

	// �ʏ�̏Փˏ����i�����j
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

