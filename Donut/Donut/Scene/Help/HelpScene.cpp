#include "HelpScene.h"
#include "DxLib.h"

void HelpScene::Initialize()
{
}

eSceneType HelpScene::Update()
{
	return eSceneType();
}

void HelpScene::Draw() const
{
	SetFontSize(20);
	DrawFormatString(0, 0, 0xffffff, "Help");
}

void HelpScene::Finalize()
{
}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType();
}
