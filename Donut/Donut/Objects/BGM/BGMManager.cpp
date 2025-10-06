#include "BGMManager.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

int BGMManager::bgmHandle = -1;

void BGMManager::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	bgmHandle = rm->GetSounds("Resource/Sounds/title_bgm.mp3");

	if (!CheckSoundMem(bgmHandle))
	{
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void BGMManager::Stop()
{
	if (CheckSoundMem(bgmHandle))
	{
		StopSoundMem(bgmHandle);
	}
}

void BGMManager::Release()
{
	if (bgmHandle)
	{
		DeleteSoundMem(bgmHandle);
	}
}
