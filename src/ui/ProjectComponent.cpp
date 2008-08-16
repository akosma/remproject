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

//! Contains the implementation of the ui::ProjectComponent class.
/*!
 * \file ProjectComponent.cpp
 *
 * Contains the implementation of the ui::ProjectComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/21/08
 */

#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

#include "ProjectComponent.h"

#ifndef DIAGRAMCOMPONENT_H_
#include "DiagramComponent.h"
#endif

#ifndef PROJECTTABBEDCOMPONENT_H_
#include "ProjectTabbedComponent.h"
#endif

#ifndef USECASEDIAGRAM_H_
#include "UseCaseDiagram.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;
using notifications::NewDiagramAdded;

namespace ui
{
    ProjectComponent::ProjectComponent()
    : Component()
    , _tabs(new ProjectTabbedComponent())
    {
        addAndMakeVisible(_tabs);
        
        NObserver<ProjectComponent, NewDiagramAdded> newUseCaseObserver(*this, &ProjectComponent::handleNewDiagramAdded);
        NotificationCenter::defaultCenter().addObserver(newUseCaseObserver);

//        PropertyPanel* panel = new PropertyPanel();
//        panel->setTopLeftPosition(100, 100);
//        addAndMakeVisible(panel, -1);
//        
//        TextPropertyComponent* text = new TextPropertyComponent(String("Test"), 2000, true);
//        Array<PropertyComponent*> array;
//        array << text;
//        panel.addProperties(array);
    }
    
    ProjectComponent::~ProjectComponent()
    {
        deleteAllChildren();
    }

    UseCaseDiagram* ProjectComponent::addUseCaseDiagram()
    {
        int index = _tabs->getNumTabs();
        UseCaseDiagram* diagram = new UseCaseDiagram();
        DiagramComponent* diagramComponent = new DiagramComponent(diagram, index);
        _tabs->addTab(String("Use Case Diagram"), Colours::white, diagramComponent, true);
        _tabs->setCurrentTabIndex(index);
        return diagram;
    }

    void ProjectComponent::resized()
    {
        if(_tabs)
        {
            _tabs->setSize(getWidth(), getHeight());
        }
    }
    
    void ProjectComponent::handleNewDiagramAdded(const AutoPtr<NewDiagramAdded>& notification)
    {
        switch(notification->getDiagramType())
        {
            case NewDiagramAdded::UseCase:
                addUseCaseDiagram();
                break;
            
            default:
                break;
        }
    }
}
