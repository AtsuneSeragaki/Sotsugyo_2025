#include "ResultScene.h"
#include "DxLib.h"

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update()
{
	return eSceneType();
}

void ResultScene::Draw() const
{
	SetFontSize(20);
	DrawFormatString(0, 0, 0xffffff, "Result");
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType();
}
