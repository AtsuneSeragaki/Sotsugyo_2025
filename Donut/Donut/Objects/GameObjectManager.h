#pragma once

#include "../Utility/Vector2D.h"
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
private:
	std::vector<GameObject*> create_objects;     // 生成するオブジェクト
	std::vector<GameObject*> destroy_objects;    // 削除するオブジェクト
	std::vector<GameObject*> game_objects_list;  // 生成したゲームオブジェクト

public:
	// コンストラクタ
	GameObjectManager();
	// デストラクタ
	~GameObjectManager();

public:
	// オブジェクトを生成するか確認する処理
	void CheckCreateObject();
	// オブジェクトを削除するか確認する処理
	void CheckDestroyObject();
	// 生成したゲームオブジェクトのリストを取得する処理
	const std::vector<GameObject*>& GetObjectList() const;
	// オブジェクトを削除する処理
	void DestroyGameObject(GameObject*);
	// 当たり判定を確認する処理
	void CheckCollision();

	//// オブジェクトを生成する処理
	//template <class T>
	//T* CreateGameObject(const Vector2D& location)
	//{
	//	T* new_instance = new T();

	//	GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

	//	if (new_object == nullptr)
	//	{
	//		delete new_instance;
	//		throw("ゲームオブジェクトが生成できませんでした\n");
	//	}

	//	new_object->SetLocation(location);

	//	new_object->Initialize();

	//	game_objects_list.push_back(new_object);

	//	return new_instance;
	//}

	// CreateGameObjectを可変引数対応にする
	template <class T, typename... Args>
	T* CreateGameObject(const Vector2D& location, Args&&... args)
	{
		T* new_instance = new T(std::forward<Args>(args)...);

		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("ゲームオブジェクトが生成できませんでした\n");
		}

		new_object->SetLocation(location);
		new_object->Initialize();
		game_objects_list.push_back(new_object);

		return new_instance;
	}

};