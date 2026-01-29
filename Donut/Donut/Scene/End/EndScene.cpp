#include "EndScene.h"
#include "../../Utility/FontManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/BGM/BGMManager.h"
#include "DxLib.h"

// コンストラクタ
EndScene::EndScene():end_timer(0)
{
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/end/end.png");
	background_img = tmp[0];
	end_se = rm->GetSounds("Resource/Sounds/GameMain/gameover_se.mp3");
	ChangeVolumeSoundMem(200, end_se);

	BGMManager::Stop();
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
	if (end_timer < 200)
	{
		end_timer++;

		if (end_timer == 30)
		{
			PlaySoundMem(end_se, DX_PLAYTYPE_BACK, TRUE);
		}
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
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR, TRUE);
	DrawGraph(0, 0, background_img, FALSE);

	// タイトル
	//SetFontSize(80);
	////DrawString(220, 300, "THANK YOU FOR PLAYING", 0xffffff);
	//FontManager::Draw(100, 270, 0.9, 0.9, 0x5C4630, "THANK YOU FOR PLAYING");

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
