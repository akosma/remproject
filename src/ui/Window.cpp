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

#include <Poco/NotificationCenter.h>

#include "Window.h"
#include <iostream>

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
    : DocumentWindow ("Rem", Colours::lightgrey, DocumentWindow::allButtons, true)
    , _menuBarModel(new MenuBar(this))
    , _commandDelegate(new CommandDelegate())
    , _commandManager(new ApplicationCommandManager())
    , _tooltipWindow()
    {
        _commandManager->registerAllCommandsForTarget(_commandDelegate);
        _commandManager->setFirstCommandTarget(_commandDelegate);
        addKeyListener(_commandManager->getKeyMappings());
        _menuBarModel->setApplicationCommandManagerToWatch(_commandManager);

#if defined(__APPLE__) && defined(__MACH__)
        MenuBarModel::setMacMainMenu(_menuBarModel);
        setMenuBar(NULL);
#else
        setMenuBar(_menuBarModel);
#endif
        centreWithSize(620, 650);
        setResizable(true, true);
        setUsingNativeTitleBar(true);

        ProjectComponent* project = new ProjectComponent();
        setContentComponent(project);

        _commandManager->invokeDirectly(CommandDelegate::projectNewUseCaseDiagram, false);
        _commandManager->invokeDirectly(CommandDelegate::projectNewUseCaseDiagram, false);
        _commandManager->invokeDirectly(CommandDelegate::projectNewUseCaseDiagram, false);

        setVisible (true);
    }

    Window::~Window()
    {
        setMenuBar(NULL);
        setContentComponent(NULL, true);
        delete _menuBarModel;
        delete _commandDelegate;
        delete _commandManager;
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
