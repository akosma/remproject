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

//! Contains the interface of the notifications::NewObjectAdded class.
/*!
 * \file NewObjectAdded.h
 *
 * Contains the interface of the notifications::NewObjectAdded class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      8/17/08
 */

#ifndef NEWOBJECTADDED_H_
#define NEWOBJECTADDED_H_

#include <string>

#include <Poco/Notification.h>

using Poco::Notification;
using std::string;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Triggers the adding of a new object to a project.
    /*!
     * \class NewObjectAdded
     *
     * Raised by the ui::CommandDelegate class when the user selects
     * to add a new object to a diagram. The main raison-d'etre of this
     * class is to generate a unique ID (ideally a UUID) to be used
     * by both the GUI component and its SQLite representation, so that
     * the controller can keep both in sync.
     */
    class NewObjectAdded : public Notification
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         */
        NewObjectAdded();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~NewObjectAdded();
        
        //! Returns the unique ID assigned to the newly created instance.
        /*!
         * Returns the unique ID assigned to the newly created instance.
         *
         * \return A string.
         */
        const string& getUniqueId() const;
        
    private:
        //! Unique ID for the new object being added
        string _id;
    };
}

#endif /* NEWOBJECTADDED_H_ */
