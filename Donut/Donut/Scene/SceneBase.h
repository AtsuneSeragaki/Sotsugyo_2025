#pragma once

#include "../Utility/Vector2D.h"
//#include "../Object/GameObject.h"
#include <vector>

enum class eSceneType
{
	eTitle,
	eInGame,
	eResult,
	eHelp,
	eEnd,
};

class SceneBase
{
protected:
	std::vector<GameObject*> objects; // ���I�z��
	int background_image;             // �w�i�摜�f�[�^

public:
	SceneBase();
	virtual ~SceneBase();

public:
	// ����������
	virtual void Initialize();
	// �X�V����
	virtual eSceneType Update();
	// �`�揈��
	virtual void Draw() const;
	// �I��������
	virtual void Finalize();

public:
	// ���݂̃V�[������Ԃ�
	virtual eSceneType  GetNowSceneType() const = 0;

protected:
	// �N���X�e���v���[�g(�e���v���[�g�̎����̓w�b�_�[�t�@�C�����ɏ���)
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		T* new_instance = new T();

		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
		}

		new_object->SetLocation(location);

		new_object->Initialize();

		objects.push_back(new_object);

		return new_instance;
	}

	void DestroyObject(GameObject* target);
};