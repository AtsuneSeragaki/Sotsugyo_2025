#pragma once
#include "../GameObject.h"

class Donuts : public GameObject
{
private:
	bool landed; // ���n������

public:
	// �R���X�g���N�^
	Donuts();
	// �f�X�g���N�^
	~Donuts();

	// ����������
	virtual void Initialize() override;
	// �X�V����
	virtual void Update() override;
	// �`�揈��
	virtual void Draw() const override;
	// �I��������
	virtual void Finalize() override;

private:
	// �h�[�i�c��������
	void FallDonut();
};
