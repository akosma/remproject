/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains platform-specific symbols used throughout the Rem application.
/*!
 * \file PlatformDefinitions.h
 *
 * Contains platform-specific symbols used throughout the Rem application.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

// When using POCO and JUCE together, Windows requires to use
// a different set of header files for JUCE than in Unixes:
#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif

// Somehow in Mac OS X, using the native UI controls 
// in "Debug" mode hangs the application... This does not
// happen in "Release", so here we make the compiler 
// choose the right setting for each environment.
// When calling JUCE dialog boxes, use the NATIVE_DIALOG macro
// to specify the type of control to use.
#if defined(__APPLE__) && defined(__MACH__) && defined(USE_JUCE_DIALOGS)
#define NATIVE_DIALOG false
#else
#define NATIVE_DIALOG true
#endif
