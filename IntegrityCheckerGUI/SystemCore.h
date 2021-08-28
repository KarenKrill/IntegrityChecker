#pragma once
#include <Windows.h>
#include <new.h>
#include <fstream>

#define MB(header, text) MessageBoxW(NULL, (LPCWSTR)(text), (LPCWSTR)header, MB_OK)

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

typedef __int8 int8;
typedef unsigned __int8 uint8;
typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

#ifndef NULL
#define NULL 0
#endif

namespace SystemCore
{
	ulong GetTime();
	namespace Memory
	{
		template<class T> T* Alloc(uint length){return new(std::nothrow) T[length];}
		template<class T> T* Alloc(){return new(std::nothrow) T;}
		template<class T> void FreeBuf(T* buffer){if(buffer) delete []buffer;}
		template<class T> void FreePtr(T* pointer){if(pointer) delete pointer;}
		bool Copy(const void *src, void *dest, uint size);
		bool Move(const void *src, void *dest, uint size);
		bool Set(void *buff, int value, uint length);
		bool Clear(void *buff, uint size);
	}
	namespace Locale
	{
		bool BytesToWchars(const char* src, uint length, wchar_t* dest);
	}
	namespace Exceptions
	{
		class Exception
		{
		public:
			Exception(){}
			~Exception(){}
		};
		class OutOfRange: public Exception
		{
		public:
			OutOfRange(){}
			~OutOfRange(){}
		};
	}
	namespace FileSystem
	{
		class FileStream
		{
			std::ifstream istream;
			std::ofstream ostream;
			std::wifstream wistream;
			std::wofstream wostream;
		public:
			bool wide;
			bool append;
			FileStream();
			~FileStream();
			void Read();
			bool Write(const wchar_t * filename, const wchar_t* buff, uint length);
		};
	}
}