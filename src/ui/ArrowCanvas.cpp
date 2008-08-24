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

//! Contains the implementation of the ui::ArrowCanvas class.
/*!
 * \file ArrowCanvas.cpp
 *
 * Contains the implementation of the ui::ArrowCanvas class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/21/08
 */

#include <cmath>

#include "ArrowCanvas.h"

#ifndef UMLDIAGRAM_H_
#include "UMLDiagram.h"
#endif

#ifndef LINEFIGURE_H_
#include "LineFigure.h"
#endif

#ifndef ARROWCANVASCLICKED_H_
#include "../notifications/ArrowCanvasClicked.h"
#endif

#ifndef FIGURESELECTED_H_
#include "../notifications/FigureSelected.h"
#endif

#ifndef FIGURELASSOSOURCE_H_
#include "FigureLassoSource.h"
#endif

using std::vector;
using Poco::AutoPtr;
using notifications::ArrowCanvasClicked;
using notifications::FigureSelected;
using juce::Rectangle;

namespace ui
{
    ArrowCanvas::ArrowCanvas()
    : Component()
    , _strokeWidth(1.0f)
    , _lines()
    , _drawGrid(true)
    , _lassoComponent(new LassoComponent<Figure*>)
    , _lassoSource(NULL)
    {
        addAndMakeVisible(_lassoComponent, -1);
        setBroughtToFrontOnMouseClick(false);
        setBufferedToImage(true);
        setRepaintsOnMouseActivity(true);
        setOpaque(false);
    }
    
    ArrowCanvas::~ArrowCanvas()
    {
        vector<DrawableLine*>::iterator it;
        for (it = _lines.begin(); it != _lines.end(); ++it)
        {
            delete (*it);
        }
        _lines.erase(_lines.begin(), _lines.end());
    }
    
    void ArrowCanvas::setSelectedItemSet(SelectedItemSet<Figure*>& itemSet, UMLDiagram* diagram)
    {
        _lassoSource = new FigureLassoSource(itemSet, diagram, this);
    }

    void ArrowCanvas::mouseUp(const MouseEvent& e)
    {
        _lassoComponent->endLasso();
    }

    void ArrowCanvas::mouseDrag(const MouseEvent& e)
    {
        _lassoComponent->dragLasso(e);
        repaint();
    }

    void ArrowCanvas::mouseMove(const MouseEvent& e)
    {
        repaint();
    }

    void ArrowCanvas::mouseDown(const MouseEvent& e)
    {
        _lassoComponent->beginLasso(e, _lassoSource);

        bool noneSelected = true;
        vector<DrawableLine*>::iterator it;
        for (it = _lines.begin(); it != _lines.end(); ++it)
        {
            if ((*it)->intersects(e))
            {
                LineFigure* lineFigure = (*it)->getLineFigure();
                postFigureSelected(lineFigure, e);
                noneSelected = false;
                break;
            }
        }
        if (noneSelected)
        {
            postArrowCanvasClicked();
        }
    }
    
    void ArrowCanvas::toggleGrid()
    {
        _drawGrid = !_drawGrid;
        repaint();
    }
    
    void ArrowCanvas::setGridVisible(const bool visible)
    {
        _drawGrid = visible;
        repaint();
    }
    
    void ArrowCanvas::paint(Graphics& g)
    {
        g.fillAll(Colours::white.withAlpha(0.0f));
        drawGrid(g);
        vector<DrawableLine*>::iterator it;
        for (it = _lines.begin(); it != _lines.end(); ++it)
        {
            const LineFigure* lineFigure = (*it)->getLineFigure();
            if (lineFigure && lineFigure->isVisible())
            {
                lineFigure->drawLine(g);
            }
        }
    }
    
    void ArrowCanvas::deselectAllArrows()
    {
        vector<DrawableLine*>::const_iterator it;
        for (it = _lines.begin(); it != _lines.end(); ++it)
        {
            (*it)->getLineFigure()->setSelected(false);
        }
    }
    
    void ArrowCanvas::drawGrid(Graphics& g)
    {
        if (_drawGrid)
        {
            Colour gray = Colour(0xfff5f5f5);
            int width = getWidth();
            int height = getHeight();
            for (int i = 0; i < width; ++i)
            {
                g.setColour(gray);
                if (i % 10 == 0)
                {
                    if (i % 100 == 0)
                    {
                        g.setColour(Colour(0xffededed));
                    }
                    g.drawLine((float)i, 0.0, (float)i, (float)height);
                }
            }
            for (int j = 0; j < height; ++j)
            {
                g.setColour(gray);
                if (j % 10 == 0)
                {
                    if (j % 100 == 0)
                    {
                        g.setColour(Colour(0xffededed));
                    }
                    g.drawLine(0.0, (float)j, (float)width, (float)j);
                }
                
            }
        }
    }
    
