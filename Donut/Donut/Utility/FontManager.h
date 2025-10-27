#pragma once
#include "DxLib.h"

class FontManager
{
private:
	static int font_handle; // フォントデータ

public:
	// 初期化処理
	static void Initialize();

	static void Cleanup();

	static int GetFontHandle() { return font_handle; }
};