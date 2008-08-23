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

//! Contains the implementation of the ui::UMLDiagram class.
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

#ifndef LINEFIGURE_H_
#include "LineFigure.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;

namespace ui
{
    UMLDiagram::UMLDiagram(const string& uniqueId)
    : Component()
    , _id(uniqueId)
    , _canvas(new ArrowCanvas())
    , _selection()
    , _figureObserver(new NObserver<UMLDiagram, FigureSelected>(*this, &UMLDiagram::handleFigureSelected))
    , _arrowObserver(new NObserver<UMLDiagram, ArrowCanvasClicked>(*this, &UMLDiagram::handleArrowCanvasClicked))
    , _movementObserver(new NObserver<UMLDiagram, FigureMoved>(*this, &UMLDiagram::handleFigureMoved))
    {
        _canvas->setSize(565, 800);
        _canvas->setSelectedItemSet(_selection, this);
        addAndMakeVisible(_canvas, 0);

        setSize(565, 800);
        
        // The NotificationCenter in the POCO libraries is inspired from Cocoa
        // http://developer.apple.com/documentation/Cocoa/Reference/Foundation/Classes/NSNotificationCenter_Class/Reference/Reference.html
        // However, this implementation uses template adaptors, in a true C++ style!
        NotificationCenter::defaultCenter().addObserver(*_figureObserver);
        NotificationCenter::defaultCenter().addObserver(*_arrowObserver);
        NotificationCenter::defaultCenter().addObserver(*_movementObserver);
    }

    UMLDiagram::~UMLDiagram()
    {
        NotificationCenter::defaultCenter().removeObserver(*_figureObserver);
        NotificationCenter::defaultCenter().removeObserver(*_arrowObserver);
        NotificationCenter::defaultCenter().removeObserver(*_movementObserver);
        deleteAndZero(_figureObserver);
        deleteAndZero(_arrowObserver);
        deleteAndZero(_movementObserver);
        deleteAllChildren();
    }

    void UMLDiagram::addArrowToCanvas(ArrowFigure* arrowFigure)
    {
        addChildComponent(arrowFigure, -1);
        _canvas->addArrow(arrowFigure);
    }

    void UMLDiagram::addLineToCanvas(LineFigure* lineFigure)
    {
        addChildComponent(lineFigure, -1);
        _canvas->addLine(lineFigure);
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
                LineFigure* lineFigure = dynamic_cast<LineFigure*>(item);
                if (lineFigure)
                {
                    _canvas->showLineSelected(lineFigure);
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
    
    const string& UMLDiagram::getUniqueId() const
    {
        return _id;
    }
    
    Figure* UMLDiagram::getFigureByUniqueId(const string& uniqueId)
    {
        Figure* figure = NULL;
        for (int i = 0; i < getNumChildComponents(); ++i)
        {
            Component* child = getChildComponent(i);
            Figure* castChild = dynamic_cast<Figure*>(child);
            if (castChild)
            {
                const string& childId = castChild->getUniqueId();
                if (childId == uniqueId)
                {
                    figure = castChild;
                    break;
                }
            }
        }
        return figure;
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
