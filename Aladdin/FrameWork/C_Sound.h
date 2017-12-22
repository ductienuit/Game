#pragma once
#include"..\FrameWork\define.h"
class C_Sound
{
	bool Loop;
	string ID;
	string File;
	DWORD Finish;
	DWORD Length;

public:
	C_Sound(string, string, bool);
	~C_Sound();

	bool Update(DWORD);
};

