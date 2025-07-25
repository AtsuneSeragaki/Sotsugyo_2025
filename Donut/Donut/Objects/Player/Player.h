#pragma once
#include "../GameObject.h"

class Player : public GameObject
{
private:
	bool is_click; // �}�E�X���N���b�N���ꂽ���H

public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();

	// ����������
	virtual void Initialize() override;
	// �X�V����
	virtual void Update() override;
	// �`�揈��
	virtual void Draw() const override;
	// �I��������
	virtual void Finalize() override;

	// ���N���b�N�t���O�ݒ�
	bool SetClickFlg(bool flg);

	// ���N���b�N�t���O�擾
	bool GetClickFlg();

private:
	// �h�[�i�c�𗎂Ƃ��g�͈̔͂����ړ��o���Ȃ��悤�ɂ��鏈��
	void LocXControl();
};
