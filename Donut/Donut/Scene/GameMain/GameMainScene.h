#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"


class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // �Q�[���I�u�W�F�N�g�N���X�̃I�u�W�F�N�g
	class Player* player;     // �v���C���[�N���X�̃I�u�W�F�N�g

public:
	// �R���X�g���N�^
	GameMainScene();

	// �f�X�g���N�^
	~GameMainScene();

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