#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"


class GameMainScene : public SceneBase
{
private:
	GameObjectManager* gameobjects;  // ゲームオブジェクトクラスのオブジェクト
	class Player* player;            // プレイヤークラスのオブジェクト
	class Order* order;              // オーダークラスのオブジェクト
	bool is_gameover;                // ゲームオーバーか？
	class Donuts* donut_collision;   // プレイヤーと当たっているドーナツの情報
	int score;

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

private:
	// ドーナツ同士の当たり判定
	void CollisionDonuts();

	// 当たった時の処理
	void ResolveDonutCollision(class Donuts* a, class Donuts* b);

	// 枠内にあるドーナツとプレイヤーの当たり判定処理(戻り値：0→当たってない 1→当たっている)
	void DonutPlayerCollision(class Donuts* donut);
};