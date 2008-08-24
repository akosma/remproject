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

//! Contains the interface of the ui::MenuBar class.
/*!
 * \file MenuBar.h
 *
 * Contains the interface of the ui::MenuBar class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      7/3/08
 */

#include "PlatformDefinitions.h"

#ifndef MENUBAR_H_
#define MENUBAR_H_

//! Contains the classes derived directly or indirectly from the JUCE framework.
/*!
 * \namespace ui
 * Contains the classes derived directly or indirectly from the JUCE framework.
 */
namespace ui
{
    // Forward declaration
    class Window;
    
    //! Provides the menu bar of the application.
    /*!
     * \class MenuBar
     *
     * Used by the application to provide a set of menu items on top of
     * the application window (or screen) with the various actions that
     * users can perform on Rem.
     */
    class MenuBar : public MenuBarModel
    {
    public:

        //! Constructor.
        /*!
         * Constructor.
         * 
         * \param owner The ui::Window object that contains this menu bar.
         * This class uses this element to retrieve the ApplicationCommandManager
         * of this application.
         */
        MenuBar(Window*);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~MenuBar();
        
        //! Returns the titles of the items in the menu bar.
        /*!
         * Returns the titles of the items in the menu bar.
         * 
         * \return A StringArray value.
         */
        virtual const StringArray getMenuBarNames();
        
        //! Called when a menu item has been clicked on.
        /*!
         * Called when a menu item has been clicked on.
         * 
         * \param menuItemID The ID of the selected item
         * \param topLevelMenuIndex The index of the top-level menu from which the item was chosen.
         */
        virtual void menuItemSelected(int, int);

        //!
        /*!
         * Returns the popup menu to display for a given top-level menu.
         * 
         * \param topLevelMenuIndex The index of the top-level menu to show.
         * \param menuName The name of the top-level menu item to show.
         */
        virtual const PopupMenu getMenuForIndex(int, const String&);

    private:
        //! The Window instance that owns this menu bar.
        Window* _owner;
    };
}

#endif /* MENUBAR_H_ */
