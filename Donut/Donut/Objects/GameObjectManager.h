#pragma once

#include "../Utility/Vector2D.h"
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
private:
	std::vector<GameObject*> create_objects;     // ��������I�u�W�F�N�g
	std::vector<GameObject*> destroy_objects;    // �폜����I�u�W�F�N�g
	std::vector<GameObject*> game_objects_list;  // ���������Q�[���I�u�W�F�N�g

public:
	// �R���X�g���N�^
	GameObjectManager();
	// �f�X�g���N�^
	~GameObjectManager();

public:
	// �I�u�W�F�N�g�𐶐����邩�m�F���鏈��
	void CheckCreateObject();
	// �I�u�W�F�N�g���폜���邩�m�F���鏈��
	void CheckDestroyObject();
	// ���������Q�[���I�u�W�F�N�g�̃��X�g���擾���鏈��
	const std::vector<GameObject*>& GetObjectList() const;
	// �I�u�W�F�N�g���폜���鏈��
	void DestroyGameObject(GameObject*);
	// �����蔻����m�F���鏈��
	void CheckCollision();

	//// �I�u�W�F�N�g�𐶐����鏈��
	//template <class T>
	//T* CreateGameObject(const Vector2D& location)
	//{
	//	T* new_instance = new T();

	//	GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

	//	if (new_object == nullptr)
	//	{
	//		delete new_instance;
	//		throw("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
	//	}

	//	new_object->SetLocation(location);

	//	new_object->Initialize();

	//	game_objects_list.push_back(new_object);

	//	return new_instance;
	//}

	// CreateGameObject���ψ����Ή��ɂ���
	template <class T, typename... Args>
	T* CreateGameObject(const Vector2D& location, Args&&... args)
	{
		T* new_instance = new T(std::forward<Args>(args)...);

		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
		}

		new_object->SetLocation(location);
		new_object->Initialize();
		game_objects_list.push_back(new_object);

		return new_instance;
	}

};