#pragma once
#include "DxLib.h"

#define FONT_NUM 2

class FontManager
{
private:
	static int font_handle[FONT_NUM]; // フォントデータ

public:
	// 初期化処理
	static void Initialize();

	static void Cleanup();

	static void DrawStr(int x,int y, double scaleX = 1.0, double scaleY = 1.0, unsigned int color = 0xffffff,const char* text = "");
	static void DrawNum(int x, int y, double scaleX = 1.0, double scaleY = 1.0, unsigned int color = 0xffffff, const char* text = "");

	static int GetFontHandle(int font_num) { return font_handle[font_num]; }
};