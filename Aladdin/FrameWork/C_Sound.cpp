#include "C_Sound.h"






C_Sound::C_Sound(string file, string id, bool loop)
{
	ID = id;
	File = file;
	Loop = loop;

	stringstream s;
	char result[256];
	s.str(std::string());
	s << "open " << File << " alias " << ID;
	mciSendString(s.str().c_str(), 0, 0, 0);
	s.str(std::string());
	s << "play " << ID;
	mciSendString(s.str().c_str(), 0, 0, 0);
	s.str(std::string());
	s << "set " << ID << " format time milliseconds";
	mciSendString(s.str().c_str(), 0, 0, 0);
	s.str(std::string());
	s << "status " << ID << " length";
	mciSendString(s.str().c_str(), result, sizeof(result), 0);

	Length = atoi(result);
	Finish = GetTickCount() + Length;
}

C_Sound::~C_Sound()
{
	stringstream s;
	s.str(std::string());
	s << "close " << ID;
	mciSendString(s.str().c_str(), 0, 0, 0);
}

bool C_Sound::Update(DWORD tick)
{
	if (tick > Finish)
	{
		if (Loop)
		{
			stringstream s;
			s.str(std::string());
			s << "play " << ID << " from 0";
			mciSendString(s.str().c_str(), 0, 0, 0);

			Finish = tick + Length;
			return false;
		}
		else
		{
			stringstream s;
			s.str(std::string());
			s << "close " << ID;
			mciSendString(s.str().c_str(), 0, 0, 0);
			return true;
		}
	}
	return false;
}
