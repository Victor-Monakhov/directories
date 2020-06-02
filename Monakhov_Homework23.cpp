#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

void dir(LPCWSTR sDir, LPCWSTR temp, bool sub = false) 
{
	WIN32_FIND_DATAW wfd;
	LARGE_INTEGER fileSize; 
	short cnt = 0;
	HANDLE hFind = FindFirstFile(sDir, &wfd); 
	wcout << endl;
	if (INVALID_HANDLE_VALUE != hFind) 
	{
		do
		{
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) 
			{
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
					wcout << "\t<DIR>"; 
				}
				else 
				{
					fileSize.LowPart = wfd.nFileSizeLow;
					fileSize.HighPart = wfd.nFileSizeHigh; 
					wcout << fileSize.QuadPart << "\t"; 
				}
				wcout << "\t" << wfd.cFileName << endl; 
				cnt++; 
			}
		} while (NULL != FindNextFileW(hFind, &wfd)); 
		FindClose(hFind); 
		cout << "\nTotal files \t" << cnt << endl; 
	}  
	hFind = FindFirstFileW(sDir, &wfd);
	wcout << endl;
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && (WCHAR)wfd.cFileName[0] != '.')
				{
					system("pause");
					wcout << wfd.cFileName << ":" << endl;
					if ((WCHAR)sDir[0] != '.') {
						for (int i = 0; i < wcslen((WCHAR*)sDir); i++) {
							if ((WCHAR)sDir[i] == '.') {
								(WCHAR)sDir[i] = '\\';
								(WCHAR)sDir[i + 1] = '\0';
							}
						}
						temp = sDir;
						wcscat((WCHAR*)temp, wfd.cFileName);
						wcscat((WCHAR*)temp, L".\\*.*");
					}
					else {
						temp = wfd.cFileName;
						wcscat((WCHAR*)temp, L".\\*.*");
					}
					dir((WCHAR*)temp, NULL, sub);
				}
			}
		} while (NULL != FindNextFileW(hFind, &wfd));
		for (int i = wcslen((WCHAR*)sDir); i > 0 ; i--) {
			if ((WCHAR)sDir[i] == '\\' && (WCHAR)sDir[i - 1] != '.'){
				(WCHAR)sDir[i] = '\0';
				wcscat((WCHAR*)sDir, L".\\*.*");
				break;
			}
		}
		FindClose(hFind);
	}
}

int main(short argc, char* argv[]) 
{								 
	setlocale(LC_ALL, "");
	WCHAR sDir[MAX_PATH] = L".\\*.*";	
	WCHAR temp[MAX_PATH] = L"\0";
	dir(sDir, temp, (argc > 1));
	wcout << endl;
	system("pause");
	return 0;
}
