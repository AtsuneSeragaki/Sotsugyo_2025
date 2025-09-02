#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define BUTTON_WIDTH   300  // �{�^���̕�
#define BUTTON_HEIGHT  70   // �{�^���̍���
#define BUTTON_NUM 1        // �{�^���̐�
#define BUTTON_LY  610                       // �{�^������Y���W
#define BUTTON_RY  BUTTON_LY + BUTTON_HEIGHT // �{�^���E��Y���W

// �^�C�g���{�^��
#define TITLE_BUTTON_LX 500 // �^�C�g���{�^������X���W(���X�^�[�g�{�^���E��X���W�{�{�^�����m�̊Ԋu)
#define TITLE_BUTTON_RX TITLE_BUTTON_LX  + BUTTON_WIDTH    // �^�C�g���{�^���E��X���W(����X���W�{�{�^���̍���)

class RankingScene : public SceneBase
{
private:
	ButtonState button[BUTTON_NUM]; // �{�^�����

public:
	// �R���X�g���N�^
	RankingScene();
	// �f�X�g���N�^
	~RankingScene();

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
