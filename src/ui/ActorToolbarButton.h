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

//! Contains the interface of the ui::ActorToolbarButton class.
/*!
 * \file ActorToolbarButton.cpp
 *
 * Contains the interface of the ui::ActorToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      16 Aug 2008 3:51:59 pm
 */

#ifndef ACTORTOOLBARBUTTON_H_
#define ACTORTOOLBARBUTTON_H_

#include "PlatformDefinitions.h"

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    //! Represents the button used to add Actors to use case diagrams.
    /*!
     * \class ActorToolbarButton
     *
     * Represents the button used to add Actors to use case diagrams.
     */
    class ActorToolbarButton  : public Button
    {
    public:
        //! Constructor
        /*!
         * Constructor.
         */
        ActorToolbarButton ();

        //! Virtual destructor
        /*!
         * Virtual destructor.
         */
        virtual ~ActorToolbarButton();

        //! Paints the button on screen.
        /*!
         * Paints the button on screen.
         * 
         * \param g The Graphics context where the button is drawn.
         * \param isMouseOverButton A flag stating if the mouse hovers the button.
         * \param isButtonDown A flag stating if the mouse button is pressed.
         */
        void paintButton (Graphics&, bool, bool);

        //! Called when the user clicks on the button.
        /*!
         * Called when the user clicks on the button.
         */
        void clicked();

        //! Returns a string to be shown as tooltip.
        /*!
         * Returns a string to be shown as tooltip when the 
         * user hovers over the figure.
         * 
         * \return A String value.
         */
        virtual const String getTooltip();
    };
}

#endif   /* ACTORTOOLBARBUTTON_H_ */
