#pragma once
#include "../GameObject.h"
#include <vector>
#define MAX_PATH_LEN 256

// ドーナツの種類
enum class DonutType
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
	DONUT_COUNT
};

// ドーナツ情報構造体
typedef struct {
	DonutType type;  // ドーナツの種類
	float size;      // サイズ(半径)
	int score;       // このドーナツが生成された時に加算されるスコア
	char image_path[MAX_PATH_LEN]; // ドーナツ画像パス
} DonutInfo;

constexpr int MAX_DONUT_NUM = static_cast<int>(DonutType::DONUT_COUNT);
extern const DonutInfo g_DonutInfoTable[MAX_DONUT_NUM];

class Donuts : public GameObject
{
private:
	bool landed; // 着地したか
	DonutType type; // ドーナツの種類
	float vx;  // ← 横方向速度
	float vy; // 重力
	const char* name; // デバック用のドーナツの種類
	bool isMerged;  // すでに合体したかどうか
	bool isDead;    // 削除予定（外部で処理）

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
	// ドーナツの半径を返す
	float GetDonutRadius(DonutType dtype);
	Vector2D GetVelocity() const { return Vector2D(vx, vy); }
	void SetVelocity(Vector2D vel) { vx = vel.x; vy = vel.y; }

	void ResolveCollision(Donuts* other);

	DonutType GetDonutType() const { return type; }
	void SetDonutType(DonutType t) { type = t; name = GetDonutTypeName(t); }
	void SetRadius(float r_) { r = r_; }

	bool IsDead() const { return isDead; }
	void SetDead(bool d) { isDead = d; }

	bool IsMerged() const { return isMerged; }
	void SetMerged(bool m) { isMerged = m; }

	// ドーナツ落下処理
	void FallDonut(const std::vector<Donuts*>& others);

private:
	// デバック用のドーナツ種類文字に変換処理
	const char* GetDonutTypeName(DonutType type);

	// ドーナツの枠はみ出し防止
	void ClampToFrame(float left, float right, float top, float bottom);
};
