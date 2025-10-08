#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define RESULT_BUTTON_WIDTH   300  // �{�^���̕�
#define RESULT_BUTTON_HEIGHT  70   // �{�^���̍���
#define RESULT_BUTTON_SPACING 100   // �{�^�����m�̊Ԋu
#define RESULT_BUTTON_NUM 2        // �{�^���̐�
#define RESULT_BUTTON_LY  610                       // �{�^������Y���W
#define RESULT_BUTTON_RY  RESULT_BUTTON_LY + RESULT_BUTTON_HEIGHT // �{�^���E��Y���W

// ���X�^�[�g�{�^��
#define RESULT_RESTART_BUTTON_LX 305                               // ���X�^�[�g�{�^������X���W
#define RESULT_RESTART_BUTTON_RX  RESULT_RESTART_BUTTON_LX + RESULT_BUTTON_WIDTH // ���X�^�[�g�{�^���E��X���W(����X���W�{�{�^���̕�)

// �^�C�g���{�^��
#define RESULT_TITLE_BUTTON_LX RESULT_RESTART_BUTTON_RX + RESULT_BUTTON_SPACING // �^�C�g���{�^������X���W(���X�^�[�g�{�^���E��X���W�{�{�^�����m�̊Ԋu)
#define RESULT_TITLE_BUTTON_RX RESULT_TITLE_BUTTON_LX + RESULT_BUTTON_WIDTH    // �^�C�g���{�^���E��X���W(����X���W�{�{�^���̍���)

class ResultScene : public SceneBase
{
private:
	int score;  // �X�R�A
	ButtonState button[RESULT_BUTTON_NUM]; // �{�^�����
	
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

private:
	// �X�R�A�`�揈��
	void DrawScore() const;
	// �����L���O�`�揈��
	void DrawRanking() const;
};