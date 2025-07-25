#include "DxLib.h"
#include "Utility/InputManager.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Windowモードで起動する
	ChangeWindowMode(TRUE);

	// Windowサイズの設定
	SetGraphMode(1280, 720, 32);

	// DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		// エラー状態を通知する
		OutputDebugString("DXライブラリが初期化できませんでした。\n");
		return -1;
	}

	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// ローカル変数定義
	SceneManager* manager = nullptr;
	ResourceManager* rm = ResourceManager::GetInstance();
	int result = 0;

	try
	{
		manager = new SceneManager();

		manager->Initialize();

		// 入力情報のインスタンスを取得
		InputManager* input = InputManager::GetInstance();

		// メインループ
		while (ProcessMessage() != -1)
		{
			// 画面の初期化
			ClearDrawScreen();

			// 入力情報の更新
			manager->Update();

			// 裏画面の内容を表画面に反映する
			ScreenFlip();

			// ESCキーが入力されたら、ループを終了する
			if (input->GetKeyInputState(KEY_INPUT_ESCAPE) == eInputState::eRelease)
			{
				break;
			}
		}
	}
	catch (std::string error_log)
	{
		// Log.txtにエラー内容を出力する
		OutputDebugString(error_log.c_str());
		// 終了状態を異常に設定する
		result = -1;
	}

	// オブジェクトの削除
	if (manager != nullptr)
	{
		manager->Finalize();
		delete manager;
	}

	// 入力機能のインスタンスを削除する
	InputManager::DeleteInstance();

	// 読み込んだ画像、音源の解放
	rm->UnloadResourcesAll();

	// リソース管理のインスタンスを削除する
	ResourceManager::DeleteInstance();

	// 終了状態の値を返却する
	DxLib_End();

	return result;

}