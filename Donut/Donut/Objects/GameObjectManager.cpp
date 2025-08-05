#include "GameObjectManager.h"
#include "Donuts/Donuts.h"

// �R���X�g���N�^
GameObjectManager::GameObjectManager()
{
}

// �f�X�g���N�^
GameObjectManager::~GameObjectManager()
{
}

// �I�u�W�F�N�g�𐶐����邩�m�F���鏈��
void GameObjectManager::CheckCreateObject()
{
}

// �I�u�W�F�N�g���폜���邩�m�F���鏈��
void GameObjectManager::CheckDestroyObject()
{
}

// ���������Q�[���I�u�W�F�N�g�̃��X�g���擾���鏈��
const std::vector<GameObject*>& GameObjectManager::GetObjectList() const
{
	return game_objects_list;
}

// �I�u�W�F�N�g���폜���鏈��
void GameObjectManager::DestroyGameObject(GameObject*)
{
}

// �����蔻����m�F���鏈��
void GameObjectManager::CheckCollision()
{
}

// �폜�Ώۂ̃I�u�W�F�N�g�����X�g�����菜������
void GameObjectManager::RemoveDeadObjects()
{
    for (auto it = game_objects_list.begin(); it != game_objects_list.end(); )
    {
        Donuts* donut = dynamic_cast<Donuts*>(*it);
        if (donut && donut->IsDead()) {
            delete donut;
            it = game_objects_list.erase(it);
        }
        else {
            ++it;
        }
    }
}

