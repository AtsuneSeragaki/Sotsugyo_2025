#pragma once
#include "../GameObject.h"

class Player : public GameObject
{
private:
	bool is_click; // マウス左クリックされたか？

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

private:
	// ドーナツを落とす枠の範囲しか移動出来ないようにする処理
	void LocXControl();
};
