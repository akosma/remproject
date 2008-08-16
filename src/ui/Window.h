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

//! Contains the interface of the ui::Window class.
/*!
 * \file Window.h
 *
 * Contains the interface of the ui::Window class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#include "PlatformDefinitions.h"

#ifndef WINDOW_H_
#define WINDOW_H_

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declarations to avoid inclusions
    class MenuBar;
    class CommandDelegate;

    //! Represents the application window, where the user adds diagrams and elements.
    /*!
     * \class Window
     *
     * Represents the application window, where the user adds diagrams and elements.
     * The only instance of this class is created by the Application::initialise method.
     */
    class Window  : public DocumentWindow
    {
    public:
        
        //! Constructor
        /*!
         * Constructor
         */
        Window();

        //! Virtual destructor
        /*!
         * Virtual destructor
         */
        virtual ~Window();

        //! Called when the 'close' button of the window is pressed.
        /*!
         * Called when the 'close' button of the window is pressed. This
         * implementation triggers the shutdown of the application.
         */
        void closeButtonPressed();
        
        //! Returns the command manager for the current window.
        /*!
         * Returns the command manager for the current window.
         * 
         * \return A pointer to a juce::ApplicationCommandManager instance.
         */
        ApplicationCommandManager* getCommandManager();
    
    protected:
        //! Called when the window becomes active or inactive.
        /*!
         * Called when the window becomes active or inactive. This implementation
         * posts a notifications::ActiveWindowStatusChanged notification.
         */
        virtual void activeWindowStatusChanged();

    private:
        //! Menu bar of the window. 
        //! In the case of Mac OS X, this points to the menu on top of the screen.
        MenuBar* _menuBarModel;
        
        //! Command delegate of the current window.
        CommandDelegate* _commandDelegate;
        
        //! Pointer to the command manager of the current window.
        ApplicationCommandManager* _commandManager;
        
        //! Single instance used to provide tooltips to individual components.
        //! Individual components wanting to show tooltips must inherit from
        //! juce::TooltipClient and implement the getTooltip() pure virtual method.
        TooltipWindow _tooltipWindow;
    };
}

#endif /* WINDOW_H_ */
