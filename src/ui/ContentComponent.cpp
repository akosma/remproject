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

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    ContentComponent::ContentComponent()
    : _current(0)
    {
        _canvas = new ArrowCanvas(this);
        _canvas->setSize(565, 800);
        addAndMakeVisible(_canvas, 0);
        
        ActorFigure* a = new ActorFigure(this);
        a->setTopLeftPosition(100, 300);
        addAndMakeVisible(a, -1);

        ActorFigure* b = new ActorFigure(this);
        b->setTopLeftPosition(100, 10);
        addAndMakeVisible(b, -1);
        
        UseCaseFigure* c = new UseCaseFigure(this);
        c->setTopLeftPosition(300, 300);
        addAndMakeVisible(c, -1);
        
        _canvas->addArrow(a, c);
        _canvas->addArrow(a, b);

        setSize(565, 800);
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
    
    void ContentComponent::setCurrent(Figure* current)
    {
        if (_current)
        {
            _current->setCurrent(false);
        }
        _current = current;
        if (_current)
        {
            _current->setCurrent(true);
            _canvas->setNoCurrentArrow();
        }
    }
    
    ArrowCanvas& ContentComponent::getArrowCanvas()
    {
        return *_canvas;
    }
}
