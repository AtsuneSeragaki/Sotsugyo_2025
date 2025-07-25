#pragma once

#include "../Utility/Vector2D.h"
#include <vector>

enum class eSceneType
{
	eTitle,
	eGameMain,
	eResult,
	eHelp,
	eEnd,
};

class SceneBase
{
protected:
	int background_image;             // �w�i�摜�f�[�^

public:
	SceneBase();
	virtual ~SceneBase();

public:
	// ����������
	virtual void Initialize();
	// �X�V����
	virtual eSceneType Update();
	// �`�揈��
	virtual void Draw() const;
	// �I��������
	virtual void Finalize();

public:
	// ���݂̃V�[������Ԃ�
	virtual eSceneType  GetNowSceneType() const = 0;
};