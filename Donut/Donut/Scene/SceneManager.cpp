#include "SceneManager.h"
#include "DxLib.h"
#include "Title/TitleScene.h"
#include "GameMain/GameMainScene.h"
#include "Help/HelpScene.h"
#include "Result/ResultScene.h"
#include "Ranking/RankingScene.h"
#include "End/EndScene.h"


SceneManager::SceneManager() : current_scene(nullptr), loop_flag(true)
{

}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	// �E�B���h�E�̃^�C�g����ݒ�
	SetMainWindowText("Donut");

	// �E�B���h�E���[�h�ŋN��
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("�E�B���h�E���[�h�ŋN���ł��܂���ł���\n");
	}

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	// DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		throw("Dx���C�u�������������ł��܂���ł���\n");
	}

	// �`���w�菈��
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("�`���̎w�肪�ł��܂���ł���\n");
	}

	ChangeScene(eSceneType::eTitle);
}

void SceneManager::Update()
{
	// �t���[���J�n����(�}�C�N���b���擾)
	LONGLONG start_time = GetNowHiPerformanceCount();

	while (ProcessMessage() != -1)
	{
		// ���ݎ��Ԃ��擾
		LONGLONG now_time = GetNowHiPerformanceCount();

		// 1�t���[��������̎��Ԃɓ��B������A�X�V����ѕ`�揈�����s��
		if ((now_time - start_time) >= DELTA_SECOND)
		{
			// �t���[���J�n���Ԃ��X�V����
			start_time = now_time;

			// �X�V����(�߂�l�͎��̃V�[�����)
			eSceneType next = current_scene->Update();

			// �`�揈��
			Draw();

			// ���݂̃V�[���Ǝ��̃V�[��������Ă�����A�؂�ւ��������s��
			if (next != current_scene->GetNowSceneType())
			{

				ChangeScene(next);
			}
		}

		// ESCAPE�L�[�������ꂽ��A�Q�[�����I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		if (!LoopCheck())
		{
			break;
		}
	}
}

void SceneManager::Finalize()
{

	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	// DX���C�u�����̎g�p���I������
	DxLib_End();
}

bool SceneManager::LoopCheck() const
{
	return loop_flag;
}

void SceneManager::Draw() const
{
	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f
	ScreenFlip();
}

void SceneManager::ChangeScene(eSceneType new_scene_type)
{
	if (new_scene_type == eSceneType::eNone)
	{
		loop_flag = false;  // ���[�v�I��
		return;
	}

	SceneBase* new_scene = CreateScene(new_scene_type);

	if (new_scene == nullptr)
	{
		throw("\n�V�����V�[���̐������ł��܂���ł����B\n");
	}

	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();

	current_scene = new_scene;
}


// dynamiccast(SceneBase���p�������Ă��邩�m�F)
SceneBase* SceneManager::CreateScene(eSceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case eSceneType::eTitle:
		return dynamic_cast<SceneBase*>(new TitleScene());

	case eSceneType::eGameMain:
		return dynamic_cast<SceneBase*>(new GameMainScene());

	case eSceneType::eHelp:
		return dynamic_cast<SceneBase*>(new HelpScene());

	case eSceneType::eResult:
	{
		GameMainScene* gm = dynamic_cast<GameMainScene*>(current_scene);
		int score = gm ? gm->GetScore() : 0; // gm��nullptr�Ȃ�0�ɂ���
		return dynamic_cast<SceneBase*>(new ResultScene(score));
	}

	case eSceneType::eRanking:
		return dynamic_cast<SceneBase*>(new RankingScene());

	case eSceneType::eEnd:
		return dynamic_cast<SceneBase*>(new EndScene());

	default:
		return nullptr;
	}
}