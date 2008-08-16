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

//! Contains the implementation of the ui::Application class.
/*!
 * \file Application.cpp
 *
 * Contains the implementation of the ui::Application class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#ifndef FILECONTROLLER_H_
#include "../controllers/FileController.h"
#endif

#include "Application.h"

#ifndef WINDOW_H_
#include "Window.h"
#endif

#ifndef COMMANDDELEGATE_H_
#include "CommandDelegate.h"
#endif

using controllers::FileController;

namespace ui
{
    Application::Application()
    : JUCEApplication()
    , _window(0)
    , _fileController(FileController::get())
    {
        _fileController.newProject();
    }

    Application::~Application()
    {
        // Do not delete the Window instance!
        // This is done in the shutdown() method.
    }

    void Application::initialise (const String& commandLine)
    {
        _window = new Window();
    }
    
    void Application::systemRequestedQuit()
    {
        if (_fileController.isProjectDirty())
        {
            int answer = AlertWindow::showYesNoCancelBox(AlertWindow::QuestionIcon, String("Are you sure?"), String("The current project has unsaved modifications.\nSave the modifications prior to quit?"));
            switch (answer)
            {
                case 0:
                    // "Cancel" => do nothing.
                    break;
                    
                case 1:
                    // "Yes" => save and quit.
                    if (_fileController.isProjectNew())
                    {
                        _window->getCommandManager()->invokeDirectly(CommandDelegate::fileSaveAs, false);
                    }
                    else
                    {
                        _fileController.saveProject();
                    }
                    quit();
                    break;
                    
                case 2:
                    // "No" => quit without saving.
                    quit();
                    break;
            }
        }
        else
        {
            quit();
        }
    }

    void Application::shutdown()
    {
        delete _window;
    }

    const String Application::getApplicationName()
    {
        return String("Rem");
    }

    const String Application::getApplicationVersion()
    {
        return String("1.0");
    }

    bool Application::moreThanOneInstanceAllowed()
    {
        return false;
    }

    void Application::anotherInstanceStarted (const String& commandLine)
    {
    }
}
