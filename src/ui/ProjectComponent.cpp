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

#include "ProjectComponent.h"

#ifndef DIAGRAMCOMPONENT_H_
#include "DiagramComponent.h"
#endif

#include "Toolbar.h"

namespace ui
{
    ProjectComponent::ProjectComponent()
    : Component()
    , _tabs(new TabbedComponent(TabbedButtonBar::TabsAtBottom))
    {
        DiagramComponent* diagram1 = new DiagramComponent();
        DiagramComponent* diagram2 = new DiagramComponent();
        _tabs->addTab(String("diagram1"), Colours::white, diagram1, true);
        _tabs->addTab(String("diagram2"), Colours::white, diagram2, true);
        addAndMakeVisible(_tabs);

        Toolbar* t = new Toolbar();
        t->setTopLeftPosition(10, 10);
        addAndMakeVisible(t, -1);
        
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
    
    void ProjectComponent::resized()
    {
        if(_tabs)
        {
            _tabs->setSize(getWidth(), getHeight());
        }
    }
}
