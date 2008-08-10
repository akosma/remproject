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

//! Contains the interface of the notifications::FigureSelected class.
/*!
 * \file FigureSelected.h
 *
 * Contains the interface of the notifications::FigureSelected class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/22/08
 */

#ifndef FIGURESELECTED_H_
#define FIGURESELECTED_H_

#include <Poco/Notification.h>

#include "../ui/PlatformDefinitions.h"

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
    //! Raised whenever a ui::Figure instance is selected on the canvas.
    /*!
     * \class FigureSelected
     *
     * Posted by the ui::Figure and ui::ArrowCanvas classes 
     * and intercepted by the ui::UMLDiagram class
     * whenever a Figure instance is selected on the canvas.
     * It stores the key combination held by the user (SHIFT, CTRL, etc)
     * while performing the selection.
     */
    class FigureSelected : public Notification
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param figure The figure being selected.
         * \param modifierKeys The key combination held by the user
         * while selecting the figure.
         */
        FigureSelected(Figure*, ModifierKeys);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~FigureSelected();
        
        //! Returns a pointer to the selected figure.
        /*!
         * Returns a pointer to the selected figure.
         * 
         * \return A pointer to a ui::Figure instance.
         */
        Figure* getSelectedFigure() const;

        //! Returns the key combination held while selecting the figure.
        /*!
         * Returns the key combination held (SHIFT, CTRL) 
         * while selecting the figure.
         * 
         * \return A ModifierKeys value.
         */
        const ModifierKeys getModifierKeys() const;
        
    private:
        //! Stores a pointer to the Figure that was selected.
        Figure* _figure;
        
        //! Stores the key combination held by the user while selecting the Figure.
        ModifierKeys _modifierKeys;
    };
}

#endif /* FIGURESELECTED_H_ */
