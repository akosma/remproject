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
 * \file Application.h
 *
 * Contains the interface of the ui::Application class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#ifndef FILECONTROLLER_H_
#include "../controllers/FileController.h"
#endif

#include "PlatformDefinitions.h"

using controllers::FileController;

/*!
 * \namespace ui
 * Insert a description for the namespace here
 */
namespace ui
{
    class Window;

    /*!
     * \class Application
     *
     *  
     */
    class Application : public JUCEApplication
    {
    public:
        Application();

        ~Application();
        
        void initialise (const String&);

        void shutdown();

        const String getApplicationName();

        const String getApplicationVersion();

        bool moreThanOneInstanceAllowed();

        void anotherInstanceStarted (const String&);

    private:
        FileController& _fileController;
        Window* _window;
    };
}

#endif /* APPLICATION_H_ */
