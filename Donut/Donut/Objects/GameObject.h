#pragma once

#include "../Utility/Vector2D.h"



// �Q�[���I�u�W�F�N�g�N���X(��ʂɏo�Ă���I�u�W�F�N�g�̐e�N���X)
class GameObject
{
protected:
	Vector2D location;   // �ʒu���W���
	float r;             // ���a
	int image;           // �`�悷��摜�f�[�^
	int flip_flag;       // �`�攽�]�t���O

public:
	// �R���X�g���N�^
	GameObject();
	
	// �f�X�g���N�^
	virtual ~GameObject();

public:
	// ����������
	virtual void Initialize();
	
	// �X�V����
	virtual void Update();
	
	// �`�揈��
	virtual void Draw() const;
	
	// �I��������
	virtual void Finalize();

public:
	// �ʒu���W�擾����
	Vector2D GetLocation() const;
	
	// ���a�̑傫���擾����
	float GetRadiusSize() const;
	
	// �ʒu���W�ݒ菈��
	void SetLocation(const Vector2D& location);

	template <typename T>
	T Clamp(const T& v, const T& lo, const T& hi) 
	{
		return (v < lo) ? lo : (v > hi) ? hi : v;
	}

};