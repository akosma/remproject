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

//! Contains the implementation of the ui::ArrowFigure class.
/*!
 * \file ArrowFigure.cpp
 *
 * Contains the implementation of the ui::ArrowFigure class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/17/08
 */

#include "ArrowFigure.h"

using std::string;

namespace ui
{
    ArrowFigure::ArrowFigure(const string& uniqueId, Figure* a, Figure* b)
    : LineFigure(uniqueId, a, b)
    {
    }

    ArrowFigure::~ArrowFigure()
    {
    }

    void ArrowFigure::drawLine(Graphics& g) const
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
                arrow.addArrow(s->getX(), s->getY(), e->getX(), e->getY(), width, 20.0f, 20.0f);
                g.strokePath(arrow, PathStrokeType(width));
            }
            delete s;
            delete e;
        }
    }
}
