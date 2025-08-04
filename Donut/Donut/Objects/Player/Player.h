#pragma once
#include "../Donuts/Donuts.h"

class Player : public GameObject
{
private:
	bool is_click; // マウス左クリックされたか？
	DonutType next_donut_type; // 次に落とすドーナツの種類
	DonutType next_next_donut_type; // 次の次に落とすドーナツの種類
	float next_r; // 次の次に落とすドーナツの半径

public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 初期化処理
	virtual void Initialize() override;
	// 更新処理
	virtual void Update() override;
	// 描画処理
	virtual void Draw() const override;
	// 終了時処理
	virtual void Finalize() override;

	// 左クリックフラグ設定
	bool SetClickFlg(bool flg);

	// 左クリックフラグ取得
	bool GetClickFlg();

	// 次に落とすドーナツの種類を取得
	DonutType GetNextDonutType() const { return next_donut_type; }

	// 次の次に落とすドーナツの種類を取得
	DonutType GetNextNextDonutType() const { return next_next_donut_type; }

	// ドーナツをランダムに選ぶ
	void ChooseRandomDonut();

	// プレイヤーが動かすドーナツを次のドーナツに変更する
	void SetDonutRadius(float r) { this->r = r; }

	//　次の次に落とすドーナツの半径設定(ネクスト描画用)
	void SetNextDonutRadius(float r) { next_r = r; }

private:
	// ドーナツを落とす枠の範囲しか移動出来ないようにする処理
	void LocXControl();
};
