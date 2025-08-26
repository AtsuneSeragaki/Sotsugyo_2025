#pragma once

#include "../SceneBase.h"


#define BUTTON_WIDTH   300  // �{�^���̕�
#define BUTTON_HEIGHT  70   // �{�^���̍���
#define BUTTON_SPACING 70   // �{�^�����m�̊Ԋu

#define BUTTON_LX  505                       // �{�^������X���W
#define BUTTON_RX  BUTTON_LX + BUTTON_WIDTH  // �{�^���E��X���W(����X���W�{�{�^���̕�)

// �X�^�[�g�{�^��
#define START_BUTTON_LY 270                             // �X�^�[�g�{�^������Y���W
#define START_BUTTON_RY START_BUTTON_LY + BUTTON_HEIGHT // �X�^�[�g�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �w���v�{�^��
#define HELP_BUTTON_LY START_BUTTON_RY + BUTTON_SPACING  // �w���v�{�^������Y���W(�X�^�[�g�{�^���E��Y���W�{�{�^�����m�̊Ԋu)
#define HELP_BUTTON_RY HELP_BUTTON_LY  + BUTTON_HEIGHT   // �w���v�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �G���h�{�^��
#define END_BUTTON_LY HELP_BUTTON_RY + BUTTON_SPACING // �G���h�{�^������Y���W(�w���v�{�^���E��Y���W�{�{�^�����m�̊Ԋu)
#define END_BUTTON_RY END_BUTTON_LY  + BUTTON_HEIGHT  // �G���h�{�^���E��Y���W(����Y���W�{�{�^���̍���)

class TitleScene : public SceneBase
{
private:
	bool start_btn_collision; // �X�^�[�g�{�^���ƃv���C���[�J�[�\���̓����蔻��t���O(false:�������Ă��Ȃ�  true:�������Ă���)
	bool help_btn_collision;  // �w���v�{�^���ƃv���C���[�J�[�\���̓����蔻��t���O(false:�������Ă��Ȃ�  true:�������Ă���)
	bool end_btn_collision;   // �G���h�{�^���ƃv���C���[�J�[�\���̓����蔻��t���O(false:�������Ă��Ȃ�  true:�������Ă���)
	bool canClick;            // �N���b�N�t���O(false:�N���b�N�ł��Ȃ�  true:�N���b�N�ł���)
	int frame_count;          // �t���[���J�E���g

public:
	// ����������
	virtual void Initialize() override;
	// �X�V����
	virtual eSceneType Update() override;
	// �`�揈��
	virtual void Draw() const override;
	// �I��������
	virtual void Finalize() override;

public:
	// ���݂̃V�[������Ԃ�
	virtual eSceneType GetNowSceneType() const override;

private:
	// �v���C���[�J�[�\���ƃ{�^���̓����蔻��(�����F�����蔻�����肽���{�^���̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
	int CheckPlayerButtonCollision(int left, int right, int top, int bottom);
};