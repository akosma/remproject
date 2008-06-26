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
 * \file ProjectTabbedComponentChangedTabNotification.h
 *
 * Contains the interface of the ui::ProjectTabbedComponentChangedTabNotification class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_
#define PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_

#include <Poco/Notification.h>

#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif

using Poco::Notification;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class ProjectTabbedComponentChangedTabNotification
     *
     *  
     */
    class ProjectTabbedComponentChangedTabNotification : public Notification
    {
    public:

        /*!
         *  ProjectTabbedComponentChangedTabNotification constructor.
         */
        ProjectTabbedComponentChangedTabNotification(const int, const String&);

        /*!
         *  ProjectTabbedComponentChangedTabNotification virtual destructor.
         */
        virtual ~ProjectTabbedComponentChangedTabNotification();

        const int getNewCurrentTabIndex() const;
        const String getNewCurrentTabName() const;
        
    private:
        
        const int _newCurrentTabIndex;
        const String _newCurrentTabName;

    };
}

#endif /* PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_ */
