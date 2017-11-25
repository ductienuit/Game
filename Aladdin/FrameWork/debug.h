
#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <iostream>
#include <string>
#include <debugapi.h>
using namespace std;

template <typename T>
// T type should in:
// int, unsigned int, long, unsigned long,
// _Longlong, _ULonglong, long double, double, float
void __debugoutput(T var)
{
#if UNICODE
	wstring str = to_wstring(var);
	OutputDebugStringW(str.c_str());
	OutputDebugStringW(L"\n");
#else
	std::string str = to_string(var);
	LPCSTR s = const_cast<char *>(str.c_str());
	OutputDebugStringA(s);
	OutputDebugStringA("\n");
#endif // UNICOE
}

#endif // !__DEBUG_H__
