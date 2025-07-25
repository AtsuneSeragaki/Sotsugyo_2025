#include "GameObject.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

// �R���X�g���N�^
GameObject::GameObject() : location(0.0f), r(0.0f), image(NULL), flip_flag(FALSE)
{

}

// �f�X�g���N�^
GameObject::~GameObject()
{

}

// ����������
void GameObject::Initialize()
{
	image = NULL;
}

// �X�V����
void GameObject::Update()
{

}

// �`�揈��
void GameObject::Draw() const
{
	// �����o�̏�����ɉ摜��`�悷��
	//DrawCircleAA(location.x, location.y, r, 32, 0xffff00, TRUE);

	// �����蔻��̋�`����`�悷��
	/*Vector2D upper_left = location - (box_size / 2.0f);
	Vector2D lower_right = location + (box_size / 2.0f);
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255, 0, 0), FALSE);*/
}

// �I��������
void GameObject::Finalize()
{

}

// �ʒu���W�擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

// ���a�̑傫���擾����
float GameObject::GetRadiusSize() const
{
	return r;
}

// �ʒu���W�ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

