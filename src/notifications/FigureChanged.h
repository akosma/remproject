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

//! Contains the interface of the notifications::FigureChanged class.
/*!
 * \file FigureChanged.h
 *
 * Contains the interface of the notifications::FigureChanged class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#ifndef FIGURECHANGED_H_
#define FIGURECHANGED_H_

#include <Poco/Notification.h>

using Poco::Notification;

// Forward declaration to avoid includes.
namespace ui
{
    class Figure;
}
using ui::Figure;

//! Notifications passed between application layers to signal events.
/*!
 * \namespace notifications
 * Contains notifications passed between application layers to signal events.
 */
namespace notifications
{
    //! Raised whenever a ui::Figure instance is changed on the canvas.
    /*!
     * \class FigureChanged
     *
     * Posted by the ui::Figure class and intercepted by the ui::UMLDiagram 
     * and the controllers::FileController classes whenever a 
     * Figure instance is changed on the canvas.
     */
    class FigureChanged : public Notification
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param figure The figure being changed.
         */
        FigureChanged(Figure*);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~FigureChanged();

        //! Returns a pointer to the changed figure.
        /*!
         * Returns a pointer to the changed figure.
         * 
         * \return A pointer to a ui::Figure instance.
         */
        Figure* getChangedFigure() const;

    private:
        //! Stores a pointer to the changed figure.
        Figure* _figure;
    };
}

#endif /* FIGURECHANGED_H_ */
