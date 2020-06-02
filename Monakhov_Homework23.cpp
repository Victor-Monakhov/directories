#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

void dir(LPCWSTR sDir, LPCWSTR temp, bool sub = false) // передаем им€ файла и одну команду дл€ ввода в консоль
{
	WIN32_FIND_DATAW wfd; // структора, котора€ описывает файл найденный ф-цией FindFirstFile
	LARGE_INTEGER fileSize; // структура дл€ хранени€ 64-х битного значени€
	short cnt = 0;
	HANDLE hFind = FindFirstFile(sDir, &wfd); // FindFirstFile - ф-ци€б котора€ ищет каталог файла или подкаталог
											  // sDir - им€ файла, &wfd - буфер данных.
	wcout << endl;
	if (INVALID_HANDLE_VALUE != hFind) // если каталог существует тогда...
	{
		do
		{
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) // если файл не скрытый тогда ...
			{
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // если файл €вл€етс€ дирикторией ...
				{
					wcout << "\t<DIR>"; // выводим в консоль <DIR>
				}
				else // иначе
				{
					fileSize.LowPart = wfd.nFileSizeLow; // младшим 32-м битам присваиваем младшее двойное слово значени€ размера файла
					fileSize.HighPart = wfd.nFileSizeHigh; // старшим 32-м битам присваиваем старшее двойное слово значени€ размера файла
					wcout << fileSize.QuadPart << "\t"; // выводим в консоль 64-х битное значение размера файла
				}
				wcout << "\t" << wfd.cFileName << endl; // устанавливаем и выводим в консоль им€ файла
				cnt++; // увеличиваем счетчик
			}
		} while (NULL != FindNextFileW(hFind, &wfd)); // когда файлы закончатс€
		FindClose(hFind); // прекращаем поиск
		cout << "\nTotal files \t" << cnt << endl; // выводим в консоль количество файлов
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

int main(short argc, char* argv[]) //argc - кол-во команд дл€ ввода в консол,
{								  //argv - название команды
	setlocale(LC_ALL, "");
	WCHAR sDir[MAX_PATH] = L".\\*.*";	// им€ файла
	WCHAR temp[MAX_PATH] = L"\0";
	dir(sDir, temp, (argc > 1));
	wcout << endl;
	system("pause");
	return 0;
}
