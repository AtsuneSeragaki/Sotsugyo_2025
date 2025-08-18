#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"


class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // �Q�[���I�u�W�F�N�g�N���X�̃I�u�W�F�N�g
	class Player* player;            // �v���C���[�N���X�̃I�u�W�F�N�g
	class Order* order;              // �I�[�_�[�N���X�̃I�u�W�F�N�g
	bool is_gameover;                // �Q�[���I�[�o�[���H
	class Donuts* donut_collision;   // �v���C���[�Ɠ������Ă���h�[�i�c�̏��
	int score;

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

private:
	// �h�[�i�c���m�̓����蔻��
	void CollisionDonuts();

	// �����������̏���
	void ResolveDonutCollision(class Donuts* a, class Donuts* b);

	// �g���ɂ���h�[�i�c�ƃv���C���[�̓����蔻�菈��(�߂�l�F0���������ĂȂ� 1���������Ă���)
	void DonutPlayerCollision(class Donuts* donut);
};