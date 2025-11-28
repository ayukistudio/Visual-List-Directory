# Visual List Directory (VLS)

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://raw.githubusercontent.com/ayukistudio/Visual-List-Directory/refs/heads/main/media/vlslogo_dark.png">
  <source media="(prefers-color-scheme: light)" srcset="https://raw.githubusercontent.com/ayukistudio/Visual-List-Directory/refs/heads/main/media/vlslogo_white.png">
  <img alt="vls logo" src="https://raw.githubusercontent.com/ayukistudio/Visual-List-Directory/refs/heads/main/media/vlslogo_white.png" width="400">
</picture>

A lightweight command-line utility for Windows that displays directory trees with color-coded files and folders. Written in pure C with full Unicode support.

![vls in action](https://raw.githubusercontent.com/ayukistudio/Visual-List-Directory/refs/heads/main/media/vls_action.gif)

## Features

- Tree-style directory visualization
- Color-coded output (folders, files, sizes)
- Full Unicode support (works with Cyrillic, CJK, Arabic, etc.)
- File size formatting (B, KB, MB, GB)
- Summary statistics (total files, folders, size)
- Works from any directory once installed
- Compatible with Windows XP through Windows 11

## Installation

### Quick Install

1. Download or clone this repository
2. Run `build.bat` to compile
3. Run `setup.bat` as administrator to install to System32
4. Use `vls` command from anywhere

### Manual Installation

```batch
gcc vls.c -o vls.exe -O2 -s
copy vls.exe C:\Windows\System32\
```

## Usage

```batch
vls              # List current directory
vls C:\path      # List specific directory
vls ..           # List parent directory
```

## Requirements

- Windows XP or later
- GCC compiler (MinGW/MinGW-w64) for building

## Building

The project includes a simple build script:

```batch
build.bat
```

This compiles `vls.c` into an optimized executable. The resulting binary is around 20-30 KB.

## Compatibility

Tested and working on:
- Windows 11
- Windows 10
- Windows 7
- Windows XP

Works with any GCC-compatible compiler, including old MinGW versions (GCC 6.3+).

## License

MIT License - See LICENSE file for details.

## Contributing

Pull requests are welcome. For major changes, open an issue first to discuss what you'd like to change.
