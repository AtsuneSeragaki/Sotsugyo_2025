#include "ResultScene.h"
#include "DxLib.h"

ResultScene::ResultScene(int score)
{
	this->score = score;
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update()
{
	return eSceneType();
}

void ResultScene::Draw() const
{
	// ��ʖ�
	SetFontSize(20);
	DrawFormatString(0, 0, 0xffffff, "Result");

	// �X�R�A
	DrawFormatString(0, 100, 0xffffff, "�X�R�A�F%d", score);
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType();
}
