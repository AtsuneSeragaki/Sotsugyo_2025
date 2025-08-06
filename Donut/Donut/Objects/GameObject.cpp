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

