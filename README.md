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

1. Add `C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\Llvm\x64\bin` to `PATH`
2. Set `VCINSTALLDIR` to `C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC`

Download the Windows QT installer at [qt.io](https://www.qt.io/download)

1. Make a personal installation and install Qt6 MSVC version and CMAKE.
2. Add `C:\Qt\Tools\CMake_64\bin` and `C:\Qt\6.4.3\msvc2019_64\bin` to your `PATH`

You can now build the project with :

```ps
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
.\build\Release\SchottenTotten.exe
```

## Build requirements on MacOS

Note : CMakeLists.txt is currently configured for `arm64` only. You can change for `x86_64`.

Install cmake and qt with [brew](https://formulae.brew.sh/) :

```bash
brew install cmake
brew install qt
```

Add the following to ~/.zshrc (if using zsh) :

```bash
export PATH="/opt/homebrew/opt/cmake/bin:$PATH"
export PATH="/opt/homebrew/opt/qt6/bin:$PATH"
```

reload terminal to apply changes or run `source ~/.zshrc`

Build and run with :

```ps
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/SchottenTotten.app/Contents/MacOS/SchottenTotten
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

## Generate a release with binaries

```bash
git tag v1.0.0
git push origin --tags
git push origin v1.0.0
```
