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

	return GetNowSceneType();
}

void SceneBase::Draw() const
{
	//DrawGraph(0, 0, background_image, TRUE);
}

void SceneBase::Finalize()
{
	
}