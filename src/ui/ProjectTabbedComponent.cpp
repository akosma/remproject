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

#ifndef PROJECTTABBEDCOMPONENTCHANGEDTABNOTIFICATION_H_
#include "ProjectTabbedComponentChangedTabNotification.h"
#endif

#ifndef DIAGRAMCOMPONENT_H_
#include "DiagramComponent.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;

namespace ui
{
    ProjectTabbedComponent::ProjectTabbedComponent()
    : TabbedComponent(TabbedButtonBar::TabsAtTop)
    {
        NObserver<ProjectTabbedComponent, ExportDiagramAsPNGNotification> exportObserver(*this, &ProjectTabbedComponent::handleExportDiagramAsPNGNotification);
        NotificationCenter::defaultCenter().addObserver(exportObserver);
    }
    
    ProjectTabbedComponent::~ProjectTabbedComponent()
    {
    }
    
    void ProjectTabbedComponent::currentTabChanged(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        postProjectTabbedComponentChangedTabNotification(newCurrentTabIndex, newCurrentTabName);
    }
    
    void ProjectTabbedComponent::postProjectTabbedComponentChangedTabNotification(const int newCurrentTabIndex, const String& newCurrentTabName)
    {
        ProjectTabbedComponentChangedTabNotification* notification = new ProjectTabbedComponentChangedTabNotification(newCurrentTabIndex, newCurrentTabName);
        NotificationCenter::defaultCenter().postNotification(notification);
    }
    
    void ProjectTabbedComponent::handleExportDiagramAsPNGNotification(const AutoPtr<ExportDiagramAsPNGNotification>& notification)
    {
        DiagramComponent* currentDiagram = (DiagramComponent*)getTabContentComponent(getCurrentTabIndex());
        currentDiagram->exportAsPNG();
    }
}
