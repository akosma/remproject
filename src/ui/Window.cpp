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
 * \file Window.cpp
 *
 * Contains the implementation of the ui::Window class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "Window.h"

#ifndef CONTENTCOMPONENT_H_
#include "ContentComponent.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    /*!
     * Window Constructor.
     */
    Window::Window()
    : DocumentWindow (T("Rem"),
                      Colours::lightgrey, 
                      DocumentWindow::allButtons, 
                      true)
    {
        TabbedComponent* project = new TabbedComponent(TabbedButtonBar::TabsAtBottom);
        ContentComponent* diagram1 = new ContentComponent();
        ContentComponent* diagram2 = new ContentComponent();
        project->addTab(String("diagram1"), Colours::white, diagram1, true);
        project->addTab(String("diagram2"), Colours::white, diagram2, true);
        setContentComponent(project);
        centreWithSize(800, 600);
        setResizable(true, true);
        setUsingNativeTitleBar(true);
        setVisible (true);
        
        // File file("test.png");
        // FileOutputStream* stream = file.createOutputStream();
        // Image* image = diagram1->createComponentSnapshot(Rectangle (0, 0, diagram1->getWidth(), diagram1->getHeight()));
        // PNGImageFormat png;
        // bool result = png.writeImageToStream(*image, *stream);
        // stream->flush();
        // delete stream;
        // delete image;
        
        
#if JUCE_MAC
//        MenuBarModel::setMacMainMenu(this->getContentComponent());
//        mainWindow->setMenuBar (0);
#endif
    }

    Window::~Window()
    {
    }

    void Window::closeButtonPressed()
    {
        JUCEApplication::quit();
    }
}
