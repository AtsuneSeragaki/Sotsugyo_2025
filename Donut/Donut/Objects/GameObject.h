#pragma once

#include "../Utility/Vector2D.h"

// ドーナツ落とす枠の情報
#define FRAME_WIDTH  480                  // ドーナツ落とす枠の幅
#define FRAME_HEIGHT 560                  // ドーナツ落とす枠の高さ
#define FRAME_LX 400                      // ドーナツ落とす枠の左上X座標
#define FRAME_LY 120                      // ドーナツ落とす枠の左上Y座標
#define FRAME_RX FRAME_LX + FRAME_WIDTH   // ドーナツ落とす枠の右下X座標(左上X座標 + 枠の幅)
#define FRAME_RY FRAME_LY + FRAME_HEIGHT  // ドーナツ落とす枠の右下Y座標(左上Y座標 + 枠の高さ)

#define MAX_PATH_LEN 256

// ドーナツの種類
//enum class DonutType
//{
//	DONUT_MINI_BASIC,           // ミスドの小さいドーナツみたいなやつ（ノーマル）
//	DONUT_MINI_VARIANT,         // ミスドの小さいドーナツみたいなやつ（色違い）
//	DONUT_FRENCH_CRULLER,       // フレンチクルーラー
//	DONUT_FRENCH_CRULLER_VAR,   // フレンチクルーラー（色違い）
//	DONUT_OLD_FASHIONED,        // オールドファッション
//	DONUT_OLD_FASHIONED_VAR,    // オールドファッション（色違い）
//	DONUT_GOLDEN_CHOCOLATE,     // ゴールデンチョコレート
//	DONUT_COCONUT_CHOCOLATE,    // ココナツチョコレート
//	DONUT_HALF_CHOCOLATE,       // 半分チョコドーナツ
//	DONUT_HALF_STRAWBERRY,      // 半分ストロベリードーナツ
//	DONUT_PON_DE_RING,          // ポン・デ・リング
//	DONUT_COUNT                 // ドーナツの総数
//};

enum class DonutType
{
	DONUT_BASIC,
	DONUT_COCONUT_CHOCOLATE,
	DONUT_HALF_CHOCOLATE,
	DONUT_STRAWBERRY,
	DONUT_CHOCOLATE,
	DONUT_FRENCH_CRULLER,
	DONUT_FRENCH_CRULLER_VAR,
	DONUT_PON_DE_RING,
	DONUT_PON_DE_RING_MATCHA,
	DONUT_PON_DE_RING_CHOCOLATE,
	DONUT_GOLDEN_CHOCOLATE,
	DONUT_COUNT  // ドーナツの総数
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


// ゲームオブジェクトクラス(画面に出てくるオブジェクトの親クラス)
class GameObject
{
protected:
	Vector2D location;   // 位置座標情報
	float r;             // 半径
	double rotation;
	int image;           // 描画する画像データ
	int flip_flag;       // 描画反転フラグ

public:
	// コンストラクタ
	GameObject();
	
	// デストラクタ
	virtual ~GameObject();

public:
	// 初期化処理
	virtual void Initialize();
	
	// 更新処理
	virtual void Update();
	
	// 描画処理
	virtual void Draw() const;
	
	// 終了時処理
	virtual void Finalize();

public:
	// 位置座標取得処理
	Vector2D GetLocation() const;
	
	// 半径の大きさ取得処理
	float GetRadiusSize() const;
	
	// 位置座標設定処理
	void SetLocation(const Vector2D& location);

	template <typename T>
	T Clamp(const T& v, const T& lo, const T& hi) 
	{
		return (v < lo) ? lo : (v > hi) ? hi : v;
	}

};