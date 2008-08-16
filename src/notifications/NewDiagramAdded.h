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

//! Contains the interface of the notifications::NewDiagramAdded class.
/*!
 * \file NewDiagramAdded.h
 *
 * Contains the interface of the notifications::NewDiagramAdded class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef NEWDIAGRAMADDED_H_
#define NEWDIAGRAMADDED_H_

#include <Poco/Notification.h>

using Poco::Notification;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Triggers the adding of a new diagram to the project.
    /*!
     * \class NewDiagramAdded
     *
     * Raised by the ui::CommandDelegate class when the user selects
     * to add a new diagram to the project.
     */
    class NewDiagramAdded : public Notification
    {
    public:

        //! Enumerates the type of diagrams announced by this notification.
        /*!
         * Enumerates the type of diagrams announced by this notification.
         */
        enum DiagramType
        {
            //! Use Case diagrams
            UseCase,
            
            //! Class diagrams
            Class,
            
            //! Sequence diagrams
            Sequence
        };

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param type The type of diagram to be added.
         */
        NewDiagramAdded(const DiagramType);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~NewDiagramAdded();
        
        //! Returns the type of diagram announced by the notification.
        /*!
         * Returns the type of diagram announced by the notification.
         * 
         * \return The type of diagram announced by the notification.
         */
        const DiagramType getDiagramType() const;
        
    private:
        //! Type of diagram being announced by the notification
        const DiagramType _type;
    };
}

#endif /* NEWDIAGRAMADDED_H_ */
