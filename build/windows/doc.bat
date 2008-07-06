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

REM Remove previous Doxygen output
echo Y | rd doc /s

REM Bring the latest sources from the repository
svn update --ignore-externals

REM Create a temporary 'doc' directory to build the application
mkdir doc

REM Launch the creation of documentation
doxygen