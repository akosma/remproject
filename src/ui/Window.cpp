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

//! Contains the implementation of the ui::Window class.
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

#include <Poco/NotificationCenter.h>

#include "Window.h"

#ifndef PROJECT_H_
#include "ProjectComponent.h"
#endif

#ifndef MENUBAR_H_
#include "MenuBar.h"
#endif

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

#ifndef ACTIVEWINDOWSTATUSCHANGED_H_
#include "../notifications/ActiveWindowStatusChanged.h"
#endif

using Poco::NotificationCenter;
using notifications::ActiveWindowStatusChanged;

namespace ui
{
    Window::Window()
    : DocumentWindow ("Rem", Colours::lightgrey, DocumentWindow::allButtons, true)
    , _menuBarModel(new MenuBar(this))
    , _commandDelegate(CommandDelegate::get())
    , _commandManager(new ApplicationCommandManager())
    , _tooltipWindow()
    {
        _commandManager->registerAllCommandsForTarget(&_commandDelegate);
        _commandManager->setFirstCommandTarget(&_commandDelegate);
        addKeyListener(_commandManager->getKeyMappings());
        _menuBarModel->setApplicationCommandManagerToWatch(_commandManager);

#if defined(__APPLE__) && defined(__MACH__)
        // In the case of the Mac OS X system, the toolbar goes 
        // on top of the screen, and it is not attached to the window.
        MenuBarModel::setMacMainMenu(_menuBarModel);
        setMenuBar(NULL);
#else
        setMenuBar(_menuBarModel);
#endif

        // This is the main component of the whole application, where the user
        // adds diagrams and elements. When added using setContentComponent()
        // it is owned and deleted by the Window class.
        ProjectComponent* project = new ProjectComponent();
        setContentComponent(project);

        // Create a default diagram when the window opens
        _commandManager->invokeDirectly(CommandDelegate::fileNewProject, false);

        // When everything's ready, show the window.
        centreWithSize(620, 650);
        setResizable(true, true);
        setUsingNativeTitleBar(true);
        setVisible (true);
    }

    Window::~Window()
    {
        setMenuBar(NULL);
        setContentComponent(NULL, true);
        deleteAndZero(_menuBarModel);
        deleteAndZero(_commandManager);
    }
    
    ApplicationCommandManager* Window::getCommandManager()
    {
        return _commandManager;
    }
    
    void Window::activeWindowStatusChanged()
    {
        ActiveWindowStatusChanged* notification = new ActiveWindowStatusChanged(isActiveWindow());
        NotificationCenter::defaultCenter().postNotification(notification);
    }
    
    void Window::closeButtonPressed()
    {
        JUCEApplication::getInstance()->systemRequestedQuit();
    }
}
