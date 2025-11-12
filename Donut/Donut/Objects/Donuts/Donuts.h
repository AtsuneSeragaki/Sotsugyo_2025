#pragma once
#include "../GameObject.h"
#include <vector>

class Donuts : public GameObject
{
private:
	bool landed;      // 地面に着地したか？フラグ
	DonutType type;   // ドーナツの種類
	float vx;         // 横方向速度
	float vy;         // 重力
	bool isMerged;    // すでに合体したかどうか
	bool isDead;      // 削除予定（外部で処理）
	bool player_collision; // プレイヤーと当たっているか？フラグ
	bool landedOnSomething; // 何かの上に着地しているか？フラグ
	int donut_img; // ドーナツ画像

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

	// ドーナツのスコアを返す処理(引数：ドーナツの種類　戻り値：スコア)
	int GetDonutScore(DonutType dtype);
	
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

	void SetImage(const char* path);

	// 着地フラグを返す処理(戻り値：着地フラグ)
	bool GetLanded() { return landed; }

	// ドーナツ落下処理(引数:全てのドーナツオブジェクト)
	void FallDonut(const std::vector<Donuts*>& others);

	// どこかに支えられているか判定する処理(引数:全てのドーナツオブジェクト)
	bool IsSupported(const std::vector<Donuts*>& others);

	// ドーナツリストをコピーする処理
	//void SetDonutList(const std::vector<Donuts*>& others);

	// プレイヤーと当たっているか？フラグの設定(引数：設定したい値)
	void SetPlayerCollisionFlg(bool flg) { player_collision = flg; }

	// プレイヤーと当たっているか？フラグを取得
	bool GetPlayerCollisionFlg() { return player_collision; }

	// ドーナツが着地したか確認する処理(引数:全てのドーナツオブジェクト)
	void CheckDonutLanded(const std::vector<Donuts*>& others);

private:
	// ドーナツの枠はみ出し防止処理(引数：ドーナツを落とす枠の座標)
	void ClampToFrame(float left, float right, float top, float bottom);

	// 衝突処理(引数:全てのドーナツオブジェクト)
	void HandleCollision(Donuts* other);
};
