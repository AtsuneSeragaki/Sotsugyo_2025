#include "RankingScene.h"
#include "DxLib.h"

// コンストラクタ
RankingScene::RankingScene():button{}
{
}

// デストラクタ
RankingScene::~RankingScene()
{
}

// 初期化処理
void RankingScene::Initialize()
{
}

// 更新処理
eSceneType RankingScene::Update()
{
	return GetNowSceneType();
}

// 描画処理
void RankingScene::Draw() const
{
	// 背景
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(90);
	DrawString(510, 35, "RANKING", 0xffffff);
}

// 終了時処理
void RankingScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}
