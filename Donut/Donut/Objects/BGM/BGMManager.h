#pragma once

class BGMManager 
{
private:
    static int bgm_handle;   // BGM�f�[�^

public:
    // �����������i�ǂݍ��݁��Đ��j
    static void Initialize(); 
    // ��~����
    static void Stop(); 
    // �������
    static void Release();
};