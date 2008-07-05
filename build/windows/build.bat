REM execute this file from the "Visual Studio 2008 Command Prompt" console,
REM so that the proper PATHs and variables are set properly.

@echo off

cd ..\..

REM remove previous build
echo Y | rd bin /s

REM bring the latest sources from the repository
svn update --ignore-externals

REM create a temporary 'bin' directory to build the application
mkdir bin
cd bin

REM generate the NMake makefiles from the CMake file
cmake -G "NMake Makefiles" ..\src

REM build the application
nmake

REM create a subdirectory with a ready-to-use distribution
mkdir Release
copy Rem.exe Release
copy ..\lib\sqlite\sqlite3.dll Release
copy ..\lib\poco\bin\PocoFoundation.dll Release

REM generate the NSIS installer
cpack 
