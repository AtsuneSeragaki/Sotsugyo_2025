#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define BUTTON_WIDTH   300  // �{�^���̕�
#define BUTTON_HEIGHT  70   // �{�^���̍���
#define BUTTON_SPACING 70   // �{�^�����m�̊Ԋu
#define BUTTON_NUM 2        // �{�^���̐�
#define BUTTON_LY  610                       // �{�^������Y���W
#define BUTTON_RY  BUTTON_LY + BUTTON_HEIGHT // �{�^���E��Y���W

// ���X�^�[�g�{�^��
#define RESTART_BUTTON_LX 305                               // ���X�^�[�g�{�^������X���W
#define RESTART_BUTTON_RX  RESTART_BUTTON_LX + BUTTON_WIDTH // ���X�^�[�g�{�^���E��X���W(����X���W�{�{�^���̕�)

// �^�C�g���{�^��
#define TITLE_BUTTON_LX RESTART_BUTTON_RX + BUTTON_SPACING // �^�C�g���{�^������X���W(���X�^�[�g�{�^���E��X���W�{�{�^�����m�̊Ԋu)
#define TITLE_BUTTON_RX TITLE_BUTTON_LX  + BUTTON_WIDTH    // �^�C�g���{�^���E��X���W(����X���W�{�{�^���̍���)

class ResultScene : public SceneBase
{
private:
	int score;             // �X�R�A
	ButtonState button[BUTTON_NUM]; // �{�^�����
	
public:
	// �R���X�g���N�^
	ResultScene(int score);
	// �f�X�g���N�^
	~ResultScene();

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