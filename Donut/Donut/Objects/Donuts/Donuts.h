#pragma once
#include "../GameObject.h"
#define MAX_PATH_LEN 256

// �h�[�i�c�̎��
enum class DonutType
{
	DONUT_MINI_BASIC,           // �~�X�h�̏������h�[�i�c�݂����Ȃ�i�m�[�}���j
	DONUT_MINI_VARIANT,         // �~�X�h�̏������h�[�i�c�݂����Ȃ�i�F�Ⴂ�j
	DONUT_FRENCH_CRULLER,       // �t�����`�N���[���[
	DONUT_FRENCH_CRULLER_VAR,   // �t�����`�N���[���[�i�F�Ⴂ�j
	DONUT_OLD_FASHIONED,        // �I�[���h�t�@�b�V����
	DONUT_OLD_FASHIONED_VAR,    // �I�[���h�t�@�b�V�����i�F�Ⴂ�j
	DONUT_GOLDEN_CHOCOLATE,     // �S�[���f���`���R���[�g
	DONUT_COCONUT_CHOCOLATE,    // �R�R�i�c�`���R���[�g
	DONUT_HALF_CHOCOLATE,       // �����`���R�h�[�i�c
	DONUT_HALF_STRAWBERRY,      // �����X�g���x���[�h�[�i�c
	DONUT_PON_DE_RING,          // �|���E�f�E�����O
	DONUT_COUNT
};

// �h�[�i�c���\����
typedef struct {
	DonutType type;  // �h�[�i�c�̎��
	float size;      // �T�C�Y(���a)
	int score;       // ���̃h�[�i�c���������ꂽ���ɉ��Z�����X�R�A
	char image_path[MAX_PATH_LEN]; // �h�[�i�c�摜�p�X
} DonutInfo;

constexpr int MAX_DONUT_NUM = static_cast<int>(DonutType::DONUT_COUNT);
extern const DonutInfo g_DonutInfoTable[MAX_DONUT_NUM];

class Donuts : public GameObject
{
private:
	bool landed; // ���n������
	DonutType type; // �h�[�i�c�̎��
	float vy; // �d��
	const char* name; // �f�o�b�N�p�̃h�[�i�c�̎��

public:
	// �R���X�g���N�^
	Donuts(DonutType type);
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
	// �h�[�i�c�̔��a��Ԃ�
	float GetDonutRadius(DonutType dtype);

private:
	// �h�[�i�c��������
	void FallDonut();

	// �f�o�b�N�p�̃h�[�i�c��ޕ����ɕϊ�����
	const char* GetDonutTypeName(DonutType type);
};