    void ArrowCanvas::addLine(LineFigure* lineFigure)
    {
        DrawableLine* line = new DrawableLine(lineFigure);
        _lines.push_back(line);
    }

    const bool ArrowCanvas::lineIntersects(LineFigure* lineFigure, const juce::Rectangle& rect)
    {
        vector<DrawableLine*>::const_iterator it;
        for (it = _lines.begin(); it != _lines.end(); ++it)
        {
            if ((*it)->getLineFigure() == lineFigure)
            {
                if ((*it)->intersects(rect))
                {
                    lineFigure->setSelected(true);
                }
                else
                {
                    lineFigure->setSelected(false);
                }
            }
        }
        return false;
    }

    void ArrowCanvas::postArrowCanvasClicked()
    {
        ArrowCanvasClicked* notification = new ArrowCanvasClicked(this);
        NotificationCenter::defaultCenter().postNotification(notification);
    }
    
    void ArrowCanvas::postFigureSelected(Figure* arrowFigure, const MouseEvent& e)
    {
        FigureSelected* notification = new FigureSelected(arrowFigure, e.mods);
        NotificationCenter::defaultCenter().postNotification(notification);
    }

    ArrowCanvas::DrawableLine::DrawableLine(LineFigure* lineFigure)
    : _lineFigure(lineFigure)
    , _selected(false)
    {
    }
    
    ArrowCanvas::DrawableLine::DrawableLine(const DrawableLine& rhs)
    : _lineFigure(rhs._lineFigure)
    , _selected(rhs._selected)
    {
    }

    ArrowCanvas::DrawableLine& ArrowCanvas::DrawableLine::operator=(const DrawableLine& rhs)
    {
        if (this != &rhs)
        {
            this->_lineFigure = rhs._lineFigure;
            this->_selected = rhs._selected;
        }
        return *this;
    }
    
    ArrowCanvas::DrawableLine::~DrawableLine()
    {
    }

    LineFigure* ArrowCanvas::DrawableLine::getLineFigure() const
    {
        return _lineFigure;
    }
    
    const bool ArrowCanvas::DrawableLine::intersects(const MouseEvent& e)
    {
        const Figure* startFigure = _lineFigure->getStartFigure();
        const Figure* endFigure = _lineFigure->getEndFigure();
        const Point* start = startFigure->getAnchorPointRelativeTo(endFigure);
        const Point* end = endFigure->getAnchorPointRelativeTo(startFigure);
        if (start && end)
        {
            juce::Line line(*start, *end);
            bool result = (line.getDistanceFromLine((float)e.getMouseDownX(), (float)e.getMouseDownY()) < 10.0f);
            delete start;
            delete end;
            return result;
        }
        else
        {
            return false;
        }
    }

    const juce::Rectangle* ArrowCanvas::DrawableLine::getEnclosingRectangle() const
    {
        const Figure* startFigure = _lineFigure->getStartFigure();
        const Figure* endFigure = _lineFigure->getEndFigure();
        const Point* start = startFigure->getAnchorPointRelativeTo(endFigure);
        const Point* end = endFigure->getAnchorPointRelativeTo(startFigure);
        int startX = 0;
        int startY = 0;
        int width = 0;
        int height = 0;
        if (start && end)
        {
            juce::Line line(*start, *end);
            startX = (start->getX() > end->getX()) ? (int)end->getX() : (int)start->getX();
            startY = (start->getY() > end->getY()) ? (int)end->getY() : (int)start->getY();
            width = abs((int)start->getX() - (int)end->getX());
            height = abs((int)start->getY() - (int)end->getY());
            if (line.isHorizontal())
            {
                height = 10;
            }
            else if (line.isVertical())
            {
                width = 10;
            }
            else
            {
            }
            delete start;
            delete end;
        }
        juce::Rectangle* result = new juce::Rectangle(startX, startY, width, height);
        return result;
    }
    
    const bool ArrowCanvas::DrawableLine::intersects(const juce::Rectangle& rect) const
    {
        const juce::Rectangle* arrowRect = getEnclosingRectangle();
        bool result = false;
        if (arrowRect)
        {
            result = arrowRect->intersects(rect);
            delete arrowRect;
        }
        return result;
    }
}
