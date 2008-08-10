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

//! Contains the interface of the notifications::DiagramToggleGrid class.
/*!
 * \file DiagramToggleGrid.h
 *
 * Contains the interface of the notifications::DiagramToggleGrid class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/6/08
 */

#ifndef DIAGRAMTOGGLEGRID_H_
#define DIAGRAMTOGGLEGRID_H_

#include <Poco/Notification.h>

using Poco::Notification;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Notifies the current diagram to toggle the grid on or off.
    /*!
     * \class DiagramToggleGrid
     *
     * Raised by the ui::CommandDelegate class when the user chooses
     * to show or hide the grid of the diagram currently visible.
     */
    class DiagramToggleGrid : public Notification
    {
    public:

        //! Constructor
        /*!
         * Constructor.
         */
        DiagramToggleGrid();

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~DiagramToggleGrid();
    };
}

#endif /* DIAGRAMTOGGLEGRID_H_ */
