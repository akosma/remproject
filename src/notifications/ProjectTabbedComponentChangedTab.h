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

/*!
 * \file ProjectTabbedComponentChangedTab.h
 *
 * Contains the interface of the notifications::ProjectTabbedComponentChangedTab class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTAB_H_
#define PROJECTTABBEDCOMPONENTCHANGEDTAB_H_

#include <Poco/Notification.h>

#include "../ui/PlatformDefinitions.h"

using Poco::Notification;

/*!
 * \namespace notifications
 * Insert a description for the namespace here
 */
namespace notifications
{
    /*!
     * \class ProjectTabbedComponentChangedTab
     *
     *  
     */
    class ProjectTabbedComponentChangedTab : public Notification
    {
    public:

        /*!
         *  ProjectTabbedComponentChangedTab constructor.
         */
        ProjectTabbedComponentChangedTab(const int, const String&);

        /*!
         *  ProjectTabbedComponentChangedTab virtual destructor.
         */
        virtual ~ProjectTabbedComponentChangedTab();

        const int getNewCurrentTabIndex() const;
        const String getNewCurrentTabName() const;
        
    private:
        
        const int _newCurrentTabIndex;
        const String _newCurrentTabName;

    };
}

#endif /* PROJECTTABBEDCOMPONENTCHANGEDTAB_H_ */
