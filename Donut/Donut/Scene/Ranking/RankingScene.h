#pragma once

#include "../SceneBase.h"

// �{�^�����ʏ��
#define RANKING_BUTTON_WIDTH   300  // �{�^���̕�
#define RANKING_BUTTON_HEIGHT  70   // �{�^���̍���
#define RANKING_BUTTON_NUM 1        // �{�^���̐�
#define RANKING_BUTTON_LY  610                       // �{�^������Y���W
#define RANKING_BUTTON_RY  RANKING_BUTTON_LY + RANKING_BUTTON_HEIGHT // �{�^���E��Y���W

// �^�C�g���{�^��
#define RANKING_TITLE_BUTTON_LX 500 // �^�C�g���{�^������X���W(���X�^�[�g�{�^���E��X���W�{�{�^�����m�̊Ԋu)
#define RANKING_TITLE_BUTTON_RX RANKING_TITLE_BUTTON_LX  + RANKING_BUTTON_WIDTH    // �^�C�g���{�^���E��X���W(����X���W�{�{�^���̍���)

class RankingScene : public SceneBase
{
private:
	ButtonState button[RANKING_BUTTON_NUM]; // �{�^�����

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
