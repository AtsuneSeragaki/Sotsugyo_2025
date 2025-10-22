#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define TITLE_BUTTON_WIDTH   300  // �{�^���̕�
#define TITLE_BUTTON_HEIGHT  70   // �{�^���̍���
#define TITLE_BUTTON_SPACING 30   // �{�^�����m�̊Ԋu
#define TITLE_BUTTON_NUM 4        // �{�^���̐�
#define TITLE_BUTTON_LX  505                       // �{�^������X���W
#define TITLE_BUTTON_RX  TITLE_BUTTON_LX + TITLE_BUTTON_WIDTH  // �{�^���E��X���W(����X���W�{�{�^���̕�)

// �X�^�[�g�{�^��
#define TITLE_START_BUTTON_LY 270                             // �X�^�[�g�{�^������Y���W
#define TITLE_START_BUTTON_RY TITLE_START_BUTTON_LY + TITLE_BUTTON_HEIGHT // �X�^�[�g�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �w���v�{�^��
#define TITLE_HELP_BUTTON_LY TITLE_START_BUTTON_RY + TITLE_BUTTON_SPACING  // �w���v�{�^������Y���W(�X�^�[�g�{�^���E��Y���W�{�{�^�����m�̊Ԋu)
#define TITLE_HELP_BUTTON_RY TITLE_HELP_BUTTON_LY  + TITLE_BUTTON_HEIGHT   // �w���v�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �����L���O�{�^��
#define TITLE_RANKING_BUTTON_LY TITLE_HELP_BUTTON_RY + TITLE_BUTTON_SPACING   // �����L���O�{�^������Y���W(�w���v�{�^���E��Y���W�{�{�^�����m�̊Ԋu)
#define TITLE_RANKING_BUTTON_RY TITLE_RANKING_BUTTON_LY + TITLE_BUTTON_HEIGHT // �����L���O�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �G���h�{�^��
#define TITLE_END_BUTTON_LY TITLE_RANKING_BUTTON_RY + TITLE_BUTTON_SPACING // �G���h�{�^������Y���W(�����L���O�{�^���E��Y���W�{�{�^�����m�̊Ԋu)
#define TITLE_END_BUTTON_RY TITLE_END_BUTTON_LY + TITLE_BUTTON_HEIGHT     // �G���h�{�^���E��Y���W(����Y���W�{�{�^���̍���)

class TitleScene : public SceneBase
{
private:
	ButtonState button[TITLE_BUTTON_NUM];  // �{�^�����

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
};