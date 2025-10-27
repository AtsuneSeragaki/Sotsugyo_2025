#include "FontManager.h"
#include "DxLib.h"

int FontManager::font_handle = -1;

void FontManager::Initialize()
{
	// ウィンドウズPCに一時的にフォントデータを読み込む(システム終了まで)
	AddFontResourceExA("Resource/Font/Guanine.otf", FR_PRIVATE, NULL);

	font_handle = CreateFontToHandle("Guanine", 100, 4, DX_FONTTYPE_ANTIALIASING_4X4);
}

void FontManager::Cleanup()
{
	DeleteFontToHandle(font_handle);

	// ウィンドウズに一時的に保持していたフォントデータを削除
	RemoveFontResourceExA("Resource/Font/Guanine.otf", FR_PRIVATE, NULL);
}

