@echo off
REM Windows 10/11 x64
gcc vls.c -o vls64.exe -O2 -s -m64

REM Windows 10/11 x86
gcc vls.c -o vls32.exe -O2 -s -m32

REM Windows 7
gcc vls.c -o vls7.exe -O2 -s -D_WIN32_WINNT=0x0601

REM Windows XP
gcc vls.c -o vlsXP.exe -O2 -s -D_WIN32_WINNT=0x0501 -static

echo Build complete!
pause