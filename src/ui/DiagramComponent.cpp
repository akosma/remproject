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

#include <string>
#include <Poco/NotificationCenter.h>

#include "DiagramComponent.h"

#ifndef USECASEDIAGRAM_H_
#include "UseCaseDiagram.h"
#endif

#ifndef DIAGRAMTOOLBAR_H_
#include "DiagramToolbar.h"
#endif

using Poco::NotificationCenter;
using Poco::NObserver;
using Poco::AutoPtr;
using juce::Rectangle;
using std::string;

namespace ui
{
    DiagramComponent::DiagramComponent(UMLDiagram* diagram, const int index)
    : Component()
    , _index(index)
    , _viewport(new Viewport())
    , _diagram(diagram)
    , _toolbar(diagram->createToolbar())
    , _isActive(false)
    , _tabObserver(new NObserver<DiagramComponent, ProjectTabbedComponentChangedTab>(*this, &DiagramComponent::handleProjectTabbedComponentChangedTab))
    , _windowStatusObserver(new NObserver<DiagramComponent, ActiveWindowStatusChanged>(*this, &DiagramComponent::handleActiveWindowStatusChanged))
    {
        _toolbar->setParent(this);
        addAndMakeVisible(_viewport);
        _toolbar->setTopLeftPosition(10, 50);
        
        _viewport->setViewedComponent(_diagram);

        NotificationCenter::defaultCenter().addObserver(*_tabObserver);
        NotificationCenter::defaultCenter().addObserver(*_windowStatusObserver);
    }

    DiagramComponent::~DiagramComponent()
    {
        NotificationCenter::defaultCenter().removeObserver(*_tabObserver);
        NotificationCenter::defaultCenter().removeObserver(*_windowStatusObserver);

        deleteAndZero (_tabObserver);
        deleteAndZero (_windowStatusObserver);
        deleteAndZero (_toolbar);
        deleteAndZero (_viewport);
    }

    void DiagramComponent::paint (Graphics& g)
    {
        g.fillAll(Colours::grey);
    }
    
    void DiagramComponent::addFigure(const AutoPtr<NewFigureAdded>& notification)
    {
        _diagram->addFigure(notification);
    }
    
    void DiagramComponent::deleteSelectedFigures()
    {
        _diagram->deleteSelectedFigures();
    }
    
    void DiagramComponent::exportAsPNG()
    {
        FileChooser fileChooser("Choose a file name for the diagram", File::getSpecialLocation(File::userDesktopDirectory), "*.png", NATIVE_DIALOG);
        if (fileChooser.browseForFileToSave(true))
        {
            File file = fileChooser.getResult();
            if (file.exists())
            {
                file.deleteFile();
            }
            FileOutputStream* stream = file.createOutputStream();
            // Windows requires the "juce::" identifier, to avoid ambiguous symbols errors
            juce::Rectangle rect(0, 0, _diagram->getWidth(), _diagram->getHeight());
            Image* image = _diagram->createComponentSnapshot(rect);
            PNGImageFormat png;
            png.writeImageToStream(*image, *stream);
            stream->flush();
            delete stream;
            delete image;
        }
    }

    void DiagramComponent::resized()
    {
        _viewport->setBounds(0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    }
    
    const string& DiagramComponent::getUniqueId() const
    {
        return _diagram->getUniqueId();
    }
    
    void DiagramComponent::handleProjectTabbedComponentChangedTab(const AutoPtr<ProjectTabbedComponentChangedTab>& notification)
    {
        const bool shouldBeVisible = (_index == notification->getNewCurrentTabIndex());
        _toolbar->setVisible(shouldBeVisible);
        _isActive = shouldBeVisible;
    }
    
    void DiagramComponent::handleActiveWindowStatusChanged(const AutoPtr<ActiveWindowStatusChanged>& notification)
    {
        const bool shouldBeVisible = (notification->getStatus() && _isActive);
        _toolbar->setVisible(shouldBeVisible);
    }
    
    void DiagramComponent::toggleGrid()
    {
        _diagram->toggleGrid();
    }
}
