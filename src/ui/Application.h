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

//! Contains the interface of the ui::Application class.
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

#include "PlatformDefinitions.h"

// Forward declaration to avoid inclusion
namespace controllers
{
    class FileController;
}
using controllers::FileController;

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declaration to avoid inclusion
    class Window;

    //! Main class of the Rem application, launched when the application starts.
    /*!
     * \class Application
     *
     * Main class of the Rem application, launched when the application starts.
     * This class is instantiated and launched when the application starts by
     * the call to the START_JUCE_APPLICATION macro in Main.cpp.
     */
    class Application : public JUCEApplication
    {
    public:
    
        //! Constructor
        /*!
         * Constructor
         */
        Application();

        //! Virtual destructor
        /*!
         * Virtual destructor
         */
        virtual ~Application();
        
        //! Called when the application starts.
        /*!
         * Called when the application starts.
         * 
         * \param commandLine Command line parameters used to launch the application.
         */
        void initialise (const String&);

        //! Called before quitting.
        /*!
         * Called before quitting, whenever someone calls 
         * JUCEApplication::getInstance()->systemRequestedQuit();
         * It prompts the user to save the file with the latest modifications
         * before leaving the application.
         */
        virtual void systemRequestedQuit();

        //! Called when the application shuts down.
        /*!
         * Called when the application shuts down.
         */
        void shutdown();
        
        //! Returns the name of the application.
        /*!
         * Returns the name of the application.
         * 
         * \return A juce::String value.
         */
        const String getApplicationName();

        //! Returns the version of the application.
        /*!
         * Returns the version of the application.
         * 
         * \return A juce::String value.
         */
        const String getApplicationVersion();
        
        //! States whether one or several instances of the application can be launched at once.
        /*!
         * States whether one or several instances of the 
         * application can be launched at once.
         * 
         * \return A boolean value.
         */
        bool moreThanOneInstanceAllowed();

        //! Called when another instance of the application starts.
        /*!
         * Called when another instance of the application starts.
         * 
         * \param commandLine Command line parameters used to 
         * launch the other instance of the application.
         */
        void anotherInstanceStarted (const String&);

    private:
        //! A reference used to create a new project in the constructor.
        FileController& _fileController;
        
        //! A pointer to the main window of the application.
        Window* _window;
    };
}

#endif /* APPLICATION_H_ */
