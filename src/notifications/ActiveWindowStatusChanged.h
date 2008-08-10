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

//! Contains the implementation of the notifications::ActiveWindowStatusChanged class.
/*!
 * \file ActiveWindowStatusChanged.h
 *
 * Contains the interface of the notifications::ActiveWindowStatusChanged class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef ACTIVEWINDOWSTATUSCHANGED_H_
#define ACTIVEWINDOWSTATUSCHANGED_H_

#include <Poco/Notification.h>

using Poco::Notification;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Posted when the Window instance becomes active or inactive.
    /*!
     * \class ActiveWindowStatusChanged
     * 
     * This notification is raised by the Window class, whenever the main
     * application window becomes active or not. It is used to hide or show 
     * the diagram toolbar, in case that this is an independent window on the desktop.
     */
    class ActiveWindowStatusChanged : public Notification
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param status A boolean with the status of the Window
         * posting this notification.
         */
        ActiveWindowStatusChanged(const bool);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ActiveWindowStatusChanged();
        
        //! Returns the status of the window that posted this notification.
        /*!
         * Returns the status of the window that posted this notification;
         * "true" if the Window is active, "false" otherwise.
         * 
         * \return A boolean
         */
        const bool getStatus() const;
        
    private:
        //! Stores the status of the window that posted this notification.
        bool _status;
    };
}

#endif /* ACTIVEWINDOWSTATUSCHANGED_H_ */
