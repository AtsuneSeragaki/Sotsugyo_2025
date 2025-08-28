#pragma once

#include "../Utility/Vector2D.h"
#include <vector>

enum class eSceneType
{
	eTitle,
	eGameMain,
	eResult,
	eHelp,
	eEnd,
};

struct ButtonState {
	int lx, rx, ly, ry;
	bool collision = false;
	eSceneType targetScene; // �N���b�N�őJ�ڂ���V�[��
};

class SceneBase
{
protected:
	int background_image; // �w�i�摜�f�[�^
	int frame_count;      // �t���[���J�E���g
	bool can_click;       // �N���b�N�t���O(false:�N���b�N�ł��Ȃ�  true:�N���b�N�ł���)

public:
	SceneBase();
	virtual ~SceneBase();

public:
	// ����������
	virtual void Initialize();
	// �X�V����
	virtual eSceneType Update();
	// �`�揈��
	virtual void Draw() const;
	// �I��������
	virtual void Finalize();

public:
	// ���݂̃V�[������Ԃ�
	virtual eSceneType  GetNowSceneType() const = 0;

	// �v���C���[�J�[�\���ƃ{�^���̓����蔻��(�����F�����蔻�����肽���{�^���̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
	int CheckPlayerButtonCollision(int left, int right, int top, int bottom);
};