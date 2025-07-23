#include "SceneBase.h"

#include "DxLib.h"

SceneBase::SceneBase() : background_image(NULL)
{

}

SceneBase::~SceneBase()
{
	this->Finalize();
}

void SceneBase::Initialize()
{

}

eSceneType SceneBase::Update()
{
	// objects�̍X�V�������܂Ƃ߂ČĂ�
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	return GetNowSceneType();
}

void SceneBase::Draw() const
{
	DrawGraph(0, 0, background_image, TRUE);

	// objects�̕`�揈�����܂Ƃ߂ČĂ�
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

void SceneBase::Finalize()
{
	// �v�f���󂩂ǂ������ׂ�
	if (objects.empty())
	{
		return;
	}

	// objects�̏I�����������܂Ƃ߂ČĂ�
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	// �v�f��S�č폜
	objects.clear();
}