#include "BGMManager.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

int BGMManager::bgm_handle = -1;

void BGMManager::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	bgm_handle = rm->GetSounds("Resource/Sounds/bgm.mp3");
	ChangeVolumeSoundMem(150, bgm_handle);

	if (!CheckSoundMem(bgm_handle))
	{
		PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void BGMManager::Stop()
{
	if (CheckSoundMem(bgm_handle))
	{
		StopSoundMem(bgm_handle);
	}
}

void BGMManager::Release()
{
	if (bgm_handle)
	{
		DeleteSoundMem(bgm_handle);
	}
}
