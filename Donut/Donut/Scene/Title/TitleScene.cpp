#include "DxLib.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
}

eSceneType TitleScene::Update()
{
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawFormatString(0, 0, 0xffffff, "Title");
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}