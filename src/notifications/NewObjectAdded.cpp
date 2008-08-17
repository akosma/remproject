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

//! Contains the implementation of the notifications::NewObjectAdded class.
/*!
 * \file NewObjectAdded.cpp
 *
 * Contains the implementation of the notifications::NewObjectAdded class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      8/17/08
 */

#include "NewObjectAdded.h"

#if defined(__APPLE__) && defined(__MACH__)
// The Mac OS X compiler requires this line, because "nil" is a reserved
// word in the Objective-C language, and without it this file won't compile.
// (The Poco/UUID.h file has definitions of a "nil()" method!)
#undef nil
#endif

#if defined(_WIN32)
#include <cstdio>
#else
#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>
using Poco::UUIDGenerator;
using Poco::UUID;
#endif

namespace notifications
{
    NewObjectAdded::NewObjectAdded()
    : Notification()
    {
#if defined(_WIN32)
        _id = tmpnam(NULL);
#else
        UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
        UUID uuid = generator.createRandom();
        _id = uuid.toString();
#endif
    }
    
    NewObjectAdded::~NewObjectAdded()
    {
    }
    
    const string& NewObjectAdded::getUniqueId() const
    {
        return _id;
    }
}
