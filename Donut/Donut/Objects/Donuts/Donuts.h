#pragma once
#include "../GameObject.h"
#include <vector>
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
	DONUT_COUNT                 // �h�[�i�c�̑���
};

// �h�[�i�c���\����
typedef struct {
	DonutType type;  // �h�[�i�c�̎��
	float size;      // �T�C�Y(���a)
	int score;       // ���̃h�[�i�c���������ꂽ���ɉ��Z�����X�R�A
	char image_path[MAX_PATH_LEN]; // �h�[�i�c�摜�p�X
	int number;      // �h�[�i�c�ԍ�
} DonutInfo;

// �h�[�i�c�̎�ޑ���
constexpr int MAX_DONUT_NUM = static_cast<int>(DonutType::DONUT_COUNT);
extern const DonutInfo g_DonutInfoTable[MAX_DONUT_NUM];

class Donuts : public GameObject
{
private:
	bool landed;      // ���n������
	DonutType type;   // �h�[�i�c�̎��
	float vx;         // ���������x
	float vy;         // �d��
	bool isMerged;    // ���łɍ��̂������ǂ���
	bool isDead;      // �폜�\��i�O���ŏ����j
	bool isRolling = false;
	float rollingDirection = 0.0f;
	float rolledDistance = 0.0f;
	const float maxRollingDistance = 100.0f;  // �]����ő勗��
	const float rollingSpeed = 1.0f;          // 1�t���[��������̓]���鑬�x
	std::vector<Donuts*>* donutList;

public:
	// �R���X�g���N�^
	Donuts(DonutType type);
	
	// �f�X�g���N�^
	~Donuts();

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
	// �h�[�i�c�̔��a��Ԃ�����(�����F�h�[�i�c�̎�ށ@�߂�l�F���a)
	float GetDonutRadius(DonutType dtype);
	
	// �h�[�i�c�̔ԍ���Ԃ�����(�����F�h�[�i�c�̎�ށ@�߂�l�F�ԍ�)
	int GetDonutNumber(DonutType dtype);
	
	// �d�͂�Ԃ�����(�߂�l�F�d��)
	Vector2D GetVelocity() const { return Vector2D(vx, vy); }
	
	// �d�͂����������鏈��(�����F�ݒ肵�����l)
	void SetVelocity(Vector2D vel) { vx = vel.x; vy = vel.y; }
	
	// �h�[�i�c�̎�ނ�Ԃ�����(�߂�l�F�h�[�i�c�̎��)
	DonutType GetDonutType() const { return type; }
	
	// �h�[�i�c�̎�ނ����������鏈��(�����F�ݒ肵�����h�[�i�c�̎��)
	void SetDonutType(DonutType t) { type = t;}
	
	// �h�[�i�c�̔��a�����������鏈��(�����F�ݒ肵�����h�[�i�c�̔��a)
	void SetRadius(float r_) { r = r_; }
	
	// �폜�\��t���O��Ԃ�����(�߂�l�F�폜�\��t���O)
	bool IsDead() const { return isDead; }
	
	// �폜�\��t���O�����������鏈��
	void SetDead(bool d) { isDead = d; }
	
	// ���̂������H�t���O��Ԃ�����(�߂�l�F���̂������H�t���O)
	bool IsMerged() const { return isMerged; }

	// ���̂������H�t���O�����������鏈��(�����F�ݒ肵�����l)
	void SetMerged(bool m) { isMerged = m; }

	// �h�[�i�c��������
	void FallDonut(const std::vector<Donuts*>& others);

	// �ǂ����Ɏx�����Ă��邩���肷�鏈��
	bool IsSupported(const std::vector<Donuts*>& others);

	// �h�[�i�c���X�g���R�s�[���鏈��
	void SetDonutList(const std::vector<Donuts*>& others);

private:
	// �h�[�i�c�̘g�͂ݏo���h�~����
	void ClampToFrame(float left, float right, float top, float bottom);
};
