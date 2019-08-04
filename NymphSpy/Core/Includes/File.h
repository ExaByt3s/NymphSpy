#pragma once 

#include "../Core.h"

struct NYMPHCORE_PHYSICAL_FILE {
	sdk::string name;
	size_t size;
};

namespace File {
	bool Exist(const char* fileName);
	bool Delete(const char* fileName);
	bool Copy(const char* srcPath, const char* dstPath);

	HANDLE Open(const char* fileName, DWORD dwAccess, DWORD dwCreation, DWORD dwFlags);
	bool Write(HANDLE hFile, const void* data, int c_data);
	DWORD Read(HANDLE hFile, void* data, int c_data);
	void Close(HANDLE hFile);

	bool SetAttributes(const char* fileName, DWORD dwAttributes);
	bool CreateTempFile(char* fileName, const char* prefix);

	sdk::list<NYMPHCORE_PHYSICAL_FILE> List(const char* szPath);
}

 