#include "SceneManager.h"
#include "DxLib.h"
#include "Title/TitleScene.h"
#include "GameMain/GameMainScene.h"
#include "Help/HelpScene.h"
#include "Result/ResultScene.h"
#include "Ranking/RankingScene.h"
#include "End/EndScene.h"
#include "../Utility/FontManager.h"


SceneManager::SceneManager() : current_scene(nullptr), loop_flag(true)
{

}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	// ウィンドウのタイトルを設定
	SetMainWindowText("Donut");

	// ウィンドウモードで起動
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("ウィンドウモードで起動できませんでした\n");
	}

	// ウィンドウサイズの設定
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	// DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		throw("Dxライブラリが初期化できませんでした\n");
	}

	// 描画先指定処理
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("描画先の指定ができませんでした\n");
	}

	FontManager::Initialize();

	ChangeScene(eSceneType::eTitle);
}

void SceneManager::Update()
{
	// フレーム開始時間(マイクロ秒を取得)
	LONGLONG start_time = GetNowHiPerformanceCount();

	while (ProcessMessage() != -1)
	{
		// 現在時間を取得
		LONGLONG now_time = GetNowHiPerformanceCount();

		// 1フレーム当たりの時間に到達したら、更新および描画処理を行う
		if ((now_time - start_time) >= DELTA_SECOND)
		{
			// フレーム開始時間を更新する
			start_time = now_time;

			// 更新処理(戻り値は次のシーン情報)
			eSceneType next = current_scene->Update();

			// 描画処理
			Draw();

			// 現在のシーンと次のシーンが違っていたら、切り替え処理を行う
			if (next != current_scene->GetNowSceneType())
			{

				ChangeScene(next);
			}
		}

		// ESCAPEキーが押されたら、ゲームを終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		if (!LoopCheck())
		{
			break;
		}
	}
}

void SceneManager::Finalize()
{
	FontManager::Cleanup();

	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	// DXライブラリの使用を終了する
	DxLib_End();
}

bool SceneManager::LoopCheck() const
{
	return loop_flag;
}

void SceneManager::Draw() const
{
	// 画面の初期化
	ClearDrawScreen();

	// シーンの描画
	current_scene->Draw();

	// 裏画面の内容を表画面に反映
	ScreenFlip();
}

void SceneManager::ChangeScene(eSceneType new_scene_type)
{
	if (new_scene_type == eSceneType::eNone)
	{
		loop_flag = false;  // ループ終了
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
	{
		GameMainScene* gm = dynamic_cast<GameMainScene*>(current_scene);
		int score = gm ? gm->GetScore() : 0; // gmがnullptrなら0にする
		return dynamic_cast<SceneBase*>(new ResultScene(score));
	}

	case eSceneType::eRanking:
		return dynamic_cast<SceneBase*>(new RankingScene());

	case eSceneType::eEnd:
		return dynamic_cast<SceneBase*>(new EndScene());

	default:
		return nullptr;
	}
}