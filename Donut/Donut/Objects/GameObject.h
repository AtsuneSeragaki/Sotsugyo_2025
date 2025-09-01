#pragma once

#include "../Utility/Vector2D.h"

// ドーナツ落とす枠の情報
#define FRAME_WIDTH  480                  // ドーナツ落とす枠の幅
#define FRAME_HEIGHT 560                  // ドーナツ落とす枠の高さ
#define FRAME_LX 400                      // ドーナツ落とす枠の左上X座標
#define FRAME_LY 120                      // ドーナツ落とす枠の左上Y座標
#define FRAME_RX FRAME_LX + FRAME_WIDTH   // ドーナツ落とす枠の右下X座標(左上X座標 + 枠の幅)
#define FRAME_RY FRAME_LY + FRAME_HEIGHT  // ドーナツ落とす枠の右下Y座標(左上Y座標 + 枠の高さ)

// ゲームオブジェクトクラス(画面に出てくるオブジェクトの親クラス)
class GameObject
{
protected:
	Vector2D location;   // 位置座標情報
	float r;             // 半径
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