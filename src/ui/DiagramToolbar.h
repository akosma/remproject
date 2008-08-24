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
 * \file DiagramToolbar.h
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
    // Forward declaration to avoid includes.
    class DiagramComponent;
    
    //! Base class for toolbars.
    /*!
     * \class DiagramToolbar
     *
     * Base class for toolbars.
     */
    class DiagramToolbar  : public Component
    {
    public:
        //! Constructor
        /*!
         * Constructor.
         */
        DiagramToolbar();

        //! Virtual destructor
        /*!
         * Virtual destructor.
         */
        virtual ~DiagramToolbar();

        //! Called when the user clicks on the toolbar.
        /*!
         * Called when the user clicks on the toolbar.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseDown(const MouseEvent&);

        //! Called when the user drags the toolbar.
        /*!
         * Called when the user drags the toolbar.
         *
         * \param e The MouseEvent object passed by the runtime.
         */
        void mouseDrag(const MouseEvent&);

        //! Called when the component is asked to redraw itself on screen.
        /*!
         * Called when the component is asked to redraw itself on screen.
         * 
         * \param g The Graphics component where the redrawing takes place.
         */
        void paint (Graphics&);
        
        //! Sets the parent component of the toolbar.
        /*!
         * Sets the parent component of the toolbar.
         * 
         * \param parent The parent component of the current toolbar.
         */
        void setParent(DiagramComponent*);

    private:
        //! Allows the toolbar to be dragged on the screen.
        ComponentDragger _dragger;
        
        //! Stores a pointer to the parent component of the toolbar.
        DiagramComponent* _parent;
    };
}

#endif   /* DIAGRAMTOOLBAR_H_ */
