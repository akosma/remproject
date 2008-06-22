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

//! Contains the interface of the ui::UseCaseToolbarButton class.
/*!
 * \file UseCaseToolbarButton.cpp
 *
 * Contains the interface of the ui::UseCaseToolbarButton class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 4:46:22 pm
 */

#ifndef __JUCER_HEADER_USECASETOOLBARBUTTON_USECASETOOLBARBUTTON_623E35BD__
#define __JUCER_HEADER_USECASETOOLBARBUTTON_USECASETOOLBARBUTTON_623E35BD__

//[Headers]     -- You can add your own extra header files here --
#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif
//[/Headers]



/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class UseCaseToolbarButton
     *
     * [Comments]
     * An auto-generated component, created by the Jucer.
     * Describe your class and how it works here!
     * [/Comments]
     *
     */
    class UseCaseToolbarButton  : public Button
    {
    public:
        UseCaseToolbarButton ();
        ~UseCaseToolbarButton();

        //[UserMethods]     -- You can add your own custom methods in this section.
        //[/UserMethods]

        void resized();
        void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);


        juce_UseDebuggingNewOperator

    private:
        //[UserVariables]   -- You can add your own custom variables in this section.
        //[/UserVariables]



        // (prevent copy constructor and operator= from being generated..)
        UseCaseToolbarButton (const UseCaseToolbarButton&);
        const UseCaseToolbarButton& operator= (const UseCaseToolbarButton&);
    };
}

#endif   // __JUCER_HEADER_USECASETOOLBARBUTTON_USECASETOOLBARBUTTON_623E35BD__
