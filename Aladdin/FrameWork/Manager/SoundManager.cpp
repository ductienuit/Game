#include "SoundManager.h"

SoundManager* SoundManager::_instance=nullptr;
void SoundManager::PlaySound(string file, bool loop)
{
	stringstream ss;
	ss.str(std::string());
	ss << soundID;
	C_Sound* sound = new C_Sound(file, ss.str(), loop);
	PlayingSounds.push_back(sound);
	++soundID;
}

void SoundManager::StopAllSound()
{
	for (vector<C_Sound*>::iterator i = PlayingSounds.begin(); i != PlayingSounds.end(); ++i)
		delete (*i);
	PlayingSounds.clear();
	soundID = 0;
}

void SoundManager::Update()
{
	DWORD tick = GetTickCount();
	for (int i = PlayingSounds.size() - 1; i >= 0; --i)
		if (PlayingSounds[i]->Update(tick))
		{
			delete PlayingSounds[i];
			PlayingSounds.erase(PlayingSounds.begin() + i);
		}
}

SoundManager * SoundManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SoundManager();
	return _instance;
}

SoundManager::SoundManager(void)
{
	this->soundID = 0;
}


SoundManager::~SoundManager()
{
}
