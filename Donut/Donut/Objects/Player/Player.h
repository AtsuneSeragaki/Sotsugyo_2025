#pragma once
#include "../Donuts/Donuts.h"

class Player : public GameObject
{
private:
	bool is_click;                  // マウス左クリックされたか？
	DonutType donut_type;           // 落とすドーナツの種類
	DonutType next_donut_type;      // 次に落とすドーナツの種類
	float next_r;                   // 次に落とすドーナツの半径
	int donut_number;               // ドーナツの番号
	int next_donut_number;          // ネクストドーナツの番号
	bool donut_collision;           // ドーナツと当たっているか？

public:
	// コンストラクタ
	Player();
	
	// デストラクタ
	~Player();

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
	// 左クリックフラグ設定
	void SetClickFlg(bool flg) { is_click = flg; }

	// 左クリックフラグ取得
	bool GetClickFlg() { return is_click; }

	// 落とすドーナツの種類を取得
	DonutType GetDonutType() const { return donut_type; }

	// プレイヤーが動かすドーナツを次のドーナツに変更する
	void SetDonutRadius(float r) { this->r = r; }

	// 次に落とすドーナツの種類を取得
	DonutType GetNextDonutType() const { return next_donut_type; }

	// 次に落とすドーナツの半径設定(ネクスト描画用)
	void SetNextDonutRadius(float r) { next_r = r; }

	// プレイヤーが動かすドーナツの番号を設定
	void SetDonutNumber(int num) { donut_number = num; }
	
	// 次に落とすドーナツの番号を設定
	void SetNextDonutNumber(int num) { next_donut_number = num; }

	// ドーナツをランダムに選ぶ
	void ChooseRandomDonut();

	// ドーナツと当たっているか？フラグを設定
	void SetDonutCollision(bool flg) { donut_collision = flg; }

	// ドーナツと当たっているか？フラグを取得
	bool GetDonutCollision() { return donut_collision; }

	// プレイヤーのX座標を設定
	void SetPlayerPosX(float pos_x) { location.x = pos_x; }

private:
	// ドーナツを落とす枠の範囲しか移動出来ないようにする処理
	void LocXControl();
};
