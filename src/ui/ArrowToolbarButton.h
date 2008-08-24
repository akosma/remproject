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

//! Contains the interface of the ui::ArrowToolbarButton class.
/*!
 * \file ArrowToolbarButton.cpp
 *
 * Contains the interface of the ui::ArrowToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      16 Aug 2008 5:12:18 pm
 */

#ifndef __JUCER_HEADER_ARROWFIGUREBUTTON_ARROWFIGUREBUTTON_A444D0E1__
#define __JUCER_HEADER_ARROWFIGUREBUTTON_ARROWFIGUREBUTTON_A444D0E1__

//[Headers]     -- You can add your own extra header files here --
#include "PlatformDefinitions.h"
//[/Headers]



//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    /*!
     * \class ArrowToolbarButton
     *
     * [Comments]
     * An auto-generated component, created by the Jucer.
     * Describe your class and how it works here!
     * [/Comments]
     *
     */
    class ArrowToolbarButton  : public Button
    {
    public:
        ArrowToolbarButton ();
        ~ArrowToolbarButton();

        //[UserMethods]     -- You can add your own custom methods in this section.
        //[/UserMethods]

        void resized();
        void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);
        void clicked();
        virtual const String getTooltip();

        juce_UseDebuggingNewOperator

    private:
        //[UserVariables]   -- You can add your own custom variables in this section.
        //[/UserVariables]

        Path internalPath2;
        Path internalPath3;
        Path internalPath5;
        Path internalPath6;

        // (prevent copy constructor and operator= from being generated..)
        ArrowToolbarButton (const ArrowToolbarButton&);
        const ArrowToolbarButton& operator= (const ArrowToolbarButton&);
    };
}

#endif   // __JUCER_HEADER_ARROWFIGUREBUTTON_ARROWFIGUREBUTTON_A444D0E1__
