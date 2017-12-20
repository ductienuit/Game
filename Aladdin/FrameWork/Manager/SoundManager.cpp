#include "SoundManager.h"

SoundManager* SoundManager::_instance;


SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::loadSound(HWND hWnd)
{
	// Khởi tạo CSoundManager.
	DirectSound_Init(hWnd);

	CSound* sound = nullptr;
	sound = LoadSound("Resources\Audio\PrinceAli.wav");
	_listSound[eSoundId::BACKGROUND_STAGE] = sound;
}

void SoundManager::Play(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		PlaySound(sound);
		this->currentSound = sound;
	}
}

void SoundManager::Stop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

void SoundManager::PlayLoop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}

bool SoundManager::IsPlaying(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}


SoundManager::SoundManager()
{
	currentSound = nullptr;
}


SoundManager::~SoundManager()
{
}
