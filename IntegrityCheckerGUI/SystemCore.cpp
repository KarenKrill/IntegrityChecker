#include "stdafx.h"
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

using namespace SystemCore;

ulong SystemCore::GetTime()
{
	DWORD time=timeGetTime();
	return time;
}

bool Memory::Copy(const void *src, void *dest, uint size)
{
	if(!src||!dest) return false;
	memcpy(dest, src, size);
	return true;
}
bool Memory::Move(const void *src, void *dest, uint size)
{
	if(!src||!dest) return false;
	memmove(dest, src, size);
	return true;
}
bool Memory::Set(void *buff, int value, uint length)
{
	if(!buff) return false;
	memset(buff, value, length);
	return true;
}
bool Memory::Clear(void *buff, uint size){return Memory::Set(buff, 0, size);}

bool Locale::BytesToWchars(const char* src, uint length, wchar_t* dest)
{
	if(!src||!dest||!length) return false;
	int wcharsNumber;
	wcharsNumber=MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, src, length, dest, 2*length);
	if(wcharsNumber) return true;
	else return false;
}

FileSystem::FileStream::FileStream(){wide=false; append=false;}
FileSystem::FileStream::~FileStream(){}
void FileSystem::FileStream::Read(){}
bool FileSystem::FileStream::Write(const wchar_t * filename, const wchar_t* buff, uint length)
{
	if(!filename) return false;
	if(wide)
	{
		if(append) wostream.open(filename, std::ios::out|std::ios::app);
		else wostream.open(filename, std::ios::out);
		wostream.imbue(std::locale("Russian_Russia.1251"));
		wostream.write(buff, length);
		wostream.close();
	}
	else
	{}
	return true;
}