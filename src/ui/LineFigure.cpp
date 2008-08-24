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

//! Contains the implementation of the ui::LineFigure class.
/*!
 * \file LineFigure.cpp
 *
 * Contains the implementation of the ui::LineFigure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/17/08
 */

#include "LineFigure.h"

using std::string;

namespace ui
{
    LineFigure::LineFigure(const string& uniqueId, Figure* a, Figure* b)
    : Figure(0, 0, uniqueId)
    , _start(a)
    , _end(b)
    {
    }

    LineFigure::~LineFigure()
    {
    }

    void LineFigure::drawFigure(Path& actor)
    {
    }

    void LineFigure::updateSpecificProperties()
    {
    }

    void LineFigure::setSpecificProperties()
    {
    }
    
    Figure* LineFigure::getStartFigure() const
    {
        return _start;
    }
    
    Figure* LineFigure::getEndFigure() const
    {
        return _end;
    }
    
    void LineFigure::drawLine(Graphics& g) const
    {
        const Figure* start = getStartFigure();
        const Figure* end = getEndFigure();
        if (start && end && start->isVisible() && end->isVisible())
        {
            const Point* s = start->getAnchorPointRelativeTo(end);
            const Point* e = end->getAnchorPointRelativeTo(start);
            if (s && e)
            {
                Path arrow;
                g.setColour(Colours::black);
                float width = 1.0f;
                if (isSelected())
                {
                    width = 3.0f;
                }
                arrow.addLineSegment(s->getX(), s->getY(), e->getX(), e->getY(), width);
                g.strokePath(arrow, PathStrokeType(width));
            }
            delete s;
            delete e;
        }
    }
}
