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

//! Contains the implementation of the notifications::ProjectTabbedComponentChangedTab class.
/*!
 * \file ProjectTabbedComponentChangedTab.cpp
 *
 * Contains the implementation of the notifications::ProjectTabbedComponentChangedTab class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#include "ProjectTabbedComponentChangedTab.h"

namespace notifications
{
    ProjectTabbedComponentChangedTab::ProjectTabbedComponentChangedTab(const int newCurrentTabIndex, const String& newCurrentTabName)
    : Notification()
    , _newCurrentTabIndex(newCurrentTabIndex)
    , _newCurrentTabName(newCurrentTabName)
    {
    }
    
    ProjectTabbedComponentChangedTab::~ProjectTabbedComponentChangedTab()
    {
    }
    
    const int ProjectTabbedComponentChangedTab::getNewCurrentTabIndex() const
    {
        return _newCurrentTabIndex;
    }

    const String ProjectTabbedComponentChangedTab::getNewCurrentTabName() const
    {
        return _newCurrentTabName;
    }
}
