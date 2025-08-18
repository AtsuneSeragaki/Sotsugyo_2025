#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"

// �|�[�Y�{�^��
#define PAUSE_LX 1170
#define PAUSE_LY 10
#define PAUSE_RX PAUSE_LX + 100
#define PAUSE_RY PAUSE_LY + 35

// �|�[�Y��ʂ̃{�^��(������)
#define PAUSE_B1_LX 500
#define PAUSE_B1_LY 250
#define PAUSE_B1_RX PAUSE_B1_LX + 300
#define PAUSE_B1_RY PAUSE_B1_LY + 100

// �|�[�Y��ʂ̃{�^��(�^�C�g���ɖ߂�)
#define PAUSE_B2_LX 500
#define PAUSE_B2_LY 400
#define PAUSE_B2_RX PAUSE_B2_LX + 300
#define PAUSE_B2_RY PAUSE_B2_LY + 100


class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // �Q�[���I�u�W�F�N�g�N���X�̃I�u�W�F�N�g
	class Player* player;            // �v���C���[�N���X�̃I�u�W�F�N�g
	class Order* order;              // �I�[�_�[�N���X�̃I�u�W�F�N�g
	bool is_gameover;                // �Q�[���I�[�o�[���H
	class Donuts* donut_collision;   // �v���C���[�Ɠ������Ă���h�[�i�c�̏��
	int score;                       // �X�R�A
	bool pause;                      // �|�[�Y�t���O
	bool pause_collision;            // �|�[�Y�{�^���Ƀv���C���[�J�[�\�����������Ă��邩�H�t���O
	bool pause_b1_collision;         // �|�[�Y��ʂ̃{�^��(������)�Ƀv���C���[�J�[�\�����������Ă��邩�H�t���O
	bool pause_b2_collision;         // �|�[�Y��ʂ̃{�^��(�^�C�g���ɖ߂�)�Ƀv���C���[�J�[�\�����������Ă��邩�H�t���O

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

	// �v���C���[�J�[�\���ƃ{�^���̓����蔻��
	int CheckPlayerButtonCollision(int left,int right,int top,int bottom);


};