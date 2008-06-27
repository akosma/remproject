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

//! Contains the implementation of the ui::DiagramComponent class.
/*!
 * \file DiagramComponent.cpp
 *
 * Contains the implementation of the ui::DiagramComponent class.
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 *
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      21 Jun 2008 3:27:04 pm
 */

#include <Poco/NotificationCenter.h>
#include <Poco/NObserver.h>

#include "DiagramComponent.h"

#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

#ifndef USECASEDIAGRAMTOOLBAR_H_
#include "UseCaseDiagramToolbar.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;

namespace ui
{
    DiagramComponent::DiagramComponent (const int index)
    : _index(index)
    , _viewport (new Viewport())
    , _toolbar(new UseCaseDiagramToolbar(this))
    {
        addAndMakeVisible(_viewport);
//        addChildComponent(_toolbar, -1); // Don't make it visible yet!
        _toolbar->setTopLeftPosition(10, 50);
        
        ContentComponent* content = new ContentComponent();
        _viewport->setViewedComponent(content);
        
        NObserver<DiagramComponent, ProjectTabbedComponentChangedTabNotification> tabObserver(*this, &DiagramComponent::handleProjectTabbedComponentChangedTabNotification);
        NotificationCenter::defaultCenter().addObserver(tabObserver);
    }

    DiagramComponent::~DiagramComponent()
    {
        deleteAndZero (_toolbar);
        deleteAndZero (_viewport);
    }

    void DiagramComponent::paint (Graphics& g)
    {
        g.fillAll (Colours::grey);
    }

    void DiagramComponent::resized()
    {
        _viewport->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    }
    
    void DiagramComponent::handleProjectTabbedComponentChangedTabNotification(const AutoPtr<ProjectTabbedComponentChangedTabNotification>& notification)
    {
        const bool shouldBeVisible = (_index == notification->getNewCurrentTabIndex());
        _toolbar->setVisible(shouldBeVisible);
    }
}
