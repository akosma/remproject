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

//! Contains the interface of the notifications::ArrowCanvasClicked class.
/*!
 * \file ArrowCanvasClicked.h
 *
 * Contains the interface of the notifications::ArrowCanvasClicked class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#ifndef ARROWCANVASCLICKED_H_
#define ARROWCANVASCLICKED_H_

#include <Poco/Notification.h>

using Poco::Notification;

// Forward declaration to avoid includes.
namespace ui
{
    class ArrowCanvas;
}
using ui::ArrowCanvas;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Indicates that the user clicked on an empty region of the ArrowCanvas.
    /*!
     * \class ArrowCanvasClicked
     *
     * Raised by ArrowCanvas instances when the user clicks on them 
     * without intercepting an arrow. This causes all selected items
     * in the canvas to be deselected.
     */
    class ArrowCanvasClicked : public Notification
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param canvas The ArrowCanvas instance posting this notification.
         */
        ArrowCanvasClicked(ArrowCanvas*);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ArrowCanvasClicked();

        //! Returns a pointer to the ArrowCanvas that posted this notification.
        /*!
         * Returns a pointer to the ArrowCanvas that posted this notification.
         * 
         * \return A pointer to an ArrowCanvas instance.
         */
        ArrowCanvas* getClickedArrowCanvas() const;
    
    private:
        //! Stores a pointer to the ArrowCanvas instance posting this notification.
        ArrowCanvas* _arrowCanvas;
    };
}

#endif /* ARROWCANVASCLICKED_H_ */
