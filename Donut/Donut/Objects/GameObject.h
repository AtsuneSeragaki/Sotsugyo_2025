#pragma once

#include "../Utility/Vector2D.h"



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