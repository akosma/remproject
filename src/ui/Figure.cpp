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

//! Contains the implementation of the ui::Figure class.
/*!
 * \file Figure.cpp
 *
 * Contains the implementation of the ui::Figure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/19/08
 */

#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

#include "Figure.h"

#ifndef DIAGRAMCOMPONENT_H_
#include "DiagramComponent.h"
#endif

#ifndef ARROWCANVAS_H_
#include "ArrowCanvas.h"
#endif

#ifndef FIGURESELECTED_H_
#include "../notifications/FigureSelected.h"
#endif

#ifndef FIGUREMOVED_H_
#include "../notifications/FigureMoved.h"
#endif

#ifndef ARROWCANVASCLICKED_H_
#include "../notifications/ArrowCanvasClicked.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using notifications::FigureSelected;
using notifications::FigureMoved;
using notifications::ArrowCanvasClicked;

namespace ui
{
    Figure::Figure(const int initWidth, const int initHeight)
    : _selected(false)
    , _hover(false)
    , _dragger()
    , _resizer(0)
    , _initWidth(initWidth)
    , _initHeight(initHeight)
    , _initMargin(10.0f)
    , _strokeWidth(1.0f)
    {
        setSize(_initWidth, _initHeight);
        setBounds(0, 0, _initWidth, _initHeight);
        setRepaintsOnMouseActivity(true);
        setBroughtToFrontOnMouseClick(true);
        setBufferedToImage(true);

        _resizer = new ResizableBorderComponent(this, 0);
        addChildComponent(_resizer, -1);
        _resizer->setSize(getWidth(),getHeight());
        _resizer->setBounds(0, 0, getWidth(), getHeight());
        
        NObserver<Figure, ArrowCanvasClicked> arrowCanvasObserver(*this, &Figure::handleArrowCanvasClicked);
        NotificationCenter::defaultCenter().addObserver(arrowCanvasObserver);
    }

    Figure::~Figure()
    {
        deleteAllChildren();
    }
    
    void Figure::mouseDown(const MouseEvent& e)
    {
        toFront(true);
        postFigureSelected(e);
        _dragger.startDraggingComponent(this, 0);
        setMouseCursor(MouseCursor(MouseCursor::DraggingHandCursor));
    }
    
    void Figure::mouseUp(const MouseEvent& e)
    {
        setMouseCursor(MouseCursor(MouseCursor::NormalCursor));
    }

    void Figure::mouseDrag(const MouseEvent& e)
    {
        _dragger.dragComponent(this, e);
        postFigureMoved();
    }
    
    void Figure::mouseEnter(const MouseEvent& e)
    {
        _hover = true;
    }
    
    void Figure::mouseExit(const MouseEvent& e)
    {
        _hover = false;
    }
    
    void Figure::resized()
    {
        // Somehow resized() is called before _resizer is constructed!
        if (_resizer)
        {
            toFront(true);
            postFigureMoved();
            _resizer->setBounds (0, 0, getWidth(), getHeight());
        }
    }
    
    const int Figure::getInitialWidth()
    {
        return _initWidth;
    }
    
    const int Figure::getInitialHeight()
    {
        return _initHeight;
    }
    
    const float Figure::getInitialMargin()
    {
        return _initMargin;
    }
    
    const float Figure::getStrokeWidth()
    {
        return _strokeWidth;
    }

    void Figure::setSelected(bool selected)
    {
        _resizer->setVisible(selected);
        _selected = selected;
        repaint();
    }
    
    const bool Figure::isSelected()
    {
        return _selected;
    }
    
    const Point* Figure::getAnchorPointRelativeTo(const Figure* other) const
    {
        const bool isBelow = (other->getY() + other->getHeight()) < getY();
        const bool isAbove = (getY() + getHeight()) < other->getY();
        const bool isRightOf = (other->getX() + other->getWidth()) < getX();
        const bool isLeftOf = (getX() + getWidth()) < other->getX();
        
        Point* point = NULL;
        
        if (isBelow)
        {
            if (point)
            {
                delete point;
            }
            point = new Point((float)(getX() + getWidth() / 2), (float)getY());
        }
        
        if (isAbove)
        {
            if (point)
            {
                delete point;
            }
            point = new Point((float)(getX() + getWidth() / 2), (float)(getY() + getHeight()));
        }
        
        if (isRightOf)
        {
            if (point)
            {
                delete point;
            }
            point = new Point((float)getX(), (float)(getY() + getHeight() / 2));
        }

        if (isLeftOf)
        {
            if (point)
            {
                delete point;
            }
            point = new Point((float)(getX() + getWidth()), (float)(getY() + getHeight() / 2));
        }
        return point;
    }
    
    void Figure::paint(Graphics& g)
    {
        Path figure;
        drawFigure(figure);
        if (_selected)
        {
            // This will create a dashed rectangle around the selected element
            drawDashedLineAround(g);
        }
        else
        {
            if (_hover)
            {
                setMouseCursor(MouseCursor(MouseCursor::PointingHandCursor));
                g.setColour(Colours::lightgrey);
                drawDashedLineAround(g);
            }
        }
        g.setColour(Colours::black);
        g.strokePath (figure, PathStrokeType (4.0f));
    }

    void Figure::drawDashedLineAround(Graphics& g)
    {
        const float dashLengths[] = { 5.0F, 5.0F };
        g.drawDashedLine(0.0f, 0.0f, 0.0f, (float)getHeight(), dashLengths, 2, 2.0f);
        g.drawDashedLine(0.0f, 0.0f, (float)getWidth(), 0.0f, dashLengths, 2, 2.0f);
        g.drawDashedLine((float)getWidth(), 0.0f, (float)getWidth(), (float)getHeight(), dashLengths, 2, 2.0f);
        g.drawDashedLine(0.0f, (float)getHeight(), (float)getWidth(), (float)getHeight(), dashLengths, 2, 2.0f);
    }
    
    void Figure::handleArrowCanvasClicked(const AutoPtr<ArrowCanvasClicked>& notification)
    {
        DiagramComponent* component = findParentComponentOfClass<DiagramComponent>();
        ArrowCanvas* canvas = notification->getClickedArrowCanvas();
        if (component->isParentOf(canvas))
        {
            setSelected(false);
        }
    }
    
    void Figure::postFigureSelected(const MouseEvent& e)
    {
        FigureSelected* notification = new FigureSelected(this, e.mods);
        NotificationCenter::defaultCenter().postNotification(notification);
    }
    
    void Figure::postFigureMoved()
    {
        FigureMoved* notification = new FigureMoved(this);
        NotificationCenter::defaultCenter().postNotification(notification);
    }
}
