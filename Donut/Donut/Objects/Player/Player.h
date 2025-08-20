#pragma once
#include "../Donuts/Donuts.h"

class Player : public GameObject
{
private:
	bool is_click;                  // �}�E�X���N���b�N���ꂽ���H
	DonutType donut_type;           // ���Ƃ��h�[�i�c�̎��
	DonutType next_donut_type;      // ���ɗ��Ƃ��h�[�i�c�̎��
	float next_r;                   // ���ɗ��Ƃ��h�[�i�c�̔��a
	int donut_number;               // �h�[�i�c�̔ԍ�
	int next_donut_number;          // �l�N�X�g�h�[�i�c�̔ԍ�
	bool donut_collision;           // �h�[�i�c�Ɠ������Ă��邩�H

public:
	// �R���X�g���N�^
	Player();
	
	// �f�X�g���N�^
	~Player();

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
	// ���N���b�N�t���O�ݒ�
	void SetClickFlg(bool flg) { is_click = flg; }

	// ���N���b�N�t���O�擾
	bool GetClickFlg() { return is_click; }

	// ���Ƃ��h�[�i�c�̎�ނ��擾
	DonutType GetDonutType() const { return donut_type; }

	// �v���C���[���������h�[�i�c�����̃h�[�i�c�ɕύX����
	void SetDonutRadius(float r) { this->r = r; }

	// ���ɗ��Ƃ��h�[�i�c�̎�ނ��擾
	DonutType GetNextDonutType() const { return next_donut_type; }

	// ���ɗ��Ƃ��h�[�i�c�̔��a�ݒ�(�l�N�X�g�`��p)
	void SetNextDonutRadius(float r) { next_r = r; }

	// �v���C���[���������h�[�i�c�̔ԍ���ݒ�
	void SetDonutNumber(int num) { donut_number = num; }
	
	// ���ɗ��Ƃ��h�[�i�c�̔ԍ���ݒ�
	void SetNextDonutNumber(int num) { next_donut_number = num; }

	// �h�[�i�c�������_���ɑI��
	void ChooseRandomDonut();

	// �h�[�i�c�Ɠ������Ă��邩�H�t���O��ݒ�
	void SetDonutCollision(bool flg) { donut_collision = flg; }

	// �h�[�i�c�Ɠ������Ă��邩�H�t���O���擾
	bool GetDonutCollision() { return donut_collision; }

	// �v���C���[��X���W��ݒ�
	void SetPlayerPosX(float pos_x) { location.x = pos_x; }

private:
	// �h�[�i�c�𗎂Ƃ��g�͈̔͂����ړ��o���Ȃ��悤�ɂ��鏈��
	void LocXControl();
};
