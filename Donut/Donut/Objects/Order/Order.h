#pragma once
#include "../Donuts/Donuts.h"

#define ORDER_LX  50               // �I�[�_�[�̘gX���W(����)
#define ORDER_LY  260              // �I�[�_�[�̘gY���W(����)
#define ORDER_RX  ORDER_LX + 300   // �I�[�_�[�̘gX���W(�E��)
#define ORDER_RY  680              // �I�[�_�[�̘gY���W(�E��)
#define ORDER_MAX 4                // �I�[�_�[�̐�
#define DIFFICULTY_MAX 5           // ��ՓxMAX�̐�            

class Order : public GameObject
{
private:
	DonutType order_list[ORDER_MAX]; // �I�[�_�[���X�g(�h�[�i�c4���)
	int order_num[ORDER_MAX];        // ���ꂼ��̃I�[�_�[�̌�
	bool complete_order;             // �I�[�_�[�S�ăN���A�������H�t���O
	int difficulty;                  // ��Փx
	int clear_timer;                 //	�N���A�̕������o������

public:
	// �R���X�g���N�^
	Order();

	// �f�X�g���N�^
	~Order();

public:
	// ����������
	virtual void Initialize() override;

	// �X�V����
	virtual void Update() override;

	// �`�揈��
	virtual void Draw() const override;

	// �I��������
	virtual void Finalize() override;

public:
	// �I�[�_�[�������_���ɐ������鏈��(�����F��Փx(0�`2))
	void SetRandomOrder(int difficulty);

	// �h�[�i�c�̐������炷����(�����F���炵�����h�[�i�c�̎��)
	void DecrementDonutNum(DonutType type);

	// �I�[�_�[�ɂ���h�[�i�c������(�����F�h�[�i�c�̎�ށ@�߂�l�F0���I�[�_�[�ɂȂ� 1���I�[�_�[�ɂ���)
	int CheckDonutOrder(DonutType type);

	// �I�[�_�[�ɂ���h�[�i�c�̌���Ԃ�����(�����F�h�[�i�c�̎�ށ@�߂�l�F�h�[�i�c�̌�)
	int GetDonutOrderNum(DonutType type);

private:
};
