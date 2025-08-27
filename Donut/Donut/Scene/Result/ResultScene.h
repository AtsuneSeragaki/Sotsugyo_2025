#pragma once

#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	int score;

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