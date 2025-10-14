#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/Order/Order.h"
#include "DxLib.h"

int GameMainScene::score = 0;

// �R���X�g���N�^
GameMainScene::GameMainScene():gameobjects(nullptr),player(nullptr),order(nullptr),is_gameover(false),pause(false),gameover_timer(0),button{},marge_se(0),drop_se(0),delete_se(0),donut_creat_count(0),donut_creat_flg(true)
{
}

// �f�X�g���N�^
GameMainScene::~GameMainScene()
{
	
}

// ����������
void GameMainScene::Initialize()
{
	gameobjects = new GameObjectManager();
	score = 0;
	pause = false;
	is_gameover = false;
	gameover_timer = 0;
	player = gameobjects->CreateGameObject<Player>(Vector2D(600.0f, 60.0f));
	order  = gameobjects->CreateGameObject<Order>(Vector2D(0.0f, 0.0f));

	// �|�[�Y�{�^��������
	button[0] = { PAUSE_LX,PAUSE_RX,PAUSE_LY,PAUSE_RY,false,eSceneType::eGameMain };

	// �u������v�{�^��������
	button[1] = { PAUSE_B1B2_LX,PAUSE_B1B2_RX,PAUSE_B1_LY,PAUSE_B1_RY,false,eSceneType::eGameMain };

	// �u�^�C�g���ɖ߂�v�{�^��������
	button[2] = { PAUSE_B1B2_LX,PAUSE_B1B2_RX,PAUSE_B2_LY,PAUSE_B2_RY,false,eSceneType::eTitle };

	ResourceManager* rm = ResourceManager::GetInstance();
	marge_se = rm->GetSounds("Resource/Sounds/GameMain/marge_se.mp3");
	ChangeVolumeSoundMem(200, marge_se);

	drop_se = rm->GetSounds("Resource/Sounds/GameMain/drop_se.mp3");
	ChangeVolumeSoundMem(170, drop_se);

	delete_se = rm->GetSounds("Resource/Sounds/GameMain/delete_se.mp3");
	ChangeVolumeSoundMem(200, delete_se);

	donut_creat_flg = true;
	donut_creat_count = 0;
}

// �X�V����
eSceneType GameMainScene::Update()
{

	InputManager* input = InputManager::GetInstance();

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
	{// �|�[�Y��Ԃ���Ȃ��Ƃ�
		if (!donut_creat_flg)
		{
			CountDonutCreateTime();
		}

		// �|�[�Y�{�^���̓����蔻�菈��
		PauseButtonCollision();

		// �v���C���[�����N���b�N�������̏���
		OnPlayerClick();

		// �h�[�i�c���X�g���쐬
		MakeDonutList();

		// �h�[�i�c�̗�������(�߂�l�F�V�[����)
		FallDonut();

		// ����Update����
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Update();
		}

		// �h�[�i�c���m�̓����蔻��
		CollisionDonuts();

		// �h�[�i�c�ƃv���C���[�̓����蔻�菈��
		HitDonutPlayerCollision();

		for (Donuts* donut : donut_list)
		{
			// ���h�[�i�c����n��
			donut->CheckDonutLanded(donut_list);
		}

		for (Donuts* donut : donut_list)
		{
			// �g����͂ݏo���Ă��Ȃ����m�F
			CheckDonutOutOfFrame(donut);
		}

		// �I�u�W�F�N�g�̍폜
		gameobjects->RemoveDeadObjects();
	}
	else
	{// �|�[�Y��Ԃ̂Ƃ�
		
		// �X�V����(�߂�l�F�V�[����)
		eSceneType next_scene = PauseUpdate();

		// �X�V��������̖߂�l�����݂̃V�[�����ƈႤ�ꍇ�A���̃V�[���ɑJ��
		if (GetNowSceneType() != next_scene)
		{
			return next_scene;
		}
	}

	return GetNowSceneType();
}

