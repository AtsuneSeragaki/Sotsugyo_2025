#include "DxLib.h"
#include "Utility/InputManager.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Window���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// Window�T�C�Y�̐ݒ�
	SetGraphMode(1280, 720, 32);

	// DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		// �G���[��Ԃ�ʒm����
		OutputDebugString("DX���C�u�������������ł��܂���ł����B\n");
		return -1;
	}

	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	// ���[�J���ϐ���`
	SceneManager* manager = nullptr;
	ResourceManager* rm = ResourceManager::GetInstance();
	int result = 0;

	try
	{
		manager = new SceneManager();

		manager->Initialize();

		// �V�[���}�l�[�W���[�@�\�̍X�V����
		manager->Update();

		// �V�[���}�l�[�W���[�@�\�̏I��������
		manager->Finalize();
	}
	catch (std::string error_log)
	{
		// Log.txt�ɃG���[���e���o�͂���
		OutputDebugString(error_log.c_str());
		// �I����Ԃ��ُ�ɐݒ肷��
		result = -1;
	}

	// �I�u�W�F�N�g�̍폜
	if (manager != nullptr)
	{
		manager->Finalize();
		delete manager;
	}

	// ���͋@�\�̃C���X�^���X���폜����
	InputManager::DeleteInstance();

	// �ǂݍ��񂾉摜�A�����̉��
	rm->UnloadResourcesAll();

	// ���\�[�X�Ǘ��̃C���X�^���X���폜����
	ResourceManager::DeleteInstance();

	// �I����Ԃ̒l��ԋp����
	DxLib_End();

	return result;

}