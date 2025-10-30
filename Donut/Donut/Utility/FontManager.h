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

	static void Draw(int x,int y, double scaleX = 1.0, double scaleY = 1.0, unsigned int color = 0xffffff,const char* text = "");

	static int GetFontHandle() { return font_handle; }
};