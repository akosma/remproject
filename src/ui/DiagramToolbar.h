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

//! Contains the interface of the ui::DiagramToolbar class.
/*!
 * \file Toolbar.cpp
 *
 * Contains the interface of the ui::DiagramToolbar class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 4:48:24 pm
 */

#ifndef DIAGRAMTOOLBAR_H_
#define DIAGRAMTOOLBAR_H_

#include "PlatformDefinitions.h"

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    /*!
     * \class Toolbar
     *
     *
     */
    class DiagramToolbar  : public Component
    {
    public:
        DiagramToolbar();
        ~DiagramToolbar();

        void mouseDown(const MouseEvent& e);
        void mouseDrag(const MouseEvent& e);

        void paint (Graphics& g);
        void resized();

        void setParent(Component*);

        juce_UseDebuggingNewOperator

    private:
        ComponentDragger _dragger;
        Component* _parent;

    private:
        DiagramToolbar (const DiagramToolbar&);
        const DiagramToolbar& operator= (const DiagramToolbar&);
    };
}

#endif   // DIAGRAMTOOLBAR_H_
