@echo off

REM Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
REM Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
REM
REM This program is free software; you can redistribute it and/or modify
REM it under the terms of the GNU General Public License as published by
REM the Free Software Foundation; either version 2 of the License, or
REM (at your option) any later version.
REM 
REM This program is distributed in the hope that it will be useful,
REM but WITHOUT ANY WARRANTY; without even the implied warranty of
REM MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
REM GNU General Public License for more details.
REM 
REM You should have received a copy of the GNU General Public License along
REM with this program; if not, write to the Free Software Foundation, Inc.,
REM 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

REM Execute this file from the "Visual Studio 2008 Command Prompt" console,
REM so that the proper PATHs and variables are set properly.

REM Change the current dir to the project root
cd ..\..

REM Remove previous build
echo Y | rd bin /s

REM Bring the latest sources from the repository
svn update --ignore-externals

REM Create a temporary 'bin' directory to build the application
mkdir bin
cd bin

REM Generate the NMake makefiles from the CMake file
cmake -DCMAKE_BUILD_TYPE=Release -G "NMake Makefiles" ..\src

REM Build the application
nmake

REM Create a subdirectory with a ready-to-use distribution
mkdir Release
copy Rem.exe Release
copy ..\lib\sqlite\sqlite3.dll Release
copy ..\lib\poco\bin\PocoFoundation.dll Release

REM Generate the NSIS installer
cpack 