// �`�揈��
void GameMainScene::Draw() const
{   
	if (pause)
	{// �|�[�Y��ʕ`��

		// �|�[�Y��ʈȊO�͈Â�����
		// �`��P�x�Z�b�g
		SetDrawBright(128, 128, 128);

		// �Q�[�����C���w�i�`��
		//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xD8C3A5, TRUE);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

		// �h�[�i�c�𗎂Ƃ��g�`��
		DrawBox(FRAME_LX, FRAME_LY, FRAME_RX, FRAME_RY, 0xD8C3A5, TRUE);

		// �I�u�W�F�N�g�`��
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Draw();
		}

		// �h�[�i�c�𗎂Ƃ��g�`��
		DrawBox(FRAME_LX, FRAME_LY, FRAME_RX, FRAME_RY, 0x1A2E40, FALSE);

		// �X�R�A�`��
		DrawScore();

		// �i���̗֕`��
		SetFontSize(30);
		DrawString(960, 300, "Donut Evolution Chart", 0x1A2E40);
		DrawCircle(1080, 510, 170, 0xD8C3A5, TRUE);
		DrawCircle(1080, 510, 170, 0x1A2E40, FALSE);

		// �|�[�Y�{�^���`��
		DrawPauseButton();

		// �`��P�x�����ɖ߂�
		SetDrawBright(255, 255, 255);

		PauseDraw();
	}
	else
	{
		// �Q�[�����C���w�i�`��
		//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xD8C3A5, TRUE);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

		// �h�[�i�c�𗎂Ƃ��g�`��
		DrawBox(FRAME_LX, FRAME_LY, FRAME_RX, FRAME_RY, 0xD8C3A5, TRUE);
		
		// �I�u�W�F�N�g�`��
		for (GameObject* obj : gameobjects->GetObjectList())
		{
			obj->Draw();
		}

		// �h�[�i�c�𗎂Ƃ��g�`��
		DrawBox(FRAME_LX, FRAME_LY, FRAME_RX, FRAME_RY, 0x1A2E40, FALSE);

		// �X�R�A�`��
		DrawScore();

		// �i���̗֕`��
		SetFontSize(20);
		DrawString(960, 300, "DONUT EVOLUTION CHART", 0x1A2E40);
		DrawCircle(1080, 510, 170, 0xD8C3A5, TRUE);
		DrawCircle(1080, 510, 170, 0x1A2E40, FALSE);

		// �|�[�Y�{�^���`��
		DrawPauseButton();

		if (is_gameover)
		{
			SetFontSize(60);
			DrawString(495, 350, "GAME OVER!", 0x000000);
		}
	}
}

// �I��������
void GameMainScene::Finalize()
{
	delete player;
	delete gameobjects;
	delete order;
	donut_list.clear();
	donut_collision.clear();
}

// ���݂̃V�[������Ԃ�
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
			else
			{
				// �g����͂ݏo���Ă��Ȃ����m�F
				CheckDonutOutOfFrame(a);
				CheckDonutOutOfFrame(b);
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

		PlaySoundMem(marge_se, DX_PLAYTYPE_BACK, TRUE);

		if (nextTypeIndex < MAX_DONUT_NUM)
		{
			// a��i��������
			a->SetDonutType(static_cast<DonutType>(nextTypeIndex));
			a->SetRadius(g_DonutInfoTable[nextTypeIndex].size);
			a->SetMerged(true);

			// b���폜�Ώۂ�
			b->SetDead(true);

			AddScore(a);

			return;
		}
		else if (nextTypeIndex == MAX_DONUT_NUM)
		{
			// �ő�܂Ői���������̓��m�����̂���ƁA����������
			AddScore(a);

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

	// �g����͂ݏo���Ă��Ȃ����m�F
	CheckDonutOutOfFrame(a);
	CheckDonutOutOfFrame(b);
}

// �h�[�i�c�ƃv���C���[�������������̏���
void GameMainScene::HitDonutPlayerCollision()
{
	// �v���C���[�ƃh�[�i�c�̓����蔻��
	// �܂��A�O�t���[���̓����蔻������N���A
	donut_collision.clear();
	player->SetDonutCollision(false);

	// �v���C���[�ƃh�[�i�c�̓����蔻��
	for (Donuts* donut : donut_list)
	{
		if (order->CheckDonutOrder(donut->GetDonutType()) == 1 && order->GetDonutOrderNum(donut->GetDonutType()) > 0)
		{
			if (CheckDonutPlayerCollision(donut) == 1)
			{
				donut->SetPlayerCollisionFlg(true);

				// �������Ă���h�[�i�c����ł������true
				player->SetDonutCollision(true);

				// ���������h�[�i�c�����X�g�ɒǉ�
				donut_collision.push_back(donut);
			}
			else
			{
				donut->SetPlayerCollisionFlg(false);
			}
		}
	}
}

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
		return 1;
	}
	else
	{
		return 0;
	}
	
}

