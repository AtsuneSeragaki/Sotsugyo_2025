#include "DxLib.h"
#include "Utility/InputManager.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Windowモードで起動する
	ChangeWindowMode(TRUE);

	// Windowサイズの設定
	SetGraphMode(640, 480, 32);

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
		// メインループ
		while (ProcessMessage() != -1)
		{
			manager = new SceneManager();

			manager->Initialize();

			// 入力情報のインスタンスを取得
			InputManager* input = InputManager::GetInstance();

			// 入力情報の更新
			manager->Update();

			// 画面の初期化
			ClearDrawScreen();

			// オブジェクトの描画処理
			object->Draw();

			// 裏画面の内容を表画面に反映する
			ScreenFlip();

			// ESCキーが入力されたら、ループを終了する
			if (input->GetKeyUp(KEY_INPUT_ESCAPE))
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
	if (object != nullptr)
	{
		object->Finalize();
		delete object;
		object = nullptr;
	}

	// 入力機能のインスタンスを削除する
	InputControl::DeleteInstance();

	// 読み込んだ画像、音源の解放
	rm->UnloadResourcesAll();

	// リソース管理のインスタンスを削除する
	ResourceManager::DeleteInstance();

	// 終了状態の値を返却する
	DxLib_End();

	return result;

}