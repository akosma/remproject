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

//! Contains the implementation of the notifications::NewLineAdded class.
/*!
 * \file NewLineAdded.cpp
 *
 * Contains the implementation of the notifications::NewLineAdded class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      8/23/08
 */

#include "NewLineAdded.h"

#ifndef LINEFIGURE_H_
#include "../ui/LineFigure.h"
#endif

namespace notifications
{
    NewLineAdded::NewLineAdded(NewFigureAdded::FigureType type, LineFigure* line)
    : NewObjectAdded()
    , _line(line)
    , _type(type)
    , _uniqueId(line->getUniqueId())
    {
    }
    
    NewLineAdded::~NewLineAdded()
    {
    }
    
    LineFigure* NewLineAdded::getLineFigure() const
    {
        return _line;
    }
    
    const NewFigureAdded::FigureType NewLineAdded::getLineType() const
    {
        return _type;
    }

    const string& NewLineAdded::getUniqueId() const
    {
        return _uniqueId;
    }
}
