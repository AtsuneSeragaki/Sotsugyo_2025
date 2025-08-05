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
	float vx;  // �� ���������x
	float vy; // �d��
	const char* name; // �f�o�b�N�p�̃h�[�i�c�̎��
	bool isMerged;  // ���łɍ��̂������ǂ���
	bool isDead;    // �폜�\��i�O���ŏ����j

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
	Vector2D GetVelocity() const { return Vector2D(vx, vy); }
	void SetVelocity(Vector2D vel) { vx = vel.x; vy = vel.y; }

	void ResolveCollision(Donuts* other);

	DonutType GetDonutType() const { return type; }
	void SetDonutType(DonutType t) { type = t; name = GetDonutTypeName(t); }
	void SetRadius(float r_) { r = r_; }

	bool IsDead() const { return isDead; }
	void SetDead(bool d) { isDead = d; }

	bool IsMerged() const { return isMerged; }
	void SetMerged(bool m) { isMerged = m; }

	// �h�[�i�c��������
	void FallDonut(const std::vector<Donuts*>& others);

private:
	// �f�o�b�N�p�̃h�[�i�c��ޕ����ɕϊ�����
	const char* GetDonutTypeName(DonutType type);

	// �h�[�i�c�̘g�͂ݏo���h�~
	void ClampToFrame(float left, float right, float top, float bottom);
};
