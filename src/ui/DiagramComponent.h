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

//! Contains the interface of the ui::DiagramComponent class.
/*!
 * \file DiagramComponent.cpp
 *
 * Contains the interface of the ui::DiagramComponent class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 3:27:04 pm
 */

#include <src/juce_WithoutMacros.h>

#ifndef DIAGRAMCOMPONENT_H_
#define DIAGRAMCOMPONENT_H_

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * \class DiagramComponent
     *
     * [Comments]
     * An auto-generated component, created by the Jucer.
     * Describe your class and how it works here!
     * [/Comments]
     *
     */
    class DiagramComponent  : public Component
    {
    public:
        DiagramComponent ();
        ~DiagramComponent();

        void paint (Graphics& g);
        void resized();


        juce_UseDebuggingNewOperator

    private:
        Viewport* viewport;

        // (prevent copy constructor and operator= from being generated..)
        DiagramComponent (const DiagramComponent&);
        const DiagramComponent& operator= (const DiagramComponent&);
    };
}

#endif   // DIAGRAMCOMPONENT_H_
