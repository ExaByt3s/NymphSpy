#include "../Includes/File.h"

bool File::Exist(const char* fileName) {
	return GetFileAttributesA(fileName) != INVALID_FILE_ATTRIBUTES;
}

bool File::Delete(const char* fileName) {
	return DeleteFileA(fileName);
}

bool File::Copy(const char* srcPath, const char* dstPath) {
	return CopyFileA(srcPath, dstPath, FALSE);
}

HANDLE File::Open(const char* fileName, DWORD dwAccess, DWORD dwCreation, DWORD dwFlags) {
	HANDLE hFile = CreateFileA(fileName, dwAccess, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, dwCreation, dwFlags, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return NULL;
	return hFile;
}

bool File::Write(HANDLE hFile, const void* data, int c_data) {
	c_data -= 1;
	DWORD writed = NULL;
	if (WriteFile(hFile, data, c_data, &writed, NULL)) return writed == (DWORD)c_data;
	return false;
}

DWORD File::Read(HANDLE hFile, void* data, int c_data) {
	DWORD readed = NULL;
	if (ReadFile(hFile, data, c_data, &readed, NULL)) return readed;
	return NULL;
}

void File::Close(HANDLE hFile) {
	CloseHandle(hFile);
}

bool File::SetAttributes(const char* fileName, DWORD dwAttributes) {
	return SetFileAttributesA(fileName, dwAttributes);
}

bool File::CreateTempFile(char* fileName, const char* prefix) {
	char* folder = new char[MAX_PATH];
	GetTempPathA(sizeof(folder), folder);
	GetTempFileNameA(folder, prefix, 0, fileName);
	return true;
}

sdk::list<NYMPHCORE_PHYSICAL_FILE> File::List(const char* szPath) {
	sdk::list<NYMPHCORE_PHYSICAL_FILE>* fileList = new sdk::list<NYMPHCORE_PHYSICAL_FILE>;
	WIN32_FIND_DATA findFileData;
	HANDLE fileHandle = FindFirstFile(szPath, &findFileData);
	if (fileHandle != INVALID_HANDLE_VALUE) {
		do {
			fileList->append({ (char*)findFileData.cFileName, findFileData.nFileSizeLow });
		} while (FindNextFile(fileHandle, &findFileData));
		FindClose(fileHandle);
	} return *fileList;
}