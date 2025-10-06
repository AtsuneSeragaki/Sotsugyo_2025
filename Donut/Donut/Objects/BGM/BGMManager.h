#pragma once

class BGMManager 
{
private:
    static int bgm_handle;   // BGMデータ

public:
    // 初期化処理（読み込み＆再生）
    static void Initialize(); 
    // 停止処理
    static void Stop(); 
    // 解放処理
    static void Release();
};