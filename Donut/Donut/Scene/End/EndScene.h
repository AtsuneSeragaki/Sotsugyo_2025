#pragma once

#include "../SceneBase.h"

class EndScene : public SceneBase
{
private:
	int end_timer; // �I���܂ł̎���

public:
	// �R���X�g���N�^
	EndScene();
	// �f�X�g���N�^
	~EndScene();

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
	// �I���܂ł̎��Ԍo�߂�Ԃ�
	int GetEndTimer() { return end_timer; }
};