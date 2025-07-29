#pragma once
#include "../GameObject.h"
#define MAX_PATH_LEN 256

// ドーナツの種類
typedef enum class DonutType
{
	DONUT_MINI_BASIC,           // ミスドの小さいドーナツみたいなやつ（ノーマル）
	DONUT_MINI_VARIANT,         // ミスドの小さいドーナツみたいなやつ（色違い）
	DONUT_FRENCH_CRULLER,       // フレンチクルーラー
	DONUT_FRENCH_CRULLER_VAR,   // フレンチクルーラー（色違い）
	DONUT_OLD_FASHIONED,        // オールドファッション
	DONUT_OLD_FASHIONED_VAR,    // オールドファッション（色違い）
	DONUT_GOLDEN_CHOCOLATE,     // ゴールデンチョコレート
	DONUT_COCONUT_CHOCOLATE,    // ココナツチョコレート
	DONUT_HALF_CHOCOLATE,       // 半分チョコドーナツ
	DONUT_HALF_STRAWBERRY,      // 半分ストロベリードーナツ
	DONUT_PON_DE_RING,          // ポン・デ・リング
	DONUT_COUNT                 // ← ドーナツの総数（自動で11になる）
};

// ドーナツ情報構造体
typedef struct {
	DonutType type;  // ドーナツの種類
	float size;      // サイズ(半径)
	int score;       // このドーナツが生成された時に加算されるスコア
	char image_path[MAX_PATH_LEN]; // ドーナツ画像パス
} DonutInfo;

class Donuts : public GameObject
{
private:
	bool landed; // 着地したか
	DonutType type; // ドーナツの種類
	float vy; // 重力

public:
	// コンストラクタ
	Donuts(DonutType type);
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
