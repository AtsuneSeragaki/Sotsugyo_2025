#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Objects/Player/Player.h"
#include <vector>

#define GAMEMAIN_BUTTON_NUM 3  // �{�^���̐�

// �|�[�Y�{�^��
#define PAUSE_WIDTH  100                  // �|�[�Y�{�^���̕�
#define PAUSE_HEIGHT 35                   // �|�[�Y�{�^���̍���
#define PAUSE_LX 1170                     // �|�[�Y�{�^������X���W
#define PAUSE_LY 10                       // �|�[�Y�{�^������Y���W
#define PAUSE_RX PAUSE_LX + PAUSE_WIDTH   // �|�[�Y�{�^���E��X���W(����X���W�{�{�^���̕�)
#define PAUSE_RY PAUSE_LY + PAUSE_HEIGHT  // �|�[�Y�{�^���E��Y���W(����Y���W�{�{�^���̍���)

// �|�[�Y��ʂ̃{�^��
#define PAUSE_B1B2_WIDTH   300  // �|�[�Y��ʂ̃{�^���̕�
#define PAUSE_B1B2_HEIGHT  100  // �|�[�Y��ʂ̃{�^���̍���
#define PAUSE_B1B2_SPACING 60   // �|�[�Y��ʂ̃{�^�����m�̊Ԋu

#define PAUSE_B1B2_LX 500                               // �|�[�Y��ʃ{�^������X���W
#define PAUSE_B1B2_RX PAUSE_B1B2_LX + PAUSE_B1B2_WIDTH  // �|�[�Y��ʃ{�^���E��X���W(����X���W�{�{�^���̕�)

// �|�[�Y��ʂ̃{�^��(������)
#define PAUSE_B1_LY 270                              // �|�[�Y��ʃ{�^���u������v����Y���W
#define PAUSE_B1_RY PAUSE_B1_LY + PAUSE_B1B2_HEIGHT  // �|�[�Y��ʃ{�^���u������v�E��Y���W(����Y���W�{�{�^���̍���)

// �|�[�Y��ʂ̃{�^��(�^�C�g���ɖ߂�)
#define PAUSE_B2_LY PAUSE_B1_RY + PAUSE_B1B2_SPACING // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v����Y���W(�u������v�{�^���̉E��Y���W�{�{�^�����m�̊Ԋu)
#define PAUSE_B2_RY PAUSE_B2_LY + PAUSE_B1B2_HEIGHT  // �|�[�Y��ʃ{�^���u�^�C�g���ɖ߂�v�E��Y���W(����Y���W�{�{�^���̍���)

class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;       // �Q�[���I�u�W�F�N�g�N���X�̃I�u�W�F�N�g
	class Player* player;                 // �v���C���[�N���X�̃I�u�W�F�N�g
	std::vector<Donuts*> donut_collision; // �v���C���[�Ɠ������Ă���h�[�i�c�̏��
	std::vector<Donuts*> donut_list;      // ��ʂɂ���S�Ẵh�[�i�c���
	class Order* order;                   // �I�[�_�[�N���X�̃I�u�W�F�N�g
	bool is_gameover;                     // �Q�[���I�[�o�[�t���O(false:�Q�[���I�[�o�[����Ȃ�  true:�Q�[���I�[�o�[)
	bool pause;                           // �|�[�Y�t���O(false:�|�[�Y��Ԃ���Ȃ�  true:�|�[�Y���)
	ButtonState button[GAMEMAIN_BUTTON_NUM];       // �{�^�����(0:�|�[�Y�{�^�� 1:�u������v�{�^�� 2:�u�^�C�g���ɖ߂�v�{�^��)
	static int score;                     // �X�R�A
	int gameover_timer;                   // �Q�[���I�[�o�[�ɂȂ��Ă���A���̉�ʂɑJ�ڂ���܂ł̎���
	int marge_se;                         // �h�[�i�c�����̂��鎞�̌��ʉ��f�[�^
	int drop_se;                          // �h�[�i�c�𗎂Ƃ����̌��ʉ��f�[�^
	int delete_se;                        // �h�[�i�c���������̌��ʉ��f�[�^

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

	// �X�R�A��Ԃ�����(�߂�l�F�X�R�A)
	int GetScore(){ return score; }

private:
	// �h�[�i�c���m�̓����蔻��
	void CollisionDonuts();

	// �h�[�i�c���m�������������̏���(�����F�h�[�i�c1(��)�̏��A�h�[�i�c2(��)�̏��)
	void ResolveDonutCollision(Donuts* a,Donuts* b);

	// �h�[�i�c�ƃv���C���[�������������̏���
	void HitDonutPlayerCollision();

	// �g���ɂ���h�[�i�c�ƃv���C���[�̓����蔻�菈��(�����F�����蔻�����肽���h�[�i�c�̏��@�߂�l�F0���������ĂȂ� 1���������Ă���)
	int CheckDonutPlayerCollision(Donuts* donut);

	// �|�[�Y��Ԃ̎��̍X�V����(�߂�l�F�V�[���^�C�v)
	eSceneType PauseUpdate();

	// �|�[�Y��Ԃ̎��̕`�揈��
	void PauseDraw() const;

	// �X�R�A���Z(�����F�X�R�A���Z����h�[�i�c���)
	void AddScore(Donuts* donut);

	// �h�[�i�c��������(�߂�l�F�V�[���^�C�v)
	void FallDonut();

	// �|�[�Y�{�^���̓����蔻�菈��
	void PauseButtonCollision();

	// �v���C���[���N���b�N�������̏���(�|�[�Y��Ԃ���Ȃ��Ƃ�)
	void OnPlayerClick();

	// �h�[�i�c���X�g���쐬���鏈��
	void MakeDonutList();

	// �X�R�A�`�揈��
	void DrawScore()const;

	// �|�[�Y�{�^���`��
	void DrawPauseButton() const;

	// �h�[�i�c���g����͂ݏo���Ă��Ȃ����m�F���鏈��
	void CheckDonutOutOfFrame(Donuts* donut);
};