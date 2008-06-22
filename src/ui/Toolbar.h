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

//! Contains the interface of the ui::Toolbar class.
/*!
 * \file Toolbar.cpp
 *
 * Contains the interface of the ui::Toolbar class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 4:48:24 pm
 */

#ifndef __JUCER_HEADER_TOOLBAR_TOOLBAR_393F2C9B__
#define __JUCER_HEADER_TOOLBAR_TOOLBAR_393F2C9B__

//[Headers]     -- You can add your own extra header files here --
#include <src/juce_WithoutMacros.h>
//[/Headers]



/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class Toolbar
     *
     * [Comments]
     * An auto-generated component, created by the Jucer.
     * Describe your class and how it works here!
     * [/Comments]
     *
     */
    class Toolbar  : public Component
    {
    public:
        Toolbar ();
        ~Toolbar();

        //[UserMethods]     -- You can add your own custom methods in this section.
        //[/UserMethods]

        void paint (Graphics& g);
        void resized();


        juce_UseDebuggingNewOperator

    private:
        //[UserVariables]   -- You can add your own custom variables in this section.
        //[/UserVariables]



        // (prevent copy constructor and operator= from being generated..)
        Toolbar (const Toolbar&);
        const Toolbar& operator= (const Toolbar&);
    };
}

#endif   // __JUCER_HEADER_TOOLBAR_TOOLBAR_393F2C9B__
