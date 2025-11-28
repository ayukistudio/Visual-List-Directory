/*
  vls — Visual Directory List
  Directory visualization for the Windows CLI
  
  @AyukiDev
  github.com/ayukistudio

 */

#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define COLOR_DIR 11
#define COLOR_FILE 15
#define COLOR_TREE 8
#define COLOR_SIZE 14

typedef struct {
    LARGE_INTEGER size;
    DWORD fileCount;
    DWORD dirCount;
} Stats;

HANDLE hConsole;

void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void formatSize(LARGE_INTEGER size, wchar_t* buffer) {
    double s = (double)size.QuadPart;
    if (s < 1024) {
        _snwprintf(buffer, 32, L"%d B", (int)s);
    } else if (s < 1024*1024) {
        _snwprintf(buffer, 32, L"%.1f KB", s/1024);
    } else if (s < 1024*1024*1024) {
        _snwprintf(buffer, 32, L"%.1f MB", s/(1024*1024));
    } else {
        _snwprintf(buffer, 32, L"%.2f GB", s/(1024*1024*1024));
    }
}

void printTreeW(const wchar_t* path, const wchar_t* prefix, int isLast, Stats* stats) {
    WIN32_FIND_DATAW findData;
    HANDLE hFind;
    wchar_t searchPath[MAX_PATH];
    wchar_t fullPath[MAX_PATH];
    wchar_t newPrefix[MAX_PATH];
    wchar_t sizeStr[32];
    wchar_t output[1024];
    DWORD written;
    
    _snwprintf(searchPath, MAX_PATH, L"%s\\*", path);
    hFind = FindFirstFileW(searchPath, &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) return;
    
    int count = 0;
    int total = 0;
    do {
        if (wcscmp(findData.cFileName, L".") != 0 && 
            wcscmp(findData.cFileName, L"..") != 0) {
            total++;
        }
    } while (FindNextFileW(hFind, &findData));
    
    FindClose(hFind);
    hFind = FindFirstFileW(searchPath, &findData);
    
    do {
        if (wcscmp(findData.cFileName, L".") == 0 || 
            wcscmp(findData.cFileName, L"..") == 0) {
            continue;
        }
        
        count++;
        int isLastItem = (count == total);
        
        setColor(COLOR_TREE);
        _snwprintf(output, 1024, L"%s%s", prefix, isLastItem ? L"+-- " : L"|-- ");
        WriteConsoleW(hConsole, output, wcslen(output), &written, NULL);
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            setColor(COLOR_DIR);
            WriteConsoleW(hConsole, findData.cFileName, wcslen(findData.cFileName), &written, NULL);
            setColor(COLOR_TREE);
            WriteConsoleW(hConsole, L"/\n", 2, &written, NULL);
            stats->dirCount++;
            
            _snwprintf(fullPath, MAX_PATH, L"%s\\%s", path, findData.cFileName);
            _snwprintf(newPrefix, MAX_PATH, L"%s%s", prefix, isLastItem ? L"    " : L"|   ");
            printTreeW(fullPath, newPrefix, isLastItem, stats);
        } else {
            setColor(COLOR_FILE);
            WriteConsoleW(hConsole, findData.cFileName, wcslen(findData.cFileName), &written, NULL);
            
            LARGE_INTEGER fileSize;
            fileSize.LowPart = findData.nFileSizeLow;
            fileSize.HighPart = findData.nFileSizeHigh;
            
            formatSize(fileSize, sizeStr);
            setColor(COLOR_SIZE);
            _snwprintf(output, 1024, L" (%s)\n", sizeStr);
            WriteConsoleW(hConsole, output, wcslen(output), &written, NULL);
            
            stats->size.QuadPart += fileSize.QuadPart;
            stats->fileCount++;
        }
        
    } while (FindNextFileW(hFind, &findData));
    
    FindClose(hFind);
}

int main(int argc, char* argv[]) {
    wchar_t fullPath[MAX_PATH];
    wchar_t sizeStr[32];
    wchar_t output[1024];
    Stats stats = {0};
    DWORD written;
    
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    if (argc > 1) {
        MultiByteToWideChar(CP_UTF8, 0, argv[1], -1, fullPath, MAX_PATH);
        DWORD attr = GetFileAttributesW(fullPath);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            MultiByteToWideChar(CP_ACP, 0, argv[1], -1, fullPath, MAX_PATH);
        }
    } else {
        GetCurrentDirectoryW(MAX_PATH, fullPath);
    }
    
    setColor(COLOR_DIR);
    _snwprintf(output, 1024, L"\nDirectory: %s\n", fullPath);
    WriteConsoleW(hConsole, output, wcslen(output), &written, NULL);
    
    setColor(COLOR_TREE);
    WriteConsoleW(hConsole, L"|\n", 2, &written, NULL);
    
    printTreeW(fullPath, L"", 0, &stats);
    
    formatSize(stats.size, sizeStr);
    setColor(COLOR_TREE);
    WriteConsoleW(hConsole, L"\n", 1, &written, NULL);
    
    setColor(15);
    _snwprintf(output, 1024, L"Summary: %d directories, %d files, %s total\n\n", 
            stats.dirCount, stats.fileCount, sizeStr);
    WriteConsoleW(hConsole, output, wcslen(output), &written, NULL);
    
    return 0;
}