#pragma once

#define RANKING_DATA_MAX 3

class RankingData
{
private:
	int rank[RANKING_DATA_MAX];   // ランク
	int score[RANKING_DATA_MAX];  // スコア

public:

	// コンストラクタ
	RankingData();

	// デストラクタ
	~RankingData();

	// 初期処理
	void Initialize();

	// 終了処理
	void Finalize();

	// ランキングデータの設定
	void SetRankingData(int score);

	// スコア取得処理
	int GetScore(int value) const { return score[value]; }

	// ランク取得処理
	int GetRank(int value) const { return rank[value]; }

private:
	// データ入れ替え処理
	void SortData();
};