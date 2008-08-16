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
 * \file UMLDiagram.cpp
 *
 * Contains the implementation of the ui::UMLDiagram class.
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

#include "UMLDiagram.h"

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

#ifndef ARROWFIGURE_H_
#include "ArrowFigure.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;

namespace ui
{
    UMLDiagram::UMLDiagram()
    : Component()
    , _canvas(new ArrowCanvas())
    , _selection()
    , _toolbar(NULL)
    {
        _canvas->setSize(565, 800);
        _canvas->setSelectedItemSet(_selection, this);
        addAndMakeVisible(_canvas, 0);

        setSize(565, 800);
        
        // The NotificationCenter in the POCO libraries is inspired from Cocoa
        // http://developer.apple.com/documentation/Cocoa/Reference/Foundation/Classes/NSNotificationCenter_Class/Reference/Reference.html
        // However, this implementation uses template adaptors, in a true C++ style!
        NObserver<UMLDiagram, FigureSelected> figureObserver(*this, &UMLDiagram::handleFigureSelected);
        NotificationCenter::defaultCenter().addObserver(figureObserver);

        NObserver<UMLDiagram, ArrowCanvasClicked> arrowObserver(*this, &UMLDiagram::handleArrowCanvasClicked);
        NotificationCenter::defaultCenter().addObserver(arrowObserver);

        NObserver<UMLDiagram, FigureMoved> movementObserver(*this, &UMLDiagram::handleFigureMoved);
        NotificationCenter::defaultCenter().addObserver(movementObserver);
    }

    UMLDiagram::~UMLDiagram()
    {
        deleteAllChildren();
    }

    DiagramToolbar* UMLDiagram::getToolbar()
    {
        if (!_toolbar)
        {
            _toolbar = createToolbar();
        }
        return _toolbar;
    }
    
    void UMLDiagram::addArrowToCanvas(Figure* a, Figure* b)
    {
        ArrowFigure* arrowFigure = new ArrowFigure();
        addChildComponent(arrowFigure, -1);
        _canvas->addArrow(a, b, arrowFigure);
    }

    void UMLDiagram::paint (Graphics& g)
    {
        g.fillAll(Colours::white);
    }

    void UMLDiagram::handleFigureSelected(const AutoPtr<FigureSelected>& notification)
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
                _canvas->deselectAllArrows();
            }
            for (int j = 0; j < _selection.getNumSelected(); ++j)
            {
                Figure* item = _selection.getSelectedItem(j);
                item->setSelected(true);
                ArrowFigure* arrowFigure = dynamic_cast<ArrowFigure*>(item);
                if (arrowFigure)
                {
                    _canvas->showArrowSelected(arrowFigure);
                }
            }
        }
    }
    
    const int UMLDiagram::getSelectedItemsCount() const
    {
        return _selection.getNumSelected();
    }
    
    const Array<Figure*>& UMLDiagram::getSelectedItems()
    {
        return _selection.getItemArray();
    }

    void UMLDiagram::handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>& notification)
    {
        ArrowCanvas* canvas = notification->getClickedArrowCanvas();
        if (isParentOf(canvas))
        {
            _selection.deselectAll();
            _canvas->deselectAllArrows();
        }
    }
    
    void UMLDiagram::handleFigureMoved(const AutoPtr<FigureMoved>& notification)
    {
        Figure* figure = notification->getMovedFigure();
        if (isParentOf(figure))
        {
            _canvas->repaint();
        }
    }

    void UMLDiagram::toggleGrid()
    {
        _canvas->toggleGrid();
    }
}
