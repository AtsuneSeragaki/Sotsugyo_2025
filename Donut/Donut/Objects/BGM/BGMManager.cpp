#include "BGMManager.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

int BGMManager::bgm_handle = -1;

// ‰Šú‰»ˆ—i“Ç‚İ‚İ•Ä¶j
void BGMManager::Initialize()
{
	// BGM“Ç‚İ‚İ
	ResourceManager* rm = ResourceManager::GetInstance();
	bgm_handle = rm->GetSounds("Resource/Sounds/bgm.mp3");
	ChangeVolumeSoundMem(150, bgm_handle);

	// BGM‚ª—¬‚ê‚Ä‚¢‚È‚©‚Á‚½‚çA—¬‚·
	if (!CheckSoundMem(bgm_handle))
	{
		PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP, TRUE);
	}
}

// ’â~ˆ—
void BGMManager::Stop()
{
	if (CheckSoundMem(bgm_handle))
	{
		StopSoundMem(bgm_handle);
	}
}

// ‰ğ•úˆ—
void BGMManager::Release()
{
	if (bgm_handle)
	{
		DeleteSoundMem(bgm_handle);
	}
}
