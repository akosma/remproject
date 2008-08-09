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
 * \file UseCaseDiagram.cpp
 *
 * Contains the implementation of the ui::UseCaseDiagram class.
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

#include "UseCaseDiagram.h"

#ifndef ACTORFIGURE_H_
#include "ActorFigure.h"
#endif

#ifndef USECASEFIGURE_H_
#include "UseCaseFigure.h"
#endif

#ifndef USECASEDIAGRAMTOOLBAR_H_
#include "UseCaseDiagramToolbar.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;

namespace ui
{
    UseCaseDiagram::UseCaseDiagram()
    : UMLDiagram()
    {
        Figure* a = addActorFigure();
        Figure* b = addActorFigure();
        Figure* c = addUseCaseFigure();
        addArrowToCanvas(a, c);
        addArrowToCanvas(a, b);
    }

    UseCaseDiagram::~UseCaseDiagram()
    {
        deleteAllChildren();
    }
    
    DiagramToolbar* UseCaseDiagram::createToolbar()
    {
        return new UseCaseDiagramToolbar();
    }
    
    ActorFigure* UseCaseDiagram::addActorFigure()
    {
        ActorFigure* figure = new ActorFigure();
        figure->setTopLeftPosition(300, 300);
        addAndMakeVisible(figure, -1);
        return figure;
    }
    
    UseCaseFigure* UseCaseDiagram::addUseCaseFigure()
    {
        UseCaseFigure* figure = new UseCaseFigure();
        figure->setTopLeftPosition(100, 10);
        addAndMakeVisible(figure, -1);
        return figure;
    }
}
