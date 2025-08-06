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
	DONUT_COUNT                 // ドーナツの総数
};

// ドーナツ情報構造体
typedef struct {
	DonutType type;  // ドーナツの種類
	float size;      // サイズ(半径)
	int score;       // このドーナツが生成された時に加算されるスコア
	char image_path[MAX_PATH_LEN]; // ドーナツ画像パス
	int number;      // ドーナツ番号
} DonutInfo;

// ドーナツの種類総数
constexpr int MAX_DONUT_NUM = static_cast<int>(DonutType::DONUT_COUNT);
extern const DonutInfo g_DonutInfoTable[MAX_DONUT_NUM];

class Donuts : public GameObject
{
private:
	bool landed;      // 着地したか
	DonutType type;   // ドーナツの種類
	float vx;         // 横方向速度
	float vy;         // 重力
	bool isMerged;    // すでに合体したかどうか
	bool isDead;      // 削除予定（外部で処理）
	bool isRolling = false;
	float rollingDirection = 0.0f;
	float rolledDistance = 0.0f;
	const float maxRollingDistance = 100.0f;  // 転がる最大距離
	const float rollingSpeed = 1.0f;          // 1フレームあたりの転がる速度
	std::vector<Donuts*>* donutList;

public:
	// コンストラクタ
	Donuts(DonutType type);
	
	// デストラクタ
	~Donuts();

public:
	// 初期化処理
	virtual void Initialize() override;
	
	// 更新処理
	virtual void Update() override;
	
	// 描画処理
	virtual void Draw() const override;
	
	// 終了時処理
	virtual void Finalize() override;

public:
	// ドーナツの半径を返す処理(引数：ドーナツの種類　戻り値：半径)
	float GetDonutRadius(DonutType dtype);
	
	// ドーナツの番号を返す処理(引数：ドーナツの種類　戻り値：番号)
	int GetDonutNumber(DonutType dtype);
	
	// 重力を返す処理(戻り値：重力)
	Vector2D GetVelocity() const { return Vector2D(vx, vy); }
	
	// 重力を書き換える処理(引数：設定したい値)
	void SetVelocity(Vector2D vel) { vx = vel.x; vy = vel.y; }
	
	// ドーナツの種類を返す処理(戻り値：ドーナツの種類)
	DonutType GetDonutType() const { return type; }
	
	// ドーナツの種類を書き換える処理(引数：設定したいドーナツの種類)
	void SetDonutType(DonutType t) { type = t;}
	
	// ドーナツの半径を書き換える処理(引数：設定したいドーナツの半径)
	void SetRadius(float r_) { r = r_; }
	
	// 削除予定フラグを返す処理(戻り値：削除予定フラグ)
	bool IsDead() const { return isDead; }
	
	// 削除予定フラグを書き換える処理
	void SetDead(bool d) { isDead = d; }
	
	// 合体したか？フラグを返す処理(戻り値：合体したか？フラグ)
	bool IsMerged() const { return isMerged; }

	// 合体したか？フラグを書き換える処理(引数：設定したい値)
	void SetMerged(bool m) { isMerged = m; }

	// ドーナツ落下処理
	void FallDonut(const std::vector<Donuts*>& others);

	// どこかに支えられているか判定する処理
	bool IsSupported(const std::vector<Donuts*>& others);

	// ドーナツリストをコピーする処理
	void SetDonutList(const std::vector<Donuts*>& others);

private:
	// ドーナツの枠はみ出し防止処理
	void ClampToFrame(float left, float right, float top, float bottom);
};
