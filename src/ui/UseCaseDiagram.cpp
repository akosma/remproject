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

//! Contains the implementation of the ui::UseCaseDiagram class.
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

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#include <iostream>
#include <Poco/NotificationCenter.h>

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
using Poco::AutoPtr;
using metamodel::Diagram;
using metamodel::Element;

namespace ui
{
    UseCaseDiagram::UseCaseDiagram()
    : UMLDiagram()
    {
        setInterceptsMouseClicks(true, true);
    }

    UseCaseDiagram::~UseCaseDiagram()
    {
        deleteAllChildren();
    }
    
    void UseCaseDiagram::populateFrom(Diagram* diagram)
    {
        Element* element = NULL;
        diagram->beginIteration();
        while (element = diagram->getNextChild())
        {
            string className = element->get<string>("class");
            string uniqueId = element->getName();
            element->dump();
            Figure* figure = NULL;
            if (className == "actor")
            {
                figure = addActorFigure(uniqueId);
                figure->setTopLeftPosition(element->get<int>("x"), element->get<int>("y"));
            }
            else if (className == "usecase")
            {
                figure = addUseCaseFigure(uniqueId);
                figure->setTopLeftPosition(element->get<int>("x"), element->get<int>("y"));
            }
        }
    }
    
    DiagramToolbar* UseCaseDiagram::createToolbar()
    {
        return new UseCaseDiagramToolbar();
    }
    
    ActorFigure* UseCaseDiagram::addActorFigure(const string& uniqueId)
    {
        ActorFigure* figure = new ActorFigure(uniqueId);
        figure->setTopLeftPosition(10, 10);
        addAndMakeVisible(figure, -1);
        return figure;
    }
    
    UseCaseFigure* UseCaseDiagram::addUseCaseFigure(const string& uniqueId)
    {
        UseCaseFigure* figure = new UseCaseFigure(uniqueId);
        figure->setTopLeftPosition(10, 10);
        addAndMakeVisible(figure, -1);
        return figure;
    }

    void UseCaseDiagram::addFigure(const AutoPtr<NewFigureAdded>& notification)
    {
        NewFigureAdded::FigureType type = notification->getFigureType();
        const string& uniqueId = notification->getUniqueId();
        switch(type)
        {
            case NewFigureAdded::Actor:
                addActorFigure(uniqueId);
                break;

            case NewFigureAdded::UseCase:
                addUseCaseFigure(uniqueId);
                break;
                
            case NewFigureAdded::Arrow:
            {
                if (getSelectedItemsCount() == 2)
                {
                    const Array<Figure*>& items = getSelectedItems();
                    ActorFigure* a = dynamic_cast<ActorFigure*>(items[0]);
                    ActorFigure* b = dynamic_cast<ActorFigure*>(items[1]);
                    if (a && b)
                    {
                        addArrowToCanvas(a, b, uniqueId);
                    }
                }
                break;
            }
            
            case NewFigureAdded::Line:
            {
                if (getSelectedItemsCount() == 2)
                {
                    const Array<Figure*>& items = getSelectedItems();
                    ActorFigure* a1 = dynamic_cast<ActorFigure*>(items[0]);
                    ActorFigure* a2 = dynamic_cast<ActorFigure*>(items[1]);
                    UseCaseFigure* b1 = dynamic_cast<UseCaseFigure*>(items[0]);
                    UseCaseFigure* b2 = dynamic_cast<UseCaseFigure*>(items[1]);
                    if (a1 && b2)
                    {
                        addLineToCanvas(a1, b2, uniqueId);
                    }
                    if (a2 && b1)
                    {
                        addLineToCanvas(a2, b1, uniqueId);
                    }
                }
                break;
            }
                
            default:
                break;
        }
    }
}
