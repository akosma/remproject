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

//! Contains the interface of the notifications::ProjectTabbedComponentChangedTab class.
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

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Raised to notify that a new diagram has been chosen in the project.
    /*!
     * \class ProjectTabbedComponentChangedTab
     *
     * Raised by the ui::ProjectTabbedComponent class and caught
     * by the ui::DiagramComponent class, to inform that the user has
     * selected another diagram in the project, and that the corresponding
     * toolbar should be shown.
     */
    class ProjectTabbedComponentChangedTab : public Notification
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param newCurrentTabIndex The index of the newly selected tab.
         * \param newCurrentTabName The name of the newly selected tab.
         */
        ProjectTabbedComponentChangedTab(const int, const String&);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ProjectTabbedComponentChangedTab();

        //! Returns the index of the newly selected tab.
        /*!
         * Returns the index of the newly selected tab.
         * 
         * \return An integer.
         */
        const int getNewCurrentTabIndex() const;
        
        //! Returns the name of the newly selected tab.
        /*!
         * Returns the name of the newly selected tab.
         * 
         * \return A string.
         */
        const String getNewCurrentTabName() const;
        
    private:
        //! Stores the index of the newly selected tab index.
        const int _newCurrentTabIndex;
        
        //! Stores the name of the newly selected tab name.
        const String _newCurrentTabName;

    };
}

#endif /* PROJECTTABBEDCOMPONENTCHANGEDTAB_H_ */
