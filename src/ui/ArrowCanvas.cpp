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

#ifndef FIGURE_H_
#include "Figure.h"
#endif

#ifndef ARROWFIGURE_H_
#include "ArrowFigure.h"
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

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * ArrowCanvas Constructor.
     */
    ArrowCanvas::ArrowCanvas()
    : _strokeWidth(1.0f)
    , _arrows()
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
    
    /*!
     * ArrowCanvas Virtual destructor.
     */
    ArrowCanvas::~ArrowCanvas()
    {
        vector<ArrowCanvas::Arrow*>::iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            delete (*it);
        }
        _arrows.erase(_arrows.begin(), _arrows.end());
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
        vector<ArrowCanvas::Arrow*>::iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            if ((*it)->intersects(e))
            {
                ArrowFigure* arrowFigure = const_cast<ArrowFigure*>((*it)->getArrowFigure());
                postFigureSelected(arrowFigure, e);
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

    void ArrowCanvas::paint(Graphics& g)
    {
        g.fillAll(Colours::white.withAlpha(0.0f));
        drawGrid(g);
        vector<ArrowCanvas::Arrow*>::const_iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            Path arrow;
            g.setColour(Colours::black);
            float width = 1.0f;
            if ((*it)->isSelected())
            {
                width = 3.0f;
            }
            const Figure* start = (*it)->getStartFigure();
            const Figure* end = (*it)->getEndFigure();
            const Point* s = start->getAnchorPointRelativeTo(end);
            const Point* e = end->getAnchorPointRelativeTo(start);
            if (s && e)
            {
                arrow.addArrow(s->getX(), s->getY(), e->getX(), e->getY(), width, 20.0f, 20.0f);
            }
            g.strokePath(arrow, PathStrokeType(width));
            delete s;
            delete e;
        }
    }
    
    const int ArrowCanvas::getNumArrows() const
    {
        return _arrows.size();
    }
    
    void ArrowCanvas::deselectAllArrows()
    {
        vector<ArrowCanvas::Arrow*>::const_iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            (*it)->setSelected(false);
        }
    }
    
    void ArrowCanvas::drawGrid(Graphics& g)
    {
        if (_drawGrid)
        {
            int width = getWidth();
            int height = getHeight();
            for (int i = 0; i < width; ++i)
            {
                g.setColour(Colour(0xfff5f5f5));
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
                g.setColour(Colour(0xfff5f5f5));
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
    
    void ArrowCanvas::addArrow(Figure* start, Figure* end, ArrowFigure* arrowFigure)
    {
        Arrow* arrow = new Arrow(start, end, arrowFigure);
        _arrows.push_back(arrow);
    }

    void ArrowCanvas::showArrowSelected(ArrowFigure* arrowFigure)
    {
        vector<ArrowCanvas::Arrow*>::const_iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            if ((*it)->getArrowFigure() == arrowFigure)
            {
                const bool value = !(*it)->isSelected();
                (*it)->setSelected(value);
                break;
            }
        }
    }

    const bool ArrowCanvas::arrowIntersects(ArrowFigure* arrowFigure, const Rectangle& rect)
    {
        vector<ArrowCanvas::Arrow*>::const_iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            if ((*it)->getArrowFigure() == arrowFigure)
            {
                if ((*it)->intersects(rect))
                {
                    (*it)->setSelected(true);
                }
                else
                {
                    (*it)->setSelected(false);
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
    
    void ArrowCanvas::postFigureSelected(ArrowFigure* arrowFigure, const MouseEvent& e)
    {
        FigureSelected* notification = new FigureSelected(arrowFigure, e.mods);
        NotificationCenter::defaultCenter().postNotification(notification);
    }

    ArrowCanvas::Arrow::Arrow(Figure* start, Figure* end, ArrowFigure* arrowFigure)
    : _start(start)
    , _end(end)
    , _arrowFigure(arrowFigure)
    , _selected(false)
    {
    }
    
    ArrowCanvas::Arrow::Arrow(const Arrow& rhs)
    : _start(rhs._start)
    , _end(rhs._end)
    , _arrowFigure(rhs._arrowFigure)
    , _selected(rhs._selected)
    {
    }

    ArrowCanvas::Arrow& ArrowCanvas::Arrow::operator=(const Arrow& rhs)
    {
        if (this != &rhs)
        {
            this->_start = rhs._start;
            this->_end = rhs._end;
            this->_arrowFigure = rhs._arrowFigure;
            this->_selected = rhs._selected;
        }
        return *this;
    }
    
    ArrowCanvas::Arrow::~Arrow()
    {
    }
    
    const Figure* ArrowCanvas::Arrow::getStartFigure() const
    {
        return _start;
    }
    
    const Figure* ArrowCanvas::Arrow::getEndFigure() const
    {
        return _end;
    }
    
    const ArrowFigure* ArrowCanvas::Arrow::getArrowFigure() const
    {
        return _arrowFigure;
    }
    
    const bool ArrowCanvas::Arrow::isSelected() const
    {
        return _selected;
    }
    
    void ArrowCanvas::Arrow::setSelected(const bool selected)
    {
        _selected = selected;
    }
    
    const bool ArrowCanvas::Arrow::intersects(const MouseEvent& e)
    {
        const Point* start = _start->getAnchorPointRelativeTo(_end);
        const Point* end = _end->getAnchorPointRelativeTo(_start);
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

    const Rectangle* ArrowCanvas::Arrow::getEnclosingRectangle() const
    {
        const Point* start = _start->getAnchorPointRelativeTo(_end);
        const Point* end = _end->getAnchorPointRelativeTo(_start);
        float startX = 0.0;
        float startY = 0.0;
        float width = 0.0;
        float height = 0.0;
        if (start && end)
        {
            juce::Line line(*start, *end);
            startX = (start->getX() > end->getX()) ? end->getX() : start->getX();
            startY = (start->getY() > end->getY()) ? end->getY() : start->getY();
            width = (float)fabs(start->getX() - end->getX());
            height = (float)fabs(start->getY() - end->getY());
            if (line.isHorizontal())
            {
                height = 10.0f;
            }
            else if (line.isVertical())
            {
                width = 10.0f;
            }
            else
            {
            }
            delete start;
            delete end;
        }
        Rectangle* result = new Rectangle(startX, startY, width, height);
        return result;
    }
    
    const bool ArrowCanvas::Arrow::intersects(const Rectangle& rect) const
    {
        const Rectangle* arrowRect = getEnclosingRectangle();
        bool result = false;
        if (arrowRect)
        {
            result = arrowRect->intersects(rect);
            delete arrowRect;
        }
        return result;
    }
}
