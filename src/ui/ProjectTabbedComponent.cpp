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

//! Contains the implementation of the ui::ProjectTabbedComponent class.
/*!
 * \file ProjectTabbedComponent.cpp
 *
 * Contains the implementation of the ui::ProjectTabbedComponent class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      6/26/08
 */

#include <string>
#include <Poco/NotificationCenter.h>

#include "ProjectTabbedComponent.h"

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTAB_H_
#include "../notifications/ProjectTabbedComponentChangedTab.h"
#endif

#ifndef DIAGRAMCOMPONENT_H_
#include "DiagramComponent.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;
using notifications::ProjectTabbedComponentChangedTab;
using notifications::NewFigureAdded;
using std::string;

namespace ui
{
    ProjectTabbedComponent::ProjectTabbedComponent()
    : TabbedComponent(TabbedButtonBar::TabsAtTop)
    , _exportObserver(new NObserver<ProjectTabbedComponent, ExportDiagramAsPNG>(*this, &ProjectTabbedComponent::handleExportDiagramAsPNG))
    , _gridObserver(new NObserver<ProjectTabbedComponent, DiagramToggleGrid>(*this, &ProjectTabbedComponent::handleDiagramToggleGrid))
    , _figureObserver(new NObserver<ProjectTabbedComponent, NewFigureAdded>(*this, &ProjectTabbedComponent::handleNewFigureAdded))
    {
        NotificationCenter::defaultCenter().addObserver(*_exportObserver);
        NotificationCenter::defaultCenter().addObserver(*_gridObserver);
        NotificationCenter::defaultCenter().addObserver(*_figureObserver);
    }
    
    ProjectTabbedComponent::~ProjectTabbedComponent()
    {
        NotificationCenter::defaultCenter().removeObserver(*_exportObserver);
        NotificationCenter::defaultCenter().removeObserver(*_gridObserver);
        NotificationCenter::defaultCenter().removeObserver(*_figureObserver);
        deleteAndZero(_exportObserver);
        deleteAndZero(_gridObserver);
        deleteAndZero(_figureObserver);
    }
    
    void ProjectTabbedComponent::currentTabChanged(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        postProjectTabbedComponentChangedTab(newCurrentTabIndex, newCurrentTabName);
    }
    
    void ProjectTabbedComponent::postProjectTabbedComponentChangedTab(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        DiagramComponent* diagramComponent = (DiagramComponent*)this->getTabContentComponent(newCurrentTabIndex);
        const string& newCurrentDiagramName = diagramComponent->getUniqueId();
        ProjectTabbedComponentChangedTab* notification = new ProjectTabbedComponentChangedTab(newCurrentTabIndex, newCurrentTabName, newCurrentDiagramName);
        NotificationCenter::defaultCenter().postNotification(notification);
    }
    
    void ProjectTabbedComponent::handleExportDiagramAsPNG(const AutoPtr<ExportDiagramAsPNG>& notification)
    {
        DiagramComponent* currentDiagram = (DiagramComponent*)getTabContentComponent(getCurrentTabIndex());
        currentDiagram->exportAsPNG();
    }

    void ProjectTabbedComponent::handleDiagramToggleGrid(const AutoPtr<DiagramToggleGrid>& notification)
    {
        DiagramComponent* currentDiagram = (DiagramComponent*)getTabContentComponent(getCurrentTabIndex());
        currentDiagram->toggleGrid();
    }

    void ProjectTabbedComponent::handleNewFigureAdded(const AutoPtr<NewFigureAdded>& notification)
    {
        DiagramComponent* currentDiagram = (DiagramComponent*)getTabContentComponent(getCurrentTabIndex());
        currentDiagram->addFigure(notification);
    }
}
