#!/usr/bin/env sh

# Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
# Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

cd ../../

# Erase previous build output
rm -r bin
rm -r doc

# Build the whole project
mkdir bin
cd bin
cmake ../src
make

# Compile the documentation
cd ..
/opt/local/bin/doxygen
make --directory=doc/latex pdf
mv doc/latex/refman.pdf doc/
rm -r doc/latex/

# Launch the tests
cd bin
ctest
cd ..
