#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__

#include "..\define.h"
#include"..\C_Sound.h"

using namespace std;
class SoundManager
{
public:

	void PlaySound(string, bool);
	void StopAllSound();
	void Update();
	static SoundManager* getInstance();
private:
	SoundManager(void);
	~SoundManager();
	int soundID;
	vector<C_Sound*> PlayingSounds;
	static SoundManager* _instance;
};

#endif // !__SOUND_MANAGER__
