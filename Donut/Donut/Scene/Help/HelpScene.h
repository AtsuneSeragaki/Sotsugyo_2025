#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define HELP_BUTTON_WIDTH   300  // �{�^���̕�
#define HELP_BUTTON_HEIGHT  70   // �{�^���̍���
#define HELP_BUTTON_SPACING 100   // �{�^�����m�̊Ԋu
#define HELP_BUTTON_NUM 2        // �{�^���̐�
#define HELP_BUTTON_LY  610                       // �{�^������Y���W
#define HELP_BUTTON_RY  HELP_BUTTON_LY + HELP_BUTTON_HEIGHT // �{�^���E��Y���W

// �X�^�[�g�{�^��
#define HELP_START_BUTTON_LX 305                              // �X�^�[�g�{�^������X���W
#define HELP_START_BUTTON_RX  HELP_START_BUTTON_LX + HELP_BUTTON_WIDTH  // �X�^�[�g�{�^���E��X���W(����X���W�{�{�^���̕�)

// �^�C�g���{�^��
#define HELP_TITLE_BUTTON_LX HELP_START_BUTTON_RX + HELP_BUTTON_SPACING // �^�C�g���{�^������X���W(�X�^�[�g�{�^���E��X���W�{�{�^�����m�̊Ԋu)
#define HELP_TITLE_BUTTON_RX HELP_TITLE_BUTTON_LX + HELP_BUTTON_WIDTH  // �^�C�g���{�^���E��X���W(����X���W�{�{�^���̍���)

class HelpScene : public SceneBase
{
private:
	ButtonState button[HELP_BUTTON_NUM]; // �{�^�����

public:
	// �R���X�g���N�^
	HelpScene();
	// �f�X�g���N�^
	~HelpScene();

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