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

#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

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

namespace ui
{
    ProjectTabbedComponent::ProjectTabbedComponent()
    : TabbedComponent(TabbedButtonBar::TabsAtTop)
    {
        NObserver<ProjectTabbedComponent, ExportDiagramAsPNG> exportObserver(*this, &ProjectTabbedComponent::handleExportDiagramAsPNG);
        NotificationCenter::defaultCenter().addObserver(exportObserver);

        NObserver<ProjectTabbedComponent, DiagramToggleGrid> gridObserver(*this, &ProjectTabbedComponent::handleDiagramToggleGrid);
        NotificationCenter::defaultCenter().addObserver(gridObserver);

        NObserver<ProjectTabbedComponent, NewFigureAdded> figureObserver(*this, &ProjectTabbedComponent::handleNewFigureAdded);
        NotificationCenter::defaultCenter().addObserver(figureObserver);
    }
    
    ProjectTabbedComponent::~ProjectTabbedComponent()
    {
    }
    
    void ProjectTabbedComponent::currentTabChanged(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        postProjectTabbedComponentChangedTab(newCurrentTabIndex, newCurrentTabName);
    }
    
    void ProjectTabbedComponent::postProjectTabbedComponentChangedTab(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        ProjectTabbedComponentChangedTab* notification = new ProjectTabbedComponentChangedTab(newCurrentTabIndex, newCurrentTabName);
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
        currentDiagram->addFigure(notification->getFigureType());
    }
}
