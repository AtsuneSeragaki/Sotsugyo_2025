#include "RankingScene.h"
#include "DxLib.h"

// �R���X�g���N�^
RankingScene::RankingScene():button{}
{
}

// �f�X�g���N�^
RankingScene::~RankingScene()
{
}

// ����������
void RankingScene::Initialize()
{
}

// �X�V����
eSceneType RankingScene::Update()
{
	return GetNowSceneType();
}

// �`�揈��
void RankingScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(90);
	DrawString(510, 35, "RANKING", 0xffffff);
}

// �I��������
void RankingScene::Finalize()
{
}

// ���݂̃V�[������Ԃ�
eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}
