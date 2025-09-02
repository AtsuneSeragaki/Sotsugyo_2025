#include "EndScene.h"
#include "DxLib.h"

// コンストラクタ
EndScene::EndScene():end_timer(0)
{
}

// デストラクタ
EndScene::~EndScene()
{
}

// 初期化処理
void EndScene::Initialize()
{
}

// 更新処理
eSceneType EndScene::Update()
{
	if (end_timer < 120)
	{
		end_timer++;
	}
	else
	{
		return eSceneType::eNone;
	}

	return GetNowSceneType();
}

// 描画処理
void EndScene::Draw() const
{
	// 背景
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// タイトル
	SetFontSize(80);
	DrawString(220, 300, "THANK YOU FOR PLAYING", 0xffffff);

	//DrawFormatString(20, 30, 0x000000, "%d", end_timer);
}

// 終了時処理
void EndScene::Finalize()
{
}

// 現在のシーン情報を返す
eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
