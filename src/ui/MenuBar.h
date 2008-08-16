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
    class Window;
    /*!
     * \class MenuBar
     *
     *  
     */
    class MenuBar : public MenuBarModel
    {
    public:

        /*!
         *  MenuBar constructor.
         */
        MenuBar(Window*);

        /*!
         *  MenuBar virtual destructor.
         */
        virtual ~MenuBar();
        
        virtual const StringArray getMenuBarNames();
        
        virtual void menuItemSelected(int, int);
        
        virtual const PopupMenu getMenuForIndex(int, const String&);

    private:
        ApplicationCommandManager* _manager;
        Window* _owner;

    };
}

#endif /* MENUBAR_H_ */
