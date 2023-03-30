# SchottenTotten

[![Build result](https://github.com/Dashstrom/SchottenTotten/actions/workflows/build.yml/badge.svg)](https://github.com/Dashstrom/SchottenTotten/actions/workflows/build.yml)
[![Linting result](https://github.com/Dashstrom/SchottenTotten/actions/workflows/lint.yml/badge.svg)](https://github.com/Dashstrom/SchottenTotten/actions/workflows/lint.yml)
[![Repo size](https://img.shields.io/github/repo-size/Dashstrom/SchottenTotten)](https://github.com/Dashstrom/SchottenTotten)

[![Linux](https://svgshare.com/i/Zhy.svg)](https://svgshare.com/i/Zhy.svg)
[![macOS](https://svgshare.com/i/ZjP.svg)](https://svgshare.com/i/ZjP.svg)
[![Windows](https://svgshare.com/i/ZhY.svg)](https://svgshare.com/i/ZhY.svg)

Gameplay in Schotten Totten resembles simultaneous play of nine separate hands of poker, but where each hand has only three cards in it. There are nine "boundary" stones between players at the start of the game. Players vie to win five of the stones, or three adjacent ones, to win the game.

## Build requirements on Windows

Install Visual Studio Build Tools 2019 from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/fr/downloads/) Dont forget to add the "C++ Clang tools for Windows".

Add `C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\Llvm\x64\bin` to `PATH`

Download the Windows QT installer at [qt.io](https://www.qt.io/download)

1. Make a personal installation and install Qt6 MSVC version and CMAKE.
2. Add `C:\Qt\Tools\CMake_64\bin` and `C:\Qt\6.4.3\msvc2019_64\bin` to your `PATH`

You can now build the project with :

```ps
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
.\build\Release\SchottenTotten.exe
```

## Completion requirements

Just add `C:\Qt\6.4.3\msvc2019_64\include`, `C:\Qt\6.4.3\msvc2019_64\include\QtCore` and `C:\Qt\6.4.3\msvc2019_64\include\QtWidgets` to your include path in your favorite IDE.

## Commit requirements

For setup commits

```bash
git clone https://github.com/Dashstrom/SchottenTotten
pip install pre-commit
pre-commit install
```

For each commit

```bash
git add .
pre-commit run -a
git commit -m "Hello !"
```
