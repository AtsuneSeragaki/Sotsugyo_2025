#include "FontManager.h"
#include "DxLib.h"

int FontManager::font_handle[] = {};

void FontManager::Initialize()
{
	// ウィンドウズPCに一時的にフォントデータを読み込む(システム終了まで)
	AddFontResourceExA("Resource/Fonts/Guanine.otf", FR_PRIVATE, NULL);
	AddFontResourceExA("Resource/Fonts/AtkinsonHyperlegibleMono-ExtraBold.ttf", FR_PRIVATE, NULL);


	font_handle[0] = CreateFontToHandle("Guanine", 100, 4, DX_FONTTYPE_ANTIALIASING_4X4);
	font_handle[1] = CreateFontToHandle("Atkinson Hyperlegible Mono ExtraBold", 100, 4, DX_FONTTYPE_ANTIALIASING);

}

void FontManager::Cleanup()
{
	for (int i = 0; i < FONT_NUM; i++)
	{
		DeleteFontToHandle(font_handle[i]);
	}
	
	// ウィンドウズに一時的に保持していたフォントデータを削除
	RemoveFontResourceExA("Resource/Fonts/Guanine.otf", FR_PRIVATE, NULL);
	RemoveFontResourceExA("Resource/Fonts/AtkinsonHyperlegibleMono-ExtraBold.ttf", FR_PRIVATE, NULL);
}

void FontManager::DrawStr(int x, int y, double scaleX, double scaleY, unsigned int color, const char* text)
{
	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	DrawExtendFormatStringToHandle(x, y, scaleX, scaleY, color, FontManager::GetFontHandle(0), "%s", text);

	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void FontManager::DrawNum(int x, int y, double scaleX, double scaleY, unsigned int color, const char* text)
{
	//バイリニア法で描画する
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	DrawExtendFormatStringToHandle(x, y, scaleX, scaleY, color, FontManager::GetFontHandle(1), "%s", text);

	// ネアレストネイバー法で描画する(標準)
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
