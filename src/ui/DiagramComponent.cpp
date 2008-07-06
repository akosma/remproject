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

// Somehow in Mac OS X, using the native UI controls 
// in "Debug" mode hangs the application... This does not
// happen in "Release", so here we make the compiler 
// choose the right setting for each environment
#if defined(__APPLE__) && defined(__MACH__)
#ifndef USE_NATIVE_DIALOGS
#define NATIVE_DIALOG false
#else
#define NATIVE_DIALOG true
#endif
#endif

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
        
        _component = new ContentComponent();
        _viewport->setViewedComponent(_component);
        
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

    bool DiagramComponent::exportAsPNG()
    {
        FileChooser fileChooser("Choose a file name for the diagram", File::getSpecialLocation(File::userDesktopDirectory), "*.png", NATIVE_DIALOG);
        bool result = false;
        // Mac OS X native controls hang the app...!
        if (fileChooser.browseForFileToSave(true))
        {
            File file = fileChooser.getResult();
            if (file.exists())
            {
                file.deleteFile();
            }
            FileOutputStream* stream = file.createOutputStream();
            Image* image = _component->createComponentSnapshot(Rectangle (0, 0, _component->getWidth(), _component->getHeight()));
            PNGImageFormat png;
            result = png.writeImageToStream(*image, *stream);
            stream->flush();
            delete stream;
            delete image;
        }
        return result;
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
