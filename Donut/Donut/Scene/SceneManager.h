#pragma once
#include "SceneBase.h"

// �Œ艻����t���[�����[�g�l
#define TARGET_FREAM_RATE (60)
// 1�t���[��������̎���(�}�C�N���b)
#define DELTA_SECOND (1000000 / TARGET_FREAM_RATE)

class SceneManager
{
private:
	SceneBase* current_scene; // ���݂̃V�[��
	bool loop_flag;           // ���[�v���邩�H

public:
	SceneManager();
	~SceneManager();

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �I��������
	void Finalize();

public:
	// loop_flg�̒l��Ԃ�
	bool LoopCheck() const;

private:
	// �`�揈��
	void Draw() const;
	// ����(new_scene_type)�V�[���ɐ؂�ւ�����
	void ChangeScene(eSceneType new_scene_type);
	// ����(new_scene_type)�̃V�[����������
	SceneBase* CreateScene(eSceneType new_scene_type);
};