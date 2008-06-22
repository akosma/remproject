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

/*!
 * \file ContentComponent.h
 *
 * Contains the interface of the ui::ContentComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include <Poco/AutoPtr.h>

#if defined(_WIN32)
#include <src/juce_WithoutMacros.h>
#else
#include <juce.h>
#endif

#ifndef CONTENTCOMPONENT_H_
#define CONTENTCOMPONENT_H_

#ifndef FIGURESELECTEDNOTIFICATION_H_
#include "FigureSelectedNotification.h"
#endif

#ifndef ARROWCANVASCLICKEDNOTIFICATION_H_
#include "ArrowCanvasClickedNotification.h"
#endif

#ifndef FIGUREMOVEDNOTIFICATION_H_
#include "FigureMovedNotification.h"
#endif

using Poco::AutoPtr;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class Figure;
    class ArrowCanvas;
    
    /*!
     * \class ContentComponent
     *
     *  
     */
    class ContentComponent : public Component, public DragAndDropTarget
    {
    public:
        ContentComponent();
        ~ContentComponent();

        void paint (Graphics&);

        bool isInterestedInDragSource (const String& sourceDescription);

        void itemDropped (const String& sourceDescription, Component* sourceComponent, int x, int y);

        void setCurrent(Figure*);
        
        void resize();
        
        ArrowCanvas& getArrowCanvas();

        void handleFigureSelectedNotification(const AutoPtr<FigureSelectedNotification>&);
        void handleArrowCanvasClickedNotification(const AutoPtr<ArrowCanvasClickedNotification>&);
        void handleFigureMovedNotification(const AutoPtr<FigureMovedNotification>&);

    private:
        ArrowCanvas* _canvas;
        Figure* _current;
    };
}

#endif /* CONTENTCOMPONENT_H_ */
