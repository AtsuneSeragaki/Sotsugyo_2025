#pragma once

class BGMManager 
{
private:
    static int bgmHandle;   // BGM�f�[�^

public:
    // �����������i�ǂݍ��݁��Đ��j
    static void Initialize(); 
    // ��~����
    static void Stop(); 
    // �������
    static void Release();
};