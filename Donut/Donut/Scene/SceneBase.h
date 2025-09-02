#pragma once

#include "../Utility/Vector2D.h"
#include <vector>

#define WINDOW_WIDTH  1280 // ��ʂ̕�
#define WINDOW_HEIGHT 720  // ��ʂ̍���

enum class eSceneType
{
	eTitle,
	eGameMain,
	eResult,
	eHelp,
	eRanking,
	eEnd,
	eNone,
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
	// ���݂̃V�[������Ԃ�����
	virtual eSceneType  GetNowSceneType() const = 0;

	// �v���C���[�J�[�\���ƃ{�^���̓����蔻�菈��(�����F�����蔻�����肽���{�^���̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
	int CheckPlayerButtonCollision(int left, int right, int top, int bottom);

	// �{�^���`�揈��(�����F�{�^���̐�)
	void DrawButton(int button_num,const ButtonState* button,int button_color) const;
};