// �|�[�Y��Ԃ̎��̍X�V����
eSceneType GameMainScene::PauseUpdate()
{
	InputManager* input = InputManager::GetInstance();

	// �{�^���ƃv���C���[�J�[�\���̓����蔻��
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

	// �{�^���̏�ŃN���b�N������A���ꂼ��̉�ʂɑJ�ڂ���
	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{		
		for (int i = 1; i < GAMEMAIN_BUTTON_NUM; i++)
		{
			if (button[i].collision)
			{
				if (i == 1)
				{
					PlayButtonSound();
					player->SetClickFlg(true);
					// �u������v�{�^�����N���b�N���ꂽ�Ƃ��A�|�[�Y��Ԃ�����
					pause = false;
					button[i].collision = false;
				}
				else
				{
					PlayButtonSound();
					player->SetClickFlg(true);
					// ���ꂼ��̉�ʂɑJ��
					return button[i].targetScene;
				}

			}
		}
	}

	return eSceneType::eGameMain;
}

// �|�[�Y��Ԃ̎��̕`�揈��
void GameMainScene::PauseDraw() const
{
	// �w�i
	DrawBox(200, 70, 1080, 650, 0xD8C3A5, TRUE);
	//DrawBox(200, 70, 1080, 650, 0xfff8f0, TRUE);
	DrawBox(200, 70, 1080, 650, 0x000000, FALSE);

	// ��ʖ�
	SetFontSize(80);
	DrawString(555, 120, "PAUSE", 0x000000);

	int button_color = 0xffffff;        // �{�^���̃J���[�R�[�h
	int button_string_color = 0x000000; // �{�^���̕����̃J���[�R�[�h
	int resume_xspacing = 105;          // RESUME�{�^���̕����̕\�����鍂��(�{�^������X���W����̋���)
	int title_xspacing = 50;            // BACK TO TITLE�{�^���̕����̕\�����鍂��(�{�^������X���W����̋���)
	int button_string_yspacing = 35;    // �{�^���̕����̕\�����鍂��(�{�^������Y���W����̋���)


	// �|�[�Y��ʃ{�^�������̐V�����ϐ����쐬
	ButtonState pause_button[2];
	pause_button[0] = button[1];
	pause_button[1] = button[2];

	// �{�^���`��
	DrawButton(2, pause_button, button_color);

	// �{�^�������`��(�摜���o���������)
	for (int i = 1; i < GAMEMAIN_BUTTON_NUM; i++)
	{
		if (button[i].collision)
		{
			if (i == 1)
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + resume_xspacing, button[i].ly + button_string_yspacing, "RESUME", button_string_color);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				SetDrawBright(128, 128, 128);
				SetFontSize(30);
				DrawString(button[i].lx + title_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
				SetDrawBright(255, 255, 255);
			}

		}
		else
		{
			if (i == 1)
			{
				SetFontSize(30);
				DrawString(button[i].lx + resume_xspacing, button[i].ly + button_string_yspacing, "RESUME", button_string_color);
			}
			else
			{
				SetFontSize(30);
				DrawString(button[i].lx + title_xspacing, button[i].ly + button_string_yspacing, "BACK TO TITLE", button_string_color);
			}
		}
	}
}

// �X�R�A���Z(�����F�X�R�A���Z����h�[�i�c���)
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

