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
 * \file ContentComponent.cpp
 *
 * Contains the implementation of the ui::ContentComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

#include "ContentComponent.h"

#ifndef ACTORFIGURE_H_
#include "ActorFigure.h"
#endif

#ifndef USECASEFIGURE_H_
#include "UseCaseFigure.h"
#endif

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;

namespace ui
{
    ContentComponent::ContentComponent()
    : Component()
    , DragAndDropTarget()
    , _canvas(new ArrowCanvas())
    , _selection()
    {
        _canvas->setSize(565, 800);
        addAndMakeVisible(_canvas, 0);
        
        ActorFigure* a = new ActorFigure();
        a->setTopLeftPosition(100, 300);
        addAndMakeVisible(a, -1);

        ActorFigure* b = new ActorFigure();
        b->setTopLeftPosition(100, 10);
        addAndMakeVisible(b, -1);
        
        UseCaseFigure* c = new UseCaseFigure();
        c->setTopLeftPosition(300, 300);
        addAndMakeVisible(c, -1);
        
        _canvas->addArrow(a, c);
        _canvas->addArrow(a, b);

        setSize(565, 800);
        
        // The NotificationCenter in the POCO libraries is inspired from Cocoa
        // http://developer.apple.com/documentation/Cocoa/Reference/Foundation/Classes/NSNotificationCenter_Class/Reference/Reference.html
        // However, this implementation uses template adaptors, in a true C++ style!
        NObserver<ContentComponent, FigureSelected> figureObserver(*this, &ContentComponent::handleFigureSelected);
        NotificationCenter::defaultCenter().addObserver(figureObserver);

        NObserver<ContentComponent, ArrowCanvasClicked> arrowObserver(*this, &ContentComponent::handleArrowCanvasClicked);
        NotificationCenter::defaultCenter().addObserver(arrowObserver);

        NObserver<ContentComponent, FigureMoved> movementObserver(*this, &ContentComponent::handleFigureMoved);
        NotificationCenter::defaultCenter().addObserver(movementObserver);

        NObserver<ContentComponent, DiagramToggleGrid> gridObserver(*this, &ContentComponent::handleDiagramToggleGrid);
        NotificationCenter::defaultCenter().addObserver(gridObserver);
    }

    ContentComponent::~ContentComponent()
    {
        deleteAllChildren();
    }

    void ContentComponent::paint (Graphics& g)
    {
        g.fillAll(Colours::white);
    }
    
    bool ContentComponent::isInterestedInDragSource (const String& sourceDescription)
    {
        // normally you'd check the sourceDescription value to see if it's the
        // sort of object that you're interested in before returning true, but for
        // the demo, we'll say yes to anything..
        return true;
    }

    void ContentComponent::itemDropped (const String& sourceDescription, Component* sourceComponent, int x, int y)
    {
        repaint();
    }

    void ContentComponent::handleFigureSelected(const AutoPtr<FigureSelected>& notification)
    {
        Figure* figure = notification->getSelectedFigure();
        if (isParentOf(figure))
        {
            ModifierKeys keys = notification->getModifierKeys();
            if (keys.isShiftDown() && figure->isSelected())
            {
                _selection.deselect(figure);
            }
            else if (figure->isSelected())
            {
                _selection.selectOnly(figure);
            }
            else
            {
                _selection.addToSelectionOnMouseDown(figure, notification->getModifierKeys());
            }
            for (int i = 0; i < getNumChildComponents(); ++i)
            {
                Component* child = getChildComponent(i);
                Figure* castChild = dynamic_cast<Figure*>(child);
                if (castChild)
                {
                    castChild->setSelected(false);
                }
            }
            for (int j = 0; j < _selection.getNumSelected(); ++j)
            {
                Figure* item = _selection.getSelectedItem(j);
                item->setSelected(true);
            }
        }
    }

    void ContentComponent::handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>& notification)
    {
        ArrowCanvas* canvas = notification->getClickedArrowCanvas();
        if (isParentOf(canvas))
        {
            _selection.deselectAll();
        }
    }
    
    void ContentComponent::handleFigureMoved(const AutoPtr<FigureMoved>& notification)
    {
        Figure* figure = notification->getMovedFigure();
        if (isParentOf(figure))
        {
            _canvas->repaint();
        }
    }
    
    void ContentComponent::handleDiagramToggleGrid(const AutoPtr<DiagramToggleGrid>&)
    {
        _canvas->toggleGrid();
    }
}
