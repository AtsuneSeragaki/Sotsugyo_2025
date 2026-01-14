#pragma once
#include "SceneBase.h"

// 固定化するフレームレート値
#define TARGET_FREAM_RATE (60)
// 1フレーム当たりの時間(マイクロ秒)
#define DELTA_SECOND (1000000 / TARGET_FREAM_RATE)

enum class DeleteDonutType {
	DONUT_FRENCH_CRULLER,
	DONUT_FRENCH_CRULLER_VAR,
	DONUT_PON_DE_RING,
	DONUT_PON_DE_RING_MATCHA,
	DONUT_PON_DE_RING_CHOCOLATE,
	DONUT_GOLDEN_CHOCOLATE,
};


class SceneManager
{
private:
	SceneBase* current_scene; // 現在のシーン
	bool loop_flag;           // ループするか？

public:
	SceneManager();
	~SceneManager();

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 終了時処理
	void Finalize();

public:
	// loop_flgの値を返す
	bool LoopCheck() const;

private:
	// 描画処理
	void Draw() const;
	// 引数(new_scene_type)シーンに切り替え処理
	void ChangeScene(eSceneType new_scene_type);
	// 引数(new_scene_type)のシーン生成処理
	SceneBase* CreateScene(eSceneType new_scene_type);
};