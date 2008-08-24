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

#ifndef PROJECT_H_
#include "../metamodel/Project.h"
#endif

#ifndef ELEMENT_H_
#include "../metamodel/Element.h"
#endif

#ifndef DIAGRAM_H_
#include "../metamodel/Diagram.h"
#endif

#ifndef FILECONTROLLER_H_
#include "../controllers/FileController.h"
#endif

#include <string>
#include <Poco/NotificationCenter.h>

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
using notifications::ProjectFileOpened;
using notifications::NewProjectCreated;
using controllers::FileController;
using metamodel::Project;
using metamodel::Diagram;
using std::string;

namespace ui
{
    ProjectComponent::ProjectComponent()
    : Component()
    , _tabs(new ProjectTabbedComponent())
    , _newDiagramObserver(new NObserver<ProjectComponent, NewDiagramAdded>(*this, &ProjectComponent::handleNewDiagramAdded))
    , _projectOpenedObserver(new NObserver<ProjectComponent, ProjectFileOpened>(*this, &ProjectComponent::handleProjectFileOpened))
    , _newProjectCreatedObserver(new NObserver<ProjectComponent, NewProjectCreated>(*this, &ProjectComponent::handleNewProjectCreated))
    {
        addAndMakeVisible(_tabs);
        
        NotificationCenter::defaultCenter().addObserver(*_newDiagramObserver);
        NotificationCenter::defaultCenter().addObserver(*_projectOpenedObserver);
        NotificationCenter::defaultCenter().addObserver(*_newProjectCreatedObserver);
    }
    
    ProjectComponent::~ProjectComponent()
    {
        NotificationCenter::defaultCenter().removeObserver(*_newDiagramObserver);
        NotificationCenter::defaultCenter().removeObserver(*_projectOpenedObserver);
        NotificationCenter::defaultCenter().removeObserver(*_newProjectCreatedObserver);
        deleteAndZero(_newDiagramObserver);
        deleteAndZero(_projectOpenedObserver);
        deleteAndZero(_newProjectCreatedObserver);
        deleteAllChildren();
    }

    UseCaseDiagram* ProjectComponent::addUseCaseDiagram(const string& uniqueId)
    {
        int index = _tabs->getNumTabs();
        UseCaseDiagram* diagram = new UseCaseDiagram(uniqueId);
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
        const string& uniqueId = notification->getUniqueId();
        switch(notification->getDiagramType())
        {
            case NewDiagramAdded::UseCase:
                addUseCaseDiagram(uniqueId);
                break;
            
            default:
                break;
        }
    }
    
    void ProjectComponent::handleProjectFileOpened(const AutoPtr<ProjectFileOpened>& notification)
    {
        FileController& controller = FileController::get();
        Project* project = controller.getProject();
        _tabs->clearTabs();
        Diagram* diagram = NULL;
        project->beginIteration();
        while (diagram = project->getNextChild())
        {
            if (diagram->get<string>("class") == string("usecase"))
            {
                UseCaseDiagram* usecaseDiagram = addUseCaseDiagram(diagram->getName());
                usecaseDiagram->populateFrom(diagram);
            }
        }
        _tabs->setCurrentTabIndex(0);
    }

    void ProjectComponent::handleNewProjectCreated(const AutoPtr<NewProjectCreated>& notification)
    {
        _tabs->clearTabs();
    }
}