// �h�[�i�c��������
void GameMainScene::FallDonut()
{
	// �h�[�i�c��������
	for (Donuts* donut : donut_list)
	{
		// ���h�[�i�c����n��
		donut->FallDonut(donut_list);
	}
}

// �|�[�Y�{�^���̓����蔻�菈��
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

// �v���C���[���N���b�N�������̏���(�|�[�Y��Ԃ���Ȃ��Ƃ�)
void GameMainScene::OnPlayerClick()
{
	InputManager* input = InputManager::GetInstance();
	Donuts* donut = nullptr;

	// �v���C���[�����N���b�N�����Ƃ�
	if (input->GetMouseInputState(MOUSE_INPUT_LEFT) == eInputState::ePress)
	{
		// �|�[�Y�{�^���̏�ō��N���b�N������A�|�[�Y��Ԃɂ���
		if (button[0].collision)
		{
			PlayButtonSound();
			player->SetClickFlg(true);
			pause = true;
			button[0].collision = false;
			player->SetClickFlg(false);
		}
		else if (player->GetDonutCollision() && !player->GetClickFlg())
		{// �v���C���[�ƃh�[�i�c���������Ă�����

			player->SetClickFlg(true);

			// �������Ă���h�[�i�c�����ׂď���
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

			// �������I������̂ŃN���A
			donut_collision.clear();
		}
		else if (!button[1].collision && !player->GetClickFlg() && donut_creat_flg == true)
		{// ���N���b�N���ꂽ��h�[�i�c�𗎂Ƃ�

			player->SetClickFlg(true);

			donut_creat_flg = false;

			// ���Ƃ��h�[�i�c�̎�ނ��擾
			DonutType type = player->GetDonutType();

			// �h�[�i�c��ǉ�(���Ƃ�)
			donut = gameobjects->CreateGameObject<Donuts>(Vector2D(player->GetLocation().x, 60.0f), type);

			PlaySoundMem(drop_se, DX_PLAYTYPE_BACK, TRUE);

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
}

// �h�[�i�c���X�g���쐬���鏈��
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

// �X�R�A�`�揈��
void GameMainScene::DrawScore() const
{
	DrawCircle(200, 135, 100, 0xD8C3A5, TRUE);
	DrawCircle(200, 135, 100, 0x1A2E40, FALSE);
	SetFontSize(20);
	DrawString(175, 80, "SCORE", 0x1A2E40);
	SetFontSize(40);
	DrawFormatString(118, 125, 0x1A2E40, "%08d", score);
}

// �|�[�Y�{�^���`��
void GameMainScene::DrawPauseButton() const
{
	DrawButton(1, button, 0xffffff);

	int pause_xspacing = 25;
	int pause_yspacing = 9;

	// �����`��
	if (button[0].collision || pause)
	{
		SetDrawBright(128, 128, 128);
		SetFontSize(20);
		DrawString(button[0].lx + pause_xspacing, button[0].ly + pause_yspacing, "PAUSE", 0x000000);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		SetFontSize(20);
		DrawString(button[0].lx + pause_xspacing, button[0].ly + pause_yspacing, "PAUSE", 0x000000);
	}
}

// �h�[�i�c���g����͂ݏo���Ă��Ȃ����m�F���鏈��
void GameMainScene::CheckDonutOutOfFrame(Donuts* donut)
{
	float upper_line = FRAME_LY;    // ��g�̈ʒu
	float d_locy = donut->GetLocation().y - donut->GetRadiusSize(); // �h�[�i�c�̏㑤��Y���W

	// �h�[�i�c����g����͂ݏo���Ă��Ȃ����m�F
	if (d_locy < upper_line && donut->GetLanded())
	{
		is_gameover = true;
	}
}

// ���̃h�[�i�c�𐶐��ł��鎞�Ԃ��J�E���g���鏈��
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
			// �g����͂ݏo���Ă��Ȃ����m�F
			CheckDonutOutOfFrame(donut);
		}
		donut_creat_flg = true;
		donut_creat_count = 0;
	}
}

