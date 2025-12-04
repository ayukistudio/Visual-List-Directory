@echo off
echo ===============================
echo   Building VLS (Windows only)
echo ===============================

REM Check GCC (MinGW)
where gcc >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ERROR: GCC not found. Install MinGW-w64.
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build

echo Building vls64.exe (x64)...
gcc vls.c -o build\vls64.exe -O2 -s -m64

echo Building vls32.exe (x86)...
gcc vls.c -o build\vls32.exe -O2 -s -m32

echo Building vls7.exe (Win7)...
gcc vls.c -o build\vls7.exe -O2 -s -D_WIN32_WINNT=0x0601

echo Building vlsXP.exe (WinXP static)...
gcc vls.c -o build\vlsXP.exe -O2 -s -D_WIN32_WINNT=0x0501 -static

echo ===============================
echo Build completed!
echo Files saved in /build/
echo ===============================
pause
