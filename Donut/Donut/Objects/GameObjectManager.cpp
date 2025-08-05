#include "GameObjectManager.h"
#include "Donuts/Donuts.h"

// コンストラクタ
GameObjectManager::GameObjectManager()
{
}

// デストラクタ
GameObjectManager::~GameObjectManager()
{
}

// オブジェクトを生成するか確認する処理
void GameObjectManager::CheckCreateObject()
{
}

// オブジェクトを削除するか確認する処理
void GameObjectManager::CheckDestroyObject()
{
}

// 生成したゲームオブジェクトのリストを取得する処理
const std::vector<GameObject*>& GameObjectManager::GetObjectList() const
{
	return game_objects_list;
}

// オブジェクトを削除する処理
void GameObjectManager::DestroyGameObject(GameObject*)
{
}

// 当たり判定を確認する処理
void GameObjectManager::CheckCollision()
{
}

// 削除対象のオブジェクトをリストから取り除く処理
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

