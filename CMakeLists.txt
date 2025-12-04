cmake_minimum_required(VERSION 3.10)
project(vls C)

set(SRC vls.c)

if(NOT WIN32)
    message(FATAL_ERROR "This project builds only on Windows.")
endif()

# -------------------------
# Windows 64-bit
# -------------------------
add_executable(vls64 ${SRC})
target_compile_options(vls64 PRIVATE -O2 -s -m64)

# -------------------------
# Windows 32-bit
# -------------------------
add_executable(vls32 ${SRC})
target_compile_options(vls32 PRIVATE -O2 -s -m32)

# -------------------------
# Windows 7
# -------------------------
add_executable(vls7 ${SRC})
target_compile_definitions(vls7 PRIVATE _WIN32_WINNT=0x0601)
target_compile_options(vls7 PRIVATE -O2 -s)

# -------------------------
# Windows XP (static)
# -------------------------
add_executable(vlsXP ${SRC})
target_compile_definitions(vlsXP PRIVATE _WIN32_WINNT=0x0501)
target_compile_options(vlsXP PRIVATE -O2 -s -static)
