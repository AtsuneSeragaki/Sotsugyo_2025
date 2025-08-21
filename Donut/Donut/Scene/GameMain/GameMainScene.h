#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Objects/Player/Player.h"
#include <vector>

// �|�[�Y�{�^��
#define PAUSE_LX 1170             // �|�[�Y�{�^������X���W
#define PAUSE_LY 10               // �|�[�Y�{�^������Y���W
#define PAUSE_RX PAUSE_LX + 100   // �|�[�Y�{�^���E��X���W(����X���W�{�{�^���̕�)
#define PAUSE_RY PAUSE_LY + 35    // �|�[�Y�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �|�[�Y��ʂ̃{�^��(������)
#define PAUSE_B1_LX 500                // �|�[�Y��ʃ{�^���u������v����X���W
#define PAUSE_B1_LY 250                // �|�[�Y��ʃ{�^���u������v����Y���W
#define PAUSE_B1_RX PAUSE_B1_LX + 300  // �|�[�Y��ʃ{�^���u������v�E��X���W(����X���W�{�{�^���̕�)
#define PAUSE_B1_RY PAUSE_B1_LY + 100  // �|�[�Y��ʃ{�^���u������v�E��Y���W(����Y���W�{�{�^���̍���)

// �|�[�Y��ʂ̃{�^��(�^�C�g���ɖ߂�)
#define PAUSE_B2_LX 500                // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v����X���W
#define PAUSE_B2_LY 400                // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v����Y���W
#define PAUSE_B2_RX PAUSE_B2_LX + 300  // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v�E��X���W(����X���W�{�{�^���̕�)
#define PAUSE_B2_RY PAUSE_B2_LY + 100  // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v�E��Y���W(����Y���W�{�{�^���̍���)

class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // �Q�[���I�u�W�F�N�g�N���X�̃I�u�W�F�N�g
	class Player* player;            // �v���C���[�N���X�̃I�u�W�F�N�g
	std::vector<Donuts*> donut_collision;   // �v���C���[�Ɠ������Ă���h�[�i�c�̏��
	class Order* order;              // �I�[�_�[�N���X�̃I�u�W�F�N�g
	bool is_gameover;                // �Q�[���I�[�o�[�t���O(false:�Q�[���I�[�o�[����Ȃ�  true:�Q�[���I�[�o�[)
	bool pause;                      // �|�[�Y�t���O(false:�|�[�Y��Ԃ���Ȃ�  true:�|�[�Y���)
	bool pause_collision;            // �|�[�Y�{�^���ƃv���C���[�J�[�\���̓����蔻��t���O(false:�������Ă��Ȃ�  true:�������Ă���)
	bool pause_b1_collision;         // �|�[�Y��ʃ{�^���u������v�ƃv���C���[�J�[�\���̓����蔻��t���O(false:�������Ă��Ȃ�  true:�������Ă���)
	bool pause_b2_collision;         // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v�ƃv���C���[�J�[�\���̓����蔻��t���O(false:�������Ă��Ȃ�  true:�������Ă���)
	int score;                       // �X�R�A

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

	// �h�[�i�c���m�������������̏���(�����F�h�[�i�c1(��)�̏��A�h�[�i�c2(��)�̏��)
	void ResolveDonutCollision(class Donuts* a, class Donuts* b);

	// �g���ɂ���h�[�i�c�ƃv���C���[�̓����蔻�菈��(�߂�l�F0���������ĂȂ� 1���������Ă���)
	int CheckDonutPlayerCollision(class Donuts* donut);

	// �v���C���[�J�[�\���ƃ{�^���̓����蔻��(�����F�����蔻�����肽���{�^���̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
	int CheckPlayerButtonCollision(int left,int right,int top,int bottom);
};