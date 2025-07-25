#pragma once
#include "../GameObject.h"

class Donuts : public GameObject
{
private:
	bool landed; // 着地したか

public:
	// コンストラクタ
	Donuts();
	// デストラクタ
	~Donuts();

	// 初期化処理
	virtual void Initialize() override;
	// 更新処理
	virtual void Update() override;
	// 描画処理
	virtual void Draw() const override;
	// 終了時処理
	virtual void Finalize() override;

private:
	// ドーナツ落下処理
	void FallDonut();
};
