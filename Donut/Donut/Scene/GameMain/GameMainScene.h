#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"


class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // ゲームオブジェクトクラスのオブジェクト
	class Player* player;     // プレイヤークラスのオブジェクト

public:
	// コンストラクタ
	GameMainScene();

	// デストラクタ
	~GameMainScene();

public:
	// 初期化処理
	virtual void Initialize() override;
	// 更新処理
	virtual eSceneType Update() override;
	// 描画処理
	virtual void Draw() const override;
	// 終了時処理
	virtual void Finalize() override;

public:
	// 現在のシーン情報を返す
	virtual eSceneType GetNowSceneType() const override;
};