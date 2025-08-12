#pragma once
#include "../Donuts/Donuts.h"

#define ORDER_X  35
#define ORDER_Y  240
#define ORDER_WIDTH 330
#define ORDER_HEIGHT (680 - ORDER_Y)
#define ORDER_MAX 4

class Order : public GameObject
{
private:
	DonutType order_list[ORDER_MAX]; // �I�[�_�[���X�g(�h�[�i�c4���)
	int order_num[ORDER_MAX];        // ���ꂼ��̃I�[�_�[�̐�

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
	// �I�[�_�[�������_���ɐ���(�����F��Փx(0�`2))
	void SetRandomOrder(int difficulty);

private:
};
