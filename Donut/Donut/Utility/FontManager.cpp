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

void FontManager::Draw(int x, int y, double scaleX, double scaleY, unsigned int color, const char* text)
{
	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	
	DrawExtendFormatStringToHandle(x, y, scaleX, scaleY, color, FontManager::GetFontHandle(), "%s", text);
	
	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

