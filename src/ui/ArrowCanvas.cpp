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

#include "ArrowCanvas.h"

#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

#ifndef FIGURE_H_
#include "Figure.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * ArrowCanvas Constructor.
     */
    ArrowCanvas::ArrowCanvas(ContentComponent* parent)
    : _parent(parent)
    , _strokeWidth(1.0f)
    , _arrows()
    , _currentArrow(0)
    {
        setBroughtToFrontOnMouseClick(false);
        setBufferedToImage(true);
        setRepaintsOnMouseActivity(true);
    }
    
    /*!
     * ArrowCanvas Virtual destructor.
     */
    ArrowCanvas::~ArrowCanvas()
    {
        std::vector<ArrowCanvas::Arrow*>::iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            delete (*it);
        }
        _arrows.erase(_arrows.begin(), _arrows.end());
    }
    
    void ArrowCanvas::mouseDown(const MouseEvent& e)
    {
        _currentArrow = NULL;
        std::vector<ArrowCanvas::Arrow*>::iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            if ((*it)->intercepts(e))
            {
                _currentArrow = (*it);
                break;
            }
        }
        _parent->setCurrent(NULL);
    }
    
    void ArrowCanvas::setNoCurrentArrow()
    {
        _currentArrow = NULL;
        repaint();
    }

    void ArrowCanvas::paint(Graphics& g)
    {
        g.fillAll(Colours::white);
        std::vector<ArrowCanvas::Arrow*>::const_iterator it;
        for (it = _arrows.begin(); it != _arrows.end(); ++it)
        {
            Path arrow;
            g.setColour(Colours::black);
            float width = 1.0f;
            if (_currentArrow == (*it))
            {
                width = 2.0f;
                g.setColour(Colours::red);
            }
            const Figure* start = (*it)->getStartFigure();
            const Figure* end = (*it)->getEndFigure();
            const Point* s = start->getAnchorPointRelativeTo(end);
            const Point* e = end->getAnchorPointRelativeTo(start);
			if (s && e)
			{
	            arrow.addArrow(s->getX(), s->getY(), e->getX(), e->getY(), width, 20.0f, 20.0f);
			}
            g.strokePath(arrow, PathStrokeType (width));
            delete s;
            delete e;
        }
    }
    
    void ArrowCanvas::addArrow(Figure* start, Figure* end)
    {
        Arrow* arrow = new Arrow(start, end);
        _arrows.push_back(arrow);
    }
    
    ArrowCanvas::Arrow::Arrow(Figure* start, Figure* end)
    : _start(start)
    , _end(end)
    {
    }
    
    ArrowCanvas::Arrow::Arrow(const Arrow& rhs)
    : _start(rhs._start)
    , _end(rhs._end)
    {
    }

    ArrowCanvas::Arrow& ArrowCanvas::Arrow::operator=(const Arrow& rhs)
    {
        if (this != &rhs)
        {
            this->_start = rhs._start;
            this->_end = rhs._end;
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
    
    const bool ArrowCanvas::Arrow::intercepts(const MouseEvent& e)
    {
        const Point* start = _start->getAnchorPointRelativeTo(_end);
        const Point* end = _end->getAnchorPointRelativeTo(_start);
        Line line(*start, *end);
        bool result = (line.getDistanceFromLine((float)e.getMouseDownX(), (float)e.getMouseDownY()) < 10.0f);
        delete start;
        delete end;
        return result;
    }
}
