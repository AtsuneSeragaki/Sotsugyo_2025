#include "EndScene.h"
#include "DxLib.h"

void EndScene::Initialize()
{
}

eSceneType EndScene::Update()
{
	return eSceneType();
}

void EndScene::Draw() const
{
	SetFontSize(20);
	DrawFormatString(0, 0, 0xffffff, "End");
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType();
}
