#include "EndScene.h"
#include "DxLib.h"

// �R���X�g���N�^
EndScene::EndScene():end_timer(0)
{
}

// �f�X�g���N�^
EndScene::~EndScene()
{
}

// ����������
void EndScene::Initialize()
{
}

// �X�V����
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

// �`�揈��
void EndScene::Draw() const
{
	// �w�i
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFC0CB, TRUE);

	// �^�C�g��
	SetFontSize(80);
	DrawString(220, 300, "THANK YOU FOR PLAYING", 0xffffff);

	//DrawFormatString(20, 30, 0x000000, "%d", end_timer);
}

// �I��������
void EndScene::Finalize()
{
}

// ���݂̃V�[������Ԃ�
eSceneType EndScene::GetNowSceneType() const
{
	return eSceneType::eEnd;
}
