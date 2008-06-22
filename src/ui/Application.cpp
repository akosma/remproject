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

#include "Application.h"

#ifndef WINDOW_H_
#include "Window.h"
#endif

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    Application::Application()
    : window(0)
    {
    }

    Application::~Application()
    {
    }

    void Application::initialise (const String& commandLine)
    {
        window = new Window();
    }

    void Application::shutdown()
    {
        delete window;
    }

    const String Application::getApplicationName()
    {
        return String("Rem Application");
    }

    const String Application::getApplicationVersion()
    {
        return String("1.0");
    }

    bool Application::moreThanOneInstanceAllowed()
    {
        return true;
    }

    void Application::anotherInstanceStarted (const String& commandLine)
    {
    }
}
