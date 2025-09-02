#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define BUTTON_WIDTH   300  // �{�^���̕�
#define BUTTON_HEIGHT  70   // �{�^���̍���
#define BUTTON_SPACING 100   // �{�^�����m�̊Ԋu
#define BUTTON_NUM 2        // �{�^���̐�
#define BUTTON_LY  610                       // �{�^������Y���W
#define BUTTON_RY  BUTTON_LY + BUTTON_HEIGHT // �{�^���E��Y���W

// �X�^�[�g�{�^��
#define START_BUTTON_LX 305                              // �X�^�[�g�{�^������X���W
#define START_BUTTON_RX  START_BUTTON_LX + BUTTON_WIDTH  // �X�^�[�g�{�^���E��X���W(����X���W�{�{�^���̕�)

// �^�C�g���{�^��
#define TITLE_BUTTON_LX START_BUTTON_RX + BUTTON_SPACING // �^�C�g���{�^������X���W(�X�^�[�g�{�^���E��X���W�{�{�^�����m�̊Ԋu)
#define TITLE_BUTTON_RX TITLE_BUTTON_LX  + BUTTON_WIDTH  // �^�C�g���{�^���E��X���W(����X���W�{�{�^���̍���)

class HelpScene : public SceneBase
{
private:
	ButtonState button[BUTTON_NUM]; // �{�^�����

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