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
	{// �|�[�Y��Ԃ���Ȃ��Ƃ�
		
		if (CheckPlayerButtonCollision(PAUSE_LX, PAUSE_RX, PAUSE_LY, PAUSE_RY) == 1)
		{
			pause_collision = true;
		}
		else
		{
			pause_collision = false;
		}

		// �v���C���[�����N���b�N�����Ƃ�
		if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
		{
			// �|�[�Y�{�^���̏�ō��N���b�N������A�|�[�Y��Ԃɂ���
			if (pause_collision == true)
			{
				player->SetClickFlg(true);
				pause = true;
			}
			else if (player->GetDonutCollision() == true && player->GetClickFlg() == false)
			{// �v���C���[�ƃh�[�i�c���������Ă�����
				
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

				//// �v���C���[�Ɠ������Ă���h�[�i�c���폜/�I�[�_�[�̌������炷
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

				// �������Ă���h�[�i�c�����ׂď���
				for (Donuts* donut : donut_collision)
				{
					if (donut->GetPlayerCollisionFlg() == true)
					{
						order->DecrementDonutNum(donut->GetDonutType());
						donut->SetDead(true);
					}
				}
				player->SetDonutCollision(false);
				donut_collision.clear(); // �������I������̂ŃN���A
			}
			else if (pause_b1_collision == false && player->GetClickFlg() == false)
			{// ���N���b�N���ꂽ��h�[�i�c�𗎂Ƃ�

				player->SetClickFlg(true);

				// ���Ƃ��h�[�i�c�̎�ނ��擾
				DonutType type = player->GetDonutType();

				// �h�[�i�c��ǉ�(���Ƃ�)
				Donuts* donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f), type);

				// ���ɗ��Ƃ��h�[�i�c�̎�ނ����߂�
				player->ChooseRandomDonut();

				// ���Ƃ��h�[�i�c�̏���ύX����
				player->SetDonutRadius(donut->GetDonutRadius(player->GetDonutType()));
				player->SetDonutNumber(donut->GetDonutNumber(player->GetDonutType()));

				// ���ɗ��Ƃ��h�[�i�c�̏���ύX����
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

		// �h�[�i�c��������
		for (Donuts* donut : donutList)
		{
			donut->FallDonut(donutList);  // ���h�[�i�c����n��

			float upper_line = 100.0f;    // ��g�̈ʒu
			float d_locy = donut->GetLocation().y - donut->GetRadiusSize(); // �h�[�i�c�̏㑤��Y���W

			// �h�[�i�c����g����͂ݏo���Ă��Ȃ����m�F
			if (d_locy < upper_line && donut->GetLanded() == true)
			{
				is_gameover = true;
				WaitTimer(2000);
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

		// �v���C���[�ƃh�[�i�c�̓����蔻��
		// �܂��A�O�t���[���̓����蔻������N���A
		donut_collision.clear();
		player->SetDonutCollision(false);

		// �v���C���[�ƃh�[�i�c�̓����蔻��
		for (Donuts* donut : donutList)
		{
			//// �I�[�_�[�ɂ���h�[�i�c���H/�I�[�_�[�̃h�[�i�c�̌���0���傫�����H
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
					player->SetDonutCollision(true); // �������Ă���h�[�i�c����ł������true
					donut_collision.push_back(donut); // ���������h�[�i�c�����X�g�ɒǉ�
				}
				else
				{
					donut->SetPlayerCollisionFlg(false);
				}
			}
		}

		// �I�u�W�F�N�g�̍폜
		gameobjects->RemoveDeadObjects();
	}
	else
	{// �|�[�Y��Ԃ̂Ƃ�
		
		// �u������v�{�^���ƃv���C���[�J�[�\���̓����蔻��
		if (CheckPlayerButtonCollision(PAUSE_B1B2_LX, PAUSE_B1B2_RX, PAUSE_B1_LY, PAUSE_B1_RY) == 1)
		{
			// �������Ă�����t���O��true��
			pause_b1_collision = true;
		}
		else
		{
			pause_b1_collision = false;
		}

		// �u�^�C�g���ɖ߂�v�{�^���ƃv���C���[�J�[�\���̓����蔻��
		if (CheckPlayerButtonCollision(PAUSE_B1B2_LX, PAUSE_B1B2_RX, PAUSE_B2_LY, PAUSE_B2_RY) == 1)
		{
			// �������Ă�����t���O��true��
			pause_b2_collision = true;
		}
		else
		{
			pause_b2_collision = false;
		}

		// �{�^���ƃJ�[�\�����������Ă���Ƃ��ɁA�v���C���[�����N���b�N�����Ƃ��̏���
		if (pause_b1_collision == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
		{
			player->SetClickFlg(true);
			// �u������v�{�^�����N���b�N���ꂽ�Ƃ��A�|�[�Y��Ԃ�����
			pause = false;
			pause_b1_collision = false;
		}
		else if (pause_b2_collision == true && input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
		{
			player->SetClickFlg(true);
			// �u�^�C�g���ɖ߂�v�{�^�����N���b�N���ꂽ�Ƃ��A�^�C�g���ɉ�ʂɑJ��
			return eSceneType::eTitle;
		}
	}

	return GetNowSceneType();
}

void GameMainScene::Draw() const
{
	// �Q�[�����C���w�i�\��
	DrawBox(0, 0, 1280, 720, 0xD8C3A5, TRUE);

	SetFontSize(20);
	DrawString(0, 0, "GameMain", 0x1A2E40);
	//DrawFormatString(0, 50, 0x000000, "%d", pause_b1_collision);

	// �I�u�W�F�N�g�̕`��
	for (GameObject* obj : gameobjects->GetObjectList())
	{
		obj->Draw();
	}

	// �h�[�i�c�𗎂Ƃ��g�̕`��
	DrawBox(400, 100, 880, 680, 0x1A2E40, FALSE);

	// �X�R�A�\��
	SetFontSize(20);
	DrawString(170, 80, "�X�R�A", 0x1A2E40);
	SetFontSize(40);
	DrawFormatString(118, 125, 0x1A2E40, "%08d", score);
	DrawCircle(200, 135,100, 0x1A2E40, FALSE);

	// �i���̗֕\��
	SetFontSize(30);
	DrawString(1015, 300, "�i���̗�", 0x1A2E40);
	DrawCircle(1080, 510, 170, 0x1A2E40, FALSE);

	// �|�[�Y�{�^���\��
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
	DrawString(PAUSE_LX + 12, PAUSE_LY + 8, "���f����", 0x000000);

	// �|�[�Y��ʕ\��
	if (pause)
	{
		DrawBox(200, 70, 1080, 650, 0xfff8f0, TRUE);
		DrawBox(200, 70, 1080, 650, 0x000000, FALSE);

		SetFontSize(30);
		DrawString(580, 120, "�|�[�Y���", 0x000000);

		// �|�[�Y��ʂ̃{�^��(������)�\��
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
		DrawString(PAUSE_B1B2_LX + 105, PAUSE_B1_LY + 35, "������", 0x000000);

		// �|�[�Y��ʂ̃{�^��(�^�C�g���ɖ߂�)�\��
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
		DrawString(PAUSE_B1B2_LX + 40, PAUSE_B2_LY + 35, "�^�C�g���ɖ߂�", 0x000000);
	}
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

// �h�[�i�c���m�������������̏���(�����F�h�[�i�c1(��)�̏��A�h�[�i�c2(��)�̏��)
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

			score += a->GetDonutScore(a->GetDonutType());

			return;
		}
		else if (nextTypeIndex == MAX_DONUT_NUM)
		{
			// �ő�܂Ői���������̓��m�����̂���ƁA����������
			score += a->GetDonutScore(a->GetDonutType());

			// a���폜�Ώۂ�
			a->SetDead(true);

			// b���폜�Ώۂ�
			b->SetDead(true);

			return;
		}
	}

	// �h�[�i�c�̎��ʂ𔼌a�ɔ�Ⴓ����
	float massA = a->GetRadiusSize();
	float massB = b->GetRadiusSize();

	// ���݂̑��x
	Vector2D vA = a->GetVelocity();
	Vector2D vB = b->GetVelocity();

	// �Փˌ�̑��x�v�Z
	Vector2D delta = a->GetLocation() - b->GetLocation();
	float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
	float rSum = a->GetRadiusSize() + b->GetRadiusSize();

	if (dist == 0.0f) return;

	// �߂荞�ݖh�~�̂��߂̈ʒu�␳
	float overlap = rSum - dist;
	Vector2D normal = delta / dist;

	// ���ʂɉ������ʒu�␳
	a->SetLocation(a->GetLocation() + normal * (overlap * (massB / (massA + massB))));
	b->SetLocation(b->GetLocation() - normal * (overlap * (massA / (massA + massB))));

	// �^���ʕۑ��̖@���Ɋ�Â��e���Փ˂̌v�Z
	float a_dot_n = vA.x * normal.x + vA.y * normal.y;
	float b_dot_n = vB.x * normal.x + vB.y * normal.y;

	float new_a_dot_n = (a_dot_n * (massA - massB) + 2 * massB * b_dot_n) / (massA + massB);
	float new_b_dot_n = (b_dot_n * (massB - massA) + 2 * massA * a_dot_n) / (massA + massB);

	// �V�������x�x�N�g�����v�Z
	Vector2D v_a_new = vA + normal * (new_a_dot_n - a_dot_n);
	Vector2D v_b_new = vB + normal * (new_b_dot_n - b_dot_n);

	// �V�������x���Z�b�g�i�����W��0.85��K�p�j
	a->SetVelocity(v_a_new * 0.85f);
	b->SetVelocity(v_b_new * 0.85f);
}
//void GameMainScene::ResolveDonutCollision(Donuts* a, Donuts* b)
//{
//	if (a->IsDead() || b->IsDead()) return;
//
//	// �����^�C�v & �܂��i�����Ă��Ȃ�
//	if (a->GetDonutType() == b->GetDonutType() && !a->IsMerged() && !b->IsMerged())
//	{
//		int nextTypeIndex = static_cast<int>(a->GetDonutType()) + 1;
//
//		if (nextTypeIndex < MAX_DONUT_NUM)
//		{
//			// a��i��������
//			a->SetDonutType(static_cast<DonutType>(nextTypeIndex));
//			a->SetRadius(g_DonutInfoTable[nextTypeIndex].size);
//			a->SetMerged(true);
//
//			// b���폜�Ώۂ�
//			b->SetDead(true);
//
//			score += a->GetDonutScore(a->GetDonutType());
//
//			return; // �Փˉ����͕s�v�i1�ɂȂ邽�߁j
//		}
//		else if (nextTypeIndex == MAX_DONUT_NUM)
//		{// �ő�܂Ői���������̓��m�����̂���ƁA����������
//
//			score += a->GetDonutScore(a->GetDonutType());
//
//			// a���폜�Ώۂ�
//			a->SetDead(true);
//
//			// b���폜�Ώۂ�
//			b->SetDead(true);
//
//			return; // �Փˉ����͕s�v�i���������邽�߁j
//		}
//	}
//
//	// �ʏ�̏Փˏ����i�����j
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

// �g���ɂ���h�[�i�c�ƃv���C���[�̓����蔻�菈��(�߂�l�F0���������ĂȂ� 1���������Ă���)
int GameMainScene::CheckDonutPlayerCollision(Donuts* donut)
{
	InputManager* input = InputManager::GetInstance();

	// �v���C���[�̏��
	float player_pos_x  = player->GetLocation().x;
	float player_pos_y  = input->GetMouseLocation().y;
	float player_radius = 10.0f;

	// �h�[�i�c�̏��
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

// �v���C���[�J�[�\���ƃ{�^���̓����蔻��(�����F�����蔻�����肽���{�^���̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
int GameMainScene::CheckPlayerButtonCollision(int left, int right, int top, int bottom)
{
	InputManager* input = InputManager::GetInstance();

	// �v���C���[���
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

