#include "SceneManager.h"
#include "DxLib.h"
#include "Title/TitleScene.h"
#include "GameMain/GameMainScene.h"
#include "Help/HelpScene.h"
#include "Result/ResultScene.h"
#include "End/EndScene.h"

SceneManager::SceneManager() : current_scene(nullptr), loop_flag(true)
{

}

SceneManager::~SceneManager()
{
	this->Finalize();
}

void SceneManager::Initialize()
{
	ChangeScene(eSceneType::eGameMain);
}

void SceneManager::Update()
{
	eSceneType next_scene_type = current_scene->Update();

	current_scene->Draw();

	if (next_scene_type != current_scene->GetNowSceneType())
	{
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Finalize()
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

bool SceneManager::LoopCheck() const
{
	return loop_flag;
}

void SceneManager::ChangeScene(eSceneType new_scene_type)
{
	if (new_scene_type == eSceneType::eEnd)
	{
		loop_flag = false;
		return;
	}

	SceneBase* new_scene = CreateScene(new_scene_type);

	if (new_scene == nullptr)
	{
		throw("\n新しいシーンの生成ができませんでした。\n");
	}

	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();

	current_scene = new_scene;
}


// dynamiccast(SceneBaseを継承しいているか確認)
SceneBase* SceneManager::CreateScene(eSceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case eSceneType::eTitle:
		return dynamic_cast<SceneBase*>(new TitleScene());

	case eSceneType::eGameMain:
		return dynamic_cast<SceneBase*>(new GameMainScene());

	case eSceneType::eHelp:
		return dynamic_cast<SceneBase*>(new HelpScene());

	case eSceneType::eResult:
		return dynamic_cast<SceneBase*>(new ResultScene());

	case eSceneType::eEnd:
		return dynamic_cast<SceneBase*>(new EndScene());

	default:
		return nullptr;
	}
}